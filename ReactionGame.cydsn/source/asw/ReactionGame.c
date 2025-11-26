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
#define RG_TIMEOUT_TIME_MS     (1000UL)

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
static TA_t analyzerGame;
volatile static RG_t game = {RG_STATE_WAIT, 0, 0, 0};

volatile static uint16_t ra_g_rndWait_ms = 0;          // random delay until number appears
volatile static uint16_t ra_g_reactionTimeout_ms = 0;  // max allowed reaction time
volatile static uint8_t ra_g_correctPress = 0;         // correct button pressed count
volatile static uint8_t ra_g_tftScore = 0;             // score in tft

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/********************************************************************************
 * API Definitions
 ********************************************************************************/

RC_t gameStateMachine(EventMaskType ev)
{
    RC_t res = RC_SUCCESS;
    
    TA_create((TA_t *)&analyzerGame, TA_MODE_DWT, NULL_PTR, "Game Analyzer"); // do it here or where ???
    
    switch(game.rg_curState)
    {
        case RG_STATE_IDLE: // what to do ???
        break;
        case RG_STATE_WAIT:
            if (ev & ev_buttonLeft || ev & ev_buttonRight)
            { //C //(N1)
                // Generate random wait time. 1000 – 3000 ms
                GetResource(res_rnd);
                ra_g_rndWait_ms = (rand() % 2000) + 1000;
                ReleaseResource(res_rnd);
                
                #ifdef OneShotAlarmNoCyclicTask
                //rndWait_ms = (rand() % 2000) + 1000;
                //SetRelAlarm(alrm_Tick1m, rndWait_ms, 0); // (N6)
                #endif
            } //S
        break;
        case RG_STATE_DISPLAY:
            if (ev & ev_randomDone)
            {
                // Show generatated random number on display
                SEVEN_writeRandom(); // audio ???
                
                game.rg_roundPlayed++;
                
                GetResource(res_out);
                ra_g_reactionTimeout_ms = RG_TIMEOUT_TIME_MS;
                ReleaseResource(res_out);
                #ifdef OneShotAlarmNoCyclicTask
                //SetRelAlarm(alrm_Tick1m, ra_g_reactionTimeout_ms, 0); // (N7)
                #endif
                
                game.rg_curState = RG_STATE_PRESSED;
                
                TA_start((TA_t *)&analyzerGame);  
            }//S
        break;
        case RG_STATE_PRESSED: 
            //C
            if (ev & ev_buttonLeft) // (N5)
            {
                TA_stop((TA_t *)&analyzerGame);
                
                // Handle button 1 press
                if (SEVEN_reg_Read() == 91) //(N2)
                { 
                    UART_LOG_PutString("Great - correct button pressed!\r\n");
                    
                    char buffer[60]; 
                    snprintf(buffer, sizeof(buffer), "Reaction time in ms: %u\r\n", TA_getElapsedTimeInMs(&analyzerGame));
                    UART_LOG_PutString(buffer);
                    
                    ra_g_correctPress++;
                    game.rg_score++;
                } else
                {
                    UART_LOG_PutString("Oops - wrong button pressed!\r\n");
                }
            } 
            if (ev & ev_buttonRight) 
            {
                TA_stop((TA_t *)&analyzerGame);
                
                // Handle button 2 press
                if (SEVEN_reg_Read() == 6) // (N3)
                {   
                    UART_LOG_PutString("Great - correct button pressed!\r\n");
                    
                    char buffer[60]; 
                    snprintf(buffer, sizeof(buffer), "Reaction time in ms: %u\r\n", TA_getElapsedTimeInMs(&analyzerGame));
                    UART_LOG_PutString(buffer);
                    
                    ra_g_correctPress++;
                    game.rg_score++;
                } else
                {
                    UART_LOG_PutString("Oops - wrong button pressed!\r\n");
                }
            }
            if (ev & ev_timeout)
            {
                TA_stop((TA_t *)&analyzerGame);
                
                // Handle timeout
                UART_LOG_PutString("\nToo slow!\r\n");
            }
            
            game.rg_totalTime += TA_getElapsedTimeInMs(&analyzerGame);
            analyzerGame.elapsed_time = 0;
            
            SEVEN_ClearAll();
            
            UART_LOG_PutString("======================================================\r\n");
            
            // Print the scoure after 1 game (10 rounds)
            if (RG_MAX_ROUNDS == game.rg_roundPlayed)
            {
                game.rg_roundPlayed = 0;
                
                uint32_t avg_time = game.rg_totalTime / ra_g_correctPress;

                char buffer[70];
                snprintf(buffer, sizeof(buffer), "Score: %u | Total Time: %ums | Avg Time: %ums\r\n", game.rg_score, game.rg_totalTime, avg_time);
                UART_LOG_PutString(buffer);
                
                UART_LOG_PutString("======================================================\r\n");
                
                ra_g_tftScore = game.rg_score;
                //SetRelAlarm(alrm_tft,1,0); //(N4)
            } 
            
            game.rg_curState = RG_STATE_WAIT;
        break;
        default:
            // do nothing
        break;
    }
    return res;
}

RC_t randomTimeCheck(void)
{
    RC_t res = RC_SUCCESS;
    
    if (ra_g_rndWait_ms > 0)
    {
        GetResource(res_rnd);
        ra_g_rndWait_ms--;
        ReleaseResource(res_rnd);
        
        if (ra_g_rndWait_ms == 0)
        {//C
            game.rg_curState = RG_STATE_DISPLAY;
            
            //Signal to tsk_Game that random delay has ended
            SetEvent(tsk_game, ev_randomDone);  // set event inside function is ok ???  
        }
    }
    return res;
}

RC_t timeoutCheck(void)
{
    RC_t res = RC_SUCCESS;

    if (ra_g_reactionTimeout_ms > 0)
    {
        GetResource(res_out);
        ra_g_reactionTimeout_ms--;
        ReleaseResource(res_out);
        
        if (ra_g_reactionTimeout_ms == 0)
        {//C
            //Signal to tsk_Game that the user failed to react in time
            SetEvent(tsk_game, ev_timeout);
        }
    }
    return res;
}

/* NOTE
 * 
 * 1. //C cancel and //S set 1ms timer alaram incase of the timer has highest priority
 *
 * 2. deci 91 = hex 5B = bin 0101 1011 = seven segment 2
 * 
 * 3. deci 6 = hex 6 = bin 0110 0000 = seven segment 1
 * 
 * 4. According to OSEK we should not use activatetask() insaide another task but alarm introduces overhat.
 * 
 * 5. Keep it seperate else wrong button press also will be counted.
 * 
 * 6. In OS config, the alarm will trigger the tsk_game with ev_randomDone.
 * 
 * 7. In OS config, the alarm will trigger the tsk_game with ev_timeout.
 *
 */

/* [ReactionGame.c] END OF FILE */