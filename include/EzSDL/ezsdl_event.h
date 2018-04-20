/** @file       ezsdl_event.h
 *  @brief      A linked list event system.
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

#ifndef EZSDL_EVENT_H
#define EZSDL_EVENT_H

#ifdef __cplusplus
extern "C"
{
#endif



#include <stdint.h>



typedef struct ezsdl_window ezsdl_window;

typedef struct ezsdl_event_node
{
    struct ezsdl_event_node    *prev;
    struct ezsdl_event_node    *next;
    void                      (*notify)(ezsdl_window *window);
}
ezsdl_event_node;



uint8_t             ezsdl_event_notifyAll(ezsdl_window *window);
ezsdl_event_node*   ezsdl_event_addNode(ezsdl_window *window,
                                        void (*notify)(ezsdl_window*));
uint8_t             ezsdl_event_removeNode(ezsdl_event_node *node);



#ifdef __cplusplus
}
#endif

#endif /* EZSDL_EVENT_H */
