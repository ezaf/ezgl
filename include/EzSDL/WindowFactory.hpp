/*  EzSDL/WindowFactory.hpp
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

#ifndef EZSDL_WINDOWFACTORY_HPP
#define EZSDL_WINDOWFACTORY_HPP

/** @file       EzSDL/WindowFactory.hpp
 *  @brief      SDL_Window factory and adapter.
 *  @details    I know from an implementation standpoint the naming of what
 *              is the window and what is the factory may seem backwards,
 *              but from the user's point of view, this interface naming scheme
 *              makes the most sense IMHO.<br>
 *              When using valgrind, note that SDL itself leaks memory. It
 *              definitely leaks 8.4kb, indirectly leaks 1.7kb, and has 120kb
 *              that is still reachable.
 */

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <memory>
#include <string>



namespace EzSDL
{

/** @brief      Window object smart pointer. */
typedef std::shared_ptr<class WindowFactory> Window;

/** @brief      SDL_Window adapter and smart pointer factory.
 *  @details    This class is not copyable.
 */
class WindowFactory
{
public:
    /** @brief      Window factory method.
     *  @details    TODO: exception safety? no-throw? JSON config file specs?
     *              Initializes SDL subsystems on-demand.
     *  @returns    Smart pointer (`std::shared_ptr`) to the newly created
     *              window instance.
     */
    static Window create(std::string const &file);

    /** @brief      Window destructor that you should never have to call.
     *  @details    Assuming you're using the `EzSDL::Window` smart pointer,
     *              you should never have to explicitly call this destructor
     *              unless you need to prematurely delete your window instance.
     */
    virtual ~WindowFactory();

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;

protected:

private:
    WindowFactory(std::string const &file);
    WindowFactory(WindowFactory const &other) = delete;
    WindowFactory& operator=(WindowFactory const &other) = delete;

    // Count of how many windows produced by this factory are currently alive.
    static int instances;

    // Pointer to SDL modules themselves
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;

    bool isPaused;
    unsigned long prevFrameTime;
};

}; /* namespace EzSDL */



#endif /* EZSDL_WINDOWFACTORY_HPP */
