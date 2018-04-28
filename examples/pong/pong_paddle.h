/** @file       pong_paddle.h
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

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H

#ifdef __cplusplus
extern "C"
{
#endif



#include <stdint.h>



typedef struct ezsdl_window ezsdl_window;
typedef struct SDL_Color SDL_Color;



typedef struct pong_paddle
{
    int16_t         x, y, w, h, dy;
    uint16_t        score;
    char            scoreStr[8];
    int16_t         scoreX, scoreY;
    uint16_t        keyUp, keyDown;
    SDL_Color      *color;
    ezsdl_window   *window;
}
pong_paddle;



pong_paddle*    pong_paddle_new(uint16_t keyUp, uint16_t keyDown,
                        SDL_Color *color, ezsdl_window *window);
uint8_t         pong_paddle_del(pong_paddle **self);

uint8_t         pong_paddle_event(pong_paddle *self);
uint8_t         pong_paddle_update(pong_paddle *self);
uint8_t         pong_paddle_draw(pong_paddle *self);



#ifdef __cplusplus
}
#endif

#endif /* PONG_PADDLE_H */
