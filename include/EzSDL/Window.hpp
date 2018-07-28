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
 *  @details    When using valgrind, note that SDL itself leaks memory. It
 *              definitely leaks 8.4kb, indirectly leaks 1.7kb, and has 120kb
 *              that is still reachable.
 */

#include "EzSDL/Object.hpp"

#include <SDL2/SDL.h>

#include <memory>
#include <string>



namespace EzSDL
{

/** @brief      Window object smart pointer. */
using WindowPtr = std::unique_ptr<class Window>;

/** @brief      SDL_Window adapter and smart pointer factory.
 *  @details    This class is not copyable nor inheritable.
 */
class Window final : private Object
{
public:
    /** @brief      Window smart pointer factory method.
     *  @details    TODO: exception safety? no-throw? JSON config file specs?
     *              Initializes SDL subsystems on-demand.
     *  @returns    Smart pointer (`std::shared_ptr`) to the newly created
     *              window instance.
     */
    static WindowPtr create(ComponentPtrList componentDeps);

    /** @brief      Window destructor that you should never have to call.
     *  @details    Assuming you're using the `EzSDL::WindowPtr` smart pointer,
     *              you should never have to explicitly call this destructor
     *              unless you need to prematurely delete your window instance.
     */
    virtual ~Window();

    void addObject(ObjectPtr object);
    void run();

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;
    std::vector<SDL_Event> getEvents() const;

protected:
    Window(ComponentPtrList componentDeps);

private:
    Window(Window const &other) = delete;
    Window& operator=(Window const &other) = delete;

    // Count of how many windows produced by this factory are currently alive.
    static int instanceCount;

    // Pointer to SDL modules themselves
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    std::vector<SDL_Event> events;

    // Objects besides this window itself
    std::vector<ObjectPtr> objects;
};

}; /* namespace EzSDL */



#endif /* EZSDL_WINDOW_HPP */
