/*  main.c
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

/** @file       main.c
 *  @brief      Hello world example for EzSDL.
 */

#include "EzSDL/ezsdl_window.h"
#include "EzC/ezc_list.h"
#include "EzC/ezc_callback.h"

#include <stdio.h>



uint8_t silly_event(ezsdl_window *window);



int main(int argc, char *argv[])
{
    ezsdl_window *ezw = ezsdl_window_new();
    ezc_list_push_back(ezw->headEvent, ezc_callback_new(&silly_event, ezw));

    while (ezw->isRunning)
    {
        ezsdl_window_pollEvent(ezw);
        ezsdl_window_updateAll(ezw);
        ezsdl_window_clear(ezw);
        ezsdl_window_drawAll(ezw);
        ezsdl_window_render(ezw);
    }

    ezsdl_window_delete(&ezw);

    return 0;
}



uint8_t silly_event(ezsdl_window *window)
{
    SDL_Event e = *(window->event);

    switch (e.type)
    {
        case SDL_KEYDOWN:
            if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
                printf("Silly event down!\n");
            break;
        case SDL_KEYUP:
            if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
                printf("Silly event up!\n");
            break;
    }

    return 1;
}
