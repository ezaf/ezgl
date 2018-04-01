/** @file       ezwindow.h
 *  @brief      Handle SDL windows and renderers.
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

#ifndef EZWINDOW_H
#define EZWINDOW_H

#ifdef __cplusplus
extern "C"
{
#endif



#include <SDL2/SDL.h>
#include <stdint.h>

typedef struct ezwindow ezwindow;



/**
 *  @brief      Create an @c ezwindow instance.
 *  @details    Some pretty prose here...
 *  @return     A pointer to the created @c ezwindow instance.
 */
ezwindow*       ezwindow_new();
uint8_t         ezwindow_del(ezwindow **self);

SDL_Window*     ezwindow_getWindow(ezwindow *self);
SDL_Renderer*   ezwindow_getRenderer(ezwindow *self);
SDL_Event*      ezwindow_getEvent(ezwindow *self);
uint8_t         ezwindow_isRunning(ezwindow *self);
uint8_t         ezwindow_isPaused(ezwindow *self);

uint8_t         ezwindow_pollEvent(ezwindow *self);
void            ezwindow_clear(ezwindow *self);
void            ezwindow_render(ezwindow *self);



#ifdef __cplusplus
}
#endif

#endif /* EZWINDOW_H */
