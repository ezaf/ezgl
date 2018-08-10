/*  EzSDL/WindowLogicComponent.cpp
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

#include "EzSDL/WindowLogicComponent.hpp"

#include "EzSDL/Object.hpp"
#include "nlohmann/json.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>
#include <SDL2/SDL.h>

namespace EzSDL
{



void WindowLogicComponent::init(Object &object, Game &game)
{
    this->lastFrame = SDL_GetTicks();

    SDL_DisplayMode display;
    if (SDL_GetDesktopDisplayMode(0, &display) != 0)
    {
        display.w = object.data["render_width"];
        display.h = object.data["render_height"];

        if (object.data["refresh_rate"] == nullptr)
            display.refresh_rate = 60;
        else
            display.refresh_rate = object.data["refresh_rate"];

        std::cout << "Failed to get desktop display mode: " <<
            SDL_GetError() << std::endl;
    }
    else
    {
#ifdef __EMSCRIPTEN__
        display.refresh_rate = 60;
#endif
        std::cout << "Display mode aquired: {"
            " w:" << display.w <<
            " h:" << display.h <<
            " refresh_rate:" << display.refresh_rate <<
            " }" << std::endl;
    }

    if (object.data["display_width"] == nullptr)
        object.data["display_width"] = display.w;

    if (object.data["render_width"] == nullptr)
        object.data["render_width"] = object.data["display_width"];

    if (object.data["display_height"] == nullptr)
        object.data["display_height"] = display.h;

    if (object.data["render_height"] == nullptr)
        object.data["render_height"] = object.data["display_height"];

    if (object.data["refresh_rate"] == nullptr)
        object.data["refresh_rate"] = display.refresh_rate;

    object.data["delta"] = 0.0;
    object.data["vsync_wait"] = 0;
}



void WindowLogicComponent::update(Object &object, Game &game)
{
    int delta = static_cast<int>(SDL_GetTicks() - this->lastFrame);
    if (delta > object.data["delta_max"]) delta = object.data["delta_max"];

    double waitTime =
        (1000.0 / static_cast<double>(object.data["refresh_rate"])) - delta;
    if (waitTime < 0.0 || !object.data["vsync"])
        waitTime = 0.0;

    object.data["delta"] = (delta / 1000.0);
    object.data["vsync_wait"] = waitTime;

    this->lastFrame = SDL_GetTicks();
}



}; /* namespace EzSDL */
