/*  pong_paddle.h
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

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

/** @file       pong_paddle.h
 *  @brief      Pong paddle module.
 */

#ifdef __cplusplus
extern "C"
{
#endif



#include <stdint.h>

#define PONG_PADDLE_VEL 0.8
#define PONG_PADDLE_AI_SLEEP_TIME 250
#define PONG_PADDLE_AI_REDIR_TIME 250



typedef struct pong_ball pong_ball;
typedef struct SDL_Color SDL_Color;
typedef struct ezsdl_window ezsdl_window;



typedef struct pong_paddle
{
    float           x, y, dy;
    uint16_t        w, h;
    uint16_t        keyUp, keyDown, keyToggleAI;
    uint8_t         isAI;
    uint32_t        AI_sleepTime, AI_redirTime;
    pong_ball      *ball;
    SDL_Color      *color;
    ezsdl_window   *window;
}
pong_paddle;



pong_paddle*    pong_paddle_new(uint16_t keyToggleAI,
                        uint16_t keyUp, uint16_t keyDown,
                        pong_ball *ball, SDL_Color *color,
                        ezsdl_window *window);
uint8_t         pong_paddle_delete(pong_paddle **self);

uint8_t         pong_paddle_event(pong_paddle *self);
uint8_t         pong_paddle_update(pong_paddle *self);
uint8_t         pong_paddle_draw(pong_paddle *self);



#ifdef __cplusplus
}
#endif

#endif /* PONG_PADDLE_H */
