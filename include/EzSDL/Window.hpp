/*  EzSDL/Window.hpp
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

#ifndef EZSDL_WINDOW_HPP
#define EZSDL_WINDOW_HPP

/** @file       EzSDL/Window.hpp
 *  @brief      SDL_Window adapter.
 *  @details    When using valgrind/memcheck, note that SDL itself leaks
 *              memory. It definitely leaks 8.4kb, indirectly leaks 1.7kb, and
 *              has 120kb that is still reachable.
 */

#include "EzSDL/Object.hpp"

#include <SDL2/SDL.h>

#include <memory>
#include <string>



namespace EzSDL
{

/** @brief      SDL_Window adapter and smart pointer factory.
 *  @details    This class is not copyable nor inheritable.
 */
class Window final : private Object
{
public:
    /** @brief      Call this before all else. */
    static void init();

    /** @brief      Window destructor that you should never have to call. */
    virtual ~Window();

    static void addObject(ObjectPtr object);
    static void run();

    std::vector<SDL_Event> getEvents() const;
    double const& getDelta() const;
    SDL_Renderer* getRenderer() const;
    SDL_Window* getWindow() const;
    DDimension* getDimension() const;

private:
    using WindowPtr = std::unique_ptr<class Window>;

    Window(ComponentPtrList componentDeps);
    Window(Window const &other) = delete;
    Window& operator=(Window const &other) = delete;

    // For Emscripten's sake
    static void runOneFrame();

    // Singleton instance
    static WindowPtr instance;

    // Pointer to SDL modules themselves
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    std::vector<SDL_Event> events;

    // Objects besides this window itself
    std::vector<ObjectPtr> objects;
};

}; /* namespace EzSDL */



#endif /* EZSDL_WINDOW_HPP */
