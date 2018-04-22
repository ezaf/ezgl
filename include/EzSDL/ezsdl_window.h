/** @file       ezsdl_window.h
 *  @brief      Handle SDL windows, renderers, and events.
 *  
 *  <!---------
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
 *  ---------->
 */

#ifndef EZSDL_WINDOW_H
#define EZSDL_WINDOW_H

#ifdef __cplusplus
extern "C"
{
#endif



#include "EzSDL/ezsdl.h"

#include <stdint.h>

struct ezutil_observer;



/* TODO: Document Me! */
typedef struct ezsdl_window
{
    SDL_Window             *window;
    SDL_Renderer           *renderer;
    SDL_Event              *event;
    struct ezutil_observer *eventObsHead;
    SDL_DisplayMode         displayMode;
    uint8_t                 isRunning;
    uint8_t                 isPaused;
}
ezsdl_window;



/**
 *  @brief      Create an `ezsdl_window` instance.
 *  @return     A pointer to the created `ezsdl_window` instance.
 *  @details    Some pretty prose here...
 */
ezsdl_window*   ezsdl_window_new();
uint8_t         ezsdl_window_del(ezsdl_window **self);

uint8_t         ezsdl_window_pollEvent(ezsdl_window *self);
uint8_t         ezsdl_window_clear(ezsdl_window *self);
uint8_t         ezsdl_window_render(ezsdl_window *self);



#ifdef __cplusplus
}
#endif

#endif /* EZSDL_WINDOW_H */
