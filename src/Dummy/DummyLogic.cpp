/*  EzGL/DummyLogic.cpp
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

#include "EzGL/Core.hpp"
#include "EzGL/Object.hpp"

namespace EzGL
{



void DummyLogic::init(Object &object, Core &core)
{
}



void DummyLogic::update(Object &object, Core &core)
{
    double const xceil =
        static_cast<double>(core.data["render_width"]) -
        static_cast<double>(object.data["w"]);
    double const yceil =
        static_cast<double>(core.data["render_height"]) -
        static_cast<double>(object.data["h"]);

    if (object.data["x"] > xceil)
    {
        object.data["x"] = xceil;
        object.data["dx"] = 0;
    }
    else if (object.data["x"] < 0)
    {
        object.data["x"] = 0;
        object.data["dx"] = 0;
    }

    if (object.data["y"] > yceil)
    {
        object.data["y"] = yceil;
        object.data["dy"] = 0;
    }
    else if (object.data["y"] < 0)
    {
        object.data["y"] = 0;
        object.data["dy"] = 0;
    }

    if (object.data["collided"])
    {
        // Do stuff in response to collision signal
    }
}



}; /* namespace EzGL */
