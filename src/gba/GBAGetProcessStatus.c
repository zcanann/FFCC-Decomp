#include "dolphin/gba/GBAPriv.h"

s32 GBAGetProcessStatus(s32 chan, u8* percentp) {
    GBAControl* gba = &__GBA[chan];
    GBABootInfo* bootInfo = &gba->bootInfo;
    BOOL enabled = OSDisableInterrupts();
    s32 ret;

    if (bootInfo->callback != NULL) {
        u8 percent;

        ret = GBA_BUSY;
        percent = (bootInfo->curOffset * 100) / bootInfo->realLength;
        if (bootInfo->begin != 0) {
            OSTime t = OSGetTime() - bootInfo->begin;
            if (OSTicksToMilliseconds(t) < 5500) {
                percent = (percent * t) / OSMillisecondsToTicks(5500ll);
            }

            if (percent >= 100) {
                percent = 100;
            }
        }

        if (percentp != NULL) {
            *percentp = percent;
        }
    } else {
        if (gba->callback == NULL) {
            ret = GBA_READY;
        } else {
            ret = GBA_BUSY;
        }
    }

    OSRestoreInterrupts(enabled);
    return ret;
}
