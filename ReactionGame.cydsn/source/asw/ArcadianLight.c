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
#define AL_TOTAL_GLOW_DURATION      (2100UL)
#define AL_GLOW_REACTION_SCALE      (1000UL)

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
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

RC_t AL_fader(uint16_t tickTime_ms, uint16_t reactionTime_ms) //(N1)
{
    if (0 == tickTime_ms && 0 == reactionTime_ms)
    {
        return RC_ERROR_BAD_PARAM;
    }
    
    if (!AL_isFaderTickDue(tickTime_ms, reactionTime_ms)) // TimeToAdvance, IsStepDue
    {
        return RC_SUCCESS;
    }
    
    uint8_t red = 0, yellow = 0, green = 0;
    
    AL_calculateIntensity(&red, &yellow, &green);

    LED_PWM_Set(red, yellow, green);

    return RC_SUCCESS;
}

boolean_t AL_isFaderTickDue(uint16_t tickTime_ms, uint16_t reactionTime_ms)
{
    // static - saved individually for this function
    static uint32_t tickCounter = 0;

    if (0 == (tickTime_ms == 0 || reactionTime_ms))
    {
        return TRUE;  // fail-safe: always update
    }
        
    // Compute modulo
    uint32_t modulo = reactionTime_ms / tickTime_ms;
    
    if (modulo == 0)
    {
        modulo = 1;
    }
        
    // Increase tick and check if update is allowed now
    return ((++tickCounter % modulo) == 0);
}

RC_t AL_calculateIntensity(uint8_t* red, uint8_t* yellow, uint8_t* green)
{
    static uint32_t phase = 0;
    
    //Compute local fade value
    uint8_t value = phase & 0xFF;   // same as % 256 but faster

    // Phase region (0–1023): fade logic
    switch (phase >> 8)       // divide by 256 using bit-shift
    {
        case 0: 
            *red = value;            // 0–255          
        break;                  
        case 1: 
            *red = 255 - value;      // 256–511
            *yellow = value; 
        break;                
        case 2: 
            *yellow = 255 - value;   // 512–767
            *green = value; 
        break;                
        default:
            *green = 255 - value;    // 768–1023        
        break;                
    }

    //Advance fade position
    if (++phase >= 1024)
    {
        phase = 0;
    }
    
    return RC_SUCCESS;
}

RC_t AL_glower(uint16_t tickTime_ms, uint16_t reactionTime_ms) // (N2)
{
    if (tickTime_ms == 0 || reactionTime_ms == 0)
    {
        return RC_ERROR_BAD_PARAM;
    }

    // Compute effective reaction time with internal scaling
    uint32_t effectiveReaction = (uint32_t)reactionTime_ms * AL_GLOW_REACTION_SCALE;

    // Get total number of glow steps
    uint32_t totalSteps = sizeof(RG_glowtable) / sizeof(RG_Glow_t);

    // Advance step (tick counting + step advancement) and get current step
    uint32_t currentStep = AL_updateGlowStep(effectiveReaction, tickTime_ms, totalSteps);

    // Apply RGB values
    LED_RGB_Set(RG_glowtable[currentStep].al_red,
                RG_glowtable[currentStep].al_green,
                RG_glowtable[currentStep].al_blue);

    return RC_SUCCESS;
}

uint32_t AL_updateGlowStep(uint32_t effectiveReaction, uint16_t tickTime_ms, uint32_t totalSteps)
{
    static uint32_t tick = 0;
    static uint32_t step = 0;

    // Compute ticks for this step
    uint32_t stepTicks = (RG_glowtable[step].al_duration * effectiveReaction) / AL_TOTAL_GLOW_DURATION / tickTime_ms;
    
    if (stepTicks == 0)
    {
        stepTicks = 1;
    }

    // Tick counting
    tick++;
    if (tick >= stepTicks)
    {
        tick = 0;
        step = (step + 1) % totalSteps;
    }

    return step;
}


/* NOTE
 * 
 * 1. reactionTime controls how fast phase increments. Smaller reactionTime - phase increments faster and viceversa.
 *
 * 2. reactionTime determines the total runtime of the whole/entire glow sequence.
 * 
 * 3. 
 * 
 * 4. 
*/
/* [ArcadianLight.c] END OF FILE */
