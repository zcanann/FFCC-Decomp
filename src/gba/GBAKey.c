#include "GBA/GBAKey.h"
#include "dolphin/dsp.h"
#include "dolphin/os.h"
#include "GBA/GBA.h"
#include "GBA/GBAPriv.h"
#include <string.h>

static s32 F152(void* task)
{
    if (task == &__GBA[0].task) {
        return 0;
    } else if (task == &__GBA[1].task) {
        return 1;
    } else if (task == &__GBA[2].task) {
        return 2;
    } else if (task == &__GBA[3].task) {
        return 3;
    } else {
        OSPanic(__FILE__, 169, "GBA - unexpected dsp call");
        return -1;
    }
}

static void F23(void* task)
{
    s32 chan;
    s32 result;
    
    chan = F152(task);
    
    DSPSendMailToDSP(0xabba0000);
    do {
        result = DSPCheckMailToDSP();
    } while (result != 0);
    
    DSPSendMailToDSP((u32)&__GBA[chan].param);
    do {
        result = DSPCheckMailToDSP();
    } while (result != 0);
}

static void F25(void* task)
{
    s32 chan;

    chan = F152(task);
    __GBAX01(chan, 0);
}

static void F232(void* task)
{
    s32 chan;

    if (&__GBA[0].task == task) {
        chan = 0;
    } else if (&__GBA[1].task == task) {
        chan = 1;
    } else if (&__GBA[2].task == task) {
        chan = 2;
    } else if (&__GBA[3].task == task) {
        chan = 3;
    } else {
        OSPanic(__FILE__, 169, "GBA - unexpected dsp call");
        chan = -1;
    }

    DSPSendMailToDSP(0xabba0000);
    while (DSPCheckMailToDSP() != 0) {
    }

    DSPSendMailToDSP((u32)((u8*)__GBA + (chan << 8) + 0xf8));
    while (DSPCheckMailToDSP() != 0) {
    }
}

static void F252(void* task)
{
    s32 chan;

    if (&__GBA[0].task == task) {
        chan = 0;
    } else if (&__GBA[1].task == task) {
        chan = 1;
    } else if (&__GBA[2].task == task) {
        chan = 2;
    } else if (&__GBA[3].task == task) {
        chan = 3;
    } else {
        OSPanic(__FILE__, 169, "GBA - unexpected dsp call");
        chan = -1;
    }
    
    __GBAX01(chan, 0);
}

void __GBAX02(s32 chan, u8* readbuf) {
    GBAControl* gba = &__GBA[chan];
    void* param = gba->param;
    
    memcpy(param, readbuf, 4);
    *(u32*)((u8*)param + 4) = gba->bootInfo.paletteColor;
    *(u32*)((u8*)param + 8) = gba->bootInfo.paletteSpeed;
    *(u32*)((u8*)param + 12) = gba->bootInfo.length;
    *(u32*)((u8*)param + 16) = (u32)param + 32;
    
    DCInvalidateRange((u8*)param + 32, 32);
    DCFlushRange(param, 32);
    
    gba->task.state = 0xff;
    gba->task.iram_addr = 0x21cb78;
    gba->task.dram_addr = 0x380;
    gba->task.dram_length = 0;
    gba->task.dsp_init_vector = 0x10;
    gba->task.init_cb = F232;
    gba->task.res_cb = 0;
    gba->task.done_cb = (DSPCallback)F252;
    gba->task.req_cb = 0;
    
    DSPAddTask(&gba->task);
}
