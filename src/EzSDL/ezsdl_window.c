/*  ezsdl_window.c
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

#include "EzSDL/ezsdl_window.h"

#include "EzC/ezc_callback.h"
#include "EzC/ezc_list.h"
#include "EzC/ezc_log.h"

#include <SDL2/SDL_image.h>



/* Anonymous previous frame time holder.
 * WARNING: I'm pretty sure this is global to all ezsdl_windows.
 * Need to implement a better solution later... */
uint32_t PREV_FRAME;

/* Anonymous window event handler function. */
void ezsdl_window_event(ezsdl_window *self);



ezsdl_window* ezsdl_window_new()
{
    ezsdl_window *self = (ezsdl_window*) malloc(sizeof(ezsdl_window));
    uint8_t error = 0;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    self->displayMode = (SDL_DisplayMode*) malloc(sizeof(SDL_DisplayMode));
    SDL_GetDesktopDisplayMode(0, self->displayMode);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    self->window = SDL_CreateWindow( "EzSDL",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            self->displayMode->w, self->displayMode->h,
            SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS |
                SDL_WINDOW_FULLSCREEN_DESKTOP );

    SDL_ShowCursor(SDL_DISABLE);

    self->renderer = SDL_CreateRenderer( self->window,
            -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    SDL_SetRenderDrawColor(self->renderer, 0x00, 0x00, 0xFF, 0xFF);

    self->font = TTF_OpenFont("res/UbuntuMono-R.ttf", self->displayMode->w/30);
    self->event = (SDL_Event*) malloc(sizeof(SDL_Event));

    ezc_list_push_back(self->headEvent,
            ezc_callback_new(&ezsdl_window_event, self));

    /* self->headEvent = ezc_list_new(); */
    /* self->headUpdate = ezc_list_new(); */
    /* self->headDraw = ezc_list_new(); */

    self->isRunning = 1;
    self->isPaused = 0;
    self->delta = 0;
    PREV_FRAME = 0;


    /* Currently, `error` is unused. */
    if (error)
    {
        ezc_log(EZC_LOG_FATAL, "Failed to create ezsdl_window instance.");
        free(self);
        self = 0;
    }
    else
    {
        ezc_log(EZC_LOG_INFO, "Successfully created new ezsdl_window "
                "instance.");
    }

    return self;
}



uint8_t ezsdl_window_delete(ezsdl_window **self)
{
    if (*self)
    {
        SDL_DestroyRenderer((*self)->renderer);
        SDL_DestroyWindow((*self)->window);
        TTF_CloseFont((*self)->font);

        TTF_Quit();
        IMG_Quit();
        SDL_Quit();

        free((*self)->displayMode);
        free((*self)->event);

        ezc_list_map((*self)->headEvent, ezc_callback_delete);
        ezc_list_map((*self)->headUpdate, ezc_callback_delete);
        ezc_list_map((*self)->headDraw, ezc_callback_delete);

        ezc_list_delete((*self)->headEvent);
        ezc_list_delete((*self)->headUpdate);
        ezc_list_delete((*self)->headDraw);

        free(*self);
        *self = 0;

        return 1;
    }
    else
    {
        ezc_log(EZC_LOG_ERROR, "Skipped deletion of ezsdl_window instance. "
                "Cannot free a null pointer.");
        return 0;
    }

}



uint8_t ezsdl_window_pollEvent(ezsdl_window *self)
{
    if (self)
    {
        while (SDL_PollEvent(self->event))
        {
            ezc_list_map(self->headEvent, ezc_callback_call);
        }

        return 1;
    }
    else
    {
        ezc_log(EZC_LOG_WARN, __func__, "Skipped event polling. Reference to "
                "self is null.");
        return 0;
    }
}



uint8_t ezsdl_window_updateAll(ezsdl_window *self)
{
    if (self)
    {
        if (PREV_FRAME != 0) self->delta = SDL_GetTicks() - PREV_FRAME;
        PREV_FRAME = SDL_GetTicks();

        if (!self->isPaused) ezc_list_map(self->headUpdate, ezc_callback_call);

        return 1;
    }
    else
    {
        ezc_log(EZC_LOG_WARN, __func__, "Skipped updating. Reference to self "
                "is null.");
        return 0;
    }
}



uint8_t ezsdl_window_drawAll(ezsdl_window *self)
{
    if (self)
    {
        ezc_list_map(self->headDraw, ezc_callback_call);
        return 1;
    }
    else
    {
        ezc_log(EZC_LOG_WARN, __func__, "Skipped drawing. Reference to self "
                "is null.");
        return 0;
    }
}



uint8_t ezsdl_window_clear(ezsdl_window *self)
{
    /* TODO: add error checking */

    SDL_RenderClear(self->renderer);
}



uint8_t ezsdl_window_render(ezsdl_window *self)
{
    /* TODO: add error checking */

    SDL_SetRenderDrawColor(self->renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderPresent(self->renderer);
}



void ezsdl_window_event(ezsdl_window *self)
{
    /* TODO: add error checking */

    SDL_Event e = *(self->event);

    /* Internal event handling */
    switch (e.type)
    {
        case SDL_QUIT:
            self->isRunning = 0;
            break;

        case SDL_KEYDOWN:
            switch (e.key.keysym.scancode)
            {
                case SDL_SCANCODE_ESCAPE:
                    self->isRunning = 0;
                    break;
                case SDL_SCANCODE_GRAVE:
                    self->isPaused = !self->isPaused;
                    break;
            }
            break;

        case SDL_KEYUP:
            break;

        case SDL_WINDOWEVENT:
            switch (e.window.event)
            {
                /* Pause app if lost keyboard focus (like tab out) */
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    self->isPaused = 0;
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    self->isPaused = 1;
                    break;
            }
            break;

        default:
            break;
    }
}



uint8_t ezsdl_window_drawText(ezsdl_window *self, const char *text,
        SDL_Color *color, int16_t x, int16_t y)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(self->font, text, *color);
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(self->renderer, textSurface);
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopyEx(self->renderer, texture, 0, &renderQuad, 0, 0, 0);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(texture);
    textSurface = 0;
    texture = 0;
}




uint8_t ezsdl_window_drawRect(ezsdl_window *self, SDL_Color *color,
        int16_t x, int16_t y, int16_t w, int16_t h)
{
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(self->renderer, color->r, color->g, color->b, 0xFF);
    SDL_RenderFillRect(self->renderer, &rect);
}
