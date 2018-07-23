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

#include <cstdlib>

namespace EzSDL
{



int WindowFactory::instances = 0;



Window WindowFactory::create(std::string const &file)
{
    return Window(new WindowFactory(file));
}



WindowFactory::WindowFactory(std::string const &file) :
    window(nullptr, SDL_DestroyWindow)
{
    // Initialize SDL video if necessary
    if (WindowFactory::instances == 0 && SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
#ifndef NDEBUG // Make all logs visible when debugging
        SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN);
#endif

        SDL_Init(SDL_INIT_VIDEO);
        atexit(SDL_Quit);
        SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_INFO,
                "Initialized SDL video subsystem.\n");
    }

    // Create actual window
    window.reset(SDL_CreateWindow("EzSDL Demo",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_RESIZABLE |
            SDL_WINDOW_ALLOW_HIGHDPI));

    // Error checking
    if (window.get() == nullptr)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR,
                "Failed to create window: %s\n", SDL_GetError());
    }
    else
    {
        WindowFactory::instances++;
        SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_INFO,
                "Sucessfully created window.\n");
    }
}



WindowFactory::~WindowFactory()
{
    WindowFactory::instances--;

    if (WindowFactory::instances <= 0)
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_LogMessage(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_INFO,
                "Quit SDL video subsystem.\n");
        /* No need to call `SDL_Quit()`, we already did `atexit(SDL_Quit)`. */
    }
}



}; /* namespace EzSDL */
