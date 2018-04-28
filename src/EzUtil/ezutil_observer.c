/*  ezutil_observer.c
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

#include "EzUtil/ezutil_observer.h"
#include "EzUtil/ezutil_log.h"



uint8_t ezutil_observer_isNull(ezutil_observer *subject, const char *caller);



ezutil_observer* ezutil_observer_new()
{
    ezutil_observer *self = (ezutil_observer*) malloc(sizeof(ezutil_observer));
    self->prev = self->next = self->notify = self->data = 0;
    return self;
}



uint8_t ezutil_observer_del(ezutil_observer **head)
{
    uint8_t error = ezutil_observer_isNull(*head, __func__);

    if (!error)
    {
        ezutil_observer *iter = *head;
        ezutil_observer *next = 0;

        /* We know head is not null thanks to earlier error check. */
        do
        {
            next = iter->next;
            free(iter);
        }
        while (iter = next);

        free(*head);
        *head = 0;
    }

    return !error;
}



uint8_t ezutil_observer_notifyAll(ezutil_observer *head)
{
    uint8_t error = ezutil_observer_isNull(head, __func__);

    if (!error)
    {
        /* Notify everybody on the linked list. */
        do if (head->notify) head->notify(head->data);
        while (head = head->next);
    }
    
    return !error;
}



ezutil_observer* ezutil_observer_add(ezutil_observer *head,
        void (*notify)(void*), void *data)
{
    uint8_t error = ezutil_observer_isNull(head, __func__);
    ezutil_observer *self = 0;

    if (error |= !notify)
    {
        ezutil_log(MAJOR, __func__, "Notify function pointer is null.");
    }

    if (!error)
    {
        self = (ezutil_observer*) malloc(sizeof(ezutil_observer));
        self->prev = head;
        self->next = head->next;
        self->notify = notify;
        self->data = data;
        head->next = self;
    }

    return self;
}



uint8_t ezutil_observer_remove(ezutil_observer **node)
{
    uint8_t error = ezutil_observer_isNull(*node, __func__);

    if (!error)
    {
        if ((*node)->prev) (*node)->prev->next = (*node)->next;
        if ((*node)->next) (*node)->next->prev = (*node)->prev;
        free(*node);
    }
    
    return !error;
}



uint8_t ezutil_observer_isNull(ezutil_observer *node, const char *caller)
{
    uint8_t error = 0;

    if (error |= !node)
    {
        ezutil_log(MAJOR, caller, "Observer node paramter is null.");
    }

    return error;
}
