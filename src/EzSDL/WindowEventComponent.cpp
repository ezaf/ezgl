/*  EzSDL/WindowEventComponent.cpp
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

#include "EzSDL/WindowEventComponent.hpp"

#include "EzSDL/Dimension.hpp"
#include "EzSDL/Object.hpp"

#include <cmath>

namespace EzSDL
{



void WindowEventComponent::initImpl(Object &object, Window const &window)
{
}



void WindowEventComponent::updateImpl(Object &object, SDL_Event &e)
{
    switch (e.type)
    {
        case SDL_QUIT:
            object.dimension->at(DimensionKey::Z) = 0;
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    object.dimension->at(DimensionKey::Z) = 0;
                    break;
                case SDL_SCANCODE_GRAVE:
                    object.dimension->at(DimensionKey::Z) *= -1;
                    break;
            }
            break;
        case SDL_WINDOWEVENT:
            switch (e.window.event)
            {
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    object.dimension->at(DimensionKey::Z) =
                        std::abs(object.dimension->at(DimensionKey::Z));
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    object.dimension->at(DimensionKey::Z) =
                        -std::abs(object.dimension->at(DimensionKey::Z));
                    break;
            }
    }
}



}; /* namespace EzSDL */
