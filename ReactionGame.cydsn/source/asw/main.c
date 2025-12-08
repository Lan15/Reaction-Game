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
#include <stdlib.h>
#include "project.h"
#include "global.h"

#include "button.h"
#include "led.h"
#include "seven.h"
#include "tft.h"
#include "UART_LOG.h"

#include "ReactionGame.h"
#include "ArcadianLight.h"
#include "TimingAnalyzer.h"

//#define CyclicTask

int main()
{
    // Enable global interrupts.
    CyGlobalIntEnable; 
    
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
    
    // Start Operating System
    for(;;) 
    {
    	StartOS(OSDEFAULTAPPMODE);
    }
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_init)
{
    //Init MCAL Drivers   
    SEVEN_Init();
    UART_LOG_Start(); 
    TFT_init();
    TFT_setBacklight(255);
    LED_Init();
    
    RG_init();
    TA_init(); // CySysTick causes issues with OS's cnt_systick
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
     
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the cyclic alarms 
    #ifdef CyclicTask
    SetRelAlarm(alrm_Tick1m,1,1);
    #endif
    SetRelAlarm(alrm_arcadian,2,1); //10

    //Activate all extended and the background task
    ActivateTask(tsk_game);
    ActivateTask(tsk_tft);
    ActivateTask(tsk_background);

    TerminateTask();
}

TASK(tsk_game)
{
    RC_t res = RC_SUCCESS;
    
    EventMaskType ev = 0;
    
    // Upon start up
    UART_LOG_PutString("\r\n\r\n============ Welcome to the Reaction Game ============\r\npress one of the two buttons to start...\r\n\r\n");
    
    while (1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_buttonLeft | ev_buttonRight | ev_timeout | ev_randomDone);
        GetEvent(tsk_game, &ev);
        ClearEvent(ev);       
        // Optional: Translate RTOS events into enum events queue - Change of data type
        /*GAME_event myEvent;
        if(ev & ev_Button_1){
            myEvent = GAME_EV_BUTTON_1;
        }*/
        res = RG_gameStateMachine(ev);
    }
    
    //Just in Case
	TerminateTask();
}

#ifdef CyclicTask

TASK(tsk_timer) 
{
    //Random-Wait Countdown (1–3 seconds random delay)
    randomTimeCheck();

    //Reaction Timeout Countdown
    timeoutCheck();
    
    TerminateTask();
}
#endif

TASK(tsk_arcadian)
{
    RC_t res = RC_SUCCESS;
    
    res = AL_fader(1, 2);
    
    res = AL_glower(1, 3);
    
    TerminateTask();
}

TASK(tsk_tft) //use set event
{    
    RG_displayTft();
    
    TerminateTask();
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

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

ISR2(isr_button)
{      
    if (BUTTON_IsPressed(BUTTON_LEFT)) { //Button left is button 1 and in case of 2 in 7 segment disaplay
        SetEvent(tsk_game, ev_buttonLeft);
    } else if (BUTTON_IsPressed(BUTTON_RIGHT)) { //Button right is button 2 and in case of 1 in 7 segment disaplay
        SetEvent(tsk_game, ev_buttonRight);
    }
}

/* [main.c] END OF FILE */
