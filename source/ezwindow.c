/* ezwindow.c
Copyright (c) 2018 by Kirk Lange

EZSDL is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

EZSDL is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE. See the GNU General Public License for more details.
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
        fprintf(logerr, "[ezwindow_new] Failed to allocate new ezwindow "
                "instance. SDL Error: %s\n", SDL_GetError());

        free(rnSelf);
        rnSelf = 0;
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
        fprintf(logerr, "[ezwindow_del] Skipped deletion of ezwindow "
                "instance. Cannot free a null pointer.\n");
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
