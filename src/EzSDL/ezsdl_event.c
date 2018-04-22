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
#include "EzUtil/ezutil_log.h"



uint8_t ezsdl_event_node_isNull(ezsdl_event_node *head, const char *caller)



uint8_t ezsdl_event_notifyAllNodes(ezsdl_event_node *head)
{
    uint8_t error = ezsdl_event_node_isNull(head, __func__);

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



ezsdl_event_node* ezsdl_event_addNode(ezsdl_event_node *head,
        void (*notify)(ezsdl_event_node*))
{
    uint8_t error = ezsdl_event_node_isNull(head, __func__);
    ezsdl_event_node *self = 0;

    if (error |= !notify)
    {
        ezutil_log(MAJOR, __func__, "Notify function pointer is null.");
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



uint8_t ezsdl_event_removeNode(ezsdl_event_node **node)
{
    uint8_t error = ezsdl_event_node_isNull(*node, __func__);

    if (!error)
    {
        if ((*node)->prev) (*node)->prev->next = (*node)->next;
        if ((*node)->next) (*node)->next->prev = (*node)->prev;
        free(*node);
    }
    
    return !error;
}



uint8_t ezsdl_event_removeAllNodes(ezsdl_event_node *head)
{
    uint8_t error = ezsdl_event_node_isNull(head, __func__);

    if (!error)
    {
        ezsdl_event_node *iter = head;
        ezsdl_event_node *next = 0;

        /* We know eventHead is not null thanks to earlier error check. */
        do
        {
            next = iter->next;
            free(iter);
        }
        while (iter = next);
    }

    return !error;
}



uint8_t ezsdl_event_node_isNull(ezsdl_event_node *node, const char *caller)
{
    uint8_t error = 0;

    if (error |= !node)
    {
        ezutil_log(MAJOR, caller, "Node paramter is null.");
    }

    return error;
}
