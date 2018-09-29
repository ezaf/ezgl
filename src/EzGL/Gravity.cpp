/*  EzGL/Gravity.cpp
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

#include "EzGL/Gravity.hpp"

#include "EzGL/Object.hpp"

namespace EzGL
{



void Gravity::init(Object &self, Object &main)
{
    if (main.data["gravity_dx"].is_null()) main.data["gravity_dx"] = 0.0;
    if (main.data["gravity_dy"].is_null()) main.data["gravity_dy"] = 0.0;
    if (main.data["gravity_dz"].is_null()) main.data["gravity_dz"] = 0.0;

    if (self.data["dx"].is_null()) self.data["dx"] = 0;
    if (self.data["dy"].is_null()) self.data["dy"] = 0;
    if (self.data["dz"].is_null()) self.data["dz"] = 0;
}



void Gravity::update(Object &self, Object &main)
{
    self.data["dx"] = self.data["dx"].get<double>() +
        main.data["gravity_dx"].get<double>();
    self.data["dy"] = self.data["dy"].get<double>() +
        main.data["gravity_dy"].get<double>();
    self.data["dz"] = self.data["dz"].get<double>() +
        main.data["gravity_dz"].get<double>();
}



}; /* namespace EzGL */
