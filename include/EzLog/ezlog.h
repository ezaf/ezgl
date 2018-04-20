/** @file       ezlog.h
 *  @brief      Prioritizes and auto-formats your log and error messages.
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

#ifndef EZLOG_H
#define EZLOG_H

#ifdef __cplusplus
extern "C"
{
#endif



#ifndef EZDEBUG_LOG
#define EZDEBUG_LOG(severity, message, ...) \
    ezlog(severity, __func__, message, __VA_ARGS__);
#endif

/* ezlog will only print messages at least as severe as VERBOSITY */
#define VERBOSITY DEBUG



typedef enum ezlog_t
{
    FATAL, VITAL, MAJOR, MINOR, DEBUG
}
ezlog_t;

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



void            ezlog(ezlog_t pType, char *pnCallee, char *pnMessage, ...);



#ifdef __cplusplus
}
#endif

#endif /* EZLOG_H */
