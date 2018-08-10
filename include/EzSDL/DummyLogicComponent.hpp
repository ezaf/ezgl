/*  EzSDL/DummyLogicComponent.hpp
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

#ifndef EZSDL_DUMMYLOGICCOMPONENT_HPP
#define EZSDL_DUMMYLOGICCOMPONENT_HPP

/** @file       EzSDL/DummyLogicComponent.hpp
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "EzSDL/LogicComponent.hpp"



namespace EzSDL
{

EZSDL_COMPONENT_ENLIST(Dummy, LogicComponent);

/** @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do
 *              eiusmod tempor incididunt ut labore et dolore magna aliqua.
 */
class DummyLogicComponent : public LogicComponent<DummyLogicComponent>
{
public:
    DummyLogicComponent() = default;
    virtual ~DummyLogicComponent() = default;

    void init(Object &object, Game &game);
    void update(Object &object, Game &game);

protected:

private:
    DummyLogicComponent(DummyLogicComponent const &other);
    DummyLogicComponent& operator=(DummyLogicComponent const &other);
};

}; /* namespace EzSDL */



#endif /* EZSDL_DUMMYLOGICCOMPONENT_HPP */
