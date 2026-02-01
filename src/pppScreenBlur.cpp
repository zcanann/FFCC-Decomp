#include "ffcc/pppScreenBlur.h"
#include "ffcc/graphic.h"
#include "ffcc/pppPart.h"
#include <dolphin/gx.h>

/*
 * --INFO--
 * PAL Address: 0x801555d8
 * PAL Size: 84b
 */
void pppConScreenBlur(void* param1, void* param2)
{
    void** ptr_struct = (void**)param2;
    void* work_ptr = ptr_struct[1];
    unsigned char* base = (unsigned char*)param1;
    
    Graphic.InitBlurParameter();
    base[((int)work_ptr + 2)] = 0;
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
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80155504
 * PAL Size: 156b
 */
void pppRenderScreenBlur(void* param1, void* param2, void* param3)
{
    void** ptr_struct2 = (void**)param2;
    void** ptr_struct3 = (void**)param3;
    
    unsigned char* base1 = (unsigned char*)param1;
    unsigned char* base2 = (unsigned char*)param2;
    
    int offset3 = (int)ptr_struct3[1];
    int offset2 = *(int*)ptr_struct3[0];
    
    base2[2] = 0;
    
    unsigned char blur_flag = base1[offset3 + 2];
    int blur_enabled = (blur_flag == 0) ? 1 : 0;
    
    Graphic.RenderBlur(blur_enabled, base2[0], base2[1], base2[2], 
                      base1[offset2 + 0x8b], *(short*)&base2[12]);
    
    pppInitBlendMode();
    
    // Set projection with screen matrix
    extern float ppvScreenMatrix[4][4];
    GXSetProjection(ppvScreenMatrix, GX_ORTHOGRAPHIC);
    
    base1[offset3 + 2] = 1;
}