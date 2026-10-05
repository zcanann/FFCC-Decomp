#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msghndlr.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msgbuf.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/nubevent.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/MWTrace.h"
#include "PowerPC_EABI_Support/MetroTRK/trk.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk.h"
#ifdef VERSION_GCCJGC
#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"
#endif
#include <string.h>

/* 8044F288-8044F290 07BFA8 0004+04 4/4 0/0 0/0 .bss             IsTRKConnected */
static BOOL IsTRKConnected;

/* 8036ECDC-8036ED84 36961C 00A8+00 0/0 1/1 0/0 .text            OutputData */
void OutputData(void* data, int length) {
    // u8 byte;
    int i;
    u8* datapointer = data;

    for (i = 0; i < length; i++) {
        MWTRACE(8, "%02x ", datapointer[i]);
        if (i % 16 == 15) {
            MWTRACE(8, "\n");
        }
    }

    MWTRACE(8, "\n");
}

/* 8036ECCC-8036ECDC 36960C 0010+00 0/0 3/3 0/0 .text            GetTRKConnected */
BOOL GetTRKConnected(void) {
    return IsTRKConnected;
}

/* 8036ECC0-8036ECCC 369600 000C+00 0/0 1/1 0/0 .text            SetTRKConnected */
void SetTRKConnected(BOOL isTRKConnected) {
    IsTRKConnected = isTRKConnected;
}

#ifdef VERSION_GCCJGC
inline
#endif
DSError TRKSendACK(TRKBuffer* buffer) {
#ifdef VERSION_GCCJGC
    DSError err;
    int retries = 3;
    do {
        err = TRKMessageSend(buffer);
        retries--;
    } while (err != DS_NoError && retries > 0);
    return err;
#else
    DSError err;
    MWTRACE(1, "SendACK : Calling MessageSend\n");
    err = TRKMessageSend(buffer);
    MWTRACE(1, "MessageSend err : %ld\n", err);
    return err;
#endif
}

DSError TRKStandardACK(TRKBuffer* buffer, MessageCommandID commandID,
                              DSReplyError replyError) {
#ifdef VERSION_GCCJGC
    TRKResetBuffer(buffer, TRUE);
    TRKAppendBuffer1_ui8(buffer, commandID);
    TRKAppendBuffer1_ui8(buffer, replyError);
    return TRKSendACK(buffer);
#else
    CommandReply reply;

    memset(&reply, 0, sizeof(CommandReply));
    reply.commandID.b = commandID;
    reply._00 = 0x40;
    reply.replyError.b = replyError;
    TRKWriteUARTN(&reply, sizeof(CommandReply));
    return DS_NoError;
#endif
}

#ifdef VERSION_GCCJGC
/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: 0x801A7358
 * JP Size: 176b
 */
DSError TRKDoUnsupported(TRKBuffer* buffer) {
    return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_UnsupportedCommandError);
}
#endif

/* 8036EC5C-8036ECC0 36959C 0064+00 0/0 1/1 0/0 .text            TRKDoConnect */
DSError TRKDoConnect(TRKBuffer* buffer) {
    IsTRKConnected = TRUE;
    return TRKStandardACK(buffer, 0x80, DSREPLY_NoError);
}

/*
 * --INFO--
 * PAL Address: 0x801AB0C8
 * PAL Size: 120b
 * EN Address: 0x801A9FAC
 * EN Size: 120b
 * JP Address: 0x801A71B8
 * JP Size: 228b
 */
DSError TRKDoDisconnect(TRKBuffer* buffer) {
    TRKEvent event;

#ifdef VERSION_GCCJGC
    DSError err;

    IsTRKConnected = FALSE;
    err = TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_NoError);
    if (err == DS_NoError) {
        TRKConstructEvent(&event, 1);
        TRKPostEvent(&event);
    }
    return err;
#else
    IsTRKConnected = FALSE;
    TRKStandardACK(buffer, 0x80, DSREPLY_NoError);
    TRKConstructEvent(&event, 1);
    TRKPostEvent(&event);
    return DS_NoError;
#endif
}

/*
 * --INFO--
 * PAL Address: 0x801AB070
 * PAL Size: 88b
 * EN Address: 0x801A9F54
 * EN Size: 88b
 * JP Address: 0x801A7100
 * JP Size: 184b
 */
DSError TRKDoReset(TRKBuffer* buffer) {
    TRKStandardACK(buffer, 0x80, DSREPLY_NoError);
    __TRK_reset();
    return DS_NoError;
}

/* 8036EB34-8036EB8C 369474 0058+00 0/0 1/1 0/0 .text            TRKDoOverride */
DSError TRKDoOverride(TRKBuffer* buffer) {
    TRKStandardACK(buffer, 0x80, DSREPLY_NoError);
    __TRK_copy_vectors();
    return DS_NoError;
}

