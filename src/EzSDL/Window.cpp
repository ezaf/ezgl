/*  EzSDL/Window.cpp
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

#include "EzSDL/Window.hpp"
#include "EzSDL/WindowEventComponent.hpp"
#include "EzSDL/WindowLogicComponent.hpp"
#include "EzSDL/WindowRenderComponent.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <cmath> // round
#include <iostream> // cout, endl

namespace EzSDL
{



Window::WindowPtr Window::instance;



void Window::init(nlohmann::json const &config)
{
    // This function should only be called once anyway!
    if (Window::instance != nullptr)
        return;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_version linked;
    SDL_GetVersion(&linked);

    std::cout << "Using SDL version " <<
        static_cast<int>(linked.major) << "." <<
        static_cast<int>(linked.minor) << "." <<
        static_cast<int>(linked.patch) << "." << std::endl <<
        "Initialized all SDL systems." << std::endl;

    Window::instance.reset(new Window(config));
}



Window::Window(nlohmann::json const &config) :
    Object(config),
    window(nullptr, SDL_DestroyWindow),
    renderer(nullptr, SDL_DestroyRenderer),
    events()
{
    // Get display information
    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
    {
        displayMode.w = 640;
        displayMode.h = 480;
        displayMode.refresh_rate = 60;
        std::cout << "Failed to get desktop display mode: " <<
            SDL_GetError() << std::endl;
    }
    else
    {
#ifdef __EMSCRIPTEN__
        displayMode.refresh_rate = 60;
#endif
        std::cout << "Display mode aquired: {"
            " w:" << displayMode.w <<
            " h:" << displayMode.h <<
            " refresh_rate:" << displayMode.refresh_rate <<
            " }" << std::endl;
    }

    // Create actual window and then renderer
    this->window.reset(
            SDL_CreateWindow("EzSDL Demo",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                displayMode.w, displayMode.h,
                SDL_WINDOW_ALLOW_HIGHDPI));

    this->renderer.reset(
            SDL_CreateRenderer(this->window.get(), -1,
                SDL_RENDERER_ACCELERATED));

    // Configure settings
    // Don't bother checking .is_null() because they ought to be there
    SDL_SetWindowFullscreen(this->window.get(),
            config["fullscreen"] ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);

    SDL_SetWindowBordered(this->window.get(),
            static_cast<SDL_bool>(static_cast<int>(config["bordered"])));

    /*
    SDL_SetWindowResizable(this->window.get(),
            static_cast<SDL_bool>(static_cast<int>(config["resizable"])));
    */

    std::string scaling = config["scaling"];
    if (!(scaling == "linear" || scaling == "nearest")) scaling = "linear";
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scaling.c_str());
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, config["vsync"] ? "1" : "0");
    SDL_ShowCursor(config["show_cursor"] ? SDL_ENABLE : SDL_DISABLE);

    // Refresh rate (Hz)
    if (this->dimension->at(DimensionKey::Z) == 0)
    {
        this->dimension->at(DimensionKey::Z) =
            static_cast<double>(displayMode.refresh_rate);
    }

    SDL_RenderSetLogicalSize(this->renderer.get(),
            this->dimension->at(DimensionKey::W),
            this->dimension->at(DimensionKey::H));

    //SDL_SetWindowIcon(this->window.get(), IMG_Load(""));
    SDL_SetRenderDrawColor(this->renderer.get(), 0x00, 0x00, 0x00, 0xFF);

    // Error checking
    if (this->window.get() != nullptr && this->renderer.get() != nullptr)
    {
        std::cout << "Successfully created window and its renderer." <<
            std::endl;

        /* Initialize this window's components by calling base class'
         * non-static init function. */
        Object::init(*Window::instance);
    }
    else
    {
        std::cout << "Failed to create window and/or renderer: " <<
            SDL_GetError() << std::endl;
    }
}



Window::~Window()
{
    // This is a singleton, we know we can quit SDL now
    SDL_Quit();

    std::cout << "Quit all SDL systems." << std::endl;
}



void Window::addObject(ObjectPtr object)
{
    object->init(*Window::instance);
    Window::instance->objects.push_back(std::move(object));
}



void Window::runOneFrame()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        Window::instance->events.push_back(event);
    }

    // Update if not paused, see Window::run() for more info on Z
    if (Window::instance->dimension->at(DimensionKey::Z) > 0)
    {
        for (auto &it : Window::instance->objects)
        {
            it->update(*Window::instance);
        }
    }

    // Refresh window (even if paused)
    Window::instance->update(*Window::instance);

    Window::instance->events.clear();
}



void Window::run()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(Window::runOneFrame, 60, 1);
#else
    /*  Let Z be used to indicate refresh rate (target fps), where
     *      =0 : quit signal
     *      <0 : pause
     *
     *  For more information on Z, DZ, and D2Z, see `WindowLogicComponent.cpp`
     */
    while (Window::instance->dimension->at(DimensionKey::Z) != 0)
    {
        Window::instance->runOneFrame();

        // Frame rate timing; WindowLogicComponent handles VSync on/off option
        if (Window::instance->dimension->at(DimensionKey::D2Z) > 0.0)
        {
            /*
            std::cout <<
                static_cast<unsigned long>(
                        round(Window::instance->dimension->at(
                                DimensionKey::D2Z))
                        ) <<
                std::endl;
            */

            SDL_Delay(static_cast<unsigned long>(
                        round(Window::instance->dimension->at(
                                DimensionKey::D2Z))));
        }
    }
#endif
}



SDL_Window* Window::getWindow() const
{
    return Window::instance->window.get();
}



SDL_Renderer* Window::getRenderer() const
{
    return Window::instance->renderer.get();
}



std::vector<SDL_Event> Window::getEvents() const
{
    return Window::instance->events;
}



double const& Window::getDelta() const
{
    return Window::instance->dimension->at(DimensionKey::DZ);
}



DDimension* Window::getDimension() const
{
    return Window::instance->dimension.get();
}



}; /* namespace EzSDL */
