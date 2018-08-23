/*  EzGL_SDL/MainLogic.cpp
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

#include "EzGL_SDL/MainLogic.hpp"

#include "EzGL/Object.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>
#include <SDL2/SDL.h>

namespace EzGL
{



void MainLogic::init(Object &self, Object &main)
{
    SDL_DisplayMode display;
    if (SDL_GetDesktopDisplayMode(0, &display) != 0)
    {
        display.w = self.data["render_width"].get<int>();
        display.h = self.data["render_height"].get<int>();

        if (self.data["refresh_rate"].is_null())
            display.refresh_rate = 60;
        else
            display.refresh_rate = self.data["refresh_rate"].get<int>();

        std::cout << "Failed to get desktop display mode: " <<
            SDL_GetError() << std::endl;
    }
    else
    {
#ifdef __EMSCRIPTEN__
        display.refresh_rate = 120;
#endif
        std::cout << "SDL display mode aquired: {"
            " w:" << display.w <<
            " h:" << display.h <<
            " refresh_rate:" << display.refresh_rate <<
            " }" << std::endl;
    }

    if (self.data["display_width"].is_null())
        self.data["display_width"] = display.w;

    if (self.data["render_width"].is_null())
        self.data["render_width"] = self.data["display_width"].get<int>();

    if (self.data["display_height"].is_null())
        self.data["display_height"] = display.h;

    if (self.data["render_height"].is_null())
        self.data["render_height"] = self.data["display_height"].get<int>();

    if (self.data["refresh_rate"].is_null())
        self.data["refresh_rate"] = display.refresh_rate;
}



void MainLogic::update(Object &self, Object &main)
{
    // IMPORTANT: GRAPHICS API WRAPPERS *MUST* CALL THIS!!!
    if (!self.data["pause"]) Object::UpdateAll();
}



}; /* namespace EzGL */
