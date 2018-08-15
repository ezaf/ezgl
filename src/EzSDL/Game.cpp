/*  EzSDL/Game.cpp
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

#include "EzSDL/Game.hpp"
#include "EzSDL/WindowEvent.hpp"
#include "EzSDL/WindowLogic.hpp"
#include "EzSDL/WindowRender.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream> // cout, endl
#include <string>

namespace EzSDL
{



Game::GamePtr Game::instance;



void Game::init(nlohmann::json &config)
{
    // This function should only be called once anyway!
    if (Game::instance != nullptr)
        return;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_version linked;
    SDL_GetVersion(&linked);

    std::cout << "Using SDL version " <<
        static_cast<int>(linked.major) << "." <<
        static_cast<int>(linked.minor) << "." <<
        static_cast<int>(linked.patch) << "." << std::endl <<
        "Initialized all SDL systems." << std::endl;

    Game::instance.reset(new Game(config));
}



// Don't bother checking config[...].is_null() because they ought to be there
Game::Game(nlohmann::json &config) :
    data(config),
    objects(),
    object(Object::create(config)), // TODO: config["window"] ???
    window(SDL_CreateWindow("", 0, 0, 0, 0, SDL_WINDOW_ALLOW_HIGHDPI)),
    renderer(SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED)),
    events()
{
    if (this->window == nullptr || this->renderer == nullptr)
    {
        std::cout << "Failed to create window and/or renderer: " <<
            SDL_GetError() << std::endl;
    }

    // object's components don't actually use the *this param
    object->init(*this);

    // Window settings
    std::string const title = object->data["title"];
    SDL_SetWindowTitle(this->window, title.c_str());
    SDL_SetWindowSize(this->window,
            this->object->data["display_width"],
            this->object->data["display_height"]);
    SDL_SetWindowFullscreen(this->window,
            this->object->data["fullscreen"] ?
            SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
    SDL_SetWindowBordered(this->window,
            static_cast<SDL_bool>(static_cast<int>(
                    this->object->data["bordered"])));
    //SDL_SetWindowResizable(this->window,
    //        static_cast<SDL_bool>(static_cast<int>(
    //              this->object->data["resizable"])));
    //SDL_SetWindowIcon(this->window, IMG_Load(""));

    // Renderer settings
    SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderSetLogicalSize(this->renderer,
            this->object->data["render_width"],
            this->object->data["render_height"]);
}



Game::~Game()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);

    // This is a singleton, we know we can quit SDL now
    SDL_Quit();

    std::cout << "Quit all SDL systems." << std::endl;
}



void Game::addObject(ObjectPtr object)
{
    object->init(*Game::instance);
    Game::instance->objects.push_back(std::move(object));
}



void Game::runOneFrame()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0)
    {
        Game::instance->events.push_back(event);
    }

    // Update if not paused, see Game::run() for more info on Z
    if (!Game::instance->data["pause"])
    {
        for (auto &it : Game::instance->objects)
        {
            it->update(*Game::instance);
        }
    }

    // Refresh window (even if paused)
    Game::instance->object->update(*Game::instance);

    Game::instance->events.clear();
}



void Game::run()
{
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(Game::runOneFrame,
            Game::instance->data["refresh_rate"], 1);
#else
    while (!Game::instance->data["quit"])
    {
        Game::instance->runOneFrame();

        // Frame rate timing; WindowLogicComponent handles vsync on/off option
        if (Game::instance->data["vsync_wait"] > 0.0)
        {
            //std::cout << Game::instance->data["vsync_wait"] << std::endl;
            SDL_Delay(Game::instance->data["vsync_wait"]);
        }
    }
#endif
}



SDL_Window* Game::getWindow()
{
    return this->window;
}



SDL_Renderer* Game::getRenderer()
{
    return this->renderer;
}



std::vector<SDL_Event> const& Game::getEvents()
{
    return this->events;
}



}; /* namespace EzSDL */
