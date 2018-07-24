/*  EzSDL/WindowFactory.cpp
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

#include "EzSDL/WindowFactory.hpp"

#include <SDL2/SDL.h>

#include <iostream>

namespace EzSDL
{



int WindowFactory::instances = 0;



Window WindowFactory::create(std::string const &file)
{
    return Window(new WindowFactory(file));
}



WindowFactory::WindowFactory(std::string const &file) :
    window(nullptr, SDL_DestroyWindow),
    renderer(nullptr, SDL_DestroyRenderer),
    isPaused(false),
    prevFrameTime(SDL_GetTicks())
{
    // Initialize SDL video if necessary
    if (WindowFactory::instances == 0 && SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
#ifndef NDEBUG // Make all logs visible when debugging
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
#endif

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

    // Create actual window
    window.reset(
            SDL_CreateWindow("EzSDL Demo",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                enableFullscreen ? displayMode.w : 640,
                enableFullscreen ? displayMode.h : 480,
                SDL_WINDOW_BORDERLESS |
                SDL_WINDOW_ALLOW_HIGHDPI));

    renderer.reset(
            SDL_CreateRenderer(getWindow(), -1,
                SDL_RENDERER_ACCELERATED |
                SDL_RENDERER_PRESENTVSYNC));

    SDL_SetRenderDrawColor(getRenderer(), 0x00, 0x00, 0x00, 0xFF);

    // Error checking
    if (getWindow() != nullptr && getRenderer() != nullptr)
    {
        WindowFactory::instances++;
        std::cout << "Successfully created window and its renderer." <<
            std::endl;
    }
    else
    {
        std::cout << "Failed to create window and/or renderer: " <<
            SDL_GetError() << std::endl;

    }
}



WindowFactory::~WindowFactory()
{
    WindowFactory::instances--;

    if (WindowFactory::instances <= 0)
    {
        SDL_Quit();
        std::cout << "Quit all SDL systems." << std::endl;
    }
}



SDL_Window* WindowFactory::getWindow() const
{
    return window.get();
}



SDL_Renderer* WindowFactory::getRenderer() const
{
    return renderer.get();
}



}; /* namespace EzSDL */
