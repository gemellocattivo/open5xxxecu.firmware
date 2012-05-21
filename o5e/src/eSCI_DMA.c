/*********************************************************************************

        @file   eSCI_DMA.c                                                              
        @author Jon Zeeff 
        @date   October 25, 2011
        @brief  Open5xxxECU - setup eSCI A to use DMA and routines to use it
        @note   See AN4147
        @version 1.1
        @copyright MIT License

*************************************************************************************/

#include "config.h"
#include "cpu.h"
#include "system.h"
#include "main.h"
#include "string.h"
#include "eSCI_DMA.h"
#include "eDMA_OPS.h"

// big enough to send/receive any tuner packet
static vuint8_t SCI_TxQ0[SERIAL_BUFFER_SIZE];
static vuint8_t SCI_RxQ0[SERIAL_BUFFER_SIZE];

void init_eSCI_DMA(void)
{
    // transmit for SCI A
    EDMA.CERQR.R = 18;          /* stop DMA on this channel */
    EDMA.TCD[18].SADDR = (uint32_t) & SCI_TxQ0; /* Load address of source data */
    EDMA.TCD[18].SSIZE = 0;     /* Read 2**0 = 1 byte per transfer */
    EDMA.TCD[18].SOFF = 1;      /* After transfer, add 1 to src addr */
    EDMA.TCD[18].SLAST = 0;     /* COUNT After major loop, reset src addr */
    EDMA.TCD[18].DADDR = (uint32_t) & ESCI_A.DR.B.D;    /* Load address of destination */
    EDMA.TCD[18].DSIZE = 0;     /* Write 2**0 = 1 byte per transfer */
    EDMA.TCD[18].DOFF = 0;      /* Do not increment destination addr */
    EDMA.TCD[18].DLAST_SGA = 0; /* After major loop, no dest addr change */
    EDMA.TCD[18].NBYTES = 1;    /* Transfer 1 byte per minor loop */
    EDMA.TCD[18].BITER = SERIAL_BUFFER_SIZE;     /* COUNT minor loop iterations */
    EDMA.TCD[18].CITER = SERIAL_BUFFER_SIZE;     /* COUNT Initialize current iteraction count */
    EDMA.TCD[18].D_REQ = 1;     /* Do disable channel when major loop is done, if 0 constant eSCI output, 1 is a single execution of the TCD */
    Zero_DMA_Channel(18);

    // receive for SCI A
    EDMA.CERQR.R = 19;          /* stop DMA on this channel */
    EDMA.TCD[19].SADDR = (uint32_t) & ESCI_A.DR.B.D;    /* Load address of source data */
    EDMA.TCD[19].SSIZE = 0;     /* Read 2**0 = 1 byte per transfer */
    EDMA.TCD[19].SOFF = 0;      /* After transfer, add 0 to src addr */
    EDMA.TCD[19].SLAST = 0;     /* After major loop, don't reset src addr */
    EDMA.TCD[19].DADDR = (uint32_t) & SCI_RxQ0; /* Load address of destination */
    EDMA.TCD[19].DSIZE = 0;     /* Write 2**0 = 1 byte per transfer */
    EDMA.TCD[19].DOFF = 1;      /* Do increment destination addr */
    EDMA.TCD[19].DLAST_SGA = 0; /* After major loop, no dest addr change */
    EDMA.TCD[19].NBYTES = 1;    /* Transfer 1 byte per minor loop */
    EDMA.TCD[19].BITER = SERIAL_BUFFER_SIZE;    /* COUNT minor loop iterations */
    EDMA.TCD[19].CITER = SERIAL_BUFFER_SIZE;    /* COUNT Initialize current iteraction count */
    EDMA.TCD[19].D_REQ = 1;     /* Disable channel when major loop is done */
    Zero_DMA_Channel(19);

    EDMA.CPR[18].R = 0x02;      // Channel 18 is Priority 3, Channel Preemption is Disabled
    EDMA.CPR[19].R = 0x03;      // Channel 19 is Priority 4, Channel Preemption is Disabled
    EDMA.CR.R = 0x0000E400;     /* Use fixed priority arbitration for DMA groups and channels */

    EDMA.EEIRL.R = 0x00000000;  // Interrupts Low channels-0-31

    EDMA.CIRQR.R = 18;          /* Clear the interrupt */
    EDMA.SERQR.R = 18;          /* Enable EDMA channel 18 */

    EDMA.CIRQR.R = 19;          /* Clear the interrupt */
    EDMA.SERQR.R = 19;          /* Enable EDMA channel 19 */

    EDMA.SSBR.R = 19;           /* Set channel 0 START bit to initiate first minor loop transfer */

}

