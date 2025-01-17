
/****************************************************************
 * WARNING this file is automatically generated DO NOT EDIT IT! *
 *                                                              *
 * FILE NAME: etpu_spwm_auto.h     COPYRIGHT (c) Freescale 2005 *
 *                                      All Rights Reserved     *
 * This file generated by:                                      *
 * $RCSfile: etpuc_spwm.c,v $ $Revision: 1.11 $
 *                                                              *
 * This file provides an interface between eTPU code and CPU    *
 * code. All references to the SPWM function should be made     *
 * withinformation in this file. This allows only symbolic      *
 * information to be referenced which allows the eTPU code to   *
 * be optimized without effecting the CPU code.                 *
 ****************************************************************/
#ifndef _ETPU_SPWM_AUTO_H_
#define _ETPU_SPWM_AUTO_H_

/* Function Configuration Information */
#define FS_ETPU_SPWM_FUNCTION_NUMBER  7 
#define FS_ETPU_SPWM_TABLE_SELECT 1 
#define FS_ETPU_SPWM_NUM_PARMS 0x0030 

/* Host Service Request Definitions */
#define FS_ETPU_SPWM_INIT_MASTER 7 
#define FS_ETPU_SPWM_INIT_SLAVE 5 

/* Function Mode Bit Definitions - polarity options */
#define FS_ETPU_SPWM_USE_TCR1 0  << 1 
#define FS_ETPU_SPWM_USE_TCR2 1  << 1 
/* INT_DMA_on_falling_edge options */
#define FS_ETPU_SPWM_NO_FALLING_EDGE_INT_DMA 0   
#define FS_ETPU_SPWM_FALLING_EDGE_INT_DMA 1   

/* Parameter Definitions */
#define FS_ETPU_SPWM_PERIOD_OFFSET  0x0001
#define FS_ETPU_SPWM_ACTIVE_OFFSET  0x0005
#define FS_ETPU_SPWM_REF_PTR_OFFSET  0x0009
#define FS_ETPU_SPWM_DELAY_OFFSET  0x000D
#define FS_ETPU_SPWM_LINK1_OFFSET  0x0010
#define FS_ETPU_SPWM_LINK2_OFFSET  0x0014
#define FS_ETPU_SPWM_MASTERRISINGEDGEPTR  0x001D
#define FS_ETPU_SPWM_REF_MODE  0x0000
#define FS_ETPU_SPWM_REFERENCE  0x0021

/* This parameter is not host modifable but the address is exported so the slave can reference it*/
#define FS_ETPU_SPWM_RISING_OFFSET  0x0019

/* reference_mode options */
#define FS_ETPU_SPWM_IMMEDIATE 0 
#define FS_ETPU_SPWM_REF_IN_PRAM 1 

#endif /* _ETPU_SPWM_AUTO_H_ */

