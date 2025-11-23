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

#include "seven.h"
//#include "pins.h"
#include "tft.h"
#include "UART_LOG.h"

#include "ReactionGame.h"
#include "TimingAnalyzer.h"

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
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
    
    //TA_init(); 
    
    //TA_create((TA_t *)&analyzer, TA_MODE_DWT, RED_LED_Write, " Main Game Analyzer");
    
    //RG_init((RG_t *)&game);
      
    //UART_LOG_PutString("press one of the two buttons to start...\r\n"); 
    //TFT_print("press one of the two buttons to start...\n");
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
     
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the cyclic alarms 
    SetRelAlarm(alrm_Tick1m,100,1);

    //Activate all extended and the background task
    ActivateTask(tsk_game);
    ActivateTask(tsk_background);

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

/* [main.c] END OF FILE */
