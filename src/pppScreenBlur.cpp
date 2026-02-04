#include "ffcc/pppScreenBlur.h"
#include "ffcc/graphic.h"
#include "ffcc/pppPart.h"
#include "global.h"
#include <dolphin/gx.h>

/*
 * --INFO--
 * PAL Address: 0x801555d8
 * PAL Size: 84b
 */
void pppConScreenBlur(void* param1, void* param2)
{
    int iVar1;
    
    void** param2_offsets = (void**)param2;
    iVar1 = (int)param2_offsets[3]; // offset from struct
    
    Graphic.InitBlurParameter();
    
    unsigned char* param1_base = (unsigned char*)param1;
    param1_base[iVar1 + 0x80] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801555d4
 * PAL Size: 4b
 */
void pppCon2ScreenBlur(void)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x801555ac
 * PAL Size: 40b
 */
void pppDesScreenBlur(void)
{
    Graphic.InitBlurParameter();
}

/*
 * --INFO--
 * PAL Address: 0x801555a0
 * PAL Size: 12b
 */
void pppFrameScreenBlur(void)
{
    // Check global state before processing
    extern int pppScreenBlurEnabled; // Placeholder global variable
    if (pppScreenBlurEnabled == 0) {
        return;
    }
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80155504
 * PAL Size: 156b
 */
void pppRenderScreenBlur(void* param1, void* param2, void* param3)
{
    unsigned int uVar1;
    int iVar2;
    int iVar3;
    
    void** param3_offsets = (void**)param3;
    iVar3 = (int)param3_offsets[3]; // offset from struct at index 3
    iVar2 = *(int*)param3_offsets[0]; // dereference pointer at index 0
    
    unsigned char* param2_base = (unsigned char*)param2;
    unsigned char* param1_base = (unsigned char*)param1;
    
    // Set byte at offset 6 in param2 to 0
    param2_base[6] = 0;
    
    // Count leading zeros on the byte at param1 + iVar3 + 0x80
    unsigned char blur_byte = param1_base[iVar3 + 0x80];
    // cntlzw pattern: if byte is 0, result is 8; if non-zero, result is less
    uVar1 = (blur_byte == 0) ? 8 : 0;
    
    Graphic.RenderBlur(uVar1 >> 5,
                      param2_base[4],
                      param2_base[5], 
                      param2_base[6],
                      param1_base[iVar2 + 0x80 + 0xb],
                      *(short*)&param2_base[8]);
    
    pppInitBlendMode();
    
    extern float ppvScreenMatrix[4][4];
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
    
    // Set the blur flag to 1
    param1_base[iVar3 + 0x80] = 1;
}