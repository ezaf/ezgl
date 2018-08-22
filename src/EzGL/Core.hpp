/*  EzGL/Core.hpp
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

#ifndef EZGL_CORE_HPP
#define EZGL_CORE_HPP

/** @file       EzGL/Core.hpp
 *  @brief      Game engine core singleton. Handles program flow.
 */

#include "EzGL/Object.hpp"
#include "EzGL/Singleton.hpp"
#include "nlohmann/json.hpp"

#include <string>
#include <vector>



namespace EzGL
{

/** @brief      Game engine core singleton. Handles program flow.
 *  @details    This class is intended to be inherited from. Base classes can
 *              implement the engine code with whatever graphics API is desired
 *              such as OpenGL or SDL.
 */
class Core : public Singleton<Core>
{
public:
    Core() = default;
    ~Core();

    void init(std::string const &fileName);

    /* Call this one in main */
    void run();

    /* Anyone can call these at any point */
    void addObject(std::string const &objectName);
    std::vector<ObjectPtr> const& getObjects();

    /* Only meant to be called by the graphics API LogicComponent. If called
     * more than once per frame, calls following the first are ignored. */
    void updateObjects();

    /* Likely only to be called by Object */
    nlohmann::json getFromRoot(std::string const &objectName);

    nlohmann::json data;

private:
    Core(Core const &other) = delete;
    Core& operator=(Core const &other) = delete;

    class Impl;
    Impl *impl;
};

}; /* namespace EzGL */



#endif /* EZGL_CORE_HPP */
