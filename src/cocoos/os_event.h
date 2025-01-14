/*
 * Copyright (c) 2012 Peter Eckstrand
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 * GRANTED BY THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the cocoOS operating system.
 * Author: Peter Eckstrand <info@cocoos.net>
 */
 
/***************************************************************************************


    Change log:
    2009-07-06: 1.0.0 First release
    2010-10-12: New event type definition
	2011-12-17: Implemented support for timeout when waiting for single event
    2012-01-04: Released under BSD license.


***************************************************************************************
*/
#ifndef OS_EVENT_H
#define OS_EVENT_H

/** @file os_event.h Event header file*/

#include "cocoos.h"
#include "stdarg.h"




#define OS_WAIT_SINGLE_EVENT(x,timeout)	do {\
								os_wait_event(running_tid,x,1,timeout);\
								OS_SCHEDULE;\
							   } while (0)






#define OS_WAIT_MULTIPLE_EVENTS( waitAll, args...)	do {\
								os_wait_multiple(waitAll, args, NO_EVENT);\
								OS_SCHEDULE;\
							   } while (0)






#define OS_SIGNAL_EVENT(event)	do {\
								os_signal_event(event);\
								os_event_set_signaling_tid( event, running_tid );\
								OS_SCHEDULE;\
								} while (0)




#define OS_INT_SIGNAL_EVENT(event)	do {\
									os_signal_event(event);\
									} while (0)


#ifdef N_TOTAL_EVENTS
    #define EVENT_QUEUE_SIZE    ((N_TOTAL_EVENTS/9)+1)
#else
    #define EVENT_QUEUE_SIZE    1
#endif


typedef uint8_t Evt_t;

typedef struct {
    uint8_t eventList[ EVENT_QUEUE_SIZE ];
} EventQueue_t;



void os_wait_event( uint8_t tid, Evt_t ev, uint8_t waitSingleEvent, uint16_t timeout );
void os_wait_multiple( uint8_t waitAll, ...);
void os_signal_event( Evt_t ev );
void os_event_set_signaling_tid( Evt_t ev, uint8_t tid );



#endif
