/*  Pong/PongBallLogic.cpp
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

#include "Pong/PongBallLogic.hpp"

#include "EzGL/Object.hpp"

#include <cmath>
#include <cstdlib>

#define PI 3.14159265

namespace EzGL
{



void PongBallLogic::init(Object &self, Object &main)
{
    this->scoreLeft = this->scoreRight = 0;
    this->goLeft = static_cast<bool>(rand() % 2);
    this->recenter(self, main);
}



void PongBallLogic::update(Object &self, Object &main)
{
    // Round start
    if (!std::isnan(this->startPause))
    {
        if (this->startPause > 0.0)
        {
            this->startPause -= main.data["dt"].get<double>();
        }
        else
        {
            this->startPause = NAN;
            main.data["pong"]["start_pause"] = false;

            // Produce non-zero angle between -45 and 45
            double angle;
            while ((angle=(rand()%90)-45) == 0.0);

            self.data["dx"] = cos((angle*PI/180.0)) *
                self.data["speed"].get<double>();

            self.data["dy"] = sin((angle*PI/180.0)) *
                self.data["speed"].get<double>();

            if (this->goLeft)
                self.data["dx"] = -self.data["dx"].get<double>();
        }
    }

    // Goal!
    if (self.data["x"] > main.data["render_width"].get<double>())
    {
        this->recenter(self, main);
        this->goLeft = false;
        this->scoreLeft++;
    }
    else if (self.data["x"] < -self.data["w"].get<double>())
    {
        this->recenter(self, main);
        this->goLeft = true;
        this->scoreRight++;
    }

    // Floor/Ceiling bounce
    double const yceil = main.data["render_height"].get<double>() -
        self.data["h"].get<double>();

    if (self.data["y"] > yceil)
    {
        self.data["y"] = yceil;
        self.data["dy"] = -self.data["dy"].get<double>();
    }
    else if (self.data["y"] < 0)
    {
        self.data["y"] = 0;
        self.data["dy"] = -self.data["dy"].get<double>();
    }

    // Paddle collision
    if (self.data["collision"]["status"] == true)
    {
        if (self.data["collision"]["y_overlap"] >
                self.data["collision"]["x_overlap"])
        {
            self.data["dx"] = -self.data["dx"].get<double>();
        }
        else
        {
            self.data["dy"] = -self.data["dy"].get<double>();
        }
    }
}



void PongBallLogic::recenter(Object &self, Object &main)
{
    this->startPause = 1.5;
    main.data["pong"]["start_pause"] = true;

    self.data["x"] = (main.data["render_width"].get<int>() / 2) -
        (self.data["w"].get<int>() / 2);
    self.data["y"] = (main.data["render_height"].get<int>() / 2) -
        (self.data["h"].get<int>() / 2);

    self.data["dx"] = 0.0;
    self.data["dy"] = 0.0;
}



}; /* namespace EzGL */
