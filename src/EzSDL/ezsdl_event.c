/*  ezsdl_event.c
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

#include "EzSDL/ezsdl_event.h"
#include "EzSDL/ezsdl_window.h"
#include "EzLog/ezlog.h"



uint8_t error_check_window_ptr(ezsdl_window *window, const char *caller);



uint8_t ezsdl_event_notifyAll(ezsdl_window *window)
{
    uint8_t error = error_check_window_ptr(window, __func__);

    if (!error)
    {
        while (SDL_PollEvent(window->event))
        {
            ezsdl_event_node *iter = window->eventHead;

            /* Notify everybody on the linked list. */
            do iter->notify(window);
            while (iter = iter->next);
        }
    }

    return !error;
}



ezsdl_event_node* ezsdl_event_addNode(ezsdl_window *window,
        void (*notify)(ezsdl_window*))
{
    uint8_t error = error_check_window_ptr(window, __func__);
    ezsdl_event_node *self = 0;

    if (error |= !notify)
    {
        ezlog(MAJOR, __func__, "Notify function pointer is null.");
    }

    if (!error)
    {
        self = (ezsdl_event_node*) malloc(sizeof(ezsdl_event_node));
        self->prev = 0;
        self->next = window->eventHead;
        self->notify = notify;

        window->eventHead->prev = self;
        window->eventHead = self;
    }

    return self;
}



uint8_t ezsdl_event_removeNode(ezsdl_event_node *node)
{
    if (node)
    {
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        free(node);
        return 1;
    }
    else
    {
        ezlog(MINOR, __func__, "Cannot remove a null node.");
        return 0;
    }
}



uint8_t error_check_window_ptr(ezsdl_window *window, const char *caller)
{
    uint8_t error = 0;

    if (error |= !window)
    {
        ezlog(MAJOR, caller, "Window pointer is null.");
    }
    else if (error |= !window->eventHead)
    {
        ezlog(MAJOR, caller, "Head of event node linked list is null.");
    }

    return error;
}
