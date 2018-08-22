/*  EzGL_SDL/Texture.cpp
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

#include "EzGL_SDL/Texture.hpp"

#include "EzGL_SDL/MainRender.hpp"
#include "EzGL/Object.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>
#include <string>

namespace EzGL
{



Texture::Texture() :
    texture(nullptr)
{
}



Texture::~Texture()
{
    this->destroy();
}



void Texture::init(Object &self, Object &main)
{
    if (MainRender::Renderer == nullptr)
    {
        std::cout << "SDL Renderer hasn't been initialized yet!" << std::endl;
        return;
    }

    this->destroy();

    if (!self.data["texture"].is_null())
    {
        std::string file = self.data["texture"];
        SDL_Surface *load = IMG_Load(file.c_str());

        if (load == nullptr)
        {
            std::cout << "Failed to load image \'" << file << "\': " <<
                IMG_GetError() << std::endl;
            return;
        }

        load = SDL_ConvertSurfaceFormat(load, SDL_PIXELFORMAT_RGBA8888, 0);
        texture = SDL_CreateTextureFromSurface(MainRender::Renderer, load);

        if (texture == nullptr)
        {
            std::cout << "Unable to create texture from " << file << "\': " <<
                SDL_GetError() << std::endl;
        }

        src = load->clip_rect;
        SDL_FreeSurface(load);
    }
    else
    {
        if (!self.data["color"].is_null())
        {
            this->color.r = self.data["color"].at(0);
            this->color.g = self.data["color"].at(1);
            this->color.b = self.data["color"].at(2);
            this->color.a = self.data["color"].at(3);
        }
        else
        {
            this->color = {255, 255, 255, 255};
        }
    }
}



void Texture::update(Object &self, Object &main)
{
    dst = {
        static_cast<int>(self.data["x"]), static_cast<int>(self.data["y"]),
        static_cast<int>(self.data["w"]), static_cast<int>(self.data["h"])
    };

    if (texture != nullptr)
    {
        // The two 0s are angle (double) and center (SDL_Point*) respectively
        SDL_RenderCopyEx(MainRender::Renderer, texture, &src, &dst,
                0, 0, SDL_FLIP_NONE);
    }
    else
    {
        SDL_SetRenderDrawColor(MainRender::Renderer,
                color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(MainRender::Renderer, &dst);
    }
}



void Texture::destroy()
{
    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    src = {0, 0, 0, 0};
    dst = {0, 0, 0, 0};
}



}; /* namespace EzGL */
