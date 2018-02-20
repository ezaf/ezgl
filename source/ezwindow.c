/* ezwindow.c
ezSDL - The Easy Simple DirectMedia Layer Wrapper
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

#include <SDL_image.h>
#include <stdio.h>



struct ezwindow
{
    SDL_Window      *mnWindow;
    SDL_Renderer    *mnRenderer;
    SDL_DisplayMode  mDisplayMode;
    SDL_Event        mEvent;
    uint8_t          mIsRunning;
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
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            640, 480,
            SDL_WINDOW_SHOWN );

    rnSelf->mnRenderer = SDL_CreateRenderer( rnSelf->mnWindow,
            -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    SDL_SetRenderDrawColor(rnSelf->mnRenderer, 0x00, 0x00, 0xFF, 0xFF);

    rnSelf->mIsRunning = 1;


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

        free(*pnfSelf);
        *pnfSelf = 0;

        return 1;
    }
    else
    {
        ezlog(CRIT, "ezwindow_del", "Skipped deletion of ezwindow instance. "
                "Cannot free a null pointer. (Duh!)");
        return 0;
    }

}



SDL_Window* ezwindow_getWindow(ezwindow *pnSelf)
{
    return pnSelf ? pnSelf->mnWindow : 0;
}



SDL_Renderer* ezwindow_getRenderer(ezwindow *pnSelf)
{
    return pnSelf ? pnSelf->mnRenderer : 0;
}



uint8_t ezwindow_isRunning(ezwindow *pnSelf)
{
    return pnSelf->mIsRunning;
}



void ezwindow_pollEvent(ezwindow *pnSelf)
{
    while ( SDL_PollEvent(&(pnSelf->mEvent)) )
    {
        if (pnSelf->mEvent.type == SDL_QUIT)
        {
            pnSelf->mIsRunning = 0;
        }
    }
}



void ezwindow_clear(ezwindow *pnSelf)
{
    SDL_SetRenderDrawColor(pnSelf->mnRenderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_RenderClear(pnSelf->mnRenderer);
}



void ezwindow_update(ezwindow *pnSelf)
{
    SDL_RenderPresent(pnSelf->mnRenderer);
}
