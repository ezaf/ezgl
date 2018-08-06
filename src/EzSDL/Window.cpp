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

#include "nlohmann/json.hpp"

#include <cmath> // round
#include <fstream> // ifstream
#include <iostream> // cout, endl

namespace EzSDL
{



int Window::instanceCount = 0;



WindowPtr Window::create(ComponentPtrList componentDeps)
{
    return WindowPtr(new Window(componentDeps));
}



Window::Window(ComponentPtrList componentDeps) :
    Object(componentDeps),
    window(nullptr, SDL_DestroyWindow),
    renderer(nullptr, SDL_DestroyRenderer),
    events()
{
    // Initialize SDL video if necessary
    if (Window::instanceCount == 0 && SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_version linked;
        SDL_GetVersion(&linked);

        std::cout << "Using SDL version " <<
            static_cast<int>(linked.major) << "." <<
            static_cast<int>(linked.minor) << "." <<
            static_cast<int>(linked.patch) << "." << std::endl <<
            "Initialized all SDL systems." << std::endl;
    }

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
        std::cout << "Display mode aquired: {"
            " w:" << displayMode.w <<
            " h:" << displayMode.h <<
            " refresh_rate:" << displayMode.refresh_rate <<
            " }" << std::endl;
    }

    this->dimension->at(DimensionKey::Z) =
        static_cast<double>(displayMode.refresh_rate); // Hz

    // Create actual window and then renderer
    this->window.reset(
            SDL_CreateWindow("EzSDL Demo",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                displayMode.w, displayMode.h,
                SDL_WINDOW_ALLOW_HIGHDPI));

    this->renderer.reset(
            SDL_CreateRenderer(getWindow(), -1, SDL_RENDERER_ACCELERATED));

    // Configure settings
    // TODO: verify file exists, otherwise, exit
    std::ifstream file("data/window.json");

    if (file.good())
    {
        nlohmann::json config;
        file >> config;

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
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, scaling.c_str());

        SDL_SetHint(SDL_HINT_RENDER_VSYNC, config["vsync"] ? "1" : "0");
        SDL_ShowCursor(config["show_cursor"] ? SDL_ENABLE : SDL_DISABLE);
        SDL_RenderSetLogicalSize(this->getRenderer(),
                config["width"], config["height"]);

        SDL_SetRenderDrawColor(this->getRenderer(), 0x00, 0x00, 0x00, 0xFF);

        // Error checking
        if (getWindow() != nullptr && this->getRenderer() != nullptr)
        {
            Window::instanceCount++;
            std::cout << "Successfully created window and its renderer." <<
                std::endl;
        }
        else
        {
            std::cout << "Failed to create window and/or renderer: " <<
                SDL_GetError() << std::endl;
        }
    }
    else
    {
        // TODO: tell desired file name
        std::cout << "Missing window configuration file!" << std::endl;
    }

}



Window::~Window()
{
    Window::instanceCount--;

    if (Window::instanceCount <= 0)
    {
        SDL_Quit();
        std::cout << "Quit all SDL systems." << std::endl;
    }
}



void Window::addObject(ObjectPtr object)
{
    objects.push_back(std::move(object));
}



void Window::runOneFrame()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        events.push_back(event);
    }

    // Update if not paused, see Window::run() for more info on Z
    if (this->dimension->at(DimensionKey::Z) > 0)
    {
        for (auto &it : this->objects)
        {
            it->update(*this);
        }
    }

    // Refresh window (even if paused)
    this->update(*this);

    events.clear();
}



void Window::run()
{
    /*  Let Z be used to indicate refresh rate (target fps), where
     *      =0 : quit signal
     *      <0 : pause
     *
     *  For more information on Z, DZ, and D2Z, see `WindowLogicComponent.cpp`
     */
    while (this->dimension->at(DimensionKey::Z) != 0)
    {
        this->runOneFrame();

        // Frame rate timing; WindowLogicComponent handles VSync on/off option
        if (this->dimension->at(DimensionKey::D2Z) > 0.0)
        {
            /*
            std::cout <<
                static_cast<unsigned long>(
                        round(this->dimension->at(DimensionKey::D2Z))) <<
                std::endl;
            */

            SDL_Delay(static_cast<unsigned long>(
                        round(this->dimension->at(DimensionKey::D2Z))));
        }
    }
}



SDL_Window* Window::getWindow() const
{
    return this->window.get();
}



SDL_Renderer* Window::getRenderer() const
{
    return this->renderer.get();
}



std::vector<SDL_Event> Window::getEvents() const
{
    return this->events;
}



double const& Window::getDelta() const
{
    return this->dimension->at(DimensionKey::D2Z);
};



}; /* namespace EzSDL */
