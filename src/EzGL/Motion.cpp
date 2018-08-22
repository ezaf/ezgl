/*  EzGL/Motion.cpp
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

#include "EzGL/Motion.hpp"

#include "EzGL/Object.hpp"

namespace EzGL
{



void Motion::init(Object &self, Object &main)
{
    if (self.data["x"].is_null()) self.data["x"] = 0;
    if (self.data["y"].is_null()) self.data["y"] = 0;
    if (self.data["z"].is_null()) self.data["z"] = 0;

    if (self.data["dx"].is_null()) self.data["dx"] = 0;
    if (self.data["dy"].is_null()) self.data["dy"] = 0;
    if (self.data["dz"].is_null()) self.data["dz"] = 0;

    if (self.data["d2x"].is_null()) self.data["d2x"] = 0;
    if (self.data["d2y"].is_null()) self.data["d2y"] = 0;
    if (self.data["d2z"].is_null()) self.data["d2z"] = 0;
}



void Motion::update(Object &self, Object &main)
{
    self.data["dx"] = self.data["dx"].get<double>() +
        (self.data["d2x"].get<double>() * main.data["dt"].get<double>());
    self.data["dy"] = self.data["dy"].get<double>() +
        (self.data["d2y"].get<double>() * main.data["dt"].get<double>());
    self.data["dz"] = self.data["dz"].get<double>() +
        (self.data["d2z"].get<double>() * main.data["dt"].get<double>());

    self.data["x"] = self.data["x"].get<double>() +
        (self.data["dx"].get<double>() * main.data["dt"].get<double>());
    self.data["y"] = self.data["y"].get<double>() +
        (self.data["dy"].get<double>() * main.data["dt"].get<double>());
    self.data["z"] = self.data["z"].get<double>() +
        (self.data["dz"].get<double>() * main.data["dt"].get<double>());
}



}; /* namespace EzGL */