/*
 * --INFO--
 * PAL Address: 0x801AB010
 * PAL Size: 8b
 * EN Address: 0x801A9EF4
 * EN Size: 8b
 * JP Address: 0x801A6E28
 * JP Size: 728b
 */
DSError TRKDoVersions(TRKBuffer* buffer) {
#ifdef VERSION_GCCJGC
    DSError err;
    DSVersions versions;

    if (buffer->length != 1) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
    }
    TRKResetBuffer(buffer, TRUE);
    TRKAppendBuffer1_ui8(buffer, DSMSG_ReplyACK);
    TRKAppendBuffer1_ui8(buffer, DSREPLY_NoError);
    err = TRKTargetVersions(&versions);
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, versions.kernelMajor);
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, versions.kernelMinor);
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, versions.protocolMajor);
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, versions.protocolMinor);
    }
    if (err != DS_NoError) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_CWDSError);
    }
    return TRKSendACK(buffer);
#else
    return DS_NoError;
#endif
}

/*
 * --INFO--
 * PAL Address: 0x801AB008
 * PAL Size: 8b
 * EN Address: 0x801A9EEC
 * EN Size: 8b
 * JP Address: 0x801A6BF8
 * JP Size: 560b
 */
DSError TRKDoSupportMask(TRKBuffer* buffer) {
#ifdef VERSION_GCCJGC
    DSError err;
    u8 mask[32];

    if (buffer->length != 1) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
    }
    TRKResetBuffer(buffer, TRUE);
    TRKAppendBuffer1_ui8(buffer, DSMSG_ReplyACK);
    TRKAppendBuffer1_ui8(buffer, DSREPLY_NoError);
    err = TRKTargetSupportMask(mask);
    if (err == DS_NoError) {
        err = TRKAppendBuffer(buffer, mask, sizeof(mask));
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, 2);
    }
    if (err != DS_NoError) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_CWDSError);
    }
    return TRKSendACK(buffer);
#else
    return DS_NoError;
#endif
}

#ifdef VERSION_GCCJGC
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: UNUSED
 * EN Size: 8b
 * JP Address: 0x801A6860
 * JP Size: 920b
 */
DSError TRKDoCPUType(TRKBuffer* buffer) {
    DSError err;
    DSCPUType cpuType;

    if (buffer->length != 1) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
    }
    TRKResetBuffer(buffer, TRUE);
    TRKAppendBuffer1_ui8(buffer, DSMSG_ReplyACK);
    TRKAppendBuffer1_ui8(buffer, DSREPLY_NoError);
    err = TRKTargetCPUType(&cpuType);
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, cpuType.cpuMajor);
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, cpuType.cpuMinor);
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, cpuType.bigEndian);
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, cpuType.defaultTypeSize);
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, cpuType.fpTypeSize);
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, cpuType.extended1TypeSize);
    }
    if (err == DS_NoError) {
        err = TRKAppendBuffer1_ui8(buffer, cpuType.extended2TypeSize);
    }
    if (err != DS_NoError) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_CWDSError);
    }
    return TRKSendACK(buffer);
}

#endif

/*
 * --INFO--
 * PAL Address: 0x801AADC4
 * PAL Size: 580b
 * EN Address: 0x801A9CA8
 * EN Size: 580b
 * JP Address: 0x801A6450
 * JP Size: 1040b
 */
DSError TRKDoReadMemory(TRKBuffer* buffer) {
#ifdef VERSION_GCCJGC
    u8 buf[0x800];
    u32 start;
    size_t tempLength;
    u16 length;
    u8 command;
    u8 options;
    DSError result;
    DSReplyError replyErr;

    if (buffer->length != 8) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
    }
    TRKSetBufferPosition(buffer, 0);
    result = TRKReadBuffer1_ui8(buffer, &command);
    if (result == DS_NoError) {
        result = TRKReadBuffer1_ui8(buffer, &options);
    }
    if (result == DS_NoError) {
        result = TRKReadBuffer1_ui16(buffer, &length);
    }
    if (result == DS_NoError) {
        result = TRKReadBuffer1_ui32(buffer, &start);
    }
    if (options & DSMSGMEMORY_Extended) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_UnsupportedOptionError);
    }
    if (length > sizeof(buf)) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_ParameterError);
    }
    TRKResetBuffer(buffer, TRUE);
    TRKAppendBuffer1_ui8(buffer, DSMSG_ReplyACK);
    TRKAppendBuffer1_ui8(buffer, DSREPLY_NoError);
    if (result == DS_NoError) {
        tempLength = length;
        result = TRKTargetAccessMemory(buf, start, &tempLength,
                                     options & DSMSGMEMORY_Userview ? 0 : 1, TRUE);
        length = tempLength;
        if (result == DS_NoError) {
            result = TRKAppendBuffer1_ui16(buffer, length);
        }
        if (result == DS_NoError) {
            result = TRKAppendBuffer(buffer, buf, tempLength);
        }
    }

    if (result) {
        switch (result) {
        case DS_CWDSException:
            replyErr = DSREPLY_CWDSException;
            break;
        case DS_InvalidMemory:
            replyErr = DSREPLY_InvalidMemoryRange;
            break;
        case DS_InvalidProcessID:
            replyErr = DSREPLY_InvalidProcessID;
            break;
        case DS_InvalidThreadID:
            replyErr = DSREPLY_InvalidThreadID;
            break;
        case DS_OSError:
            replyErr = DSREPLY_OSError;
            break;
        default:
            replyErr = DSREPLY_CWDSError;
            break;
        }
        return TRKStandardACK(buffer, DSMSG_ReplyACK, replyErr);
    }

    return TRKSendACK(buffer);
