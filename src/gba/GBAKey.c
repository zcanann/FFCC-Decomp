#include "dolphin/dsp.h"
#include "dolphin/gba/GBAPriv.h"
#include "GBA/GBAKey.h"
#include <string.h>

extern u8 GBAKeyDspTaskIram[];
extern char s_GBAKey_c_8021cef8[];
extern char s_GBA___unexpected_dsp_call_8021cf04[];

static s32 F152(void* task)
{
    s32 chan;

    for (chan = 0; chan < 4; chan++) {
        if (&__GBA[chan].task == task) {
            return chan;
        }
    }

    OSPanic(s_GBAKey_c_8021cef8, 169, s_GBA___unexpected_dsp_call_8021cf04);
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
    GBAControl* gba;

    chan = F152(task);
    gba = &__GBA[chan];

    DSPSendMailToDSP(0xabba0000);
    while (DSPCheckMailToDSP() != 0U) {
    }

    DSPSendMailToDSP((u32)gba->param);
    while (DSPCheckMailToDSP() != 0U) {
    }
}

static void F252(void* task)
{
    s32 chan;

    chan = F152(task);

    __GBAX01(chan, 0);
}

void __GBAX02(s32 chan, u8* readbuf)
{
    GBAControl* gba = &__GBA[chan];
    GBABootInfo* bootInfo = &gba->bootInfo;
    GBASecParam* param = gba->param;
    DSPTaskInfo* task;
    
    memcpy(param, readbuf, 4);
    param->paletteColor = bootInfo->paletteColor;
    param->paletteSpeed = bootInfo->paletteSpeed;
    param->length = bootInfo->length;
    param->out = &param->keyA;

    DCInvalidateRange(&param->keyA, 32);
    DCFlushRange(param, 32);

    task = &gba->task;

    task->priority = 0xff;
    task->iram_mmem_addr = (u16*)OSCachedToPhysical(GBAKeyDspTaskIram);
    task->iram_length = 0x380;
    task->iram_addr = 0;
    task->dsp_init_vector = 0x10;
    task->init_cb = F232;
    task->res_cb = NULL;
    task->done_cb = F252;
    task->req_cb = NULL;

    DSPAddTask(task);
}
