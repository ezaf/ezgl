/*  EzGL/Object.cpp
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

#include "EzGL/Object.hpp"

#include "EzGL/Core.hpp"
#include "EzGL/ComponentFactory.hpp"
#include "EzGL/IComponent.hpp"

#include <string>
#include <vector>

namespace EzGL
{



class Object::Impl
{
public:
    Impl(nlohmann::json &config) :
        components(ComponentFactory::Instance().create(config["components"]))
    {
    }

    ~Impl()
    {
        components.clear();
        components.shrink_to_fit();
    }

    std::vector<ComponentPtr> components;
};



ObjectPtr Object::Create(nlohmann::json &config)
{
    return ObjectPtr(new Object(config));
}



Object::Object(nlohmann::json &config) :
    data(config),
    other(nullptr),
    impl(nullptr)
{
}



Object::~Object()
{
    delete impl;
}



void Object::init(Core &core)
{
    if (!this->data["inherit"].is_null())
    {
        // Have this->data override what it inherits from
        nlohmann::json temp =
            core.getFromRoot(this->data["inherit"].get<std::string>());
        temp.merge_patch(this->data);
        this->data = temp;
    }

    this->impl = new Impl(this->data);

    for (auto &it : this->impl->components)
    {
        it->IInit(*this, core);
    }
}



void Object::update(Core &core)
{
    for (auto &it : this->impl->components)
    {
        it->IUpdate(*this, core);
    }
}



}; /* namespace EzGL */
