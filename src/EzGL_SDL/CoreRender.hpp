/*  EzGL_SDL/CoreRender.hpp
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

#ifndef EZGL_SDL_CORERENDER_HPP
#define EZGL_SDL_CORERENDER_HPP

/** @file       EzGL_SDL/CoreRender.hpp
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "EzGL/Component.hpp"

#include <SDL2/SDL.h>



namespace EzGL
{

EZGL_COMPONENT_ENLIST(CoreRender);

class CoreRender : public Component<CoreRender>
{
public:
    CoreRender() = default;
    virtual ~CoreRender();

    void init(Object &object, Core &core);
    void update(Object &object, Core &core);

protected:

private:
    CoreRender(CoreRender const &) = delete;
    CoreRender& operator=(CoreRender const &) = delete;

    void destroy();

    SDL_Window *window;
    SDL_Renderer *renderer;
};

}; /* namespace EzGL */



#endif /* EZGL_SDL_CORERENDER_HPP */
