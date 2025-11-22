/*******************************************************************************
* File Name: isr_ButtonLeft.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_ButtonLeft_H)
#define CY_ISR_isr_ButtonLeft_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_ButtonLeft_Start(void);
void isr_ButtonLeft_StartEx(cyisraddress address);
void isr_ButtonLeft_Stop(void);

CY_ISR_PROTO(isr_ButtonLeft_Interrupt);

void isr_ButtonLeft_SetVector(cyisraddress address);
cyisraddress isr_ButtonLeft_GetVector(void);

void isr_ButtonLeft_SetPriority(uint8 priority);
uint8 isr_ButtonLeft_GetPriority(void);

void isr_ButtonLeft_Enable(void);
uint8 isr_ButtonLeft_GetState(void);
void isr_ButtonLeft_Disable(void);

void isr_ButtonLeft_SetPending(void);
void isr_ButtonLeft_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_ButtonLeft ISR. */
#define isr_ButtonLeft_INTC_VECTOR            ((reg32 *) isr_ButtonLeft__INTC_VECT)

/* Address of the isr_ButtonLeft ISR priority. */
#define isr_ButtonLeft_INTC_PRIOR             ((reg8 *) isr_ButtonLeft__INTC_PRIOR_REG)

/* Priority of the isr_ButtonLeft interrupt. */
#define isr_ButtonLeft_INTC_PRIOR_NUMBER      isr_ButtonLeft__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_ButtonLeft interrupt. */
#define isr_ButtonLeft_INTC_SET_EN            ((reg32 *) isr_ButtonLeft__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_ButtonLeft interrupt. */
#define isr_ButtonLeft_INTC_CLR_EN            ((reg32 *) isr_ButtonLeft__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_ButtonLeft interrupt state to pending. */
#define isr_ButtonLeft_INTC_SET_PD            ((reg32 *) isr_ButtonLeft__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_ButtonLeft interrupt. */
#define isr_ButtonLeft_INTC_CLR_PD            ((reg32 *) isr_ButtonLeft__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_ButtonLeft_H */


/* [] END OF FILE */