#else
    u8 buf[0x820] __attribute__((aligned(32)));
    size_t tempLength;
    int result;
    int replyErr;
    int options;
    size_t length;
    u32 start;

    start = *(u32*)(buffer->data + 16);
    length = *(u16*)(buffer->data + 12);
    options = buffer->data[8];

    MWTRACE(1, "ReadMemory (0x%02x) : 0x%08x 0x%08x 0x%08x\n", buffer->data[4], start, length,
            options);

    if (options & DSMSGMEMORY_Extended) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_UnsupportedOptionError);
    }

    tempLength = length;

    if (options & DSMSGMEMORY_Space_data) {
        result = TRKTargetAccessARAM((u32)buf, start, &tempLength, TRUE);
    } else {
        result = TRKTargetAccessMemory(buf, start, &tempLength,
                                       options & DSMSGMEMORY_Userview ? 0 : 1, TRUE);
    }

    TRKResetBuffer(buffer, 0);

    if (result == DS_NoError) {
        CommandReply reply;
        memset(&reply, 0, sizeof(CommandReply));
        reply.replyError.b = result;
        reply._00 = tempLength + 0x40;
        reply.commandID.b = DSMSG_ReplyACK;
        TRKAppendBuffer(buffer, &reply, sizeof(CommandReply));

        if (options & 0x40) {
            result = TRKAppendBuffer(buffer, buf + (start & 0x1F), tempLength);
        } else {
            result = TRKAppendBuffer(buffer, buf, tempLength);
        }
    }

    if (result) {
        switch (result) {
        case DS_CWDSException:
            replyErr = DSREPLY_CWDSException;
            break;
        case DS_InvalidMemory:
            replyErr = DSREPLY_InvalidMemoryRange;
            break;
        case DS_InvalidProcessID:
            replyErr = DSREPLY_InvalidProcessID;
            break;
        case DS_InvalidThreadID:
            replyErr = DSREPLY_InvalidThreadID;
            break;
        case DS_OSError:
            replyErr = DSREPLY_OSError;
            break;
        default:
            replyErr = DSREPLY_CWDSError;
            break;
        }
        return TRKStandardACK(buffer, DSMSG_ReplyACK, replyErr);
    }

    return TRKSendACK(buffer);
#endif
}

/*
 * --INFO--
 * PAL Address: 0x801AAB88
 * PAL Size: 572b
 * EN Address: 0x801A9A6C
 * EN Size: 572b
 * JP Address: 0x801A6030
 * JP Size: 1056b
 */
DSError TRKDoWriteMemory(TRKBuffer* b) {
#ifdef VERSION_GCCJGC
    u8 buf[0x800];
    u32 start;
    size_t tempLength;
    u16 length;
    u8 command;
    u8 options;
    DSError result;
    DSReplyError replyErr;

    if (b->length <= 8) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
    }
    TRKSetBufferPosition(b, 0);
    result = TRKReadBuffer1_ui8(b, &command);
    if (result == DS_NoError) {
        result = TRKReadBuffer1_ui8(b, &options);
    }
    if (result == DS_NoError) {
        result = TRKReadBuffer1_ui16(b, &length);
    }
    if (result == DS_NoError) {
        result = TRKReadBuffer1_ui32(b, &start);
    }
    if (options & DSMSGMEMORY_Extended) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_UnsupportedOptionError);
    }
    if (b->length != length + 8 || length > sizeof(buf)) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_ParameterError);
    }
    if (result == DS_NoError) {
        tempLength = length;
        result = TRKReadBuffer(b, buf, tempLength);
        if (result == DS_NoError) {
            result = TRKTargetAccessMemory(buf, start, &tempLength,
                                         options & DSMSGMEMORY_Userview ? 0 : 1, FALSE);
        }
        length = tempLength;
    }
    if (result == DS_NoError) {
        TRKResetBuffer(b, TRUE);
        TRKAppendBuffer1_ui8(b, DSMSG_ReplyACK);
        TRKAppendBuffer1_ui8(b, DSREPLY_NoError);
    }
    if (result == DS_NoError) {
        result = TRKAppendBuffer1_ui16(b, length);
    }

    if (result != DS_NoError) {
        switch (result) {
        case DS_CWDSException:
            replyErr = DSREPLY_CWDSException;
            break;
        case DS_InvalidMemory:
            replyErr = DSREPLY_InvalidMemoryRange;
            break;
        case DS_InvalidProcessID:
            replyErr = DSREPLY_InvalidProcessID;
            break;
        case DS_InvalidThreadID:
            replyErr = DSREPLY_InvalidThreadID;
            break;
        case DS_OSError:
            replyErr = DSREPLY_OSError;
            break;
        default:
            replyErr = DSREPLY_CWDSError;
            break;
        }
        return TRKStandardACK(b, DSMSG_ReplyACK, replyErr);
    }

    return TRKSendACK(b);
