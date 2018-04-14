/** @file       ezsdl.h
 *  @brief      Include SDL2 and fix its non-C89-compliant macro.
 *  @details    If C89 compliance is desired, be sure to use
 *              @code{.c} #include "EzSDL/ezsdl.h" @endcode
 *              instead of
 *              @code{.c} #include <SDL2/SDL.h> @endcode
 *              This ensures that `SDL_FORCE_INLINE` gets defined before
 *              SDL2 gets included. At least on my machine with Windows 10,
 *              this macro was triggering errors while I was compiling with
 *              `gcc -std=c89 -pedantic`.
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

#ifndef EZSDL_H
#define EZSDL_H

#ifdef __cplusplus
extern "C"
{
#endif



#define SDL_FORCE_INLINE static __inline__
#include <SDL2/SDL.h>



#ifdef __cplusplus
}
#endif

#endif /* EZSDL_H */
