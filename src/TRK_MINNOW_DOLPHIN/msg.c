/**
 * msg.c
 * Description:
 */

#include "PowerPC_EABI_Support/MetroTRK/trk.h"

/* 8036CFD8-8036D01C 367918 0044+00 0/0 6/6 0/0 .text            TRKMessageSend */
DSError TRKMessageSend(TRKBuffer* msg) {
    DSError writeErr = TRKWriteUARTN(&msg->data, msg->length);
    MWTRACE(1, "MessageSend : cc_write returned %ld\n", writeErr);
    return DS_NoError;
}
