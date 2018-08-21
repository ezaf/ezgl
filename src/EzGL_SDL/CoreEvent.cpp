/*  EzGL_SDL/CoreEvent.cpp
 *
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
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

#include "EzGL_SDL/CoreEvent.hpp"

#include "EzGL/Core.hpp"

#include <iostream>
#include <SDL2/SDL.h>

namespace EzGL
{



void CoreEvent::init(Object &object, Core &core)
{
    // TODO: If SDL wasn't initialized already
    if (true)
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_version linked;
        SDL_GetVersion(&linked);

        std::cout << "Using SDL version " <<
            static_cast<int>(linked.major) << "." <<
            static_cast<int>(linked.minor) << "." <<
            static_cast<int>(linked.patch) << "." << std::endl <<
            "Initialized all SDL systems." << std::endl;
    }

    core.data["pause"] = false;
    core.data["quit"] = false;

#define KEY(keyname) \
    core.data["key"][#keyname] = false

    KEY(F1); KEY(F2); KEY(F3); KEY(F4); KEY(F5); KEY(F6); KEY(F7); KEY(F8);
    KEY(F9); KEY(F10); KEY(F11); KEY(F12); KEY(F13); KEY(F14); KEY(F15);
    KEY(F16); KEY(F17); KEY(F18); KEY(F19); KEY(F20); KEY(F21); KEY(F22);
    KEY(F23); KEY(F24);

    KEY(0); KEY(1); KEY(2); KEY(3); KEY(4); KEY(5); KEY(6); KEY(7); KEY(8);
    KEY(9); KEY(NUMLOCKCLEAR);

    KEY(EQUALS); KEY(MINUS); KEY(QUOTE);

    KEY(a); KEY(b); KEY(c); KEY(d); KEY(e); KEY(f); KEY(g); KEY(h); KEY(i);
    KEY(j); KEY(k); KEY(l); KEY(m); KEY(n); KEY(o); KEY(p); KEY(q); KEY(r);
    KEY(s); KEY(t); KEY(u); KEY(v); KEY(w); KEY(x); KEY(y); KEY(z);

    KEY(BACKSLASH); /*KEY(BACKQUOTE);*/ KEY(LEFTBRACKET); KEY(PERIOD);
    KEY(RIGHTBRACKET); KEY(SEMICOLON); KEY(SLASH);

    KEY(DOWN); KEY(UP); KEY(LEFT); KEY(RIGHT);

    KEY(DELETE); KEY(END); KEY(HOME); KEY(INSERT); KEY(PAGEDOWN); KEY(PAGEUP);
    KEY(PAUSE); KEY(PRINTSCREEN); KEY(SCROLLLOCK); KEY(SYSREQ);

    KEY(CAPSLOCK); /*KEY(ESCAPE);*/ KEY(LALT); KEY(LCTRL); KEY(LGUI);
    KEY(LSHIFT); KEY(MENU); KEY(RALT); KEY(RCTRL); KEY(RGUI); KEY(RSHIFT);

    KEY(BACKSPACE); KEY(RETURN); KEY(SPACE); KEY(TAB);

#undef KEY
}



void CoreEvent::update(Object &object, Core &core)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            core.data["quit"] = true;
            break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
            switch (e.key.keysym.sym)
            {
#ifndef __EMSCRIPTEN__
            case SDLK_ESCAPE:
                core.data["quit"] = true;
                core.data["key"]["ESCAPE"] =
                    (e.key.type == SDL_KEYDOWN ? true : false);
                break;
#endif
            case SDLK_BACKQUOTE:
                core.data["pause"] = !core.data["pause"];
                core.data["key"]["BACKQUOTE"] =
                    (e.key.type == SDL_KEYDOWN ? true : false);
                break;

#define KEY(keyname) \
            case SDLK_##keyname: \
                core.data["key"][#keyname] = \
                    (e.key.type == SDL_KEYDOWN ? true : false); \
                break;

            KEY(F1); KEY(F2); KEY(F3); KEY(F4); KEY(F5); KEY(F6);
            KEY(F7); KEY(F8); KEY(F9); KEY(F10); KEY(F11); KEY(F12);
            KEY(F13); KEY(F14); KEY(F15); KEY(F16); KEY(F17); KEY(F18);
            KEY(F19); KEY(F20); KEY(F21); KEY(F22); KEY(F23); KEY(F24);

            KEY(0); KEY(1); KEY(2); KEY(3); KEY(4); KEY(5); KEY(6);
            KEY(7); KEY(8); KEY(9); KEY(NUMLOCKCLEAR);

            KEY(EQUALS); KEY(MINUS); KEY(QUOTE);

            KEY(a); KEY(b); KEY(c); KEY(d); KEY(e); KEY(f); KEY(g);
            KEY(h); KEY(i); KEY(j); KEY(k); KEY(l); KEY(m); KEY(n);
            KEY(o); KEY(p); KEY(q); KEY(r); KEY(s); KEY(t); KEY(u);
            KEY(v); KEY(w); KEY(x); KEY(y); KEY(z);

            KEY(BACKSLASH); /*KEY(BACKQUOTE);*/ KEY(LEFTBRACKET);
            KEY(PERIOD); KEY(RIGHTBRACKET); KEY(SEMICOLON); KEY(SLASH);

            KEY(DOWN); KEY(UP); KEY(LEFT); KEY(RIGHT);

            KEY(DELETE); KEY(END); KEY(HOME); KEY(INSERT); KEY(PAGEDOWN);
            KEY(PAGEUP); KEY(PAUSE); KEY(PRINTSCREEN); KEY(SCROLLLOCK);
            KEY(SYSREQ);

            KEY(CAPSLOCK); /*KEY(ESCAPE);*/ KEY(LALT); KEY(LCTRL);
            KEY(LGUI); KEY(LSHIFT); KEY(MENU); KEY(RALT); KEY(RCTRL);
            KEY(RGUI); KEY(RSHIFT);

            KEY(BACKSPACE); KEY(RETURN); KEY(SPACE); KEY(TAB);

#undef KEY_SDLK
            }
            break;
        // End SDL_KEYDOWN || SDL_KEYUP

        case SDL_WINDOWEVENT:
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                core.data["pause"] = false;
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                core.data["pause"] = true;
                break;
            }
        }
    }
}



}; /* namespace EzGL */
