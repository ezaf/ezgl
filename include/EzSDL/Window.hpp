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
 */

#include <SDL2/SDL_video.h>

#include <memory>
#include <string>



namespace EzSDL
{

/** @brief      Smart pointer for `EzSDL::Window`. */
typedef std::shared_ptr<class Window> WindowPtr;

/** @brief      SDL_Window adapter and smart pointer factory.
 *  @details    This class is not copyable.
 */
class Window
{
public:
    /** @brief      `EzSDL::WindowPtr` factory method.
     *  @details    TODO: exception safety? no-throw? JSON config file specs?
     *  @returns    `EzSDL::WindowPtr` smart pointer to the newly created
     *              `EzSDL::Window` instance.
     */
    static WindowPtr create(std::string const &file);

    /** @brief      `EzSDL::Window` destructor that you should never have to
     *              call.
     *  @details    Assuming you're using `EzSDL::WindowPtr`, you should never
     *              have to explicitly call this destructor unless you need to
     *              prematurely delete your `EzSDL::Window` instance.
     */
    virtual ~Window();

    SDL_Window* get() const;

protected:

private:
    Window(std::string const &file);
    Window(Window const &other) = delete;
    Window& operator=(Window const &other) = delete;

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
};

}; /* namespace EzSDL */



#endif /* EZSDL_WINDOW_HPP */
