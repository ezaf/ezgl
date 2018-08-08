/*  EzSDL/Component.cpp
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

#include "EzSDL/Component.hpp"

#include <iostream>

namespace EzSDL
{



ComponentPtr Component::create(Key const &key)
{
    typename ComponentMap::iterator it =
        Component::getComponentMap().find(key);

    if (it != Component::getComponentMap().end())
    {
        return (it->second)();
    }
    else
    {
        std::cout << "Failed to find component with key: " << key << std::endl;
        return ComponentPtr(nullptr);
    }
}



Component::ComponentMap& Component::getComponentMap()
{
    /* Must use this technique instead of a static member to ensure that the
     * map gets initialized before global initializers try to enlist
     * components. If we initialized the map in this translation unit
     * (Component.cpp) then we cannot guarentee that it is initialized before
     * another translation unit tries to access the map. That is why we
     * initialize the map inside this static function which is called by
     * whatever translation unit wants to access the map.
     *
     * This should be thread safe because this method is first called by a
     * global initializer, i.e. before main(). Please correct me if I'm wrong.
     * https://stackoverflow.com/a/1962918/5890633
     */

    static ComponentMap map;
    return map;
}



}; /* namespace EzSDL */
