/*  EzGL/Component.hpp
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

#ifndef EZGL_COMPONENT_HPP
#define EZGL_COMPONENT_HPP

/** @file       EzGL/Component.hpp
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "EzGL/ComponentFactory.hpp"
#include "EzGL/IComponent.hpp"



namespace EzGL
{

template <class T>
class Component : private IComponent
{
public:
    virtual ~Component() = default;

    static ComponentPtr Create()
    {
        return ComponentPtr(new T());
    }

    void IInit(Object &object, Core &core) override
    {
        static_cast<T*>(this)->init(object, core);
    }

    void IUpdate(Object &object, Core &core) override
    {
        static_cast<T*>(this)->update(object, core);
    }

protected:
    Component() = default;

private:
    Component(Component const &) = delete;
    Component& operator=(Component const &) = delete;
};

}; /* namespace EzGL */



#endif /* EZGL_COMPONENT_HPP */
