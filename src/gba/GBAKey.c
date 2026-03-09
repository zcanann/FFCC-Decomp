#include "dolphin/dsp.h"
#include "dolphin/gba/GBAPriv.h"
#include "GBA/GBAKey.h"
#include <string.h>

extern u8 GBAKeyDspTaskIram[];

static s32 F152(void* task)
{
    s32 chan;

    for (chan = 0; chan < 4; chan++) {
        if (&__GBA[chan].task == task) {
            return chan;
        }
    }

    OSPanic(__FILE__, 169, "GBA - unexpected dsp call");
    return -1;
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

/*
 * --INFO--
 * PAL Address: 0x801A8D9C
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static void F232(void* task)
{
    s32 chan;

    chan = F152(task);

    DSPSendMailToDSP(0xabba0000);
    while (DSPCheckMailToDSP() != 0) {
    }

    DSPSendMailToDSP((u32)&__GBA[chan].param);
    while (DSPCheckMailToDSP() != 0) {
    }
}

static void F252(void* task)
{
    s32 chan;

    chan = F152(task);

    __GBAX01(chan, 0);
}

void __GBAX02(s32 chan, u8* readbuf) {
    GBAControl* gba = &__GBA[chan];
    GBABootInfo* bootInfo = &gba->bootInfo;
    GBASecParam* param = gba->param;
    
    memcpy(param, readbuf, 4);
    param->paletteColor = bootInfo->paletteColor;
    param->paletteSpeed = bootInfo->paletteSpeed;
    param->length = bootInfo->length;
    param->out = (u32*)(param + 1);
    
    DCInvalidateRange(param + 1, 32);
    DCFlushRange(param, 32);
    
    gba->task.priority = 0xff;
    gba->task.iram_mmem_addr = (u16*)OSCachedToPhysical(GBAKeyDspTaskIram);
    gba->task.iram_length = 0x380;
    gba->task.iram_addr = 0;
    gba->task.dsp_init_vector = 0x10;
    gba->task.init_cb = F232;
    gba->task.res_cb = NULL;
    gba->task.done_cb = F252;
    gba->task.req_cb = NULL;
    
    DSPAddTask(&gba->task);
}
