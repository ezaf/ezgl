/*  EzGL/Object.cpp
 *
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 */

#include "EzGL/Object.hpp"

#include "EzGL/ComponentFactory.hpp"
#include "EzGL/IComponent.hpp"

#ifdef __linux__
#include <dlfcn.h>
#define DLEXT ".so"
#elif _WIN32
#include "dlfcn-win32/dlfcn.h"
#define DLEXT ".dll"
#endif
// TODO: Mac OS support

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using Clock = std::chrono::high_resolution_clock;

namespace EzGL
{



class Object::Impl
{
public:
    Impl(nlohmann::json const &config) :
        components(ComponentFactory::Create(config["components"]))
    {
    }

    ~Impl()
    {
        components.clear();
        components.shrink_to_fit();
    }

    std::vector<ComponentPtr> components;

    // Need a static function for emscripten's sake
    static void UpdateMain(Object &main) { main.update(main); }

    static nlohmann::json Root;
    static bool Updated;
    static ObjectPtr MainObject;
    static std::vector<ObjectPtr> Objects;
};

nlohmann::json Object::Impl::Root;
bool Object::Impl::Updated = false;
ObjectPtr Object::Impl::MainObject;
std::vector<ObjectPtr> Object::Impl::Objects;



int Object::Main(char const *fileName)
{
    return Object::Main(std::string(fileName));
}



int Object::Main(std::string const &fileName)
{
    // Load file
    std::ifstream file(fileName);
    if (!file.good())
    {
        std::cout << "Failed to load main json file \'" << fileName <<
            "\'." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Successfully loaded main json file \'" << fileName <<
        "\'." << std::endl;
    file >> Object::Impl::Root;
    file.close();

    // Load all plugins
    for (auto &objname : Object::Impl::Root)
    {
        for (std::string plugin : objname["plugins"])
        {
            plugin.append(DLEXT);
            dlopen(plugin.c_str(), RTLD_LAZY);
        }
    }

    // Initialize main
    Object::Impl::MainObject.reset(new Object(Object::Impl::Root["main"]));
    Object &main = *Object::Impl::MainObject;
    main.init(main);

    // Spawn all initial objects
    for (nlohmann::json::iterator it = main.data["objects"].begin();
            it != main.data["objects"].end(); it++)
    {
        for (int i=0; i<it.value(); i++)
        {
            Object::Create(it.key());
        }
    }

    // Main loop
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(Object::Impl::UpdateMain, main,
            main.data["refresh_rate"].get<int>(), 1);
#else
    std::chrono::time_point<Clock> prev = Clock::now();

    while (!main.data["quit"].get<bool>())
    {
        std::chrono::time_point<Clock> now = Clock::now();
        double dt = std::chrono::duration<double>(now - prev).count();

        if (dt > main.data["dt_max"].get<double>())
            dt = main.data["dt_max"].get<double>();

        main.data["dt"] = dt;
        main.data["t"] = std::chrono::duration_cast
            <std::chrono::milliseconds>(now.time_since_epoch()).count();

        if (!main.data["self_destruct"].is_null())
        {
            if (main.data["self_destruct"].get<double>() < 0.0)
                main.data["quit"] = true;
            else
                main.data["self_destruct"] =
                    main.data["self_destruct"].get<double>() -
                    main.data["dt"].get<double>();
        }

        Object::Impl::UpdateMain(main);

        prev = Clock::now();
        Object::Impl::Updated = false;

        if (main.data["vsync"].get<bool>())
        {
            long wait = lround(
                    (1000.0 / main.data["refresh_rate"].get<double>()) - dt);

            if (wait > 0)
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        }
    }
#endif

    Object::Impl::MainObject.reset();

    return EXIT_SUCCESS;
}



Object& Object::Create(std::string const &objectName)
{
    ObjectPtr object(new Object(Object::Impl::Root[objectName]));
    object->init(*Object::Impl::MainObject);
    Object::Impl::Objects.push_back(std::move(object));
    return *object; // TODO: Verify if still points to object after std::move
}



void Object::UpdateAll()
{
    // Won't update if called more than once per frame
    if (!Object::Impl::Updated)
    {
        for (auto &it : Object::Impl::Objects)
        {
            it->update(*Object::Impl::MainObject);
        }

        Object::Impl::Updated = true;
    }
}



Object::Object(nlohmann::json &config) :
    data(config),
    other(nullptr),
    impl(nullptr) // Must load inherits first in init
{
}



Object::~Object()
{
    delete impl;
}



void Object::init(Object &main)
{
    if (!this->data["inherit"].is_null())
    {
        // Have this->data override what it inherits from
        nlohmann::json temp = Object::Impl::Root[
            this->data["inherit"].get<std::string>()];
        temp.merge_patch(this->data);
        this->data = temp;
    }

    this->impl = new Impl(this->data);

    for (auto &it : this->impl->components)
    {
        it->IInit(*this, main);
    }
}



void Object::update(Object &main)
{
    for (auto &it : this->impl->components)
    {
        it->IUpdate(*this, main);
    }
}



}; /* namespace EzGL */
