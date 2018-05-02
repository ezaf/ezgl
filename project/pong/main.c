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
#include "pong_ball.h"

#include <stdio.h>



int main(int argc, char *argv[])
{
    SDL_Color white = {255,255,255};
    SDL_Color red = {255,0,0};
    SDL_Color blue = {0,0,255};

    
    /* Setting up all the game objects */
    ezsdl_window *ezw = ezsdl_window_new();

    pong_ball *ball = pong_ball_new(&white, ezw);

    pong_paddle *paddleL0 =
        pong_paddle_new(SDL_SCANCODE_W, SDL_SCANCODE_S, ball, &blue, ezw);
   
    pong_paddle *paddleR0 =
        pong_paddle_new(SDL_SCANCODE_I, SDL_SCANCODE_K, ball, &red, ezw);

    paddleL0->x = ezw->displayMode->w * 0.04;
    paddleR0->x = ezw->displayMode->w - paddleL0->x - paddleR0->w;


    /* Running the game */
    while (ezw->isRunning)
    {
        ezsdl_window_pollEvent(ezw);
        ezsdl_window_updateAll(ezw);
        ezsdl_window_clear(ezw);
        ezsdl_window_drawAll(ezw);
        ezsdl_window_render(ezw);
    }


    /* Deleting all the game objects */
    pong_ball_del(&ball);
    pong_paddle_del(&paddleL0);
    pong_paddle_del(&paddleR0);
    ezsdl_window_del(&ezw);

    return 0;
}
