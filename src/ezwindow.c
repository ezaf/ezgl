/* ezwindow.c
Copyright (c) 2018 Kirk Lange

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "ezwindow.h"
#include "ezlog.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>



struct ezwindow
{
    SDL_Window      *mnWindow;
    SDL_Renderer    *mnRenderer;
    SDL_Event       *mnEvent;
    SDL_DisplayMode  mDisplayMode;
    uint8_t          mIsRunning;
    uint8_t          mIsPaused;
};



ezwindow* ezwindow_new()
{
    ezwindow *rnSelf = (ezwindow*) malloc(sizeof(ezwindow));
    uint8_t vError = 0;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    SDL_GetDesktopDisplayMode(0, &rnSelf->mDisplayMode);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    rnSelf->mnWindow = SDL_CreateWindow( "ezsdl",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            640, 480,
            SDL_WINDOW_SHOWN );

    rnSelf->mnRenderer = SDL_CreateRenderer( rnSelf->mnWindow,
            -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    SDL_SetRenderDrawColor(rnSelf->mnRenderer, 0x00, 0x00, 0xFF, 0xFF);

    rnSelf->mnEvent = (SDL_Event*) malloc(sizeof(SDL_Event));
    rnSelf->mIsRunning = 1;
    rnSelf->mIsPaused = 0;


    if (vError)
    {
        ezlog(FATAL, "ezwindow_new", "Failed to create ezwindow instance.");
        free(rnSelf);
        rnSelf = 0;
    }
    else
    {
        ezlog(DEBUG, "ezwindow_new", "Successfully created new ezwindow "
                "instance.");
    }

    return rnSelf;
}



uint8_t ezwindow_del(ezwindow **pnfSelf)
{
    if (*pnfSelf)
    {
        SDL_DestroyRenderer((*pnfSelf)->mnRenderer);
        SDL_DestroyWindow((*pnfSelf)->mnWindow);
        IMG_Quit();
        SDL_Quit();

        free((*pnfSelf)->mnEvent);
        free(*pnfSelf);
        *pnfSelf = 0;

        return 1;
    }
    else
    {
        ezlog(VITAL, "ezwindow_del", "Skipped deletion of ezwindow instance. "
                "Cannot free a null pointer.");
        return 0;
    }

}



/* C Preprocessor Magic ;)
 * Typing out these getter functions gets pretty repetitive... */
#define EZWINDOW_GETTER(get_t, fn, get_m, error) \
    get_t ezwindow_##fn(ezwindow *pnSelf) \
    { \
        if (pnSelf) \
        { \
            return pnSelf->get_m; \
        } \
        else \
        { \
            ezlog(MAJOR, "ezwindow_"#fn, error); \
            return 0; \
        } \
    }

EZWINDOW_GETTER(SDL_Window*, getWindow, mnWindow, "Cannot get SDL_Window off "
        "of an ezwindow null pointer.")

EZWINDOW_GETTER(SDL_Renderer*, getRenderer, mnRenderer, "Cannot get SDL_"
        "Renderer off of an ezwindow null pointer.")

EZWINDOW_GETTER(SDL_Event*, getEvent, mnEvent, "Cannot get SDL_Event off of "
        "an ezwindow null pointer.")

EZWINDOW_GETTER(uint8_t, isRunning, mIsRunning, "Cannot determine if window "
        "is running because an ezwindow null pointer was given.")

EZWINDOW_GETTER(uint8_t, isPaused, mIsPaused, "Cannot determine if window is "
        "paused because an ezwindow null pointer was given.")

#undef EZWINDOW_GETTER



uint8_t ezwindow_pollEvent(ezwindow *pnSelf)
{
    uint8_t rPolling;
    
    if (pnSelf)
    {
        /* Save polling status so we can return to everyone else.
         * It is essential that pnSelf's actual mnEvent rather than a copy
         *   of pnSelf *mnEvent be passed to SDL_PollEvent() */
        rPolling = SDL_PollEvent(ezwindow_getEvent(pnSelf));
        /* So that I don't have to keep typing this darn function call */
        SDL_Event vEvent = *ezwindow_getEvent(pnSelf);

        /* Internal event handling */
        if (rPolling)
        {
            switch (vEvent.type)
            {
                case SDL_QUIT:
                    pnSelf->mIsRunning = 0;
                    break;

                case SDL_KEYDOWN:
                    switch (vEvent.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_ESCAPE:
                            pnSelf->mIsRunning = 0;
                            break;

                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    break;

                case SDL_WINDOWEVENT:
                    switch (vEvent.window.event)
                    {
                        /* Pause app if lost keyboard focus (like tab out) */
                        case SDL_WINDOWEVENT_FOCUS_GAINED:
                            pnSelf->mIsPaused = 0;
                            break;
                        case SDL_WINDOWEVENT_FOCUS_LOST:
                            pnSelf->mIsPaused = 1;
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
    }
    else
    {
        ezlog(MAJOR, "ezwindow_pollEvent", "Cannot poll events off of an "
                "ezwindow null pointer.");
        rPolling = 0;
    }
    
    /* Return polling status to everyone else */
    return rPolling;
}



void ezwindow_clear(ezwindow *pnSelf)
{
    /* TODO: For now it's an obnoxious, bright blue so that it's obvious
     * when the bare background is exposed. Replace later with black. */
    SDL_SetRenderDrawColor(pnSelf->mnRenderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderClear(pnSelf->mnRenderer);
}



void ezwindow_render(ezwindow *pnSelf)
{
    SDL_RenderPresent(pnSelf->mnRenderer);
}
