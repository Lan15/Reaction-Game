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
#include "project.h"
#include "global.h"
#include "led.h"

#include "ArcadianLight.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/ 

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/
const RG_Glow_t RG_glowtable[] = {
    //Red Green Blue TimeInMS
    {255, 0, 0, 500},
    {0, 255, 0, 500},
    {0, 0, 255, 500},
    {0, 0, 0, 100},
    {255, 255, 255, 100},
    {0, 0, 0, 100},
    {255, 255, 255, 100},
    {0, 0, 0, 100},
    {255, 255, 255, 100}
};

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/ 

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/********************************************************************************
 * API Definitions
 ********************************************************************************/

RC_t AL_fader(uint16_t tickTime_ms, uint16_t reactionTime_ms)
{
    static uint32_t tickCounter = 0;
    static uint32_t phase = 0;

    if (0 == tickTime_ms && 0 == reactionTime_ms)
    {
        return RC_ERROR_BAD_PARAM;
    }

    /* Compute update rate every call (safe and simple) */
    uint32_t modulo = reactionTime_ms / tickTime_ms;
    
    if (modulo == 0)
    {
        modulo = 1;
    }
    
    /* Tick counting + update control */
    if (++tickCounter % modulo != 0)
    {
        return RC_SUCCESS;
    }
    
    /* Compute local fade value */
    uint8_t value = phase & 0xFF;        // same as % 256 but faster

    uint8_t r = 0, g = 0, b = 0;

    /* Phase region (0–1023): fade logic */
    switch (phase >> 8)       // divide by 256 using bit-shift
    {
        case 0: 
            r = value;                
        break;                  // 0–255
        case 1: 
            r = 255 - value; g = value; 
        break;                // 256–511
        case 2: 
            g = 255 - value; b = value; 
        break;                // 512–767
        default:
            b = 255 - value;            
        break;                // 768–1023
    }

    LED_PWM_Set(r, g, b);

    /* Advance fade position */
    if (++phase >= 1024)
        phase = 0;

    return RC_SUCCESS;
}

RC_t AL_glower(uint16_t tickTime_ms, uint16_t reactionTime_ms) //TODO: work on tuning
{
    static uint32_t tickCounter = 0;
    static uint32_t step = 0;
    static uint32_t modulo = 1;

    if (0 == tickTime_ms && 0 == reactionTime_ms)
    {
        return RC_ERROR_BAD_PARAM;
    }
    
    /* Initialize update rate once */
    static uint8_t init = 0;
    if (!init)
    {
        modulo = (RG_glowtable[step].al_duration + tickTime_ms - 1) / tickTime_ms; // ceil
        if (modulo == 0) modulo = 1;
        init = 1;
    }

    /* Tick counting + update control */
    if (++tickCounter % modulo != 0)
        return RC_SUCCESS;

    /* Set RGB values for current step */
    LED_RGB_Set(RG_glowtable[step].al_red,
                RG_glowtable[step].al_green,
                RG_glowtable[step].al_blue);

    /* Advance to next step */
    step++;
    if (step >= (sizeof(RG_glowtable) / sizeof(RG_Glow_t)))
        step = 0;  // Loop back to start

    /* Update modulo for the new step */
    modulo = (RG_glowtable[step].al_duration + tickTime_ms - 1) / tickTime_ms; // ceil
    if (modulo == 0) modulo = 1;

    return RC_SUCCESS;
}


/* [ArcadianLight.c] END OF FILE */
