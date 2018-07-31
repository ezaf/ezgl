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

#include <iostream>

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

    // TODO: parse a json config file
    bool enableFullscreen = true;

    SDL_DisplayMode displayMode;
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0)
    {
        enableFullscreen = false;
        std::cout << "Failed to get desktop display mode: " <<
            SDL_GetError() << std::endl;
    }

    this->dimension->at(DimensionKey::Z) = 60; // Hz

    // Create actual window
    this->window.reset(
            SDL_CreateWindow("EzSDL Demo",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                enableFullscreen ? displayMode.w : 640,
                enableFullscreen ? displayMode.h : 480,
                SDL_WINDOW_BORDERLESS |
                SDL_WINDOW_ALLOW_HIGHDPI));

    this->renderer.reset(
            SDL_CreateRenderer(getWindow(), -1,
                SDL_RENDERER_ACCELERATED |
                SDL_RENDERER_PRESENTVSYNC));

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



void Window::run()
{
    SDL_Event event;

    /*  Let Z be used to indicate refresh rate (target fps), where
     *      =0 : quit signal
     *      <0 : pause
     */
    while (this->dimension->at(DimensionKey::Z) != 0)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            events.push_back(event);
        }

        // Update if not paused
        if (this->dimension->at(DimensionKey::Z) > 0)
        {
            for (auto &it : this->objects)
            {
                it->update(*this);
            }
        }

        // Refresh window (even if paused)
        this->update(*this);

        // TODO: replace with framerate handler
        SDL_Delay(10);

        events.clear();
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
