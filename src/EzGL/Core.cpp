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

#include "EzGL/Object.hpp"

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
    Impl(nlohmann::json &config) :
        selfObject(),
        objects(),
        lastFrame(Clock::now()),
        updated(false)
    {
        std::string api = config["api"];
        api.append(DLEXT);
        dlopen(api.c_str(), RTLD_LAZY);

        // Mandatory default names for window-related core API components.
        // TextureRender must also exist, but the Core class won't use it.
        config["components"] =
            { "CoreEvent", "CoreLogic", "CoreRender" };

        this->selfObject = EzGL::Object::create(config);
        this->selfObject->init(EzGL::Core::Instance());

        for (nlohmann::json::iterator it = config["objects"].begin();
                it != config["objects"].end();
                it++)
        {
            // Add that kind of object to the game n times
            for (int i=0; i<it.value(); i++)
            {
                //Core::Instance().addObject(config[it.key()]);
            }
        }
    };

    ~Impl() = default;

    static void runOneFrame(Core &core)
    {
        core.impl->selfObject->update(core);
    }

    ObjectPtr selfObject;
    std::vector<ObjectPtr> objects;

    std::chrono::time_point<Clock> lastFrame;
    bool updated;
};



Core::~Core()
{
    delete impl;
}



void Core::init(nlohmann::json &config)
{
    this->data = config;

    if (this->impl != nullptr) delete this->impl;
    this->impl = new Impl(data);
}



void Core::run()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(Core::Impl::runOneFrame, *this,
            this->data["refresh_rate"], 1);
#else
    while (!this->data["quit"])
    {
        std::chrono::time_point<Clock> now = Clock::now();

        double delta = std::chrono::duration<double>(
                this->impl->lastFrame - Clock::now()).count() * 1000.0;

        if (delta > this->data["delta_max"])
            delta = static_cast<double>(this->data["delta_max"]);

        this->data["delta"] = delta;

        Core::Impl::runOneFrame(*this);

        if (this->data["vsync"])
        {
            long wait = lround(
                    (1000.0 / static_cast<double>(this->data["refresh_rate"]))
                    - delta);

            if (wait > 0)
                std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        }

        this->impl->lastFrame = Clock::now();
        this->impl->updated = false;
    }
#endif
}



void Core::addObject(nlohmann::json &config)
{
    ObjectPtr object(Object::create(config));
    object->init(Core::Instance());
    Core::Instance().impl->objects.push_back(std::move(object));
}



void Core::updateObjects()
{
    if (!this->impl->updated)
    {
        if (!this->data["pause"])
        {
            for (auto &it : this->impl->objects)
            {
                it->update(*this);
            }
        }

        this->impl->updated = true;
    }
}



}; /* namespace EzGL */
