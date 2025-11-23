/**
* \file <ReactionGame.c>
* \author <AGILAN V S>
* \date <26-11-2025>
*
* \brief <Symbolic File name>   // ???
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "project.h"
#include "global.h"

#include "seven.h"
//#include "pins.h"
#include "tft.h"
#include "UART_LOG.h"

#include "ReactionGame.h"
#include "TimingAnalyzer.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/ 
#define RG_MAX_ROUNDS          (10UL)


/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
volatile static TA_t analyzer;
volatile static RG_t game = {RG_STATE_WAIT, 0, 0, 0};

volatile static uint16_t ra_g_rndWait_ms = 0;          // random delay until number appears
volatile static uint16_t ra_g_reactionTimeout_ms = 0;  // max allowed reaction time
volatile static uint8_t ra_g_buttonNumber = 0;         // correct button number
volatile static uint8_t ra_g_tftScore = 0;             // score in tft

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_game)
{
    EventMaskType ev = 0;

    // Upon start up
    UART_LOG_PutString("\r\n\r\n============ Welcome to the Reaction Game ============\r\n"); 
    SetRelAlarm(alrm_tft,110,0); // one shot alarm
    
    while (1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_buttonLeft | ev_buttonRight | ev_timeout | ev_randomDone);  // evaluate based on eventys or state ???
        GetEvent(tsk_game, &ev);
        ClearEvent(ev);
        //UART_LOG_PutString("event\r\n");         

        switch(game.m_curState) // extra while for SM ???
        {
            case RG_STATE_IDLE: 
            break;
            case RG_STATE_WAIT: // TODO: handle button comming during wait time ???
                CancelAlarm(alrm_Tick1m);
                //UART_LOG_PutString("wait\r\n"); 
                //Generate random wait time
                ra_g_rndWait_ms = (rand() % 2000) + 1000;  // 1000 – 3000 ms
                //rndWait_ms = (rand() % 2000) + 1000; // single shot alaram instead of global var, reduction ???
                //SetRelAlarm(alrm_Tick1m, rndWait_ms, 0);
                SetRelAlarm(alrm_Tick1m,1,1);
            break;
            case RG_STATE_DISPLAY:
                if (ev & ev_randomDone)
                {
                    //Show random number on display
                    SEVEN_writeRandom(); // Ok or a seperate task ???
                    game.m_roundPlayed++;
                    ra_g_reactionTimeout_ms = 1000;
                    game.m_curState = RG_STATE_PRESSED;
                    SetRelAlarm(alrm_Tick1m,1,1);
                }
            break;
            case RG_STATE_PRESSED: 
                //UART_LOG_PutString("ingame\r\n"); 
                CancelAlarm(alrm_Tick1m);
                if (ev & ev_buttonLeft)
                {
                    //Handle button 1 press
                    UART_LOG_PutString("BUTT\r\n"); 
                    if (SEVEN_reg_Read() == 91) { // deci 91 = hex 5B = bin 0101 1011 = seven segment 2
                        //uint32_t time_ms = (analyzer.elapsed_time / BCLK__BUS_CLK__KHZ); //calculate here ???
                        //Buffer to assemble string
                        //char buffer[150]; 
                        
                        //Send string to UART
                        UART_LOG_PutString("Great - correct button pressed!\r\n");
                        //snprintf(buffer, sizeof(buffer), "Reaction time in ms: %u\r\n", time_ms);
                        //UART_LOG_PutString(buffer);
                        game.m_score++;
                    } else
                    {
                        UART_LOG_PutString("Oops - wrong button pressed!\r\n");
                    }
                } 
                if (ev & ev_buttonRight)
                {
                    //Handle button 2 press
                    if (SEVEN_reg_Read() == 6)
                    { // deci 6 = hex 6 = bin 0110 0000 = seven segment 1
                        //uint32_t time_ms = analyzer.elapsed_time;
                        //Buffer to assemble string
                        //char buffer[150]; 
                        
                        //Send string to UART
                        UART_LOG_PutString("Great - correct button pressed!\r\n");
                        //snprintf(buffer, sizeof(buffer), "Reaction time in ms: %u\r\n", time_ms);
                        //UART_LOG_PutString(buffer);
                        game.m_score++;
                    } else
                    {
                        UART_LOG_PutString("Oops - wrong button pressed!\r\n");
                    }
                }
                if (ev & ev_timeout)
                {
                    //Handle timeout
                    UART_LOG_PutString("Too slow!\r\n");    // log or func ???
                    //game.m_curState = RG_STATE_IDLE;
                }
                
                SEVEN_ClearAll();
                
                game.m_curState = RG_STATE_WAIT;
                
                UART_LOG_PutString("======================================================\r\n");
                // One game consists out of 10 rounds - END - consider as a seperate state ???
                
                if (RG_MAX_ROUNDS == game.m_roundPlayed)
                {
                    game.m_roundPlayed = 0;
                    /* Print for the rounds played */
                    char buffer[50];
                    sprintf(buffer, "Score: %d\r\n", game.m_score);
                    UART_LOG_PutString(buffer);
                    UART_LOG_PutString("======================================================\r\n");
                    ra_g_tftScore = game.m_score;
                    TFT_clearScreen();
                    SetRelAlarm(alrm_tft,110,0); // one shot alarm
                }
                
            break;
            default:
                // do nothing
            break;
        }
    }
    
    //Just in Case
	TerminateTask();
}

