/*  EzSDL/EventComponent.hpp
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

#ifndef EZSDL_EVENTCOMPONENT_HPP
#define EZSDL_EVENTCOMPONENT_HPP

/** @file       EzSDL/EventComponent.hpp
 *  @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit.
 */

#include "EzSDL/Component.hpp"
#include "EzSDL/Game.hpp"

union SDL_Event;



namespace EzSDL
{

/** @brief      Lorem ipsum
 *  @details    Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do
 *              eiusmod tempor incididunt ut labore et dolore magna aliqua.
 */
template <class T>
class EventComponent : public Component
{
public:
    virtual ~EventComponent() = default;

    void IInit(Object &object, Game &game) override
    {
        static_cast<T*>(this)->init(object, game);
    };

    void IUpdate(Object &object, Game &game) override
    {
        for (auto const &it : game.events)
        {
            static_cast<T*>(this)->update(object, it);
        }
    };

    static ComponentPtr create()
    {
        return ComponentPtr(new T());
    };

protected:
    EventComponent() = default;

private:
    EventComponent(EventComponent const &other) = delete;
    EventComponent& operator=(EventComponent const &other) = delete;
};

}; /* namespace EzSDL */



#endif /* EZSDL_EVENTCOMPONENT_HPP */
