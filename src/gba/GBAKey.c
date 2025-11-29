#include "GBA/GBAKey.h"

static s32 F152(void* task)
{
	/*
    s32 chan;
    void* gba;

    for (chan = 0; chan < 4; chan++) {
        gba = &__GBA[chan];
        if (&gba->task == task) {
            return chan;
        }
    }
    
    ASSERTLINE(173, 0 <= chan && chan < 4);
    OSPanic(__FILE__, 174, "GBA - unexpected dsp call");*/
    return -1;
}

static void F23(void* task)
{
	// TODO
}

static void F25(void* task)
{
    s32 chan;

    // chan = F152(task);
    // __GBAX01(chan, 0);
}

void __GBAX02(s32 chan, u8* readbuf) {
	/*
    GBAControl* gba = &__GBA[chan];
    GBABootInfo* bootInfo = &__GBA[chan].bootInfo;
    GBASecParam* param = gba->param;
    void* task = &gba->task;

    memcpy(param, readbuf, 4u);
    param->paletteColor = bootInfo->paletteColor;
    param->paletteSpeed = bootInfo->paletteSpeed;
    param->length = bootInfo->length;
    param->out = &param->keyA;
    DCInvalidateRange(&param->keyA, 32);
    DCFlushRange(param, 32);
    Jac_DSPagbDecodeAsync(task, param, F25);
	*/
}
