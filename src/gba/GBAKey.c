#include "GBA/GBAKey.h"
#include "dolphin/dsp.h"
#include "dolphin/os.h"
#include "GBA/GBA.h"

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
    gba->task.iramAddress = 0x21cb78;
    gba->task.aramAddress = 0x380;
    gba->task.aramLength = 0;
    gba->task.aramMmemAddress = 0x10;
    gba->task.resumeCallback = F23;
    gba->task.resumeContext = 0;
    gba->task.doneCallback = F25;
    gba->task.doneContext = 0;
    
    DSPAddTask(&gba->task);
}
