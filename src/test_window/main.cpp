/*  test_window/main.cpp
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

/** @file       test_window/main.cpp
 *  @brief      Hello world example for EzGL.
 */

#include "EzGL/Core.hpp"

#include "nlohmann/json.hpp"

#include <fstream> // ifstream

#ifdef __linux__
#include <dlfcn.h>
#define DLEXT ".so"
#elif _WIN32
#include "dlfcn-win32/dlfcn.h"
#define DLEXT ".dll"
#endif

// Counteract SDL hijacking
#define SDL_main main



int main(int argc, char *argv[])
{
    std::ifstream file("data/main.json");
    if (!file.good()) return 1;

    nlohmann::json config;
    file >> config;

    // TODO: load using json file strings
    dlopen("Dummy" DLEXT, RTLD_LAZY);

    EzGL::Core::Instance().init(config["core"]);
    EzGL::Core::Instance().addObject(config["dummy"]);
    EzGL::Core::Instance().run();

    return 0;
}
