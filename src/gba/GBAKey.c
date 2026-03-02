#include "GBA/GBAKey.h"
#include "dolphin/dsp.h"
#include "dolphin/os.h"
#include "GBA/GBA.h"
#include "GBA/GBAPriv.h"
#include <string.h>

static s32 F152(void* task)
{
    if ((int)task == -0x7fcd7c38) {
        return 0;
    } else if ((int)task == -0x7fcd7b38) {
        return 1;
    } else if ((int)task == -0x7fcd7a38) {
        return 2;
    } else if ((int)task == -0x7fcd7938) {
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
    s32 result;
    
    if ((int)task == -0x7fcd7c38) {
        chan = 0;
    } else if ((int)task == -0x7fcd7b38) {
        chan = 1;
    } else if ((int)task == -0x7fcd7a38) {
        chan = 2;
    } else if ((int)task == -0x7fcd7938) {
        chan = 3;
    } else {
        OSPanic(__FILE__, 169, "GBA - unexpected dsp call");
        chan = -1;
    }
    
    DSPSendMailToDSP(0xabba0000);
    do {
        result = DSPCheckMailToDSP();
    } while (result != 0);
    
    DSPSendMailToDSP((u32)&__GBA[chan].param);
    do {
        result = DSPCheckMailToDSP();
    } while (result != 0);
}

static void F252(void* task)
{
    s32 chan;

    if ((int)task == -0x7fcd7c38) {
        chan = 0;
    } else if ((int)task == -0x7fcd7b38) {
        chan = 1;
    } else if ((int)task == -0x7fcd7a38) {
        chan = 2;
    } else if ((int)task == -0x7fcd7938) {
        chan = 3;
    } else {
        OSPanic(__FILE__, 169, "GBA - unexpected dsp call");
        chan = -1;
    }
    
    __GBAX01(chan, 0);
}

void __GBAX02(s32 chan, u8* readbuf) {
    GBAControl* gba = &__GBA[chan];
    void* param = &gba->param;
    
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
    gba->task.dram_mmem_addr = (u16*)0x10;
    gba->task.res_cb = F232;
    gba->task.done_cb = F252;
    
    DSPAddTask(&gba->task);
}