TASK(tsk_timer) // Keep this taks execution time below cycle time ???
{
    //Random-Wait Countdown (1–3 seconds random delay)
    if (ra_g_rndWait_ms > 0)
    {
        ra_g_rndWait_ms--;
        
        if (ra_g_rndWait_ms == 0)
        {
            CancelAlarm(alrm_Tick1m);
            UART_LOG_PutString("rndwait\r\n"); 
            game.m_curState = RG_STATE_DISPLAY;
            //Signal to tsk_Game that random delay has ended
            SetEvent(tsk_game, ev_randomDone);        
        }
    }

    //Reaction Timeout Countdown
    if (ra_g_reactionTimeout_ms > 0)
    {
        ra_g_reactionTimeout_ms--;
        
        if (ra_g_reactionTimeout_ms == 0)
        {
            CancelAlarm(alrm_Tick1m);
            //User failed to react in time
            SetEvent(tsk_game, ev_timeout);
        }
    }
    
    TerminateTask();
}

TASK(tsk_tft)
{
    if(!game.m_score)
    {
        TFT_clearScreen();
        
        TFT_setCursor(17, 60);
        TFT_setTextSize(2);
        TFT_setTextColor(RED);
        TFT_print("REACTION\n");
        TFT_setCursor(40, 80);
        TFT_setTextColor(BLUE);
        TFT_print("GAME\n");
    }
    
    if(game.m_score){ // If score is atleaset 1
        TFT_setCursor(18, 70);
        TFT_setTextSize(2);
        TFT_setTextColor(YELLOW);
        
        TFT_drawRect(12, 65, 105, 24, WHITE);
        
        char buffer[16];
        sprintf(buffer, "SCORE:%d", ra_g_tftScore);
        TFT_print(buffer);
        
        TFT_drawChar(55, 30, 2, YELLOW, 0, 4);
    }
    
    TerminateTask();
}

/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

ISR2(isr_button)
{   
    if (ButtonLeft_Read() == 1) { //Button left is button 1 and in case of 2
        SetEvent(tsk_game, ev_buttonLeft);
    } else if (ButtonRight_Read() == 1) { //Button right is button 2 and in case of 1
        SetEvent(tsk_game, ev_buttonRight);
    }
}

/* NOTE
 * 
 * 1. 
 *
 * 2. 
 *
 */

/* [ReactionGame.c] END OF FILE */