/*  EzSDL/Game.hpp
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

#ifndef EZSDL_GAME_HPP
#define EZSDL_GAME_HPP

/** @file       EzSDL/Game.hpp
 *  @brief      SDL_Window adapter.
 *  @details    When using valgrind/memcheck, note that SDL itself leaks
 *              memory. It definitely leaks 8.4kb, indirectly leaks 1.7kb, and
 *              has 120kb that is still reachable.
 */

#include "EzSDL/EventComponent.hpp"
#include "EzSDL/LogicComponent.hpp"
#include "EzSDL/RenderComponent.hpp"
#include "EzSDL/Object.hpp"
#include "nlohmann/json.hpp"

#include <memory>
#include <SDL2/SDL.h>
#include <string>



namespace EzSDL
{

/** @brief      SDL_Window adapter and smart pointer factory.
 *  @details    This class is not copyable nor inheritable.
 */
class Game final
{
    template <class T> friend class EventComponent;
    template <class T> friend class LogicComponent;
    template <class T> friend class RenderComponent;

public:
    /** @brief      Call this before all else. */
    static void init(nlohmann::json &config);

    /** @brief      Game destructor that you should never have to call. */
    ~Game();

    // TODO: deprecate, load via the json
    static void addObject(ObjectPtr object);

    static void run();

    nlohmann::json &data;

private:
    using GamePtr = std::unique_ptr<class Game>;

    Game(nlohmann::json &config);
    Game(Game const &other) = delete;
    Game& operator=(Game const &other) = delete;

    // For Emscripten's sake
    static void runOneFrame();

    // Singleton instance
    static GamePtr instance;

    std::vector<ObjectPtr> objects;
    ObjectPtr object;

    SDL_Window *window;
    SDL_Renderer *renderer;
    std::vector<SDL_Event> events;
};

}; /* namespace EzSDL */



#endif /* EZSDL_GAME_HPP */
