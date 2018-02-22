/* ezlog.c
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

#include "ezlog.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>



const char* ezlog_typeSymbol(ezlog_t pType)
{
    switch (pType)
    {
        case FATAL:
            return "X";
        case VITAL:
            return "!";
        case MAJOR:
            return ">";
        case MINOR:
            return "<";
        case DEBUG:
            return "-";
        default:
            return "?";
    }
}



void ezlog(ezlog_t pType, char *pnCallee, char *pnMessage, ...)
{
    if (VERBOSITY >= pType)
    {
        // Allocate output buffer of necessary size
        char nOutput[ (strlen(pnCallee)+strlen(pnMessage))+8 ];

        // Format it as "[type] (callee) message"
        strcpy(nOutput, "[");
        strcat(nOutput, ezlog_typeSymbol(pType));
        strcat(nOutput, "] (");
        strcat(nOutput, pnCallee);
        strcat(nOutput, ") ");
        strcat(nOutput, pnMessage);
        strcat(nOutput, "\n");

        // Pass on any printf args
        va_list vArgs;
        va_start(vArgs, pnMessage);
        vfprintf(stdout, nOutput, vArgs);
        
        /* Causes seg faults on linux due to SDL_GetError() returning a
         * non-0 pointer yet there being no string there.

        // If SDL has something to say, display it
        if (strlen(SDL_GetError()) > 0)
        {
            fprintf(stdout, "    SDL Error: %s\n", SDL_GetError());
        }

        */
    }
}
