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
    this->window = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            object.data["display_width"], object.data["display_height"],
            SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_SetWindowFullscreen(this->window,
            object.data["fullscreen"] ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0 );
    SDL_SetWindowBordered(this->window,
            static_cast<SDL_bool>(static_cast<int>(object.data["bordered"])));
    //SDL_SetWindowIcon(this->window, IMG_Load(object.data["icon"]));

    this->renderer = SDL_CreateRenderer(this->window, -1,
            SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderSetLogicalSize(this->renderer,
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
    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect rect = { 128, 128, 32, 32 };
    SDL_RenderFillRect(this->renderer, &rect);

    SDL_RenderPresent(this->renderer);

    // For some reason need to disable this when doing Emscripten
#ifndef __EMSCRIPTEN__
    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(this->renderer);
#endif
}



void CoreRender::destroy()
{
    if (this->renderer != nullptr)
    {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = 0;
    }

    if (this->window != nullptr)
    {
        SDL_DestroyWindow(this->window);
        this->window = 0;
    }
}



}; /* namespace EzGL */
