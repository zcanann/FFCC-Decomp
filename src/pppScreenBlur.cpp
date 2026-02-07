#include "ffcc/pppScreenBlur.h"
#include "ffcc/graphic.h"
#include "ffcc/pppPart.h"
#include "global.h"
#include <dolphin/gx.h>

typedef struct {
    u8 data[0x80];
} pppScreenBlur;

typedef struct {
    u32 m_dataValIndex; // 0x00
    u8 m_blurR;         // 0x04
    u8 m_blurG;         // 0x05
    u8 m_blurB;         // 0x06
    u8 m_pad7;          // 0x07
    s16 m_initWOrk;     // 0x08
} pppScreenBlurParam;

typedef struct {
    u8 pad[0x0C];
    s32* m_serializedDataOffsets; // 0x0C
} pppScreenBlurOffsets;

extern float ppvScreenMatrix[4][4];
extern int lbl_8032ED70;

/*
 * --INFO--
 * PAL Address: 0x801555d8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConScreenBlur(void* param1, void* param2)
{
    pppScreenBlur* blur = (pppScreenBlur*)param1;
    pppScreenBlurOffsets* offsets = (pppScreenBlurOffsets*)param2;
    s32 blurOffset = offsets->m_serializedDataOffsets[1] + 0x80;

    Graphic.InitBlurParameter();
    blur->data[blurOffset] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801555d4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCon2ScreenBlur(void)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x801555ac
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDesScreenBlur(void)
{
    Graphic.InitBlurParameter();
}

/*
 * --INFO--
 * PAL Address: 0x801555a0
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameScreenBlur(void)
{
    if (lbl_8032ED70 == 0) {
        return;
    }
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80155504
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderScreenBlur(void* param1, void* param2, void* param3)
{
    pppScreenBlur* blur = (pppScreenBlur*)param1;
    pppScreenBlurParam* blurParam = (pppScreenBlurParam*)param2;
    pppScreenBlurOffsets* offsets = (pppScreenBlurOffsets*)param3;
    s32 blurActiveOffset = offsets->m_serializedDataOffsets[1] + 0x80;
    s32 blurValueOffset = offsets->m_serializedDataOffsets[0] + 0x80;
    u32 blurMask;

    blurParam->m_blurB = 0;
    blurMask = __cntlzw((u32)blur->data[blurActiveOffset]);
    Graphic.RenderBlur(blurMask >> 5, blurParam->m_blurR, blurParam->m_blurG, blurParam->m_blurB,
                       blur->data[blurValueOffset + 0x0B], blurParam->m_initWOrk);
    pppInitBlendMode();
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
    blur->data[blurActiveOffset] = 1;
}
