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

#include "EzGL/Core.hpp"
#include "EzGL/Object.hpp"

namespace EzGL
{



void Motion::init(Object &object, Core &core)
{
    if (object.data["x"].is_null()) object.data["x"] = 0;
    if (object.data["y"].is_null()) object.data["y"] = 0;
    if (object.data["z"].is_null()) object.data["z"] = 0;

    if (object.data["dx"].is_null()) object.data["dx"] = 0;
    if (object.data["dy"].is_null()) object.data["dy"] = 0;
    if (object.data["dz"].is_null()) object.data["dz"] = 0;

    if (object.data["d2x"].is_null()) object.data["d2x"] = 0;
    if (object.data["d2y"].is_null()) object.data["d2y"] = 0;
    if (object.data["d2z"].is_null()) object.data["d2z"] = 0;
}



void Motion::update(Object &object, Core &core)
{
    object.data["dx"] = object.data["dx"].get<double>() +
        (object.data["d2x"].get<double>() * core.data["delta"].get<double>());
    object.data["dy"] = object.data["dy"].get<double>() +
        (object.data["d2y"].get<double>() * core.data["delta"].get<double>());
    object.data["dz"] = object.data["dz"].get<double>() +
        (object.data["d2z"].get<double>() * core.data["delta"].get<double>());

    object.data["x"] = object.data["x"].get<double>() +
        (object.data["dx"].get<double>() * core.data["delta"].get<double>());
    object.data["y"] = object.data["y"].get<double>() +
        (object.data["dy"].get<double>() * core.data["delta"].get<double>());
    object.data["z"] = object.data["z"].get<double>() +
        (object.data["dz"].get<double>() * core.data["delta"].get<double>());
}



}; /* namespace EzGL */