#else
    u8 buf[0x820] __attribute__((aligned(32)));
    size_t tempLength;
    int options;
    int result;
    int replyErr;
    size_t length;
    u32 start;

    start = *(u32*)(&b->data[16]);
    length = *(u16*)(&b->data[12]);
    options = b->data[8];

    MWTRACE(1, "WriteMemory (0x%02x) : 0x%08x 0x%08x 0x%08x\n", (unsigned int)b->data[0x4], start,
            length, options);

    if (options & DSMSGMEMORY_Extended) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSMSG_ReadRegisters);
    }

    tempLength = length;

    TRKSetBufferPosition(b, DSMSGMEMORY_Space_data);
    if (options & DSMSGMEMORY_Space_data) {
        TRKReadBuffer(b, buf + (start & 0x1f), tempLength);
        result = TRKTargetAccessARAM((u32)buf, start, &tempLength, FALSE);
    } else {
        TRKReadBuffer(b, buf, tempLength);
        result = TRKTargetAccessMemory(buf, start, &tempLength,
                                       options & DSMSGMEMORY_Userview ? 0 : 1, FALSE);
    }

    TRKResetBuffer(b, 0);

    if (result == DS_NoError) {
        CommandReply reply;
        memset(&reply, 0, sizeof(CommandReply));
        reply._00 = 0x40;
        reply.commandID.b = DSMSG_ReplyACK;
        reply.replyError.b = result;
        result = TRKAppendBuffer(b, &reply, sizeof(CommandReply));
    }

    if (result != DS_NoError) {
        switch (result) {
        case DS_CWDSException:
            replyErr = DSREPLY_CWDSException;
            break;
        case DS_InvalidMemory:
            replyErr = DSREPLY_InvalidMemoryRange;
            break;
        case DS_InvalidProcessID:
            replyErr = DSREPLY_InvalidProcessID;
            break;
        case DS_InvalidThreadID:
            replyErr = DSREPLY_InvalidThreadID;
            break;
        case DS_OSError:
            replyErr = DSREPLY_OSError;
            break;
        default:
            replyErr = DSREPLY_CWDSError;
            break;
        }
        return TRKStandardACK(b, DSMSG_ReplyACK, replyErr);
    }

    return TRKSendACK(b);
#endif
}

/*
 * --INFO--
 * PAL Address: 0x801AA8A8
 * PAL Size: 736b
 * EN Address: 0x801A978C
 * EN Size: 736b
 * JP Address: 0x801A5C64
 * JP Size: 972b
 */
