#include "dolphin/gba/GBAPriv.h"

/*
 * --INFO--
 * PAL Address: 0x801a76fc
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

s32 GBAGetProcessStatus(s32 chan, u8* percentp) {
    BOOL enabled;
    s32 ret;
    u8* gbaBase;
    s32 offset;
    u8 percent;
    OSTime t;

    enabled = OSDisableInterrupts();
    
    offset = chan * sizeof(GBAControl);
    gbaBase = (u8*)__GBA + offset;

    if (*(void**)(gbaBase + 0x1c) != NULL) {
        ret = GBA_BUSY;
        
        if (*(void**)(gbaBase + 0x54) != NULL) {
            percent = (*(u32*)(gbaBase + 0x74) * 100) / *(u32*)(gbaBase + 0xa4);
            
            if (*(u32*)(gbaBase + 0x6c) != 0 || *(u32*)(gbaBase + 0x68) != 0) {
                t = OSGetTime();
                t = t - *(OSTime*)(gbaBase + 0x68);
                
                if (OSTicksToMilliseconds(t) < 5500) {
                    percent = (percent * (u32)t) / (u32)OSMillisecondsToTicks(5500);
                }
                
                if (percent >= 100) {
                    percent = 100;
                }
            }
            
            if (percentp != NULL) {
                *percentp = percent;
            }
        }
    } else {
        ret = GBA_READY;
    }

    OSRestoreInterrupts(enabled);
    return ret;
}
