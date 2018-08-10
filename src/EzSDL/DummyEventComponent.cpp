/*  EzSDL/DummyEventComponent.cpp
 *
 *  Copythis->right (c) 2018 Kirk Lange <github.com/kirklange>
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

#include "EzSDL/DummyEventComponent.hpp"

#include "EzSDL/Object.hpp"

#include <SDL2/SDL_events.h>

namespace EzSDL
{



void DummyEventComponent::init(Object &object, Game &game)
{
    this->up = this->down = this->left = this->right = false;
}



void DummyEventComponent::update(Object &object, SDL_Event const &e)
{
    switch (e.type)
    {
    case SDL_KEYDOWN:
        switch (e.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_W:
            this->up = true;
            break;
        case SDL_SCANCODE_DOWN:
        case SDL_SCANCODE_S:
            this->down = true;
            break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A:
            this->left = true;
            break;
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:
            this->right = true;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (e.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_W:
            this->up = false;
            break;
        case SDL_SCANCODE_DOWN:
        case SDL_SCANCODE_S:
            this->down = false;
            break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A:
            this->left = false;
            break;
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:
            this->right = false;
            break;
        }
        break;
    }

    if (this->up)
        object.data["dy"] = -static_cast<double>(object.data["speed"]);
    else if (this->down)
        object.data["dy"] = static_cast<double>(object.data["speed"]);
    else
        object.data["dy"] = 0.0;

    if (this->left)
        object.data["dx"] = -static_cast<double>(object.data["speed"]);
    else if (this->right)
        object.data["dx"] = static_cast<double>(object.data["speed"]);
    else
        object.data["dx"] = 0.0;
}



}; /* namespace EzSDL */