#ifdef VERSION_GCCJGC
DSError TRKDoReadRegisters(TRKBuffer* b) {
    DSError error;
    DSReplyError replyError;
    size_t registersLength;
    u16 firstRegister;
    u16 lastRegister;
    u8 command;
    u8 options;

    if (b->length != 6) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
    }
    TRKSetBufferPosition(b, 0);
    error = TRKReadBuffer1_ui8(b, &command);
    if (error == DS_NoError) {
        error = TRKReadBuffer1_ui8(b, &options);
    }
    if (error == DS_NoError) {
        error = TRKReadBuffer1_ui16(b, &firstRegister);
    }
    if (error == DS_NoError) {
        error = TRKReadBuffer1_ui16(b, &lastRegister);
    }
    if (firstRegister > lastRegister) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_InvalidRegisterRange);
    }
    if (error == DS_NoError) {
        TRKResetBuffer(b, TRUE);
        TRKAppendBuffer1_ui8(b, DSMSG_ReplyACK);
        TRKAppendBuffer1_ui8(b, DSREPLY_NoError);
    }
    switch (options & 7) {
    case DSREG_Default:
        error = TRKTargetAccessDefault(firstRegister, lastRegister, b, &registersLength, TRUE);
        break;
    case DSREG_FP:
        error = TRKTargetAccessFP(firstRegister, lastRegister, b, &registersLength, TRUE);
        break;
    case DSREG_Extended1:
        error = TRKTargetAccessExtended1(firstRegister, lastRegister, b, &registersLength, TRUE);
        break;
    case DSREG_Extended2:
        error = TRKTargetAccessExtended2(firstRegister, lastRegister, b, &registersLength, TRUE);
        break;
    default:
        error = DS_UnsupportedError;
        break;
    }

    // Check if there was an error, and respond accordingly
    if (error != DS_NoError) {
        switch (error) {
        case DS_UnsupportedError:
            replyError = DSREPLY_UnsupportedOptionError;
            break;
        case DS_InvalidRegister:
            replyError = DSREPLY_InvalidRegisterRange;
            break;
        case DS_CWDSException:
            replyError = DSREPLY_CWDSException;
            break;
        case DS_InvalidProcessID:
            replyError = DSREPLY_InvalidProcessID;
            break;
        case DS_InvalidThreadID:
            replyError = DSREPLY_InvalidThreadID;
            break;
        case DS_OSError:
            replyError = DSREPLY_OSError;
            break;
        default:
            replyError = DSREPLY_CWDSError;
        }

        return TRKStandardACK(b, DSMSG_ReplyACK, replyError);
    } else {
        // No error, send ack
        return TRKSendACK(b);
    }
}
#else
DSError TRKDoReadRegisters(TRKBuffer* b) {
    int error;
    u8 options;
    u16 firstRegister;
    u16 lastRegister;
    size_t registersLength;
    CommandReply local_50;

    options = b->data[8];
    firstRegister = *(u16*)(b->data + 12);
    lastRegister = *(u16*)(b->data + 16);

    if (firstRegister > lastRegister) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_InvalidRegisterRange);
    }

    local_50.commandID.b = DSMSG_ReplyACK;
    local_50._00 = 0x468;

    TRKResetBuffer(b, 0);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", b->length);

    TRKAppendBuffer_ui8(b, (u8*)&local_50, sizeof(CommandReply));
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", b->length);

    error = TRKTargetAccessDefault(0, 36, b, &registersLength, TRUE);
    MWTRACE(4, "DoReadRegisters : Error reading  default regs 0x%08x\n", error);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", b->length);

    if (error == DS_NoError) {
        error = TRKTargetAccessFP(0, 33, b, &registersLength, TRUE);
    }
    MWTRACE(4, "DoReadRegisters : Error FP regs 0x%08x\n", error);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", b->length);
    if (error == DS_NoError) {
        error = TRKTargetAccessExtended1(0, 0x60, b, &registersLength, TRUE);
    }
    MWTRACE(4, "DoReadRegisters : Error extended1 regs 0x%08x\n", error);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", b->length);
    if (error == DS_NoError) {
        error = TRKTargetAccessExtended2(0, 31, b, &registersLength, TRUE);
    }
    MWTRACE(4, "DoReadRegisters : Error extended2 regs 0x%08x\n", error);
    MWTRACE(4, "DoReadRegisters : Buffer length 0x%08x\n", b->length);

    // Check if there was an error, and respond accordingly
    if (error != DS_NoError) {
        int replyError;
        switch (error) {
        case DS_UnsupportedError:
            replyError = DSREPLY_UnsupportedOptionError;
            break;
        case DS_InvalidRegister:
            replyError = DSREPLY_InvalidRegisterRange;
            break;
        case DS_CWDSException:
            replyError = DSREPLY_CWDSException;
            break;
        case DS_InvalidProcessID:
            replyError = DSREPLY_InvalidProcessID;
            break;
        case DS_InvalidThreadID:
            replyError = DSREPLY_InvalidThreadID;
            break;
        case DS_OSError:
            replyError = DSREPLY_OSError;
            break;
        default:
            replyError = DSREPLY_CWDSError;
        }

        return TRKStandardACK(b, DSMSG_ReplyACK, replyError);
    } else {
        // No error, send ack
        return TRKSendACK(b);
    }
}
#endif

/*
 * --INFO--
 * PAL Address: 0x801AA618
 * PAL Size: 656b
 * EN Address: 0x801A94FC
 * EN Size: 656b
 * JP Address: 0x801A589C
 * JP Size: 968b
 */
