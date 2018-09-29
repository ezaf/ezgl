/*  EzGL/PlatformerEvent.hpp
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

#ifndef EZGL_PLATFORMEREVENT_HPP
#define EZGL_PLATFORMEREVENT_HPP

/** @file       EzGL/PlatformerEvent.hpp
 *  @brief      PlatformerEvent component.
 *  @details    Updates object's position, velocity, and acceleration based on
 *              game window's delta-time.
 */

#include "EzGL/Component.hpp"



namespace EzGL
{

EZGL_COMPONENT_ENLIST(PlatformerEvent);

class PlatformerEvent final : public Component<PlatformerEvent>
{
public:
    PlatformerEvent() = default;
    ~PlatformerEvent() = default;

    void init(Object &self, Object &main);
    void update(Object &self, Object &main);
};

}; /* namespace EzGL */



#endif /* EZGL_PLATFORMEREVENT_HPP */
