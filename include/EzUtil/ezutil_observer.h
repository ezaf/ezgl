/** @file       ezutil_observer.h
 *  @brief      Observer design pattern using a linked list.
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

#ifndef EZUTIL_OBSERVER_H
#define EZUTIL_OBSERVER_H

#ifdef __cplusplus
extern "C"
{
#endif



#include <stdint.h>



typedef struct ezutil_observer
{
    struct ezutil_observer     *prev;
    struct ezutil_observer     *next;
    void                      (*notify)(void*);
    void                       *data;
}
ezutil_observer;



ezutil_observer*    ezutil_observer_new();
uint8_t             ezutil_observer_del(ezutil_observer **head);

uint8_t             ezutil_observer_notifyAll(ezutil_observer *head);
ezutil_observer*    ezutil_observer_add(ezutil_observer *head,
                                        void (*notify)(void*), void *data);
uint8_t             ezutil_observer_remove(ezutil_observer **node);



#ifdef __cplusplus
}
#endif

#endif /* EZUTIL_OBSERVER_H */
