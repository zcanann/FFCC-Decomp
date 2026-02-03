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

s32 GBAGetProcessStatus(s32 param_1, u8* param_2) {
    u32 uVar1;
    u32 uVar4;
    s32 iVar3;
    u32 uVar2;
    u64 uVar6;
    
    param_1 = param_1 * 0x100;
    uVar1 = OSDisableInterrupts();
    
    if (*(s32*)((u8*)&__GBA + param_1 + 0x54) == 0) {
        if (*(s32*)((u8*)&__GBA + param_1 + 0x1c) == 0) {
            iVar3 = 0;
        } else {
            iVar3 = 2;
        }
    } else {
        iVar3 = 2;
        uVar4 = (*(s32*)((u8*)&__GBA + param_1 + 0x74) * 100) / *(s32*)((u8*)&__GBA + param_1 + 0xa4) & 0xff;
        
        if (*(s32*)((u8*)&__GBA + param_1 + 0x6c) != 0 || *(s32*)((u8*)&__GBA + param_1 + 0x68) != 0) {
            uVar6 = OSGetTime();
            uVar2 = (u32)uVar6 - *(u32*)((u8*)&__GBA + param_1 + 0x68);
            iVar3 = (s32)(uVar6 >> 32) - ((u32)uVar6 < *(u32*)((u8*)&__GBA + param_1 + 0x68)) - *(s32*)((u8*)&__GBA + param_1 + 0x6c);
            
            uVar6 = __div2i(iVar3, uVar2, 0, *(u32*)0x800000f8 / 4000);
            if (((u32)(uVar6 >> 32) ^ 0x80000000) < (((u32)uVar6 < 0x157c) + 0x80000000)) {
                uVar4 = __div2i((s32)((u64)uVar4 * (u64)uVar2 >> 32) + uVar4 * iVar3, uVar4 * uVar2, 
                               (s32)((u64)(*(u32*)0x800000f8 / 4000) * 0x157cULL >> 32), 
                               (*(u32*)0x800000f8 / 4000) * 0x157c) & 0xff;
            }
            
            if (99 < (uVar4 & 0xff)) {
                uVar4 = 100;
            }
        }
        
        if (param_2 != NULL) {
            *param_2 = (u8)uVar4;
        }
        
        iVar3 = 2;
    }
    
    OSRestoreInterrupts(uVar1);
    return iVar3;
}
