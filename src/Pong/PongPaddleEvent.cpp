/*  Pong/PongPaddleEvent.cpp
 *
 *  Copythis->right (c) 2018 Kirk Lange <github.com/kirklange>
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

#include "Pong/PongPaddleEvent.hpp"

#include "EzGL/Object.hpp"

namespace EzGL
{



void PongPaddleEvent::init(Object &self, Object &main)
{
}



void PongPaddleEvent::update(Object &self, Object &main)
{
    bool up = self.data["input"]["up"];
    bool down = self.data["input"]["down"];

    if (up && !down)
        self.data["dy"] = -static_cast<double>(self.data["speed"]);
    else if (down && !up)
        self.data["dy"] = static_cast<double>(self.data["speed"]);
    else
        self.data["dy"] = 0.0;
}



}; /* namespace EzGL */
