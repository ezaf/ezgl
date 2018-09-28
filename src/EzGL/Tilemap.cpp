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

namespace EzGL
{



void Tilemap::init(Object &self, Object &main)
{
    for (char const &c : self.data["tilemap"]["map"].get<std::string>())
    {
        this->tiles.push_back(&Object::Create(
                    self.data["tilemap"]["tiles"][std::string(1, c)]));

        this->tiles.back()->data["collision"]["no_self_check"] = true;
    }

    self.data["w"] = self.data["tilemap"]["map_w"].get<int>() *
        self.data["tilemap"]["tile_w"].get<int>();
    self.data["h"] = self.data["tilemap"]["map_h"].get<int>() *
        self.data["tilemap"]["tile_h"].get<int>();
}



void Tilemap::update(Object &self, Object &main)
{
    // TODO: Destroy this level then reload A NEW LEVEL
    if (self.data["input"]["destroy"].get<bool>())
    {
        for (Object *tile : tiles)
        {
            Object::Destroy(*tile);
        }

        this->tiles.clear();

        // Reloads same level instead of some next level
        this->init(self, main);
    }

    // TODO: Move camera around map instead of vice versa
    long mapX = self.data["x"].get<long>(),
         mapY = self.data["y"].get<long>();

    long const tileW = self.data["tilemap"]["tile_w"].get<long>(),
               tileH = self.data["tilemap"]["tile_h"].get<long>(),
               mapW = mapX + (tileW *
                       self.data["tilemap"]["map_w"].get<long>()),
               mapH = mapY + (tileH *
                       self.data["tilemap"]["map_h"].get<long>());

    // Draw/Move all tiles. Assumes correct ordering!
    for (Object *tile : this->tiles)
    {
        tile->data["x"] = mapX;
        tile->data["y"] = mapY;

        tile->update(main);

        mapX += tileW;
        if (mapX >= mapW)
        {
            mapX = self.data["x"].get<long>();
            mapY += tileH;
        }
        //if (mapY >= mapH) { break; }
    }
}



}; /* namespace EzGL */
