/*  EzSDL/Component.hpp
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

#ifndef EZSDL_COMPONENT_HPP
#define EZSDL_COMPONENT_HPP

/** @file       EzSDL/Component.hpp
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include <map>
#include <memory>
#include <vector>



namespace EzSDL
{

class Object;
class Window;

/** @brief      Component smart pointer. */
using ComponentPtr = std::shared_ptr<class Component>;

/** @brief      Component template class and smart pointer factory.
 *  @details    Components can be any one of the parts of the MVC model.
 *              Components are made by creating a template specializations of
 *              this class. As such, this class is not inheritable nor
 *              copyable.
 */
class Component
{
public:
    /** @brief      Key/ID type used when enlisting and creating components. */
    using Key = unsigned long;

    virtual ~Component() = default;
    virtual void init(Object &object, Window const &window) = 0;
    virtual void update(Object &object, Window const &window) = 0;

    static ComponentPtr create(Key const &key);

    /* T is a container of keys with iterator support */
    template <typename T>
    static std::vector<ComponentPtr> create(T const &keys)
    {
        std::vector<ComponentPtr> components;
        for (Key const &key : keys)
        {
            components.push_back(Component::create(key));
        }
        return components;
    };

    /* TODO: Remark that T must have a static T::create() */
    template <Key K, class T>
    static Key enlist()
    {
        Component::getComponentMap()[K] = T::create;
        return K;
    };

protected:
    Component() = default;

private:
    Component(Component const &other) = delete;
    Component& operator=(Component const &other) = delete;

    using ComponentMap = std::map<Key, ComponentPtr (*)()>;
    static ComponentMap& getComponentMap();
};

}; /* namespace EzSDL */



#endif /* EZSDL_COMPONENT_HPP */
