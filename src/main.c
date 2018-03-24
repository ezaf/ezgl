/* main.cpp
Main function for ezSDL. None of this code is part of the engine itself.
Rather, treat this as an example or template for basing your future projects
off of.


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

#include "ezsdl/ezwindow.h"

#include <stdio.h>

void sillyEvent(ezwindow *pnWindow);



int main(int argc, char *argv[])
{
    printf("Hello world, I am ezsdl!\n");

    ezwindow *ezw = ezwindow_new();
    while (ezwindow_isRunning(ezw))
    {
        while (ezwindow_pollEvent(ezw))
        {
            /* Send events to game objects. Something like:
             * player_checkEvent(player, ezw); */

            /* Here's a quick demo */
            sillyEvent(ezw);
        }

        ezwindow_clear(ezw);
        /* Draw the game objects. Something like:
         * player_draw(player, ezw); */

        ezwindow_render(ezw);
    }
    ezwindow_del(&ezw);

    return 0;
}



void sillyEvent(ezwindow *pnWindow)
{
    /* So that I don't have to keep typing this darn function call */
    SDL_Event vEvent = *ezwindow_getEvent(pnWindow);

    switch (vEvent.type)
    {
        case SDL_KEYDOWN:
            switch (vEvent.key.keysym.scancode)
            {
                case SDL_SCANCODE_SPACE:
                    printf("You pressed space bar!\n");
                    break;
            }
            break;
    }
}
