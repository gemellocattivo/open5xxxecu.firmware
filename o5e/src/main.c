/*********************************************************************************

    @file main.c                                                              
    @date   October, 2011
    @brief  Open5xxxECU - calls init routines, creates tasks, starts scheduler to run them
    @note www.Open5xxxECU.org
    @version 1.3
    @copyright 2011 Jon Zeeff
    @warning O5E is not for use in safety critical systems or pollution controlled vehicles.

**********************************************************************************/

/*
Copyright (c) 2011 Jon Zeeff  - All Rights Reserved
Copyright (c) 2012 Sean Stasiak <sstasiak at gmail dot com>
*/

#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include "mpc563xm.h"
#include "cocoos.h"
#include "main.h"
#include "variables.h"
#include "Tuner.h"
#include "Engine_OPS.h"
#include "err.h"
#include "led.h"







static void LED_Task(void);

// Note: CocoOS allows less critical tasks to run less frequently and prevents spagetti code caused by state machines
//       Currently it uses no interrupts and no preemption.  But it does use Duff's device - so no non-static local 
//       variables in a task (elsewhere is fine).
/* classic misunderstanding above TODO: remove */

void System_Init(void);                 // init routine

/*************************************************************************************/

void main( void )
{
  err_init(); /**< get code logger abilities up asap */
    // Initialize the O5E system
    System_Init();
    // the code that we want to run repeatedly
    // Note: all tasks must "task_wait(n)" at least every 1/2 msec, preferably more often
    // CRITICAL: tasks cannot have non-static local variables and cannot use switch statements!
    /* classic misunderstanding above TODO: remove */
    
    if (Flash_OK != 0) {        // don't run these with nonsense flash values 
        (void)task_create(Engine10_Task, 0 + 128, 0, 0, 0);      // create the task
        (void)task_create(Fuel_Pump_Task, 1 + 128, 0, 0, 0);     // create the task
        (void)task_create(Slow_Vars_Task, 2 + 128, 0, 0, 0);     // create the task
        (void)task_create(Eng_Pos_Status_BLINK_Task, 3 + 128, 0, 0, 0);      //create the task 
        if (Sync_Mode_Select == 1) {   // user option to generate a cam signal
           (void)task_create(Cam_Pulse_Task, 4 + 128, 0, 0, 0);      // create the task
        }

    } 
  // #ifdef SIMULATOR ////create the task to jitter toothgen signal during testing
    	(void)task_create(Test_RPM_Task, 5 + 128, 0, 0, 0);
  // #endif
    
    (void)task_create(Tuner_Task, 6 + 128, 0, 0, 0);     // create the task
    (void)task_create(LED_Task, 7 + 128, 0, 0, 0);       // create the task 

  os_start();
}


// Task to verify that OS is running - flash a LED, feed the watchdog, feed TunerStudio

static void LED_Task(void)
{
    task_open();                // NOTE:  no non-static local variables allowed
    task_wait(410);             /**< why the wait? */

    // flash every second and feed watchdog
    for (;;) {
        /* don't even bother hitting wd here, this is the wrong way to it */
        //Feed_Watchdog();        // will reset cpu if not fed


        // DEBUG - check for DMA errors
        /* if we have DMA errors, so what ? */
        if (EDMA.ESR.R != 0)
            err_push( CODE_OLDJUNK_D5 );

        led_invert( LED1 );
        if (Last_Error == 0)
            task_wait(999);     // delay about 1 sec
        else 
            task_wait(303);     // something is wrong, blink fast
        
    }                           // for ever

    task_close();               // never reached

}                               // LED_task()
