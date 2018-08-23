/*  EzGL/ComponentFactory.hpp
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

#ifndef EZGL_COMPONENTFACTORY_HPP
#define EZGL_COMPONENTFACTORY_HPP

/** @file       EzGL/ComponentFactory.hpp
 *  @brief      Component enlister and smart pointer factory.
 */

#include "EzGL/IComponent.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>



/** @brief      Enlist your custom component to the component factory.
 *  @details    When implementing a component, place this in your header file
 *              just before the class definition.
 *  @param      Obj     The name of the component class being enlisted.
 */
#define EZGL_COMPONENT_ENLIST(Obj) \
EzGL::ComponentFactory::Key const Obj##ComponentID = \
    EzGL::ComponentFactory::Enlist<Component<class Obj>>(#Obj)



namespace EzGL
{

/** @brief      Component smart pointer type. */
using ComponentPtr = std::unique_ptr<class IComponent>;

/** @brief      Component smart pointer container. */
using ComponentVec = std::vector<ComponentPtr>;

/** @brief      Component enlister and smart pointer factory.
 *  @details    Component developers need only to worry about the enlisting
 *              capabilities of this class. Component creation is Object's
 *              responsability.
 */
class ComponentFactory final
{
public:
    /** @brief      Component key type.
     *  @details    Component keys are essentially the name of the component
     *              we will use when refering to it during enlistment and
     *              creation.
     */
    using Key = std::string;

    /** @brief      Component smart pointer creator.
     *  @param      key     Key of the desired component.
     *  @returns    A smart pointer to the newly created component.
     */
    static ComponentPtr Create(Key const &key);

    /** @brief      Component container creator.
     *  @tparam     T       Container of keys with iterator support.
     *  @param      keys    Keys of the desired components.
     *  @returns    A container of smart pointers to the newly created
     *              components.
     */
    template <typename T>
    static ComponentVec Create(T const &keys)
    {
        ComponentVec components;
        for (Key const &key : keys)
            components.push_back(ComponentFactory::Create(key));
        return components;
    }

    /** @brief      Component enlister.
     *  @details    _**It is NOT RECOMMENDED for you to call this directly.**_
     *              Use the @ref EZGL_COMPONENT_ENLIST macro, it will do a lot
     *              of the work for you as well as make sure that your
     *              component gets enlisted before anyone attempts to create
     *              it.
     *  @tparam     T       Name of the component class being enlisted.
     *  @param      key     Key that should be associated with the component.
     *  @returns    Same value as the `key` parameter.
     */
    template <class T>
    static Key Enlist(Key const &key)
    {
        if (ComponentFactory::GetComponentMap().count(key) == 0)
            ComponentFactory::GetComponentMap()[key] = T::Create;
        return key;
    }

private:
    ComponentFactory() = default;
    ComponentFactory(ComponentFactory const &) = delete;
    ComponentFactory& operator=(ComponentFactory const &) = delete;

    using ComponentMap = std::map<Key, ComponentPtr (*)()>;
    static ComponentMap& GetComponentMap();
};

}; /* namespace EzGL */



#endif /* EZGL_COMPONENTFACTORY_HPP */
