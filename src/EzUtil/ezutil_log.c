/*  ezutil_log.c
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

#include "EzUtil/ezutil_log.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>



void ezutil_log(ezutil_log_t type, char *callee, char *message, ...)
{
    if (EZUTIL_LOG_VERBOSITY >= type)
    {
        /* Allocate output buffer of necessary size */
        char output[ (strlen(callee)+strlen(message))+8 ];

        char typestr[1];
        typestr[0] = (char) type;

        /* Format it as "[type] (callee) message" */
        strcpy(output, "[");
        strcat(output, typestr);
        strcat(output, "] (");
        strcat(output, callee);
        strcat(output, ") ");
        strcat(output, message);
        strcat(output, "\n");

        /* Pass on any printf args */
        va_list args;
        va_start(args, message);
        vfprintf(EZUTIL_LOG_OUT, output, args);
    }
}
