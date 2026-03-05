#include "dolphin/gba/GBAPriv.h"
#include "string.h"

/*
 * --INFO--
 * PAL Address: 0x801A88DC
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void WriteProc(s32 chan) {
    GBAControl* gba;
    gba = &__GBA[chan];

    if (gba->ret != 0) {
        return;
    }

    gba->status[0] = gba->input[0] & GBA_JSTAT_MASK;
}

/*
 * --INFO--
 * PAL Address: 0x801A890C
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
s32 GBAWriteAsync(s32 chan, u8* src, u8* status, GBACallback callback) {
    GBAControl* gba;
    gba = &__GBA[chan];

    if (gba->callback != NULL) {
        return GBA_BUSY;
    }

    gba->output[0] = 0x15;
    memcpy(&gba->output[1], src, 4);
    gba->ptr = src;
    gba->status = status;
    gba->callback = callback;

    return __GBATransfer(chan, 5, 1, WriteProc);
}

s32 GBAWrite(s32 chan, u8* src, u8* status) {
    GBAControl* gba = &__GBA[chan];
    volatile u8 pad[8];
    s32 ret;
    (void)pad;

    ret = GBAWriteAsync(chan, src, status, __GBASyncCallback);
    if (ret != GBA_READY) {
        return ret;
    }
    return __GBASync(chan);
}
