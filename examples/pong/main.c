/** @file       main.c
 *  @brief      Example main function for EzSDL.
 *  @details    None of this code is part of the engine itself. Instead, treat
 *              this as an example or template for basing your future projects
 *              off of.
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

#include "EzSDL/ezsdl_window.h"
#include "EzUtil/ezutil_observer.h"
#include "pong_paddle.h"

#include <stdio.h>



int main(int argc, char *argv[])
{
    ezsdl_window *ezw = ezsdl_window_new();

    SDL_Color white = {255,255,255};

    pong_paddle *paddleLeft = pong_paddle_new(
            SDL_SCANCODE_W, SDL_SCANCODE_S, &white, ezw);
    
    pong_paddle *paddleRight = pong_paddle_new(
            SDL_SCANCODE_I, SDL_SCANCODE_K, &white, ezw);

    paddleLeft->x = ezw->displayMode->w * 0.04;
    paddleRight->x = ezw->displayMode->w - paddleLeft->x - paddleRight->w;

    uint16_t leftScoreX = ezw->displayMode->w * 0.4,
             rightScoreX = ezw->displayMode->w * 0.55,
             allScoreY = ezw->displayMode->h * 0.01;

    while (ezw->isRunning)
    {
        ezsdl_window_pollEvent(ezw);
        ezsdl_window_updateAll(ezw);
        ezsdl_window_clear(ezw);
        
        ezsdl_window_drawText(ezw, paddleLeft->scoreStr,
                &white, leftScoreX, allScoreY);
        ezsdl_window_drawText(ezw, paddleRight->scoreStr,
                &white, rightScoreX, allScoreY);

        ezsdl_window_drawAll(ezw);
        ezsdl_window_render(ezw);
    }

    ezsdl_window_del(&ezw);
    return 0;
}
