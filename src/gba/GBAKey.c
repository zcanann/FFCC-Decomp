#include "GBA/GBAKey.h"
#include "dolphin/dsp.h"
#include "dolphin/os.h"
#include "GBA/GBA.h"
#include "GBA/GBAPriv.h"
#include <string.h>

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
    GBASecParam* param = gba->param;
    u32 paletteColor = gba->bootInfo.paletteColor;
    u32 paletteSpeed = gba->bootInfo.paletteSpeed;
    u32 length = gba->bootInfo.length;

    memcpy(param, readbuf, 4);
    *(u32*)((u8*)param + 4) = paletteColor;
    *(u32*)((u8*)param + 8) = paletteSpeed;
    *(u32*)((u8*)param + 12) = length;
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
