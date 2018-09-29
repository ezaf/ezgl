/*  EzGL/CenterCamera.cpp
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

#include "EzGL/CenterCamera.hpp"

#include "EzGL/Object.hpp"

#include <cmath>

namespace EzGL
{



void CenterCamera::init(Object &self, Object &main)
{
    this->update(self, main);
}



void CenterCamera::update(Object &self, Object &main)
{
    main.data["camera_x"] = static_cast<int>(floor(
                    self.data["x"].get<double>() +
                    (self.data["w"].get<double>()/2.0)));
    main.data["camera_y"] = static_cast<int>(floor(
                    self.data["y"].get<double>() +
                    (self.data["h"].get<double>()/2.0)));
}



}; /* namespace EzGL */
