/* ezlog.h
Prioritizes and auto-formats your log and error messages.


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

#ifndef EZLOG_H
#define EZLOG_H



// ezlog will only print messages at least as severe as VERBOSITY
#define VERBOSITY DEBUG

typedef enum
{
    FATAL,      /* So bad that a crash is imminent or program can't run.
                     Example: failed to initialize SDL                       */
    CRIT,       /* Won't cause a crash but may lead to instability.
                     Example: couldn't get desktop display mode              */
    HARD,       /* Bad enough that the program may become unusable.
                     Example: missing textures                               */
    SOFT,       /* Still an error but not that bad of one.
                     Example: had to skip a frame for whatever reason        */
    DEBUG       /* Not necessarily an error, just helpful for debugging.
                     Example: input log, application state log, etc          */
} ezlog_t;


void            ezlog(ezlog_t pType, char *pnCallee, char *pnMessage, ...);



#endif // EZLOG_H