#ifdef VERSION_GCCJGC
DSError TRKDoWriteRegisters(TRKBuffer* b) {
    DSError error;
    DSReplyError replyError;
    size_t registersLength;
    u16 firstRegister;
    u16 lastRegister;
    u8 command;
    u8 options;

    if (b->length <= 6) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
    }
    TRKSetBufferPosition(b, 0);
    error = TRKReadBuffer1_ui8(b, &command);
    if (error == DS_NoError) {
        error = TRKReadBuffer1_ui8(b, &options);
    }
    if (error == DS_NoError) {
        error = TRKReadBuffer1_ui16(b, &firstRegister);
    }
    if (error == DS_NoError) {
        error = TRKReadBuffer1_ui16(b, &lastRegister);
    }
    if (firstRegister > lastRegister) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_InvalidRegisterRange);
    }
    switch (options) {
    case DSREG_Default:
        error = TRKTargetAccessDefault(firstRegister, lastRegister, b, &registersLength, FALSE);
        break;
    case DSREG_FP:
        error = TRKTargetAccessFP(firstRegister, lastRegister, b, &registersLength, FALSE);
        break;
    case DSREG_Extended1:
        error = TRKTargetAccessExtended1(firstRegister, lastRegister, b, &registersLength, FALSE);
        break;
    case DSREG_Extended2:
        error = TRKTargetAccessExtended2(firstRegister, lastRegister, b, &registersLength, FALSE);
        break;
    default:
        error = DS_UnsupportedError;
        break;
    }
    if (error == DS_NoError) {
        TRKResetBuffer(b, TRUE);
        TRKAppendBuffer1_ui8(b, DSMSG_ReplyACK);
        TRKAppendBuffer1_ui8(b, DSREPLY_NoError);
    }

    // Check if there was an error, and respond accordingly
    if (error != DS_NoError) {
        switch (error) {
        case DS_UnsupportedError:
            replyError = DSREPLY_UnsupportedOptionError;
            break;
        case DS_InvalidRegister:
            replyError = DSREPLY_InvalidRegisterRange;
            break;
        case DS_MessageBufferReadError:
            replyError = DSREPLY_PacketSizeError;
            break;
        case DS_CWDSException:
            replyError = DSREPLY_CWDSException;
            break;
        case DS_InvalidProcessID:
            replyError = DSREPLY_InvalidProcessID;
            break;
        case DS_InvalidThreadID:
            replyError = DSREPLY_InvalidThreadID;
            break;
        case DS_OSError:
            replyError = DSREPLY_OSError;
            break;
        default:
            replyError = DSREPLY_CWDSError;
        }

        return TRKStandardACK(b, DSMSG_ReplyACK, replyError);
    } else {
        // No error, send ack
        return TRKSendACK(b);
    }
}
#else
DSError TRKDoWriteRegisters(TRKBuffer* b) {
    int error;
    int replyError;
    u8 options;
    u16 firstRegister;
    u16 lastRegister;
    size_t registersLength;

    options = b->data[8];
    firstRegister = *(u16*)(b->data + 12);
    lastRegister = *(u16*)(b->data + 16);

    TRKSetBufferPosition(b, 0);

    if (firstRegister > lastRegister) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_InvalidRegisterRange);
    }

    TRKSetBufferPosition(b, 0x40);

    switch (options) {
    case DSREG_Default:
        error = TRKTargetAccessDefault(firstRegister, lastRegister, b, &registersLength, FALSE);
        break;
    case DSREG_FP:
        error = TRKTargetAccessFP(firstRegister, lastRegister, b, &registersLength, FALSE);
        break;
    case DSREG_Extended1:
        error = TRKTargetAccessExtended1(firstRegister, lastRegister, b, &registersLength, FALSE);
        break;
    case DSREG_Extended2:
        error = TRKTargetAccessExtended2(firstRegister, lastRegister, b, &registersLength, FALSE);
        break;
    default:
        // invalid option
        error = DS_UnsupportedError;
        break;
    }

    TRKResetBuffer(b, 0);

    if (error == DS_NoError) {
        CommandReply local_50;
        memset(&local_50, 0, sizeof(CommandReply));
        local_50._00 = 0x40;
        local_50.commandID.b = DSMSG_ReplyACK;
        local_50.replyError.b = error;
        error = TRKAppendBuffer(b, (u8*)&local_50, sizeof(CommandReply));
    }

    // Check if there was an error, and respond accordingly
    if (error != DS_NoError) {
        switch (error) {
        case DS_UnsupportedError:
            replyError = DSREPLY_UnsupportedOptionError;
            break;
        case DS_InvalidRegister:
            replyError = DSREPLY_InvalidRegisterRange;
            break;
        case DS_MessageBufferReadError:
            replyError = DSREPLY_PacketSizeError;
            break;
        case DS_CWDSException:
            replyError = DSREPLY_CWDSException;
            break;
        case DS_InvalidProcessID:
            replyError = DSREPLY_InvalidProcessID;
            break;
        case DS_InvalidThreadID:
            replyError = DSREPLY_InvalidThreadID;
            break;
        case DS_OSError:
            replyError = DSREPLY_OSError;
            break;
        default:
            replyError = DSREPLY_CWDSError;
        }

        return TRKStandardACK(b, DSMSG_ReplyACK, replyError);
    } else {
        // No error, send ack
        return TRKSendACK(b);
    }
}
#endif

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 592b
 * EN Address: UNUSED
 * EN Size: 592b
 * JP Address: 0x801A55A4
 * JP Size: 760b
 */
