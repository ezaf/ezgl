/*  Pong/PongPaddleLogic.cpp
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

#include "Pong/PongPaddleLogic.hpp"

#include "EzGL/Object.hpp"

namespace EzGL
{



void PongPaddleLogic::init(Object &self, Object &main)
{
    self.data["y"] = (main.data["render_height"].get<int>() / 2) -
        (self.data["h"].get<int>() / 2);

    if (self.data["side"] == "left")
    {
        self.data["x"] = self.data["w"];
    }
    else
    {
        self.data["x"] = main.data["render_width"].get<int>() -
            (self.data["w"].get<int>() * 2);
    }
}



void PongPaddleLogic::update(Object &self, Object &main)
{
    if (main.data["pong"]["start_pause"] == true)
    {
        self.data["y"] = (main.data["render_height"].get<int>() / 2) -
            (self.data["h"].get<int>() / 2);
        self.data["dy"] = 0;
    }

    double const yceil =
        static_cast<double>(main.data["render_height"]) -
        static_cast<double>(self.data["h"]);

    if (self.data["y"] > yceil)
    {
        self.data["y"] = yceil;
        self.data["dy"] = 0;
    }
    else if (self.data["y"] < 0)
    {
        self.data["y"] = 0;
        self.data["dy"] = 0;
    }

    if (self.data["collision"]["status"] == true)
    {
        // Do stuff in response to collision signal?
    }
}



}; /* namespace EzGL */
