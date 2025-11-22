/*******************************************************************************
* File Name: ButtonRight.h  
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

#if !defined(CY_PINS_ButtonRight_H) /* Pins ButtonRight_H */
#define CY_PINS_ButtonRight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ButtonRight_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ButtonRight__PORT == 15 && ((ButtonRight__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ButtonRight_Write(uint8 value);
void    ButtonRight_SetDriveMode(uint8 mode);
uint8   ButtonRight_ReadDataReg(void);
uint8   ButtonRight_Read(void);
void    ButtonRight_SetInterruptMode(uint16 position, uint16 mode);
uint8   ButtonRight_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ButtonRight_SetDriveMode() function.
     *  @{
     */
        #define ButtonRight_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ButtonRight_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ButtonRight_DM_RES_UP          PIN_DM_RES_UP
        #define ButtonRight_DM_RES_DWN         PIN_DM_RES_DWN
        #define ButtonRight_DM_OD_LO           PIN_DM_OD_LO
        #define ButtonRight_DM_OD_HI           PIN_DM_OD_HI
        #define ButtonRight_DM_STRONG          PIN_DM_STRONG
        #define ButtonRight_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ButtonRight_MASK               ButtonRight__MASK
#define ButtonRight_SHIFT              ButtonRight__SHIFT
#define ButtonRight_WIDTH              1u

/* Interrupt constants */
#if defined(ButtonRight__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ButtonRight_SetInterruptMode() function.
     *  @{
     */
        #define ButtonRight_INTR_NONE      (uint16)(0x0000u)
        #define ButtonRight_INTR_RISING    (uint16)(0x0001u)
        #define ButtonRight_INTR_FALLING   (uint16)(0x0002u)
        #define ButtonRight_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ButtonRight_INTR_MASK      (0x01u) 
#endif /* (ButtonRight__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ButtonRight_PS                     (* (reg8 *) ButtonRight__PS)
/* Data Register */
#define ButtonRight_DR                     (* (reg8 *) ButtonRight__DR)
/* Port Number */
#define ButtonRight_PRT_NUM                (* (reg8 *) ButtonRight__PRT) 
/* Connect to Analog Globals */                                                  
#define ButtonRight_AG                     (* (reg8 *) ButtonRight__AG)                       
/* Analog MUX bux enable */
#define ButtonRight_AMUX                   (* (reg8 *) ButtonRight__AMUX) 
/* Bidirectional Enable */                                                        
#define ButtonRight_BIE                    (* (reg8 *) ButtonRight__BIE)
/* Bit-mask for Aliased Register Access */
#define ButtonRight_BIT_MASK               (* (reg8 *) ButtonRight__BIT_MASK)
/* Bypass Enable */
#define ButtonRight_BYP                    (* (reg8 *) ButtonRight__BYP)
/* Port wide control signals */                                                   
#define ButtonRight_CTL                    (* (reg8 *) ButtonRight__CTL)
/* Drive Modes */
#define ButtonRight_DM0                    (* (reg8 *) ButtonRight__DM0) 
#define ButtonRight_DM1                    (* (reg8 *) ButtonRight__DM1)
#define ButtonRight_DM2                    (* (reg8 *) ButtonRight__DM2) 
/* Input Buffer Disable Override */
#define ButtonRight_INP_DIS                (* (reg8 *) ButtonRight__INP_DIS)
/* LCD Common or Segment Drive */
#define ButtonRight_LCD_COM_SEG            (* (reg8 *) ButtonRight__LCD_COM_SEG)
/* Enable Segment LCD */
#define ButtonRight_LCD_EN                 (* (reg8 *) ButtonRight__LCD_EN)
/* Slew Rate Control */
#define ButtonRight_SLW                    (* (reg8 *) ButtonRight__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ButtonRight_PRTDSI__CAPS_SEL       (* (reg8 *) ButtonRight__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ButtonRight_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ButtonRight__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ButtonRight_PRTDSI__OE_SEL0        (* (reg8 *) ButtonRight__PRTDSI__OE_SEL0) 
#define ButtonRight_PRTDSI__OE_SEL1        (* (reg8 *) ButtonRight__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ButtonRight_PRTDSI__OUT_SEL0       (* (reg8 *) ButtonRight__PRTDSI__OUT_SEL0) 
#define ButtonRight_PRTDSI__OUT_SEL1       (* (reg8 *) ButtonRight__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ButtonRight_PRTDSI__SYNC_OUT       (* (reg8 *) ButtonRight__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ButtonRight__SIO_CFG)
    #define ButtonRight_SIO_HYST_EN        (* (reg8 *) ButtonRight__SIO_HYST_EN)
    #define ButtonRight_SIO_REG_HIFREQ     (* (reg8 *) ButtonRight__SIO_REG_HIFREQ)
    #define ButtonRight_SIO_CFG            (* (reg8 *) ButtonRight__SIO_CFG)
    #define ButtonRight_SIO_DIFF           (* (reg8 *) ButtonRight__SIO_DIFF)
#endif /* (ButtonRight__SIO_CFG) */

/* Interrupt Registers */
#if defined(ButtonRight__INTSTAT)
    #define ButtonRight_INTSTAT            (* (reg8 *) ButtonRight__INTSTAT)
    #define ButtonRight_SNAP               (* (reg8 *) ButtonRight__SNAP)
    
	#define ButtonRight_0_INTTYPE_REG 		(* (reg8 *) ButtonRight__0__INTTYPE)
#endif /* (ButtonRight__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ButtonRight_H */


/* [] END OF FILE */
