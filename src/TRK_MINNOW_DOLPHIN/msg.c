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
    u8 byte;
    u8 csByte;
    s32 err;
    s32 i;

    checksum = 0;
    for (i = 0; i < msg->length; i++) {
        checksum = checksum + msg->data[i];
    }
    checksum = checksum ^ 0xFF;
    err = WriteUART1(0x7E);
    if (err == 0) {
        for (i = 0; i < msg->length; i++) {
            byte = msg->data[i];
            if (byte == 0x7E || byte == 0x7D) {
                err = WriteUART1(0x7D);
                byte ^= 0x20;
                if (err != 0) {
                    break;
                }
            }
            err = WriteUART1(byte);
            if (err != 0) {
                break;
            }
        }
    }
    if (err == 0) {
        csByte = checksum;
        for (i = 0; i < 1; i++) {
            if (csByte == 0x7E || csByte == 0x7D) {
                err = WriteUART1(0x7D);
                csByte ^= 0x20;
                if (err != 0) {
                    break;
                }
            }
            err = WriteUART1(csByte);
            if (err != 0) {
                break;
            }
        }
    }
    if (err == 0) {
        err = WriteUART1(0x7E);
    }
    if (err == 0) {
        err = WriteUARTFlush();
    }
    return err;
#else
    DSError writeErr = TRKWriteUARTN(&msg->data, msg->length);
    MWTRACE(1, "MessageSend : cc_write returned %ld\n", writeErr);
    return DS_NoError;
#endif
}
