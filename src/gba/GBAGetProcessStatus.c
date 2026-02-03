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
    u32 enabled;
    s32 ret;
    u8 percent;
    OSTime time;
    s32 param_offset;
    
    param_offset = chan * 0x100;
    enabled = OSDisableInterrupts();
    
    if (*(s32*)((u8*)&__GBA + param_offset + 0x54) == 0) {
        if (*(s32*)((u8*)&__GBA + param_offset + 0x1c) == 0) {
            ret = 0;
        } else {
            ret = 2;
        }
    } else {
        ret = 2;
        percent = (*(s32*)((u8*)&__GBA + param_offset + 0x74) * 100) / *(s32*)((u8*)&__GBA + param_offset + 0xa4) & 0xff;
        
        if (*(s32*)((u8*)&__GBA + param_offset + 0x6c) != 0 || *(s32*)((u8*)&__GBA + param_offset + 0x68) != 0) {
            time = OSGetTime();
            time = time - *(OSTime*)((u8*)&__GBA + param_offset + 0x68);
            
            if (__div2i(0, time, 0, OSSecondsToTicks(1) / 1000 * 5500) < 0x157c) {
                percent = __div2i(0, percent * time, 0, OSSecondsToTicks(1) / 1000 * 5500) & 0xff;
            }
            
            if ((percent & 0xff) > 99) {
                percent = 100;
            }
        }
        
        if (percentp != NULL) {
            *percentp = percent;
        }
    }
    
    OSRestoreInterrupts(enabled);
    return ret;
}
