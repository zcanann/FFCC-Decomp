#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/serpoll.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/nubevent.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/MWTrace.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msgbuf.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msghndlr.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk_glue.h"

/* 8044F270-8044F288 07BF90 0014+04 3/3 0/0 0/0 .bss             gTRKFramingState */
static TRKFramingState gTRKFramingState;

/* 804519B8-804519C0 000EB8 0004+04 0/0 2/2 0/0 .sbss            gTRKInputPendingPtr */
void* gTRKInputPendingPtr;

#ifdef VERSION_GCCJGC
static inline void TRKDiscardFrame(void) {
    if (gTRKFramingState.msgBufID != -1) {
        TRKReleaseBuffer(gTRKFramingState.msgBufID);
        gTRKFramingState.msgBufID = -1;
    }
    gTRKFramingState.buffer = NULL;
    gTRKFramingState.receiveState = DSRECV_Wait;
}

static inline BOOL TRKValidateFrame(TRKBuffer* buffer) {
    if (buffer->length < 2) {
        TRKStandardACK(buffer, DSMSG_ReplyNAK, DSREPLY_PacketSizeError);
        TRKDiscardFrame();
        return FALSE;
    }
    buffer->position = 0;
    buffer->length--;
    return TRUE;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x801A9EB8
 * PAL Size: 316b
 * EN Address: 0x801A8D9C
 * EN Size: 316b
 * JP Address: 0x801A489C
 * JP Size: 696b
 */
MessageBufferID TRKTestForPacket() {
#ifdef VERSION_GCCJGC
    char byte;
    DSError err = DS_NoError;
    UARTError uartErr = TRKReadUARTPoll((u8*)&byte);

    while (uartErr == UART_NoError && err == DS_NoError) {
        if (gTRKFramingState.receiveState != DSRECV_InFrame) {
            gTRKFramingState.isEscape = FALSE;
        }
        switch (gTRKFramingState.receiveState) {
        case DSRECV_Wait:
            if (byte == 0x7E) {
                err = TRKGetFreeBuffer(&gTRKFramingState.msgBufID, &gTRKFramingState.buffer);
                gTRKFramingState.checksum = 0;
                gTRKFramingState.receiveState = DSRECV_Found;
            }
            break;
        case DSRECV_Found:
            if (byte == 0x7E) {
                break;
            }
            gTRKFramingState.receiveState = DSRECV_InFrame;
        case DSRECV_InFrame:
            if (byte == 0x7E) {
                if (gTRKFramingState.isEscape) {
                    TRKStandardACK(gTRKFramingState.buffer, DSMSG_ReplyNAK, DSREPLY_EscapeError);
                    TRKDiscardFrame();
                } else {
                    if (TRKValidateFrame(gTRKFramingState.buffer)) {
                        MessageBufferID result = gTRKFramingState.msgBufID;
                        gTRKFramingState.msgBufID = -1;
                        gTRKFramingState.buffer = NULL;
                        gTRKFramingState.receiveState = DSRECV_Wait;
                        return result;
                    }
                    gTRKFramingState.receiveState = DSRECV_Wait;
                }
            } else {
                if (gTRKFramingState.isEscape) {
                    byte ^= 0x20;
                    gTRKFramingState.isEscape = FALSE;
                } else if (byte == 0x7D) {
                    gTRKFramingState.isEscape = TRUE;
                    break;
                }
                err = TRKAppendBuffer1_ui8(gTRKFramingState.buffer, byte);
                gTRKFramingState.checksum += (u8)byte;
            }
            break;
        case DSRECV_FrameOverflow:
            if (byte == 0x7E) {
                TRKDiscardFrame();
            }
            break;
        }
        uartErr = TRKReadUARTPoll((u8*)&byte);
    }
    return -1;
#else
    u8 payloadBuf[0x880];
    u8 packetBuf[0x40];
    int bufID;
    TRKBuffer* msg;
    MessageBufferID result;

    if (TRKPollUART() <= 0) {
        return -1;
    }

    result = TRKGetFreeBuffer(&bufID, &msg);

    MWTRACE(4, "TestForPacket : FreeBuffer is  %ld\n", result);

    TRKSetBufferPosition(msg, 0);
    if (TRKReadUARTN(packetBuf, 0x40) == UART_NoError) {
        int readSize;

        TRKAppendBuffer_ui8(msg, packetBuf, 0x40);
        readSize = ((u32*)packetBuf)[0] - 0x40;
        result = bufID;
        if (readSize > 0) {
            MWTRACE(1, "Reading payload %ld bytes\n", readSize);
            if (TRKReadUARTN(payloadBuf, ((u32*)packetBuf)[0] - 0x40) == UART_NoError) {
                TRKAppendBuffer_ui8(msg, payloadBuf, ((u32*)packetBuf)[0]);
            } else {
                MWTRACE(8, "TestForPacket : Invalid size of packet hdr.size\n");
                TRKReleaseBuffer(result);
                result = -1;
            }
        }
    } else {
        MWTRACE(8, "TestForPacket : Invalid size of packet\n");
        TRKReleaseBuffer(result);
        result = -1;
    }

    MWTRACE(1, "TestForPacket returning %ld\n", result);
    return result;
#endif
}

/*
 * --INFO--
 * PAL Address: 0x801A9E58
 * PAL Size: 96b
 * EN Address: 0x801A8D3C
 * EN Size: 96b
 * JP Address: 0x801A4804
 * JP Size: 152b
 */
void TRKGetInput(void) {
#ifdef VERSION_GCCJGC
    TRKBuffer* buffer;
#endif
    MessageBufferID id = TRKTestForPacket();
    if (id != -1) {
#ifdef VERSION_GCCJGC
        u8 command;
        buffer = TRKGetBuffer(id);
        TRKSetBufferPosition(buffer, 0);
        TRKReadBuffer1_ui8(buffer, &command);
        if (command < DSMSG_ReplyACK) {
            TRKEvent event;
            TRKConstructEvent(&event, NUBEVENT_Request);
            event.msgBufID = id;
            gTRKFramingState.msgBufID = -1;
            TRKPostEvent(&event);
        } else {
            TRKReleaseBuffer(id);
        }
#else
        TRKEvent event;
        TRKGetBuffer(id);
        TRKConstructEvent(&event, NUBEVENT_Request);
        event.msgBufID = id;
        gTRKFramingState.msgBufID = -1;
        TRKPostEvent(&event);
#endif
    }
}

/* 8036D924-8036D974 368264 0050+00 0/0 1/1 0/0 .text            TRKProcessInput */
void TRKProcessInput(int bufferIdx) {
    TRKEvent event;

    TRKConstructEvent(&event, NUBEVENT_Request);
    event.msgBufID = bufferIdx;
    gTRKFramingState.msgBufID = -1;
    TRKPostEvent(&event);
}

/*
 * --INFO--
 * PAL Address: 0x801A9D44
 * PAL Size: 196b
 * EN Address: 0x801A8C28
 * EN Size: 196b
 * JP Address: 0x801A4790
 * JP Size: 36b
 */
DSError TRKInitializeSerialHandler() {
    gTRKFramingState.msgBufID = -1;
    gTRKFramingState.receiveState = DSRECV_Wait;
    gTRKFramingState.isEscape = FALSE;

#ifndef VERSION_GCCJGC
    MWTRACE(1, "TRK_Packet_Header \t    %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_ReadMemory     %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_WriteMemory    %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_Connect \t    %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_ReplyAck\t    %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_ReadRegisters\t%ld bytes\n", 0x40);
#endif

    return DS_NoError;
}

/* 8036D858-8036D860 368198 0008+00 0/0 1/1 0/0 .text            TRKTerminateSerialHandler */
DSError TRKTerminateSerialHandler(void) {
    return DS_NoError;
}
