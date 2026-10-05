/**
 * dispatch.c
 * Description:
 */

#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/dispatch.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msgbuf.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/MWTrace.h"
#include "TRK_MINNOW_DOLPHIN/MetroTRK/Portable/msghndlr.h"

#ifdef VERSION_GCCJGC
typedef DSError (*TRKDispatchFunc)(TRKBuffer*);

static TRKDispatchFunc gTRKDispatchTable[] = {
    TRKDoUnsupported,
    TRKDoConnect,
    TRKDoDisconnect,
    TRKDoReset,
    TRKDoVersions,
    TRKDoSupportMask,
    TRKDoCPUType,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoReadMemory,
    TRKDoWriteMemory,
    TRKDoReadRegisters,
    TRKDoWriteRegisters,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoFlushCache,
    TRKDoSetOption,
    TRKDoContinue,
    TRKDoStep,
    TRKDoStop,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
    TRKDoUnsupported,
};
static u32 gTRKDispatchTableSize;
#endif

/*
 * --INFO--
 * PAL Address: 0x801AA1F0
 * PAL Size: 8b
 * EN Address: 0x801A90D4
 * EN Size: 8b
 * JP Address: 0x801A4C64
 * JP Size: 24b
 */
DSError TRKInitializeDispatcher() {
#ifdef VERSION_GCCJGC
    gTRKDispatchTableSize = sizeof(gTRKDispatchTable) / sizeof(gTRKDispatchTable[0]);
#endif
    return DS_NoError;
}

/*
 * --INFO--
 * PAL Address: 0x801AA080
 * PAL Size: 368b
 * EN Address: 0x801A8F64
 * EN Size: 368b
 * JP Address: 0x801A4BE0
 * JP Size: 132b
 */
DSError TRKDispatchMessage(TRKBuffer* msg) {
#ifdef VERSION_GCCJGC
    u32 err;
    u8 command;

    err = DS_DispatchError;
    TRKSetBufferPosition(msg, 0);
    TRKReadBuffer1_ui8(msg, &command);
    if (command < gTRKDispatchTableSize) {
        err = gTRKDispatchTable[command](msg);
    }
    return err;
#else
    u32 err;

	err = DS_DispatchError;
	TRKSetBufferPosition(msg, 0);
	MWTRACE(1, "Dispatch command 0x%08x\n", msg->data[4]);

	switch (msg->data[4]) {
	case DSMSG_Connect:
		err = TRKDoConnect(msg);
		break;
	case DSMSG_Disconnect:
		err = TRKDoDisconnect(msg);
		break;
	case DSMSG_Reset:
		err = TRKDoReset(msg);
		break;
	case DSMSG_Override:
		err = TRKDoOverride(msg);
		break;
	case DSMSG_Versions:
		err = TRKDoVersions(msg);
		break;
	case DSMSG_SupportMask:
		err = TRKDoSupportMask(msg);
		break;
	case DSMSG_ReadMemory:
		err = TRKDoReadMemory(msg);
		break;
	case DSMSG_WriteMemory:
		err = TRKDoWriteMemory(msg);
		break;
	case DSMSG_ReadRegisters:
		err = TRKDoReadRegisters(msg);
		break;
	case DSMSG_WriteRegisters:
		err = TRKDoWriteRegisters(msg);
		break;
	case DSMSG_Continue:
		err = TRKDoContinue(msg);
		break;
	case DSMSG_Step:
		err = TRKDoStep(msg);
		break;
	case DSMSG_Stop:
		err = TRKDoStop(msg);
		break;
	case DSMSG_SetOption:
		err = TRKDoSetOption(msg);
		break;
	}
	MWTRACE(1, "Dispatch complete err = %ld\n", err);
	return err;
#endif
}