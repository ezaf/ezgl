/*  EzGL/PlatformerLogic.cpp
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

#include "EzGL/PlatformerLogic.hpp"

#include "EzGL/Motion.hpp"
#include "EzGL/Object.hpp"

namespace EzGL
{



void PlatformerLogic::init(Object &self, Object &main)
{
}



void PlatformerLogic::update(Object &self, Object &main)
{
    if (self.data["collision"]["status"] == true)
    {
        if (self.data["collision"]["x_overlap"].get<double>() >
                self.data["collision"]["y_overlap"].get<double>())
        {
            self.data["dy"] = -self.data["dy"].get<double>() / 4.0;
            //self.data["dy"] = 0.0;
        }
        else
        {
            self.data["dx"] = -self.data["dx"].get<double>() / 4.0;
            //self.data["dx"] = 0.0;
        }

        Motion m;
        m.update(self, main);
    }
}



}; /* namespace EzGL */
