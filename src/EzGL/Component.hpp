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
 *  @brief      The base class to inherit from for all components.
 */

#include "EzGL/ComponentFactory.hpp"
#include "EzGL/IComponent.hpp"



namespace EzGL
{

/** @brief      The base class to inherit from for all components.
 *  @details    To inherit from this class the curiously recurring template
 *              pattern (CRTP) must be used. The main reason this is done is
 *              so that the Create() function can be automatically generated.
 */
template <class T>
class Component : private IComponent
{
public:
    virtual ~Component() = default;

    /** @brief      Automatically generated per-class component factory.
     *  @details    Only ComponentFactory should be calling this.
     */
    static ComponentPtr Create()
    {
        return ComponentPtr(new T());
    }

    /** @brief      Initialize all components.
     *  @details    Inheritors to Component must define a function exactly like
     *              this one except with the name `init`.
     *  @param      self    Reference to object in question.
     *  @param      main    Reference to main object.
     */
    void IInit(Object &self, Object &main) override
    {
        static_cast<T*>(this)->init(self, main);
    }

    /** @brief      Initialize all components.
     *  @details    Inheritors to Component must define a function exactly like
     *              this one except with the name `update`.
     *  @param      self    Reference to object in question.
     *  @param      main    Reference to main object.
     */
    void IUpdate(Object &self, Object &main) override
    {
        static_cast<T*>(this)->update(self, main);
    }

protected:
    Component() = default;
};

}; /* namespace EzGL */



#endif /* EZGL_COMPONENT_HPP */
