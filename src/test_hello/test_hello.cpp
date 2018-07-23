/*  test_hello.cpp
 *
 *  Copyright (c) 2018 Kirk Lange
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
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

/** @file       test_hello.cpp
 *  @brief      Hello world example for EzSDL.
 */

#include "EzSDL/WindowFactory.hpp"

#include <SDL2/SDL.h>

#include <iostream>

void sillyEvent(EzSDL::Window window);



int main(int argc, char *argv[])
{
    EzSDL::Window windowA(EzSDL::WindowFactory::create("default.json"));

    SDL_Init(SDL_INIT_TIMER);
    SDL_Delay(3000);

    EzSDL::Window windowB(EzSDL::WindowFactory::create("default.json"));

    SDL_Delay(3000);

    return 0;
}



void sillyEvent(EzSDL::Window window)
{
    SDL_Event e; /* TODO: get event from window!!! */

    switch (e.type)
    {
        case SDL_KEYDOWN:
            if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
                std::cout << "Silly spacebar event down!" << std::endl;
            break;
        case SDL_KEYUP:
            if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
                std::cout << "Silly spacebar event up!" << std::endl;
            break;
    }
}
