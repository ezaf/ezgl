/*  EzGL/Collision.cpp
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

#include "EzGL/Collision.hpp"

#include "EzGL/Core.hpp"
#include "EzGL/Motion.hpp"
#include "EzGL/Object.hpp"

namespace EzGL
{



long long Collision::time = 0;
std::vector<Object*> Collision::Objects;



void Collision::init(Object &object, Core &core)
{
    if (object.data["x"].is_null()) object.data["x"] = 0;
    if (object.data["y"].is_null()) object.data["y"] = 0;
    if (object.data["z"].is_null()) object.data["z"] = 0;

    if (object.data["impact_resolve"].is_null())
        object.data["impact_resolve"] = 4;

    if (object.data["hitbox"].is_null()) object.data["hitbox"] = "rectangle";

    if (object.data["hitbox"] == "rectangle")
    {
        if (object.data["w"].is_null()) object.data["w"] = 0;
        if (object.data["h"].is_null()) object.data["h"] = 0;
        if (object.data["d"].is_null()) object.data["d"] = 0;
    }
    else if (object.data["hitbox"] == "circle")
    {
        if (object.data["r"].is_null()) object.data["r"] = 0;

        // WARNING: circles are actually treated as squares right now...
        object.data["w"] = object.data["r"];
        object.data["h"] = object.data["r"];
        object.data["d"] = object.data["r"];
    }

    object.data["collided"] = false;
    Collision::Objects.push_back(&object);
}



void Collision::update(Object &object, Core &core)
{
    if (Collision::time != core.data["time"])
    {
        for (Object *other : Collision::Objects)
            other->data["collided"] = false;
        Collision::time = core.data["time"];
    }

    // TODO: damn it this is O(n^2)
    for (Object *other : Collision::Objects)
    {
        if (&object != other && this->isCollision(object, *other))
        {
            object.data["collided"] = true;
            other->data["collided"] = true;
            object.other = other;
            other->other = &object;

            if (object.data["impact_resolve"] > 0)
            {
                double origObjDX = object.data["dx"].get<double>();
                double origObjDY = object.data["dy"].get<double>();
                double origObjDZ = object.data["dz"].get<double>();
                double origOthDX = other->data["dx"].get<double>();
                double origOthDY = other->data["dy"].get<double>();
                double origOthDZ = other->data["dz"].get<double>();

                Motion motion;
                for (int i=0; i<object.data["impact_resolve"] &&
                        this->isCollision(object, *other); i++)
                {
                    this->undoTimestep(object, *other, core);

                    object.data["dx"] = object.data["dx"].get<double>() / 2.0;
                    object.data["dy"] = object.data["dy"].get<double>() / 2.0;
                    object.data["dz"] = object.data["dz"].get<double>() / 2.0;

                    other->data["dx"] = other->data["dx"].get<double>() / 2.0;
                    other->data["dy"] = other->data["dy"].get<double>() / 2.0;
                    other->data["dz"] = other->data["dz"].get<double>() / 2.0;

                    motion.update(object, core);
                    motion.update(*other, core);
                }

                if (this->isCollision(object, *other))
                    this->undoTimestep(object, *other, core);

                object.data["dx"] = origObjDX;
                object.data["dy"] = origObjDY;
                object.data["dz"] = origObjDZ;
                other->data["dx"] = origOthDX;
                other->data["dy"] = origOthDY;
                other->data["dz"] = origOthDZ;
            }
        }
    }
}



bool Collision::isCollision(Object const &alpha, Object const &bravo)
{
    return
        (alpha.data["x"].get<double>() + alpha.data["w"].get<double>() >=
            bravo.data["x"].get<double>()) &&
        (bravo.data["x"].get<double>() + bravo.data["w"].get<double>() >=
            alpha.data["x"].get<double>()) &&
        (alpha.data["y"].get<double>() + alpha.data["h"].get<double>() >=
            bravo.data["y"].get<double>()) &&
        (bravo.data["y"].get<double>() + bravo.data["h"].get<double>() >=
            alpha.data["y"].get<double>()) &&
        (alpha.data["z"].get<double>() + alpha.data["d"].get<double>() >=
            bravo.data["z"].get<double>()) &&
        (bravo.data["z"].get<double>() + bravo.data["d"].get<double>() >=
            alpha.data["z"].get<double>());
}



void Collision::undoTimestep(Object &alpha, Object &bravo, Core &core)
{
    Motion motion;
    core.data["delta"] = -core.data["delta"].get<double>();
    motion.update(alpha, core);
    motion.update(bravo, core);
    core.data["delta"] = -core.data["delta"].get<double>();
}



}; /* namespace EzGL */
