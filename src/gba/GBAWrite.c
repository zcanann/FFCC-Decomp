#include "dolphin/gba/GBAPriv.h"
#include "string.h"

static void WriteProc(s32 chan) {
    if (__GBA[chan].ret != 0) {
        return;
    }

    __GBA[chan].status[0] = __GBA[chan].input[0] & GBA_JSTAT_MASK;
}

s32 GBAWriteAsync(s32 chan, u8* src, u8* status, GBACallback callback) {
    if (__GBA[chan].callback != NULL) {
        return GBA_BUSY;
    }
    __GBA[chan].output[0] = 0x15;
    memcpy(&__GBA[chan].output[1], src, 4);
    __GBA[chan].ptr = src;
    __GBA[chan].status = status;
    __GBA[chan].callback = callback;
    return __GBATransfer(chan, 5, 1, WriteProc);
}

s32 GBAWrite(s32 chan, u8* src, u8* status) {
    s32 ret;
    ret = GBAWriteAsync(chan, src, status, __GBASyncCallback);
    if (ret != GBA_READY) {
        return ret;
    }
    return __GBASync(chan);
}
