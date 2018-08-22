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

#include "EzGL/Object.hpp"
#include "EzGL_SDL/CoreRender.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>
#include <string>

namespace EzGL
{



Texture::~Texture()
{
    this->destroy();
}



void Texture::init(Object &object, Core &core)
{
    if (CoreRender::Renderer == nullptr)
    {
        std::cout << "SDL Renderer hasn't been initialized yet!" << std::endl;
        return;
    }

    this->destroy();

    std::string file = object.data["texture"];
    SDL_Surface *load = IMG_Load(file.c_str());

    if (load == nullptr)
    {
        std::cout << "Failed to load image \'" << file << "\': " <<
            IMG_GetError() << std::endl;
        return;
    }

    load = SDL_ConvertSurfaceFormat(load, SDL_PIXELFORMAT_RGBA8888, 0);
    texture = SDL_CreateTextureFromSurface(CoreRender::Renderer, load);

    if (texture == nullptr)
    {
        std::cout << "Unable to create texture from " << file << "\': " <<
            SDL_GetError() << std::endl;
    }

    src = load->clip_rect;
    dst = {
        static_cast<int>(object.data["x"]), static_cast<int>(object.data["y"]),
        static_cast<int>(object.data["w"]), static_cast<int>(object.data["h"])
    };

    SDL_FreeSurface(load);
}



void Texture::update(Object &object, Core &core)
{
    dst = {
        static_cast<int>(object.data["x"]), static_cast<int>(object.data["y"]),
        static_cast<int>(object.data["w"]), static_cast<int>(object.data["h"])
    };

    // The two 0s are angle (double) and center (SDL_Point*) respectively
    SDL_RenderCopyEx(CoreRender::Renderer, texture, &src, &dst,
            0, 0, SDL_FLIP_NONE);
}



void Texture::destroy()
{
    if (this->texture != nullptr)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = 0;
    }

    src = {0, 0, 0, 0};
    dst = {0, 0, 0, 0};
}



}; /* namespace EzGL */
