/*  EzGL_SDL/CoreRender.cpp
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

#include "EzGL_SDL/CoreRender.hpp"

#include "EzGL/Object.hpp"

#include <iostream>
#include <string>

namespace EzGL
{



SDL_Window* EzGL::CoreRender::Window = 0;
SDL_Renderer* EzGL::CoreRender::Renderer = 0;



CoreRender::~CoreRender()
{
    this->destroy();
    SDL_Quit();

    std::cout << "Quit all SDL systems." << std::endl;
}



void CoreRender::init(Object &object, Core &core)
{
    this->destroy();

    std::string title = object.data["title"];
    CoreRender::Window = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            object.data["display_width"], object.data["display_height"],
            SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_SetWindowFullscreen(CoreRender::Window,
            object.data["fullscreen"] ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0 );
    SDL_SetWindowBordered(CoreRender::Window,
            static_cast<SDL_bool>(static_cast<int>(object.data["bordered"])));
    //SDL_SetWindowIcon(CoreRender::Window, IMG_Load(object.data["icon"]));

    CoreRender::Renderer = SDL_CreateRenderer(CoreRender::Window, -1,
            SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(CoreRender::Renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderSetLogicalSize(CoreRender::Renderer,
            object.data["render_width"], object.data["render_height"]);

    std::string scaling = object.data["scaling"];
    if (scaling != "linear" && scaling != "nearest")
        scaling = "linear";

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scaling.c_str());
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, object.data["vsync"] ? "1" : "0");
    SDL_ShowCursor(object.data["show_cursor"] ? SDL_ENABLE : SDL_DISABLE);
}



void CoreRender::update(Object &object, Core &core)
{
    SDL_RenderPresent(CoreRender::Renderer);

    // For some reason need to disable this when doing Emscripten
#ifndef __EMSCRIPTEN__
    SDL_SetRenderDrawColor(CoreRender::Renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(CoreRender::Renderer);
#endif
}



void CoreRender::destroy()
{
    if (CoreRender::Renderer != nullptr)
    {
        SDL_DestroyRenderer(CoreRender::Renderer);
        CoreRender::Renderer = 0;
    }

    if (CoreRender::Window != nullptr)
    {
        SDL_DestroyWindow(CoreRender::Window);
        CoreRender::Window = 0;
    }
}



}; /* namespace EzGL */