// this routine causes the DMA controller to send count bytes out the serial port
// call write_serial_busy() before calling this

uint_fast16_t
write_serial(const uint8_t * const bytes, const uint_fast16_t count)
{
    if (count > SERIAL_BUFFER_SIZE) {   // too big - not allowed 
        system_error(25829, __FILE__, __LINE__, "");
        return 0;
    }

    if (count == 0) return 0;

    EDMA.CERQR.R = 18;          /* stop DMA on this channel */

    memcpy((void *)&SCI_TxQ0, (void *)bytes, count);    // Copy bytes to output buffer - free up callers buffer

    EDMA.TCD[18].CITER = EDMA.TCD[18].BITER = count;    // Outer loop count
    EDMA.TCD[18].SADDR = (uint32_t) & SCI_TxQ0; 	// reset Start Address to beginning of buffer
    //EDMA.TCD[18].SLAST = -count;        		// After major loop, reset src addr

    ESCI_A.SR.R = 0x80000000;   /* Clear TDRE flag */

    EDMA.SERQR.R = 18;          /* start DMA on this channel */

    return count;               // how many we wrote    

}                               // write_serial()

//  copy any bytes received from the serial port to into the callers buffer
//  return number of bytes
//  Note: the DMA transfer is "in progress"
//  TODO - check for overrun errors

#include <stdio.h>

uint_fast16_t read_serial(uint8_t * bytes, const uint_fast16_t max_bytes)
{
    uint32_t n;

    // find how many bytes we have collected 
    n = EDMA.TCD[19].DADDR - (uint32_t) & SCI_RxQ0;

    if (n > 0) {

        EDMA.CERQR.R = 19;      /* stop DMA on this channel */
        n = EDMA.TCD[19].DADDR - (uint32_t) & SCI_RxQ0; // check again

        n = min(n, max_bytes);				// allow caller to specify max, dump others

        memcpy((void *)bytes, (void *)&SCI_RxQ0, n);    // copy the bytes we have to callers buffer

        // reset everything and start again

        ESCI_A.SR.R = 0x20000000;       		/* Clear status flags */

        EDMA.TCD[19].CITER = EDMA.TCD[19].BITER = SERIAL_BUFFER_SIZE;   // Inner 'Minor' Byte Count
        EDMA.TCD[19].DADDR = (uint32_t) &SCI_RxQ0;     // reset dest Address

        EDMA.SERQR.R = 19;      /* restart DMA on this channel */

    }                           // if

    return (uint_fast16_t) n;
}

// These aren't DMA, but are similar in function to above
// read/write a string to serial port A or B
// TODO - these routines can only be used on startup - it will block!

uint_fast16_t send_serial_A(uint8_t * bytes, const uint_fast16_t length)
{
    uint_fast16_t n = length;
    while (n-- != 0) {
        while (ESCI_A.SR.B.TDRE == 0) {
        }                       /* Wait for transmit data reg empty = 1 */
        ESCI_A.SR.R = 0x80000000;       /* Clear TDRE flag */
        ESCI_A.DR.B.D = *(bytes++);     /* Transmit 8 bits Data */
    }
    return length;
}

uint_fast16_t get_serial_A(uint8_t * bytes, const uint_fast16_t length)
{
    uint_fast16_t n = length;
    while (n-- != 0) {
        while (ESCI_A.SR.B.RDRF == 0) {
        }                       /* Wait for receieve data reg = 1 */
        *(bytes++) = ESCI_A.DR.B.D;     /* Read 8 bits Data */
        ESCI_A.SR.R = 0x20000000;       /* Clear RDRF flag */
    }
    return length;
}

uint_fast16_t send_serial_B(uint8_t * bytes, const uint_fast16_t length)
{
    uint_fast16_t n = length;
    while (n-- != 0) {
        while (ESCI_B.SR.B.TDRE == 0) {
        }                       /* Wait for transmit data reg empty = 1 */
        ESCI_B.SR.R = 0x80000000;       /* Clear TDRE flag */
        ESCI_B.DR.B.D = *(bytes++);     /* Transmit 8 bits Data */
    }
    return length;
}

/****************************************************************************/

// Code to be compatible with CodeWarrior printf()

int32_t ReadUARTN(void *bytes, unsigned long limit)
{
    return read_serial(bytes, (uint_fast16_t) limit);
}

int32_t WriteUARTN(const void *bytes, unsigned long length)
{
    return send_serial_A(bytes, (uint_fast16_t) length);
}

int32_t InitializeUART(int32_t baudRate)
{
    return 0;
}

