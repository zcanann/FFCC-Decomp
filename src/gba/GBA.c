#include "dolphin/gba/GBAPriv.h"

static GBASecParam SecParams[4];
GBAControl __GBA[4];
BOOL __GBAReset = FALSE;

static BOOL OnReset(BOOL final);

static OSResetFunctionInfo ResetFunctionInfo = {OnReset, 127};

static void ShortCommandProc(s32 chan) {
    s32 offset = chan * 0x100;
    
    if (*(s32*)((u8*)&__GBA[0] + offset + 0x20) != 0) {
        return;
    }

    if (*((u8*)&__GBA[0] + offset + 0x5) != 0 || *((u8*)&__GBA[0] + offset + 0x6) != 4) {
        *(s32*)((u8*)&__GBA[0] + offset + 0x20) = 1;
        return;
    }

    **(u8**)((u8*)&__GBA[0] + offset + 0x14) = *((u8*)&__GBA[0] + offset + 0x7) & 0x3a;
}

void GBAInit() {
    u32 ticks;
    s32 chan;
    u8* gbaPtr;
    u8* paramPtr;
    
    gbaPtr = (u8*)&__GBA[0];
    chan = 0;
    ticks = *(u32*)0x800000F8 / 500000;
    paramPtr = (u8*)&SecParams[0];
    
    do {
        *(u32*)(gbaPtr + 0x34) = ticks * 0x3c >> 3;
        *(u32*)(gbaPtr + 0x30) = 0;
        OSInitThreadQueue(gbaPtr + 0x24);
        chan = chan + 1;
        *(u8**)(gbaPtr + 0xF8) = paramPtr;
        gbaPtr = gbaPtr + 0x100;
        paramPtr = paramPtr + 0x40;
    } while (chan < 4);
    
    OSInitAlarm();
    DSPInit();
    __GBAReset = FALSE;
    OSRegisterResetFunction(&ResetFunctionInfo);
}

s32 GBAGetStatusAsync(s32 chan, u8* status, GBACallback callback) {
    s32 offset = chan * 0x100;
    
    if (*(void**)((u8*)&__GBA[0] + offset + 0x1C) != NULL) {
        return GBA_BUSY;
    }

    *((u8*)&__GBA[0] + offset) = 0;
    *(u8**)((u8*)&__GBA[0] + offset + 0x14) = status;
    *(GBACallback*)((u8*)&__GBA[0] + offset + 0x1C) = callback;
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

BOOL OnReset(BOOL final) {
    __GBAReset = TRUE;
    return TRUE;
}