#ifdef VERSION_GCCJGC
DSError TRKDoFlushCache(TRKBuffer* buffer) {
    DSError err;
    u32 start;
    u32 end;
    u8 command;
    u8 options;
    DSReplyError replyError;

    if (buffer->length != 10) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
    }
    TRKSetBufferPosition(buffer, 0);
    err = TRKReadBuffer1_ui8(buffer, &command);
    if (err == DS_NoError) {
        err = TRKReadBuffer1_ui8(buffer, &options);
    }
    if (err == DS_NoError) {
        err = TRKReadBuffer1_ui32(buffer, &start);
    }
    if (err == DS_NoError) {
        err = TRKReadBuffer1_ui32(buffer, &end);
    }
    if (start > end) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_InvalidMemoryRange);
    }
    if (err == DS_NoError) {
        err = TRKTargetFlushCache(options, (void*)start, (void*)end);
    }
    if (err == DS_NoError) {
        TRKResetBuffer(buffer, TRUE);
        TRKAppendBuffer1_ui8(buffer, DSMSG_ReplyACK);
        TRKAppendBuffer1_ui8(buffer, DSREPLY_NoError);
    }
    if (err != DS_NoError) {
        switch (err) {
        case DS_UnsupportedError:
            replyError = DSREPLY_UnsupportedOptionError;
            break;
        default:
            replyError = DSREPLY_CWDSError;
            break;
        }
        return TRKStandardACK(buffer, DSMSG_ReplyACK, replyError);
    }
    return TRKSendACK(buffer);
}
#else
void TRKDoFlushCache(void) {
    MWTRACE(1, "DoFlushCache unimplemented!!!\n");
    // UNUSED FUNCTION
}
#endif

/*
 * --INFO--
 * PAL Address: 0x801AA568
 * PAL Size: 176b
 * EN Address: 0x801A944C
 * EN Size: 176b
 * JP Address: 0x801A5450
 * JP Size: 340b
 */
DSError TRKDoContinue(TRKBuffer* buffer) {
#ifdef VERSION_GCCJGC
    DSError err;

    if (!TRKTargetStopped()) {
        return TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_NotStopped);
    }
    err = TRKStandardACK(buffer, DSMSG_ReplyACK, DSREPLY_NoError);
    if (err == DS_NoError) {
        err = TRKTargetContinue();
    }
    return err;
#else
    MWTRACE(1, "DoContinue\n");
    if (!TRKTargetStopped()) {
        u8 arr[0x40];
        memset(arr, 0, 0x40);

        arr[4] = 0x80;
        *(u32*)arr = 0x40;
        arr[8] = 0x16;

        TRKWriteUARTN(arr, 0x40);
        return DS_NoError;
    } else {
        u8 arr[0x40];
        memset(arr, 0, 0x40);

        arr[4] = 0x80;
        *(u32*)arr = 0x40;
        arr[8] = 0x00;

        TRKWriteUARTN(arr, 0x40);
        return TRKTargetContinue();
    }
#endif
}

/*
 * --INFO--
 * PAL Address: 0x801AA348
 * PAL Size: 544b
 * EN Address: 0x801A922C
 * EN Size: 544b
 * JP Address: 0x801A4F20
 * JP Size: 1328b
 */
DSError TRKDoStep(TRKBuffer* b) {
#ifdef VERSION_GCCJGC
    DSError result;
    u32 rangeStart;
    u32 rangeEnd;
    u32 pc;
    u8 command;
    u8 options;
    u8 count;

    if (b->length < 3) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
    }
    TRKSetBufferPosition(b, 0);
    result = TRKReadBuffer1_ui8(b, &command);
    if (result == DS_NoError) {
        result = TRKReadBuffer1_ui8(b, &options);
    }

    switch (options) {
    case DSSTEP_IntoCount:
    case DSSTEP_OverCount:
        if (result == DS_NoError) {
            result = TRKReadBuffer1_ui8(b, &count);
        }
        if (count >= 1) {
            break;
        }
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_ParameterError);
    case DSSTEP_IntoRange:
    case DSSTEP_OverRange:
        if (b->length != 10) {
            return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_PacketSizeError);
        }
        if (result == DS_NoError) {
            result = TRKReadBuffer1_ui32(b, &rangeStart);
        }
        if (result == DS_NoError) {
            result = TRKReadBuffer1_ui32(b, &rangeEnd);
        }
        pc = TRKTargetGetPC();
        if (pc >= rangeStart && pc <= rangeEnd) {
            break;
        }
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_ParameterError);
    default:
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_UnsupportedOptionError);
    }

    if (!TRKTargetStopped()) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_NotStopped);
    } else {
        result = TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_NoError);
        if (result == DS_NoError) {
            switch (options) {
            case DSSTEP_IntoCount:
            case DSSTEP_OverCount:
                result = TRKTargetSingleStep(count, (options == DSSTEP_OverCount));
                break;
            case DSSTEP_IntoRange:
            case DSSTEP_OverRange:
                result = TRKTargetStepOutOfRange(rangeStart, rangeEnd, (options == DSSTEP_OverRange));
                break;
            }
        }
        return result;
    }
