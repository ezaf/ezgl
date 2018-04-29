/** @file       pong_ball.h
 *  @brief      Functions and structures for pong paddle.
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

#ifndef PONG_BALL_H
#define PONG_BALL_H

#ifdef __cplusplus
extern "C"
{
#endif



#include <stdint.h>

#define PONG_BALL_VEL 1.2
#define PI 3.14159265
#define DTOR(angle) ((angle*PI)/180.0)
#define RTOD(rad) ((rad*180.0)/PI)



typedef struct ezsdl_window ezsdl_window;
typedef struct SDL_Color SDL_Color;



typedef struct pong_ball
{
    float           x, y, dx, dy;
    uint16_t        r;
    uint8_t         scoreL, scoreR;
    char            scoreStrL[8], scoreStrR[8], winnerStr[16];
    int8_t          winner; /* -1: left, 0: none, 1: right */
    int32_t        pauseTime;
    SDL_Color      *color;
    ezsdl_window   *window;
}
pong_ball;



pong_ball*      pong_ball_new(SDL_Color *color, ezsdl_window *window);
uint8_t         pong_ball_del(pong_ball **self);

uint8_t         pong_ball_event(pong_ball *self);
uint8_t         pong_ball_update(pong_ball *self);
uint8_t         pong_ball_draw(pong_ball *self);



#ifdef __cplusplus
}
#endif

#endif /* PONG_BALL_H */
