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
 * Task Definitions
 ********************************************************************************/

/*TASK(tsk_fader)
{
    for (int phase = 0; phase < 4*256; phase++) 
    {
        int value = phase % 256;
        if (phase < 256) {
            PWM_RED_WriteCompare(value);            // RED in
        } else if (phase < 512) {
            PWM_RED_WriteCompare(255 - value);      // RED out
            PWM_YELLOW_WriteCompare(value);         // YELLOW in
        } else if (phase < 768) {
            PWM_YELLOW_WriteCompare(255 - value);   // YELLOW out
            PWM_GREEN_WriteCompare(value);          // GREEN in
        } else {
            PWM_GREEN_WriteCompare(255 - value);    // GREEN out
        }
        CyDelay(1);
    }
    
    TerminateTask();
}*/

void fader(void)
{
    static uint16_t phase = 0;
    uint8_t value = phase & 0xFF;

    // ----- Continuous RGB cycle -----
    if (phase < 256) {
        PWM_RED_WriteCompare(value);              // Red fades in
    }
    else if (phase < 512) {
        PWM_RED_WriteCompare(255 - value);        // Red fades out
        PWM_YELLOW_WriteCompare(value);           // Yellow fades in
    }
    else if (phase < 768) {
        PWM_YELLOW_WriteCompare(255 - value);     // Yellow fades out
        PWM_GREEN_WriteCompare(value);            // Green fades in
    }
    else {
        PWM_GREEN_WriteCompare(255 - value);      // Green fades out
    }

    phase++;
    if (phase >= 1024)
        phase = 0;     // Restart continuous cycle
}

TASK(tsk_glower)
{
    
    for (uint8_t i = 0; i < (sizeof(RG_glowtable) / sizeof(RG_Glow_t)); ++i)
    {
        PWM_RGB_RED_WriteCompare(RG_glowtable[i].al_red);
        PWM_RGB_GREEN_WriteCompare(RG_glowtable[i].al_green);
        PWM_RGB_BLUE_WriteCompare(RG_glowtable[i].al_blue);
        CyDelay(RG_glowtable[i].al_duration);
    }
    
    TerminateTask();
}

/* [ArcadianLight.c] END OF FILE */
