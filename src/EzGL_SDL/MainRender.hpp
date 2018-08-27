/*  EzGL_SDL/MainRender.hpp
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

#ifndef EZGL_SDL_MAINRENDER_HPP
#define EZGL_SDL_MAINRENDER_HPP

/** @file       EzGL_SDL/MainRender.hpp
 *  @brief      Creates the SDL2 window and renderer.
 *  @details    See \ref src/docs/main_object_interface.md for more
 *              information.
 */

#include "EzGL/Component.hpp"

#include <SDL2/SDL.h>



namespace EzGL
{

EZGL_COMPONENT_ENLIST(MainRender);

class MainRender final : public Component<MainRender>
{
public:
    MainRender() = default;
    ~MainRender();

    void init(Object &self, Object &main);
    void update(Object &self, Object &main);

    // Texture needs to access SDL_Renderer somehow...
    static SDL_Window *Window;
    static SDL_Renderer *Renderer;

private:
    void destroy();
};

}; /* namespace EzGL */



#endif /* EZGL_SDL_MAINRENDER_HPP */