#else
    DSError result;
    u8 options;
    u8 count;
    u32 rangeStart;
    u32 rangeEnd;
    u32 pc;
    TRKSetBufferPosition(b, 0);

    options = *(u8*)&b->data[8];
    rangeStart = *(u32*)&b->data[16];
    rangeEnd = *(u32*)&b->data[20];

    switch (options) {
    case DSSTEP_IntoCount:
    case DSSTEP_OverCount:
        count = b->data[12];
        if (count >= 1) {
            break;
        }
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_ParameterError);
    case DSSTEP_IntoRange:
    case DSSTEP_OverRange:
        pc = TRKTargetGetPC();
        if (pc >= rangeStart && pc <= rangeEnd) {
            break;
        }
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_ParameterError);
    default:
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_UnsupportedOptionError);
    }

    if (!TRKTargetStopped()) {
        return TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_NotStopped);
    } else {
        result = TRKStandardACK(b, DSMSG_ReplyACK, DSREPLY_NoError);
        switch (options) {
        case DSSTEP_IntoCount:
        case DSSTEP_OverCount:
            result = TRKTargetSingleStep(count, (options == DSSTEP_OverCount));
            break;
        case DSSTEP_IntoRange:
        case DSSTEP_OverRange:
            result = TRKTargetStepOutOfRange(rangeStart, rangeEnd, (options == DSSTEP_OverRange));
            break;
        }

        return result;
    }
#endif
}

/*
 * --INFO--
 * PAL Address: 0x801AA2A0
 * PAL Size: 168b
 * EN Address: 0x801A9184
 * EN Size: 168b
 * JP Address: 0x801A4E20
 * JP Size: 256b
 */
DSError TRKDoStop(TRKBuffer* b) {
    MessageCommandID c;

    switch (TRKTargetStop()) {
    case DS_NoError:
        c = DSMSG_Ping;
        break;
    case DS_InvalidProcessID:
        c = '!';
        break;
    case DS_InvalidThreadID:
        c = '\"';
        break;
    case DS_OSError:
        c = ' ';
        break;
    default:
        c = DSMSG_Connect;
        break;
    }

#ifdef VERSION_GCCJGC
    return TRKStandardACK(b, DSMSG_ReplyACK, c);
#else
    TRKStandardACK(b, DSMSG_ReplyACK, c);

    return DS_NoError;
#endif
}

/*
 * --INFO--
 * PAL Address: 0x801AA1F8
 * PAL Size: 168b
 * EN Address: 0x801A90DC
 * EN Size: 168b
 * JP Address: 0x801A4C7C
 * JP Size: 420b
 */
DSError TRKDoSetOption(TRKBuffer* message) {
#ifdef VERSION_GCCJGC
    DSError err;
    u8 command = 0;
    u8 option = 0;
    u8 enable = 0;

    TRKSetBufferPosition(message, 0);
    err = TRKReadBuffer1_ui8(message, &command);
    if (err == DS_NoError) {
        err = TRKReadBuffer1_ui8(message, &option);
    }
    if (err == DS_NoError) {
        err = TRKReadBuffer1_ui8(message, &enable);
    }
    if (err != DS_NoError) {
        TRKStandardACK(message, DSMSG_ReplyACK, DSREPLY_Error);
    } else if (option == 1) {
        SetUseSerialIO(enable);
    }
    return TRKStandardACK(message, DSMSG_ReplyACK, DSREPLY_NoError);
#else
    u8 enable = message->data[0xc];

    if (message->data[0x8] == '\1') {
        usr_puts_serial("\nMetroTRK Option : SerialIO - ");
        if (enable) {
            usr_puts_serial("Enable\n");
        } else {
            usr_puts_serial("Disable\n");
        }
        SetUseSerialIO(enable);
    }

    TRKStandardACK(message, DSMSG_ReplyACK, DS_NoError);

    return 0;
#endif
}
