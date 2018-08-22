/*  EzGL_SDL/MainRender.cpp
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

#include "EzGL_SDL/MainRender.hpp"

#include "EzGL/Object.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>
#include <string>

namespace EzGL
{



SDL_Window* EzGL::MainRender::Window = 0;
SDL_Renderer* EzGL::MainRender::Renderer = 0;



MainRender::~MainRender()
{
    this->destroy();
    SDL_Quit();

    std::cout << "Quit all SDL systems." << std::endl;
}



void MainRender::init(Object &self, Object &main)
{
    this->destroy();

    std::string title = self.data["title"].get<std::string>();
    MainRender::Window = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            self.data["display_width"].get<int>(),
            self.data["display_height"].get<int>(),
            SDL_WINDOW_ALLOW_HIGHDPI);

    SDL_SetWindowSize(MainRender::Window,
            self.data["display_width"].get<int>(),
            self.data["display_height"].get<int>());
    SDL_SetWindowFullscreen(MainRender::Window,
            self.data["fullscreen"].get<bool>() ?
                SDL_WINDOW_FULLSCREEN_DESKTOP : 0 );
    SDL_SetWindowBordered(MainRender::Window,
            static_cast<SDL_bool>(self.data["bordered"].get<bool>()));
    if (!self.data["icon"].is_null())
    {
        std::string icon = self.data["icon"];
        SDL_SetWindowIcon(MainRender::Window, IMG_Load(icon.c_str()));
    }

    MainRender::Renderer = SDL_CreateRenderer(MainRender::Window, -1,
            SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(MainRender::Renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderSetLogicalSize(MainRender::Renderer,
            self.data["render_width"].get<int>(),
            self.data["render_height"].get<int>());

    std::string scaling = self.data["scaling"].get<std::string>();
    if (scaling != "linear" && scaling != "nearest")
        scaling = "linear";

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scaling.c_str());
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, self.data["vsync"].get<bool>() ?
            "1" : "0");
    SDL_ShowCursor(self.data["show_cursor"].get<bool>() ?
            SDL_ENABLE : SDL_DISABLE);
}



void MainRender::update(Object &self, Object &main)
{
    SDL_RenderPresent(MainRender::Renderer);

    // For some reason need to disable this when doing Emscripten
#ifndef __EMSCRIPTEN__
    SDL_SetRenderDrawColor(MainRender::Renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(MainRender::Renderer);
#endif
}



void MainRender::destroy()
{
    if (MainRender::Renderer != nullptr)
    {
        SDL_DestroyRenderer(MainRender::Renderer);
        MainRender::Renderer = nullptr;
    }

    if (MainRender::Window != nullptr)
    {
        SDL_DestroyWindow(MainRender::Window);
        MainRender::Window = nullptr;
    }
}



}; /* namespace EzGL */
