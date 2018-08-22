/*  Dummy/DummyLogic.cpp
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

#include "Dummy/DummyLogic.hpp"

#include "EzGL/Object.hpp"

namespace EzGL
{



void DummyLogic::init(Object &self, Object &main)
{
}



void DummyLogic::update(Object &self, Object &main)
{
    double const xceil =
        static_cast<double>(main.data["render_width"]) -
        static_cast<double>(self.data["w"]);
    double const yceil =
        static_cast<double>(main.data["render_height"]) -
        static_cast<double>(self.data["h"]);

    if (self.data["x"] > xceil)
    {
        self.data["x"] = xceil;
        self.data["dx"] = 0;
    }
    else if (self.data["x"] < 0)
    {
        self.data["x"] = 0;
        self.data["dx"] = 0;
    }

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

    if (self.data["collided"])
    {
        // Do stuff in response to collision signal
    }
}



}; /* namespace EzGL */
