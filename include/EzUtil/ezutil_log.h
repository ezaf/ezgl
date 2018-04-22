/** @file       ezutil_log.h
 *  @brief      Prioritize your log messages.
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

#ifndef EZDEBUG_H
#define EZDEBUG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>



/* TODO: Move this to its own *.h file `ezutil_assert` */
#ifndef ezutil_assert
#define ezutil_assert(expA, op, expB) \
{ \
    if (!( expA op expB )) \
        fprintf(stdout, "FAIL:   !( " #expA " " #op " " #expB " )\n"); \
}
#endif /* ezdebug_assert */

/* TODO: Placeholder. Replace with OOP-like file I/O system? */
#ifndef EZUTIL_LOG_OUT
#define EZUTIL_LOG_OUT stdout
#endif

/*
#ifndef EZUTIL_LOG
#define EZUTIL_LOG(severity, message, ...) \
    ezutil_log(severity, __func__, message, __VA_ARGS__);
#endif
*/

/* ezdebug_log will only print messages at least as severe as this */
#ifndef EZUTIL_LOG_VERBOSITY
#define EZUTIL_LOG_VERBOSITY DEBUG
#endif



typedef enum ezutil_log_t
{
    FATAL='X', VITAL='!', MAJOR='>', MINOR='<', DEBUG='-'
} ezutil_log_t;

/* ezlog_t Reference
 * 
 * FATAL
 *   - So bad that either a crash is imminent or the program will not run
 *   - e.g. failed to initialize SDL
 *
 * VITAL
 *   - Won't cause a crash but may lead to instability
 *   - e.g. couldn't get desktop display mode
 *
 * MAJOR
 *   - Bad enough that some of the program's functionality is compromised
 *   - e.g. missing textures, cannot fetch user input
 *
 * MINOR
 *   - Still an error but not that bad of one
 *   - e.g. had to skip a frame, using default values due to bad user input
 *
 * DEBUG
 *   - Miscellaneous debugging messages; not necessarily errors
 *   - e.g. input log, application state log, etc
 *
 */



void            ezutil_log(ezutil_log_t pType, char *pnCallee,
                            char *pnMessage, ...);



#ifdef __cplusplus
}
#endif

#endif /* EZDEBUG_H */