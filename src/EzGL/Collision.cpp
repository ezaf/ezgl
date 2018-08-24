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

#include "EzGL/Object.hpp"
#include "EzGL/Motion.hpp"

#include <algorithm>

namespace EzGL
{



long long Collision::time = 0;
std::vector<Object*> Collision::Objects;



void Collision::init(Object &self, Object &main)
{
    if (self.data["x"].is_null()) self.data["x"] = 0;
    if (self.data["y"].is_null()) self.data["y"] = 0;
    if (self.data["z"].is_null()) self.data["z"] = 0;

    if (self.data["impact_resolve"].is_null())
        self.data["impact_resolve"] = 4;

    if (self.data["hitbox"].is_null()) self.data["hitbox"] = "rectangle";

    if (self.data["hitbox"] == "rectangle")
    {
        if (self.data["w"].is_null()) self.data["w"] = 0;
        if (self.data["h"].is_null()) self.data["h"] = 0;
        if (self.data["d"].is_null()) self.data["d"] = 0;
    }
    else if (self.data["hitbox"] == "circle")
    {
        if (self.data["r"].is_null()) self.data["r"] = 0;

        // WARNING: circles are actually treated as squares right now...
        self.data["w"] = self.data["r"];
        self.data["h"] = self.data["r"];
        self.data["d"] = self.data["r"];
    }

    self.data["collision"]["status"] = false;
    self.data["collision"]["x_overlap"] = 0.0;
    self.data["collision"]["y_overlap"] = 0.0;
    self.data["collision"]["z_overlap"] = 0.0;
    Collision::Objects.push_back(&self);
}



void Collision::update(Object &self, Object &main)
{
    if (Collision::time != main.data["time"])
    {
        for (Object *other : Collision::Objects)
        {
            other->data["collision"]["status"] = false;
        }
        Collision::time = main.data["t"];
    }

    // TODO: damn it this is O(n^2)
    for (Object *other : Collision::Objects)
    {
        if (&self != other && this->isCollision(self, *other))
        {
            self.data["collision"]["status"] = true;
            other->data["collision"]["status"] = true;
            self.other = other;
            other->other = &self;

            self.data["collision"]["x_overlap"] =
                other->data["collision"]["x_overlap"] =
                    this->getOverlap(self, *other, "x", "w");
            self.data["collision"]["y_overlap"] =
                other->data["collision"]["y_overlap"] =
                    this->getOverlap(self, *other, "y", "h");
            self.data["collision"]["z_overlap"] =
                other->data["collision"]["z_overlap"] =
                    this->getOverlap(self, *other, "z", "d");

            if (self.data["impact_resolve"] > 0)
            {
                double origObjDX = self.data["dx"].get<double>();
                double origObjDY = self.data["dy"].get<double>();
                double origObjDZ = self.data["dz"].get<double>();
                double origOthDX = other->data["dx"].get<double>();
                double origOthDY = other->data["dy"].get<double>();
                double origOthDZ = other->data["dz"].get<double>();

                Motion motion;
                for (int i=0; i<self.data["impact_resolve"] &&
                        this->isCollision(self, *other); i++)
                {
                    this->undoTimestep(self, *other, main);

                    self.data["dx"] = self.data["dx"].get<double>() / 2.0;
                    self.data["dy"] = self.data["dy"].get<double>() / 2.0;
                    self.data["dz"] = self.data["dz"].get<double>() / 2.0;

                    other->data["dx"] = other->data["dx"].get<double>() / 2.0;
                    other->data["dy"] = other->data["dy"].get<double>() / 2.0;
                    other->data["dz"] = other->data["dz"].get<double>() / 2.0;

                    motion.update(self, main);
                    motion.update(*other, main);
                }

                if (this->isCollision(self, *other))
                    this->undoTimestep(self, *other, main);

                self.data["dx"] = origObjDX;
                self.data["dy"] = origObjDY;
                self.data["dz"] = origObjDZ;
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



void Collision::undoTimestep(Object &alpha, Object &bravo, Object &main)
{
    Motion motion;
    main.data["dt"] = -main.data["dt"].get<double>();
    motion.update(alpha, main);
    motion.update(bravo, main);
    main.data["dt"] = -main.data["dt"].get<double>();
}



double Collision::getOverlap(Object &alpha, Object &bravo,
        std::string const &pos, std::string const &dim)
{
    // Algorithm from https://stackoverflow.com/a/16691908/5890633
    return std::max(0.0, (
                std::min(
                    alpha.data[pos].get<double>() +
                        alpha.data[dim].get<double>(),
                    bravo.data[pos].get<double>() +
                        bravo.data[dim].get<double>())
                -
                std::max(
                    alpha.data[pos].get<double>(),
                    bravo.data[pos].get<double>())
                ));
}



}; /* namespace EzGL */
