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

#include "EzSDL/Dimension.hpp"
#include "EzSDL/Object.hpp"

#include <SDL2/SDL.h> // SDL_GetTicks

namespace EzSDL
{



void WindowLogicComponent::initImpl(Object &object, Window const &window)
{
    //TODO: parse a config file
    enableVSync = true;
    deltaCeil = 100.0; // No slower than 10 fps
    lastFrame = 0;
}



void WindowLogicComponent::updateImpl(Object &object, double const &ignore)
{
    /*  Ironically, it is this function's job to *set* the delta! Here we will
     *  rename the const delta parameter to "ignore". ;)
     *
     *  Window Z Dimension
     *  Z   : frames per time (s), i.e. target fps
     *  DZ  : time (ms) since last frame, i.e. delta
     *  D2Z : wait time (ms) per frame, i.e. vsync waiting time
     */
    double delta = static_cast<double>(SDL_GetTicks() - this->lastFrame);
    if (delta > this->deltaCeil) delta = this->deltaCeil;

    double waitTime = (1000.0 / object.dimension->at(DimensionKey::Z)) - delta;
    if (waitTime < 0.0 || !this->enableVSync) waitTime = 0.0;

    object.dimension->at(DimensionKey::DZ) = delta;
    object.dimension->at(DimensionKey::D2Z) = waitTime;

    this->lastFrame = SDL_GetTicks();
}



}; /* namespace EzSDL */
