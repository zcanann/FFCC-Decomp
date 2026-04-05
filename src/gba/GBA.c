#include "dolphin/gba/GBAPriv.h"

extern GBASecParam SecParams[4];
GBAControl __GBA[4];
BOOL __GBAReset = FALSE;

BOOL OnReset4(BOOL final);

static OSResetFunctionInfo ResetFunctionInfo = {OnReset4, 127};

void ShortCommandProc(s32 chan) {
    GBAControl* gba;
    gba = &__GBA[chan];

    if (gba->ret != 0) {
        return;
    }

    if (gba->input[0] != 0 || gba->input[1] != 4) {
        gba->ret = 1;
        return;
    }

    gba->status[0] = gba->input[2] & GBA_JSTAT_MASK;
}

/*
 * --INFO--
 * PAL Address: 0x801A7460
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GBAInit() {
    GBAControl* gba;
    s32 chan;

    for (chan = 0; chan < 4; ++chan) {
        gba = &__GBA[chan];
        gba->delay = OSMicrosecondsToTicks(60);
        OSInitThreadQueue(&gba->threadQueue);
        gba->param = &SecParams[chan];
    }

    OSInitAlarm();
    DSPInit();

    __GBAReset = FALSE;
    OSRegisterResetFunction(&ResetFunctionInfo);
}

s32 GBAGetStatusAsync(s32 chan, u8* status, GBACallback callback) {
    GBAControl* gba;
    gba = &__GBA[chan];
    if (gba->callback != NULL) {
        return GBA_BUSY;
    }

    gba->output[0] = 0;
    gba->status = status;
    gba->callback = callback;
    return __GBATransfer(chan, 1, 3, ShortCommandProc);
}

s32 GBAGetStatus(s32 chan, u8* status) {
    GBAControl* gba = &__GBA[chan];

    s32 ret = GBAGetStatusAsync(chan, status, __GBASyncCallback);
    if (ret != GBA_READY) {
        return ret;
    }
    return __GBASync(chan);
}

s32 GBAResetAsync(s32 chan, u8* status, GBACallback callback) {
    GBAControl* gba = &__GBA[chan];
    if (gba->callback != NULL) {
        return GBA_BUSY;
    }
    gba->output[0] = 0xFF;
    gba->status = status;
    gba->callback = callback;
    return __GBATransfer(chan, 1, 3, ShortCommandProc);
}

s32 GBAReset(s32 chan, u8* status) {
    GBAControl* gba = &__GBA[chan];
    s32 ret;

    ret = GBAResetAsync(chan, status, __GBASyncCallback);
    if (ret != GBA_READY) {
        return ret;
    }
    return __GBASync(chan);
}

/*
 * --INFO--
 * PAL Address: 0x801A76EC
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
BOOL OnReset4(BOOL final) {
    __GBAReset = TRUE;
    return TRUE;
}
