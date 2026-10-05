/**
 * msg.c
 * Description:
 */

#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.h"

/*
 * --INFO--
 * PAL Address: 0x801A94BC
 * PAL Size: 68b
 * EN Address: 0x801A83A0
 * EN Size: 68b
 * JP Address: 0x801A39D0
 * JP Size: 476b
 */
DSError TRKMessageSend(TRKBuffer* msg) {
#ifdef VERSION_GCCJGC
    u8 checksum;
    int i;
    UARTError err;
    {
        u8 sum = 0;
        int j;
        for (j = 0; j < msg->length; j++) {
            sum = (u8)(sum + msg->data[j]);
        }
        checksum = sum ^ 0xFF;
    }
    err = WriteUART1(0x7E);
    if (err == UART_NoError) {
        for (i = 0; i < msg->length; i++) {
            u8 byte = msg->data[i];
            if (byte == 0x7E || byte == 0x7D) {
                err = WriteUART1(0x7D);
                byte ^= 0x20;
                if (err != UART_NoError) {
                    break;
                }
            }
            err = WriteUART1(byte);
            if (err != UART_NoError) {
                break;
            }
        }
    }
    if (err == UART_NoError) {
        u8 byte = checksum;
        do {
            if (byte == 0x7E || byte == 0x7D) {
                err = WriteUART1(0x7D);
                byte ^= 0x20;
                if (err != UART_NoError) {
                    break;
                }
            }
            err = WriteUART1(byte);
            if (err != UART_NoError) {
                break;
            }
        } while (FALSE);
    }
    if (err == UART_NoError) {
        err = WriteUART1(0x7E);
    }
    if (err == UART_NoError) {
        err = WriteUARTFlush();
    }
    return err;
#else
    DSError writeErr = TRKWriteUARTN(&msg->data, msg->length);
    MWTRACE(1, "MessageSend : cc_write returned %ld\n", writeErr);
    return DS_NoError;
#endif
}
