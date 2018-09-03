/*  EzGL_SDL/Texture.hpp
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

#ifndef EZGL_SDL_TEXTURE_HPP
#define EZGL_SDL_TEXTURE_HPP

/** @file       EzGL_SDL/Texture.hpp
 *  @brief      Texture component with image file loading support.
 *  @details    Texture render position and dimensions match that of the
 *              object's `"x"`, `"y"`, `"w"`, and `"h"` dimensions. To load
 *              an image from file specify its relative path in `"texture"`.
 *              If instead you want to render a solid, colored rectangle,
 *              provide an integer RGBA array of size four in `"color"`.
 *
 *              Example with image file:
 *
 *              @code{.json}
 *              "DankMeme": {
 *                  "texture": "data/dankmeme.png"
 *              }
 *              @endcode
 *
 *              Example with color:
 *
 *              @code{.json}
 *              "CommunistRectangle": {
 *                  "color": [255, 0, 0, 255]
 *              }
 *              @endcode
 */

#include "EzGL/Component.hpp"

#include <map>
#include <SDL2/SDL.h>
#include <string>



namespace EzGL
{

EZGL_COMPONENT_ENLIST(Texture);

class Texture final : public Component<Texture>
{
public:
    Texture();
    ~Texture();

    void init(Object &self, Object &main);
    void update(Object &self, Object &main);

private:
    void destroy();

    static std::map<std::string, SDL_Texture*> Textures;

    SDL_Texture *texture;
    SDL_Color color;
    SDL_Rect src, dst;
};

}; /* namespace EzGL */



#endif /* EZGL_SDL_TEXTURE_HPP */
