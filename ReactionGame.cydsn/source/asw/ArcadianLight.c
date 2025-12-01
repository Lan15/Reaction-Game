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

/*RC_t AL_fader(void)
{
    RC_t res = RC_SUCCESS;
    for (int phase = 0; phase < 4*256; phase++) 
    {
        uint16_t value = phase % 256;
        if (phase < 256) {
            LED_PWM_Set(value, 0, 0);               // RED in
        } else if (phase < 512) {
            LED_PWM_Set((255 - value), value, 0);   // RED out YELLOW in
        } else if (phase < 768) {
            LED_PWM_Set(0, (255 - value), value);   // YELLOW out GREEN in
        } else {
            LED_PWM_Set(0, 0, value);               // GREEN out
        }
        CyDelay(1);
    }
    return res;
}*/

RC_t AL_fader(uint16_t tickTime_ms, uint16_t reactionTime_ms)
{
    RC_t res = RC_SUCCESS;

    static uint32_t tickCounter = 0;
    static uint32_t phase = 0;
    static uint32_t modulo = 1;
    
    /* Compute update rate once */
    static uint8_t init = 0;
    if (!init)
    {
        modulo = reactionTime_ms / tickTime_ms;
        if (modulo == 0)
        {
            modulo = 1;
        }
        init = 1;
    }
    
    /* Count ticks */
    tickCounter++;

    /* Update output only every <modulo> calls */
    if ((tickCounter % modulo) != 0)
    {
        return res;
    }

    uint8_t value = phase % 256;

    if (phase < 256) {
        LED_PWM_Set(value, 0, 0);
    }
    else if (phase < 512) {
        LED_PWM_Set(255 - value, value, 0);
    }
    else if (phase < 768) {
        LED_PWM_Set(0, 255 - value, value);
    }
    else {
        LED_PWM_Set(0, 0, 255 - value);
    }
    /* Move to next fade step (reactionTime now actually controls this!) */
    phase++;

    if (phase >= 1024)
        phase = 0;

    return res;
}

RC_t AL_glower(void)
{
    RC_t res = RC_SUCCESS;

    for (uint8_t i = 0; i < (sizeof(RG_glowtable) / sizeof(RG_Glow_t)); ++i)
    {
        LED_RGB_Set(RG_glowtable[i].al_red, RG_glowtable[i].al_green, RG_glowtable[i].al_blue);
        CyDelay(RG_glowtable[i].al_duration);
    }
    return res;
}

/* [ArcadianLight.c] END OF FILE */
