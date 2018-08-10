/*  EzSDL/DummyRenderComponent.cpp
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

#include "EzSDL/DummyRenderComponent.hpp"

#include "EzSDL/Object.hpp"

#include <cmath>
#include <SDL2/SDL_render.h>

namespace EzSDL
{



void DummyRenderComponent::init(Object &object, Game &game)
{
}



void DummyRenderComponent::update(Object &object, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

    SDL_Rect rect = {
        static_cast<int>(std::round(static_cast<double>(object.data["x"]))),
        static_cast<int>(std::round(static_cast<double>(object.data["y"]))),
        static_cast<int>(object.data["w"]),
        static_cast<int>(object.data["h"]) };
    SDL_RenderFillRect(renderer, &rect);

    SDL_Rect rectB = { 0, 0, 10, 10 };
    SDL_RenderFillRect(renderer, &rectB);
}



}; /* namespace EzSDL */
