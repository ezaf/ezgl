/*  ezsdl_window.h
 *
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
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

#ifndef EZSDL_WINDOW_H
#define EZSDL_WINDOW_H

/** @file       ezsdl_window.h
 *  @brief      Handle SDL windows, renderers, and events.
 *  @details    TODO: seperate input management into another module.
 */

#ifdef __cplusplus
extern "C"
{
#endif



#include "EzSDL/ezsdl.h"
#include <SDL2/SDL_ttf.h>

#include <stdint.h>

struct ezc_list;



/* TODO: Document Me! */
typedef struct ezsdl_window
{
    SDL_Window             *window;
    SDL_DisplayMode        *displayMode;
    SDL_Renderer           *renderer;
    TTF_Font               *font;
    SDL_Event              *event;
    struct ezc_list        *headEvent;
    struct ezc_list        *headUpdate;
    struct ezc_list        *headDraw;
    uint8_t                 isRunning;
    uint8_t                 isPaused;
    uint32_t                delta;
}
ezsdl_window;



/**
 *  @brief      Create an `ezsdl_window` instance.
 *  @return     A pointer to the created `ezsdl_window` instance.
 *  @details    Some pretty prose here...
 */
ezsdl_window*   ezsdl_window_new();
uint8_t         ezsdl_window_delete(ezsdl_window **self);

uint8_t         ezsdl_window_pollEvent(ezsdl_window *self);
uint8_t         ezsdl_window_updateAll(ezsdl_window *self);
uint8_t         ezsdl_window_drawAll(ezsdl_window *self);
uint8_t         ezsdl_window_clear(ezsdl_window *self);
uint8_t         ezsdl_window_render(ezsdl_window *self);

/* These are quick-and-dirty interfaces and implementations. Polish later. */
uint8_t         ezsdl_window_drawText(ezsdl_window *self, const char *text,
                        SDL_Color *color, int16_t x, int16_t y);
uint8_t         ezsdl_window_drawRect(ezsdl_window *self, SDL_Color *color,
                        int16_t x, int16_t y, int16_t w, int16_t h);



#ifdef __cplusplus
}
#endif

#endif /* EZSDL_WINDOW_H */
