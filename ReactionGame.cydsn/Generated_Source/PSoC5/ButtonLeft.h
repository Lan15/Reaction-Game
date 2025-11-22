/*******************************************************************************
* File Name: ButtonLeft.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ButtonLeft_H) /* Pins ButtonLeft_H */
#define CY_PINS_ButtonLeft_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ButtonLeft_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ButtonLeft__PORT == 15 && ((ButtonLeft__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ButtonLeft_Write(uint8 value);
void    ButtonLeft_SetDriveMode(uint8 mode);
uint8   ButtonLeft_ReadDataReg(void);
uint8   ButtonLeft_Read(void);
void    ButtonLeft_SetInterruptMode(uint16 position, uint16 mode);
uint8   ButtonLeft_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ButtonLeft_SetDriveMode() function.
     *  @{
     */
        #define ButtonLeft_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ButtonLeft_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ButtonLeft_DM_RES_UP          PIN_DM_RES_UP
        #define ButtonLeft_DM_RES_DWN         PIN_DM_RES_DWN
        #define ButtonLeft_DM_OD_LO           PIN_DM_OD_LO
        #define ButtonLeft_DM_OD_HI           PIN_DM_OD_HI
        #define ButtonLeft_DM_STRONG          PIN_DM_STRONG
        #define ButtonLeft_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ButtonLeft_MASK               ButtonLeft__MASK
#define ButtonLeft_SHIFT              ButtonLeft__SHIFT
#define ButtonLeft_WIDTH              1u

/* Interrupt constants */
#if defined(ButtonLeft__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ButtonLeft_SetInterruptMode() function.
     *  @{
     */
        #define ButtonLeft_INTR_NONE      (uint16)(0x0000u)
        #define ButtonLeft_INTR_RISING    (uint16)(0x0001u)
        #define ButtonLeft_INTR_FALLING   (uint16)(0x0002u)
        #define ButtonLeft_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ButtonLeft_INTR_MASK      (0x01u) 
#endif /* (ButtonLeft__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ButtonLeft_PS                     (* (reg8 *) ButtonLeft__PS)
/* Data Register */
#define ButtonLeft_DR                     (* (reg8 *) ButtonLeft__DR)
/* Port Number */
#define ButtonLeft_PRT_NUM                (* (reg8 *) ButtonLeft__PRT) 
/* Connect to Analog Globals */                                                  
#define ButtonLeft_AG                     (* (reg8 *) ButtonLeft__AG)                       
/* Analog MUX bux enable */
#define ButtonLeft_AMUX                   (* (reg8 *) ButtonLeft__AMUX) 
/* Bidirectional Enable */                                                        
#define ButtonLeft_BIE                    (* (reg8 *) ButtonLeft__BIE)
/* Bit-mask for Aliased Register Access */
#define ButtonLeft_BIT_MASK               (* (reg8 *) ButtonLeft__BIT_MASK)
/* Bypass Enable */
#define ButtonLeft_BYP                    (* (reg8 *) ButtonLeft__BYP)
/* Port wide control signals */                                                   
#define ButtonLeft_CTL                    (* (reg8 *) ButtonLeft__CTL)
/* Drive Modes */
#define ButtonLeft_DM0                    (* (reg8 *) ButtonLeft__DM0) 
#define ButtonLeft_DM1                    (* (reg8 *) ButtonLeft__DM1)
#define ButtonLeft_DM2                    (* (reg8 *) ButtonLeft__DM2) 
/* Input Buffer Disable Override */
#define ButtonLeft_INP_DIS                (* (reg8 *) ButtonLeft__INP_DIS)
/* LCD Common or Segment Drive */
#define ButtonLeft_LCD_COM_SEG            (* (reg8 *) ButtonLeft__LCD_COM_SEG)
/* Enable Segment LCD */
#define ButtonLeft_LCD_EN                 (* (reg8 *) ButtonLeft__LCD_EN)
/* Slew Rate Control */
#define ButtonLeft_SLW                    (* (reg8 *) ButtonLeft__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ButtonLeft_PRTDSI__CAPS_SEL       (* (reg8 *) ButtonLeft__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ButtonLeft_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ButtonLeft__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ButtonLeft_PRTDSI__OE_SEL0        (* (reg8 *) ButtonLeft__PRTDSI__OE_SEL0) 
#define ButtonLeft_PRTDSI__OE_SEL1        (* (reg8 *) ButtonLeft__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ButtonLeft_PRTDSI__OUT_SEL0       (* (reg8 *) ButtonLeft__PRTDSI__OUT_SEL0) 
#define ButtonLeft_PRTDSI__OUT_SEL1       (* (reg8 *) ButtonLeft__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ButtonLeft_PRTDSI__SYNC_OUT       (* (reg8 *) ButtonLeft__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ButtonLeft__SIO_CFG)
    #define ButtonLeft_SIO_HYST_EN        (* (reg8 *) ButtonLeft__SIO_HYST_EN)
    #define ButtonLeft_SIO_REG_HIFREQ     (* (reg8 *) ButtonLeft__SIO_REG_HIFREQ)
    #define ButtonLeft_SIO_CFG            (* (reg8 *) ButtonLeft__SIO_CFG)
    #define ButtonLeft_SIO_DIFF           (* (reg8 *) ButtonLeft__SIO_DIFF)
#endif /* (ButtonLeft__SIO_CFG) */

/* Interrupt Registers */
#if defined(ButtonLeft__INTSTAT)
    #define ButtonLeft_INTSTAT            (* (reg8 *) ButtonLeft__INTSTAT)
    #define ButtonLeft_SNAP               (* (reg8 *) ButtonLeft__SNAP)
    
	#define ButtonLeft_0_INTTYPE_REG 		(* (reg8 *) ButtonLeft__0__INTTYPE)
#endif /* (ButtonLeft__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ButtonLeft_H */


/* [] END OF FILE */
