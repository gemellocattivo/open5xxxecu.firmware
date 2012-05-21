

/****************************************************************/
/* WARNING this file is automatically generated DO NOT EDIT IT! */
/*                                                              */
/* This file provides an interface between eTPU code and CPU    */
/* code. All references to the UART_FC function should be made with*/
/* information in this file. This allows only symbolic          */
/* information to be referenced which allows the eTPU code to be*/
/* optimized without effecting the CPU code.                    */
/****************************************************************/
#ifndef _ETPU_UART_FC_AUTO_H_
#define _ETPU_UART_FC_AUTO_H_

/* Function Configuration Information */
#define FS_ETPU_UART_FC_FUNCTION_NUMBER 10 
#define FS_ETPU_UART_FC_TABLE_SELECT 1 
#define FS_ETPU_UART_FC_NUM_PARMS 0x0010 

/* Host Service Request Definitions */
#define FS_ETPU_UART_FC_TX_INIT 7 
#define FS_ETPU_UART_FC_RX_INIT 2
#define FS_ETPU_UART_FC_RTS_INIT 2
#define FS_ETPU_UART_FC_READ_DATA 4

/* Function Mode Bit Definitions - polarity options */
#define FS_ETPU_UART_FC_NO_PARITY 0 
#define FS_ETPU_UART_FC_EVEN_PARITY 0  + 2 
#define FS_ETPU_UART_FC_ODD_PARITY 1  + 2 

/* Parameter Definitions */
#define FS_ETPU_UART_FC_MATCH_RATE_OFFSET  0x0001
#define FS_ETPU_UART_FC_TX_RX_DATA_OFFSET  0x0009
#define FS_ETPU_UART_FC_BITS_PER_WORD_OFFSET  0x000C
#define FS_ETPU_UART_FC_ACTUAL_BIT_COUNT_OFFSET  0x0000
#define FS_ETPU_UART_FC_SHIFT_REG_OFFSET  0x0005
#define FS_ETPU_UART_FC_PARITY_TEMP_OFFSET  0x0004
#define FS_ETPU_UART_FC_RX_ERROR_OFFSET  0x0008

#endif

