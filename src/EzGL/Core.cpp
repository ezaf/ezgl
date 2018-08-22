/*  EzGL/Core.cpp
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

#include "EzGL/Core.hpp"

#ifdef __linux__
#include <dlfcn.h>
#define DLEXT ".so"
#elif _WIN32
#include "dlfcn-win32/dlfcn.h"
#define DLEXT ".dll"
#endif

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

using Clock = std::chrono::high_resolution_clock;

namespace EzGL
{



class Core::Impl
{
public:
    Impl(nlohmann::json config) :
        selfObject(EzGL::Object::Create(config["core"])),
        objects(),
        lastFrame(Clock::now()),
        updated(false),
        root(config)
    {
    }

    ~Impl() = default;

    static void runOneFrame(Core &core)
    {
        core.impl->selfObject->update(core);
    }

    ObjectPtr selfObject;
    std::vector<ObjectPtr> objects;

    std::chrono::time_point<Clock> lastFrame;
    bool updated;

    nlohmann::json root;
};



Core::~Core()
{
    delete impl;
}



void Core::init(std::string const &fileName)
{
    if (this->impl != nullptr) delete this->impl;

    std::ifstream file(fileName);

    if (!file.good())
    {
        std::cout << "Failed to initialize EzGL core with \'" << fileName <<
            "\'." << std::endl;
        return;
    }

    nlohmann::json config;
    file >> config;

    for (auto &object : config)
    {
        for (std::string plugin : object["plugins"])
        {
            plugin.append(DLEXT);
            dlopen(plugin.c_str(), RTLD_LAZY);
        }
    }

    this->data = config["core"];
    this->impl = new Impl(config);
    this->impl->selfObject->init(*this);

    for (nlohmann::json::iterator it = this->data["objects"].begin();
            it != this->data["objects"].end();
            it++)
    {
        for (int i=0; i<it.value(); i++)
        {
            this->addObject(it.key());
        }
    }
}



void Core::run()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(Core::Impl::runOneFrame, *this,
            this->data["refresh_rate"].get<int>(), 1);
#else
    while (!this->data["quit"].get<bool>())
    {
        std::chrono::time_point<Clock> now = Clock::now();

        double delta = std::chrono::duration<double>(
                Clock::now() - this->impl->lastFrame).count();

        if (delta > this->data["delta_max"].get<double>())
            delta = this->data["delta_max"].get<double>();

        this->data["delta"] = delta;
        this->data["time"] =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    Clock::now().time_since_epoch()).count();

        Core::Impl::runOneFrame(*this);

        this->impl->lastFrame = Clock::now();
        this->impl->updated = false;

        if (this->data["vsync"].get<bool>())
        {
            long wait = lround(
                    (1000.0 / this->data["refresh_rate"].get<double>())
                    - delta);

            if (wait > 0)
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        }
    }
#endif
}



void Core::addObject(std::string const &objectName)
{
    nlohmann::json objectData = this->getFromRoot(objectName);
    ObjectPtr object(Object::Create(objectData));
    object->init(*this);
    this->impl->objects.push_back(std::move(object));
}



void Core::updateObjects()
{
    if (!this->impl->updated)
    {
        if (!this->data["pause"].get<bool>())
        {
            for (auto &it : this->impl->objects)
            {
                it->update(*this);
            }
        }

        this->impl->updated = true;
    }
}



nlohmann::json Core::getFromRoot(std::string const &objectName)
{
    return this->impl->root[objectName];
}



}; /* namespace EzGL */
