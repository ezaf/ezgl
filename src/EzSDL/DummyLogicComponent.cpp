/*  EzSDL/DummyLogicComponent.cpp
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

#include "EzSDL/DummyLogicComponent.hpp"

#include "EzSDL/Dimension.hpp"
#include "EzSDL/Object.hpp"

namespace EzSDL
{

using DK = DimensionKey;



DummyLogicComponent::DummyLogicComponent() :
    dimCeil(DDimension::create()),
    dimFloor(DDimension::create())
{
}



void DummyLogicComponent::initImpl(Object &object, Window const &window)
{
    object.dimension->at(DK::W) = 64;
    object.dimension->at(DK::H) = 64;

    this->dimFloor->at(DK::X) = 0;
    this->dimFloor->at(DK::Y) = 0;
    this->dimCeil->at(DK::X) =
        window.getDimension()->at(DK::W) - object.dimension->at(DK::W);
    this->dimCeil->at(DK::Y) =
        window.getDimension()->at(DK::H) - object.dimension->at(DK::H);

    object.dimension->at(DK::X) = 0;
    object.dimension->at(DK::Y) = object.dimension->at(DK::H);
    object.dimension->at(DK::DX) = 1000.0;
    object.dimension->at(DK::DY) = 0;
}



void DummyLogicComponent::updateImpl(Object &object, double const &delta)
{
    if (object.dimension->at(DK::X) > this->dimCeil->at(DK::X))
    {
        object.dimension->at(DK::X) = this->dimCeil->at(DK::X);
        object.dimension->at(DK::DX) = 0;
    }
    else if (object.dimension->at(DK::X) < this->dimFloor->at(DK::X))
    {
        object.dimension->at(DK::X) = this->dimFloor->at(DK::X);
        object.dimension->at(DK::DX) = 0;
    }

    if (object.dimension->at(DK::Y) > this->dimCeil->at(DK::Y))
    {
        object.dimension->at(DK::Y) = this->dimCeil->at(DK::Y);
        object.dimension->at(DK::DY) = 0;
    }
    else if (object.dimension->at(DK::Y) < this->dimFloor->at(DK::Y))
    {
        object.dimension->at(DK::Y) = this->dimFloor->at(DK::Y);
        object.dimension->at(DK::DY) = 0;
    }


    double const dt = delta / 1000.0;
    object.dimension->at(DK::X) += (object.dimension->at(DK::DX) * dt);
    object.dimension->at(DK::Y) += (object.dimension->at(DK::DY) * dt);
}



}; /* namespace EzSDL */
