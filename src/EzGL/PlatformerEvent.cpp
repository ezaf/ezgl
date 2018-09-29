/*  EzGL/PlatformerEvent.cpp
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

#include "EzGL/PlatformerEvent.hpp"

#include "EzGL/Object.hpp"

namespace EzGL
{



void PlatformerEvent::init(Object &self, Object &main)
{
}



void PlatformerEvent::update(Object &self, Object &main)
{
    bool left = self.data["input"]["left"],
        right = self.data["input"]["right"];

    if (left && !right)
    {
        self.data["dx"] = -self.data["speed"].get<double>();
    }
    else if (right && !left)
    {
        self.data["dx"] = self.data["speed"].get<double>();
    }
    else
    {
        self.data["dx"] = 0.0;
    }

    // If jump and is collided horizontally
    if (self.data["input"]["jump"].get<bool>() &&
            self.data["collision"]["status"] == true &&
            self.data["collision"]["x_overlap"].get<double>() >
            self.data["collision"]["y_overlap"].get<double>() &&
            self.data["dy"].get<double>() < 0.0)
        self.data["dy"] = -self.data["jump_speed"].get<double>();
}



}; /* namespace EzGL */
