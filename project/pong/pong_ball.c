/*  pong_ball.c
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
#include "EzUtil/ezutil_log.h"
#include "EzUtil/ezutil_observer.h"
#include "pong_ball.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>



uint8_t pong_ball_reset(pong_ball *self, int8_t direction)
{
    if (self)
    {
        self->x = (self->window->displayMode->w/2) - (self->d/2);
        self->y = (self->window->displayMode->h/2) - (self->d/2);

        float angle;
        float windowRatio = (float) self->window->displayMode->w / 1920.0;

        while ((angle = (rand()%10)-5) == 0);

        self->dx = cos(DTOR(angle)) * windowRatio * PONG_BALL_VEL;

        if (direction)
            self->dx *= (direction/abs(direction));
        else if (rand() % 2)
            self->dx *= -1;
        
        self->dy = sin(DTOR(angle)) * windowRatio * PONG_BALL_VEL;

        if (rand() % 2)
            self->dy *= -1;

        self->pauseTime = 2000;

        return 1;
    }
    else
    {
        /* TODO: error handling */
        return 0;
    }
}



pong_ball* pong_ball_new(SDL_Color *color, ezsdl_window *window)
{
    pong_ball *self = (pong_ball*) malloc(sizeof(pong_ball));
    self->window = window;
    self->color = color;
    self->winner = 0;
    self->d = self->window->displayMode->w * 0.01;
    pong_ball_reset(self, 0);

    ezutil_observer_add(self->window->headEvent, &pong_ball_event, self);
    ezutil_observer_add(self->window->headUpdate, &pong_ball_update, self);
    ezutil_observer_add(self->window->headDraw, &pong_ball_draw, self);

    return self;
}



uint8_t pong_ball_del(pong_ball **self)
{
    if (*self)
    {
        free(*self);
        *self = 0;

        return 1;
    }
    else
    {
        ezutil_log(VITAL, __func__, "Skipped deletion of pong_ball "
                "instance. Cannot free a null pointer.");
        return 0;
    }

}



uint8_t pong_ball_event(pong_ball *self)
{
    if (self)
    {
        SDL_Event e = *(self->window->event);

        switch (e.type)
        {
            case SDL_KEYUP:
                switch (e.key.keysym.scancode)
                {
                    case SDL_SCANCODE_BACKSPACE:
                        pong_ball_reset(self, 0);
                        self->scoreL = self->scoreR = 0;
                        self->winner = 0;
                        break;
                }
                break;
        }

        return 1;
    }
    else
    {
        /* TODO: error handling */
        return 0;
    }
}



uint8_t pong_ball_update(pong_ball *self)
{
    if (self)
    {
        if (!self->pauseTime && !self->winner)
        {
            self->x += self->dx * self->window->delta;
            self->y += self->dy * self->window->delta;

            if (self->y < 0)
            {
                self->y = 0;
                self->dy = -self->dy;
            }
            else if (self->y > self->window->displayMode->h - self->d)
            {
                self->y = self->window->displayMode->h - self->d;
                self->dy = -self->dy;
            }

            if (self->x < 0 - self->d)
            {
                if (++self->scoreR == 11) self->winner = 1;
                else pong_ball_reset(self, -1);
            }
            else if (self->x > self->window->displayMode->w)
            {
                if (++self->scoreL == 11) self->winner = -1;
                else pong_ball_reset(self, 1);
            }
        }
        else
        {
            if ((self->pauseTime -= self->window->delta) <= 0)
                self->pauseTime = 0;
        }
        
        snprintf(self->scoreStrL, 8, "%i", self->scoreL);
        snprintf(self->scoreStrR, 8, "%i", self->scoreR);

        return 1;
    }
    else
    {
        /* TODO: error handling */
        return 0;
    }
}



uint8_t pong_ball_draw(pong_ball *self)
{
    if (self)
    {
        SDL_Color white = {255, 255, 255};
        ezsdl_window_drawText(self->window, self->scoreStrL, &white,
                self->window->displayMode->w * 0.4,
                self->window->displayMode->h * 0.01);
        ezsdl_window_drawText(self->window, self->scoreStrR, &white,
                self->window->displayMode->w * 0.55,
                self->window->displayMode->h * 0.01);

        ezsdl_window_drawRect(self->window, self->color,
                0, 0, self->window->displayMode->w, 2);
        ezsdl_window_drawRect(self->window, self->color,
                0, self->window->displayMode->h-2,
                self->window->displayMode->w, 2);

        if (self->winner == 0)
        {
            ezsdl_window_drawRect(self->window, self->color,
                    self->x, self->y, self->d, self->d);
        }
        else
        {
            if (self->winner == -1) strcpy(self->winnerStr, "Left wins!");
            else strcpy(self->winnerStr, "Right wins!");

            ezsdl_window_drawText(self->window, self->winnerStr, &white,
                    self->window->displayMode->w * 0.425,
                    self->window->displayMode->h * 0.8);
        }
        
        return 1;
    }
    else
    {
        /* TODO: error handling */
        return 0;
    }
}
