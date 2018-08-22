/*  EzGL/ComponentFactory.cpp
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

#include "EzGL/ComponentFactory.hpp"

#include <iostream>

namespace EzGL
{



ComponentPtr ComponentFactory::Create(Key const &key)
{
    typename ComponentMap::iterator it =
        ComponentFactory::GetComponentMap().find(key);

    if (it != ComponentFactory::GetComponentMap().end())
    {
        return (it->second)();
    }
    else
    {
        std::cout << "Failed to find component with key: " << key << std::endl;
        return ComponentPtr(nullptr);
    }
}



ComponentFactory::ComponentMap& ComponentFactory::GetComponentMap()
{
    static ComponentMap instance;
    return instance;
}



}; /* namespace EzGL */
