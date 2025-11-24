/*******************************************************************************
* File Name: PWM_YELLOW_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_YELLOW.h"

static PWM_YELLOW_backupStruct PWM_YELLOW_backup;


/*******************************************************************************
* Function Name: PWM_YELLOW_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_YELLOW_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_YELLOW_SaveConfig(void) 
{

    #if(!PWM_YELLOW_UsingFixedFunction)
        #if(!PWM_YELLOW_PWMModeIsCenterAligned)
            PWM_YELLOW_backup.PWMPeriod = PWM_YELLOW_ReadPeriod();
        #endif /* (!PWM_YELLOW_PWMModeIsCenterAligned) */
        PWM_YELLOW_backup.PWMUdb = PWM_YELLOW_ReadCounter();
        #if (PWM_YELLOW_UseStatus)
            PWM_YELLOW_backup.InterruptMaskValue = PWM_YELLOW_STATUS_MASK;
        #endif /* (PWM_YELLOW_UseStatus) */

        #if(PWM_YELLOW_DeadBandMode == PWM_YELLOW__B_PWM__DBM_256_CLOCKS || \
            PWM_YELLOW_DeadBandMode == PWM_YELLOW__B_PWM__DBM_2_4_CLOCKS)
            PWM_YELLOW_backup.PWMdeadBandValue = PWM_YELLOW_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_YELLOW_KillModeMinTime)
             PWM_YELLOW_backup.PWMKillCounterPeriod = PWM_YELLOW_ReadKillTime();
        #endif /* (PWM_YELLOW_KillModeMinTime) */

        #if(PWM_YELLOW_UseControl)
            PWM_YELLOW_backup.PWMControlRegister = PWM_YELLOW_ReadControlRegister();
        #endif /* (PWM_YELLOW_UseControl) */
    #endif  /* (!PWM_YELLOW_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_YELLOW_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_YELLOW_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_YELLOW_RestoreConfig(void) 
{
        #if(!PWM_YELLOW_UsingFixedFunction)
            #if(!PWM_YELLOW_PWMModeIsCenterAligned)
                PWM_YELLOW_WritePeriod(PWM_YELLOW_backup.PWMPeriod);
            #endif /* (!PWM_YELLOW_PWMModeIsCenterAligned) */

            PWM_YELLOW_WriteCounter(PWM_YELLOW_backup.PWMUdb);

            #if (PWM_YELLOW_UseStatus)
                PWM_YELLOW_STATUS_MASK = PWM_YELLOW_backup.InterruptMaskValue;
            #endif /* (PWM_YELLOW_UseStatus) */

            #if(PWM_YELLOW_DeadBandMode == PWM_YELLOW__B_PWM__DBM_256_CLOCKS || \
                PWM_YELLOW_DeadBandMode == PWM_YELLOW__B_PWM__DBM_2_4_CLOCKS)
                PWM_YELLOW_WriteDeadTime(PWM_YELLOW_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_YELLOW_KillModeMinTime)
                PWM_YELLOW_WriteKillTime(PWM_YELLOW_backup.PWMKillCounterPeriod);
            #endif /* (PWM_YELLOW_KillModeMinTime) */

            #if(PWM_YELLOW_UseControl)
                PWM_YELLOW_WriteControlRegister(PWM_YELLOW_backup.PWMControlRegister);
            #endif /* (PWM_YELLOW_UseControl) */
        #endif  /* (!PWM_YELLOW_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_YELLOW_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_YELLOW_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_YELLOW_Sleep(void) 
{
    #if(PWM_YELLOW_UseControl)
        if(PWM_YELLOW_CTRL_ENABLE == (PWM_YELLOW_CONTROL & PWM_YELLOW_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_YELLOW_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_YELLOW_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_YELLOW_UseControl) */

    /* Stop component */
    PWM_YELLOW_Stop();

    /* Save registers configuration */
    PWM_YELLOW_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_YELLOW_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_YELLOW_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_YELLOW_Wakeup(void) 
{
     /* Restore registers values */
    PWM_YELLOW_RestoreConfig();

    if(PWM_YELLOW_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_YELLOW_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
