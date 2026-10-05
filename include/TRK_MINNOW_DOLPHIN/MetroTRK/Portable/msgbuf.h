#ifndef METROTRK_PORTABLE_MSGBUF_H
#define METROTRK_PORTABLE_MSGBUF_H

#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/mem_TRK.h"

inline DSError TRKAppendBuffer1_ui8(TRKBuffer* buffer, const u8 data) {
    if (buffer->position >= 0x880) {
        return DS_MessageBufferOverflow;
    }

    buffer->data[buffer->position++] = data;
    buffer->length++;
    return DS_NoError;
}

#endif /* METROTRK_PORTABLE_MSGBUF_H */
