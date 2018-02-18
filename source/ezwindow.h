/* ezwindow.h
Copyright (c) 2018 by Kirk Lange

Handle your windows and renderers here!

EZSDL is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

EZSDL is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE. See the GNU General Public License for more details.
*/

#ifndef EZWINDOW_H
#define EZWINDOW_H

#include <SDL.h>
#include <stdint.h>

typedef struct ezwindow ezwindow;



ezwindow*       ezwindow_new();
uint8_t         ezwindow_del(ezwindow **pnfSelf);


SDL_Window*     ezwindow_getWindow(ezwindow *pnSelf);
SDL_Renderer*   ezwindow_getRenderer(ezwindow *pnSelf);
uint8_t         ezwindow_isRunning(ezwindow *pnSelf);


void            ezwindow_pollEvent(ezwindow *pnSelf);
void            ezwindow_clear(ezwindow *pnSelf);
void            ezwindow_update(ezwindow *pnSelf);



#endif // EZWINDOW_H
