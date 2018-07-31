/*  test_hello.cpp
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

/** @file       test_hello.cpp
 *  @brief      Hello world example for EzSDL.
 */

#include "EzSDL/Window.hpp"
#include "EzSDL/WindowEventComponent.hpp"
#include "EzSDL/WindowLogicComponent.hpp"
#include "EzSDL/WindowRenderComponent.hpp"



int main(int argc, char *argv[])
{
    EzSDL::Component::enlist<EzSDL::WindowEventComponentID,
        EzSDL::EventComponent<EzSDL::WindowEventComponent>>();

    EzSDL::Component::enlist<EzSDL::WindowLogicComponentID,
        EzSDL::LogicComponent<EzSDL::WindowLogicComponent>>();

    EzSDL::Component::enlist<EzSDL::WindowRenderComponentID,
        EzSDL::RenderComponent<EzSDL::WindowRenderComponent>>();


    EzSDL::WindowPtr window(EzSDL::Window::create({
                EzSDL::Component::create(EzSDL::WindowEventComponentID),
                EzSDL::Component::create(EzSDL::WindowLogicComponentID),
                EzSDL::Component::create(EzSDL::WindowRenderComponentID)
            }));

    window->run();

    return 0;
}
