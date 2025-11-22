/*******************************************************************************
* File Name: ButtonLeft.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ButtonLeft_ALIASES_H) /* Pins ButtonLeft_ALIASES_H */
#define CY_PINS_ButtonLeft_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define ButtonLeft_0			(ButtonLeft__0__PC)
#define ButtonLeft_0_INTR	((uint16)((uint16)0x0001u << ButtonLeft__0__SHIFT))

#define ButtonLeft_INTR_ALL	 ((uint16)(ButtonLeft_0_INTR))

#endif /* End Pins ButtonLeft_ALIASES_H */


/* [] END OF FILE */
