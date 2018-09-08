/*  EzGL/Tilemap.cpp
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

#include "EzGL/Tilemap.hpp"

#include "EzGL/Object.hpp"

#include <iostream>

namespace EzGL
{



void Tilemap::init(Object &self, Object &main)
{
    //for (auto &tile : self.data["tilemap"]["tiles"])
    for (nlohmann::json::iterator it = self.data["tilemap"]["tiles"].begin();
            it != self.data["tilemap"]["tiles"].end(); it++)
    {
        it.value()["collision"]["no_self_check"] = true;

        this->tiles[static_cast<std::string>(it.key())[0]] =
            &Object::Create(it.value());
    }
}



void Tilemap::update(Object &self, Object &main)
{
    long mapX = self.data["x"].get<long>(),
         mapY = self.data["y"].get<long>();

    long const tileW = self.data["tilemap"]["tile_w"].get<long>(),
               tileH = self.data["tilemap"]["tile_h"].get<long>(),
               mapW = mapX + (tileW *
                       self.data["tilemap"]["map_w"].get<long>()),
               mapH = mapY + (tileH *
                       self.data["tilemap"]["map_h"].get<long>());

    for (char const &c : self.data["tilemap"]["map"].get<std::string>())
    {
        Object &tile = *this->tiles[c];
        tile.data["x"] = mapX;
        tile.data["y"] = mapY;

        tile.update(main);

        mapX += tileW;
        if (mapX >= mapW)
        {
            mapX = self.data["x"].get<long>();
            mapY += tileH;
        }
        if (mapY >= mapH)
        {
            break;
        }
    }

    // Hide tile flyweights off-screen
    for (auto &kv : this->tiles)
    {
        Object &tile = *kv.second;
        tile.data["x"] = -tile.data["w"].get<long>();
        tile.data["y"] = -tile.data["h"].get<long>();
    }
}



}; /* namespace EzGL */
