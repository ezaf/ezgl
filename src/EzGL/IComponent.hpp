/*  EzGL/IComponent.hpp
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

#ifndef EZGL_ICOMPONENT_HPP
#define EZGL_ICOMPONENT_HPP

/** @file       EzGL/IComponent.hpp
 *  @brief      Allows Component to utilize dynamic polymorphism.
 */



namespace EzGL
{

class Object;

/** @brief      Allows Component to utilize dynamic polymorphism.
 *  @details    Without this base class, components of unspecified types
 *              couldn't be stored inside containers like vectors. This class
 *              is not copyable.
 */
class IComponent
{
public:
    virtual ~IComponent() = default;

    /** @brief      Initialize all components.
     *  @param      self    Reference to object in question.
     *  @param      main    Reference to main object.
     */
    virtual void IInit(Object &self, Object &main) = 0;

    /** @brief      Update all components.
     *  @param      self    Reference to object in question.
     *  @param      main    Reference to main object.
     */
    virtual void IUpdate(Object &self, Object &main) = 0;

protected:
    IComponent() = default;

private:
    IComponent(IComponent const &) = delete;
    IComponent& operator=(IComponent const &) = delete;
};

}; /* namespace EzGL */



#endif /* EZGL_ICOMPONENT_HPP */
