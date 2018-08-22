/*  EzGL_Main/main.cpp
 *
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
 */

/** @file       EzGL_Main/main.cpp
 *  @brief      The only main function you'll ever need!
 *  @details    You shouldn't have to change the main function whatsoever. All
 *              programming and customization is done through plugins and
 *              json configuration files.
 */

#include "EzGL/Object.hpp"

// Counteract SDL2's `-Dmain=SDL_main` hijacking the main function.
#undef main



int main(int argc, char *argv[])
{
    return EzGL::Object::Main((argc == 2) ? argv[2] : "data/main.json");
}
