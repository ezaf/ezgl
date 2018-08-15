/*  EzSDL/Object.hpp
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

#ifndef EZSDL_OBJECT_HPP
#define EZSDL_OBJECT_HPP

/** @file       EzSDL/Object.hpp
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "EzSDL/Component.hpp"
#include "nlohmann/json.hpp"

#include <memory>
#include <vector>



namespace EzSDL
{

class Game;

using ObjectPtr = std::unique_ptr<Object>;

/** @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do
 *              eiusmod tempor incididunt ut labore et dolore magna aliqua.
 */
class Object final
{
public:
    static ObjectPtr create(nlohmann::json &config);
    virtual ~Object() = default;

    void init(Game &game);
    void update(Game &game);

    nlohmann::json &data;

private:
    Object(nlohmann::json &config);
    Object(Object const &other) = delete;
    Object& operator=(Object const &other) = delete;

    std::vector<ComponentPtr> components;
};

}; /* namespace EzSDL */



#endif /* EZSDL_OBJECT_HPP */
