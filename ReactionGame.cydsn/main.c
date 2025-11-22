/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "global.h"

#include "button.h"
#include "led.h"
#include "seven.h"

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_init)
{
    
    //Init MCAL Drivers
    LED_Init();
    SEVEN_Init();
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the alarm with 100ms cycle time
    SetRelAlarm(alarm_ledBlink,100,100);
 
    ActivateTask(tsk_sevenSet);
    ActivateTask(tsk_background);
    
    TerminateTask();
    
}


TASK(tsk_ledBlink)
{
    static uint8_t counter = 0;
    
    //After 10 calls == 1s fire the 1s event to the sevenSet task
    counter++;
    if (10 == counter)
    {
        counter = 0;
        SetEvent(tsk_sevenSet, ev_1s);
    }
    
    
    LED_Toggle(LED_ALL);
    TerminateTask();
    
}

TASK(tsk_sevenSet)
{
 
    static uint8_t count = 0;
    
    EventMaskType ev = 0;
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_1s | ev_reset);
        GetEvent(tsk_sevenSet,&ev);
        ClearEvent(ev);
        
        if (ev & ev_1s)
        {
            SEVEN_SetHex(++count);
        }

        if (ev & ev_reset)
        {
            count = 0;
            SEVEN_SetHex(count);
        }

        
    }
}

TASK(tsk_background)
{
    while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

ISR2(isr_Button)
{
    SetEvent(tsk_sevenSet,ev_reset);   
}
/* [] END OF FILE */
