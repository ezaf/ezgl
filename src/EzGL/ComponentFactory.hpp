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
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "EzGL/IComponent.hpp"
#include "EzGL/Singleton.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>



#define EZGL_COMPONENT_ENLIST(Obj) \
EzGL::ComponentFactory::Key const Obj##ComponentID = \
    EzGL::ComponentFactory::Instance().enlist<Component<class Obj>>(#Obj)



namespace EzGL
{

using ComponentPtr = std::unique_ptr<class IComponent>;
using ComponentVec = std::vector<ComponentPtr>;

/** @brief      Component smart pointer factory. */
class ComponentFactory final : public Singleton<ComponentFactory>
{
public:
    /** @brief      Key/ID type used when enlisting and creating components. */
    using Key = std::string;

    ComponentPtr create(Key const &key);

    /* T is a container of keys with iterator support */
    template <typename T>
    ComponentVec create(T const &keys)
    {
        ComponentVec components;
        for (Key const &key : keys)
            components.push_back(this->create(key));
        return components;
    }

    template <class T>
    Key enlist(Key const &key)
    {
        if (ComponentFactory::GetComponentMap().count(key) == 0)
            ComponentFactory::GetComponentMap()[key] = T::Create;
        return key;
    }

private:
    using ComponentMap = std::map<Key, ComponentPtr (*)()>;
    // Yes, this needs to be static too...
    static ComponentMap& GetComponentMap();
};

}; /* namespace EzGL */



#endif /* EZGL_COMPONENTFACTORY_HPP */
