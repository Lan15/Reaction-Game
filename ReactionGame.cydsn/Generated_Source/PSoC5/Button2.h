/*******************************************************************************
* File Name: Button2.h  
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

#if !defined(CY_PINS_Button2_H) /* Pins Button2_H */
#define CY_PINS_Button2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Button2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Button2__PORT == 15 && ((Button2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Button2_Write(uint8 value);
void    Button2_SetDriveMode(uint8 mode);
uint8   Button2_ReadDataReg(void);
uint8   Button2_Read(void);
void    Button2_SetInterruptMode(uint16 position, uint16 mode);
uint8   Button2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Button2_SetDriveMode() function.
     *  @{
     */
        #define Button2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Button2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Button2_DM_RES_UP          PIN_DM_RES_UP
        #define Button2_DM_RES_DWN         PIN_DM_RES_DWN
        #define Button2_DM_OD_LO           PIN_DM_OD_LO
        #define Button2_DM_OD_HI           PIN_DM_OD_HI
        #define Button2_DM_STRONG          PIN_DM_STRONG
        #define Button2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Button2_MASK               Button2__MASK
#define Button2_SHIFT              Button2__SHIFT
#define Button2_WIDTH              1u

/* Interrupt constants */
#if defined(Button2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Button2_SetInterruptMode() function.
     *  @{
     */
        #define Button2_INTR_NONE      (uint16)(0x0000u)
        #define Button2_INTR_RISING    (uint16)(0x0001u)
        #define Button2_INTR_FALLING   (uint16)(0x0002u)
        #define Button2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Button2_INTR_MASK      (0x01u) 
#endif /* (Button2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button2_PS                     (* (reg8 *) Button2__PS)
/* Data Register */
#define Button2_DR                     (* (reg8 *) Button2__DR)
/* Port Number */
#define Button2_PRT_NUM                (* (reg8 *) Button2__PRT) 
/* Connect to Analog Globals */                                                  
#define Button2_AG                     (* (reg8 *) Button2__AG)                       
/* Analog MUX bux enable */
#define Button2_AMUX                   (* (reg8 *) Button2__AMUX) 
/* Bidirectional Enable */                                                        
#define Button2_BIE                    (* (reg8 *) Button2__BIE)
/* Bit-mask for Aliased Register Access */
#define Button2_BIT_MASK               (* (reg8 *) Button2__BIT_MASK)
/* Bypass Enable */
#define Button2_BYP                    (* (reg8 *) Button2__BYP)
/* Port wide control signals */                                                   
#define Button2_CTL                    (* (reg8 *) Button2__CTL)
/* Drive Modes */
#define Button2_DM0                    (* (reg8 *) Button2__DM0) 
#define Button2_DM1                    (* (reg8 *) Button2__DM1)
#define Button2_DM2                    (* (reg8 *) Button2__DM2) 
/* Input Buffer Disable Override */
#define Button2_INP_DIS                (* (reg8 *) Button2__INP_DIS)
/* LCD Common or Segment Drive */
#define Button2_LCD_COM_SEG            (* (reg8 *) Button2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Button2_LCD_EN                 (* (reg8 *) Button2__LCD_EN)
/* Slew Rate Control */
#define Button2_SLW                    (* (reg8 *) Button2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Button2_PRTDSI__CAPS_SEL       (* (reg8 *) Button2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Button2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Button2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Button2_PRTDSI__OE_SEL0        (* (reg8 *) Button2__PRTDSI__OE_SEL0) 
#define Button2_PRTDSI__OE_SEL1        (* (reg8 *) Button2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Button2_PRTDSI__OUT_SEL0       (* (reg8 *) Button2__PRTDSI__OUT_SEL0) 
#define Button2_PRTDSI__OUT_SEL1       (* (reg8 *) Button2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Button2_PRTDSI__SYNC_OUT       (* (reg8 *) Button2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Button2__SIO_CFG)
    #define Button2_SIO_HYST_EN        (* (reg8 *) Button2__SIO_HYST_EN)
    #define Button2_SIO_REG_HIFREQ     (* (reg8 *) Button2__SIO_REG_HIFREQ)
    #define Button2_SIO_CFG            (* (reg8 *) Button2__SIO_CFG)
    #define Button2_SIO_DIFF           (* (reg8 *) Button2__SIO_DIFF)
#endif /* (Button2__SIO_CFG) */

/* Interrupt Registers */
#if defined(Button2__INTSTAT)
    #define Button2_INTSTAT            (* (reg8 *) Button2__INTSTAT)
    #define Button2_SNAP               (* (reg8 *) Button2__SNAP)
    
	#define Button2_0_INTTYPE_REG 		(* (reg8 *) Button2__0__INTTYPE)
#endif /* (Button2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Button2_H */


/* [] END OF FILE */
