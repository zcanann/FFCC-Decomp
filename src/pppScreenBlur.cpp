#include "ffcc/pppScreenBlur.h"
#include "ffcc/pppPart.h"
#include "global.h"
#include <dolphin/gx.h>

extern "C" {
void InitBlurParameter__8CGraphicFv(void* graphic);
void RenderBlur__8CGraphicFiUcUcUcUcs(void* graphic, int enable, u8 r, u8 g, u8 b, u8 strength, s16 work);
}

extern char Graphic[];

extern float ppvScreenMatrix[4][4];
extern int gPppCalcDisabled;

/*
 * --INFO--
 * PAL Address: 0x80155504
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderScreenBlur(pppScreenBlur* blur, pppScreenBlurUnkB* blurParam, _pppCtrlTable* ctrlTable)
{
    s32 blurActiveOffset = ctrlTable->m_serializedDataOffsets[1] + 0x80;
    u8* blurValuePtr = blur->data + ctrlTable->m_serializedDataOffsets[0] + 0x80;
    u32 blurMask;

    blurParam->m_blurB = 0;
    blurMask = __cntlzw((u32)blur->data[blurActiveOffset]);
    RenderBlur__8CGraphicFiUcUcUcUcs(Graphic, blurMask >> 5, blurParam->m_blurR, blurParam->m_blurG,
                                     blurParam->m_blurB, blurValuePtr[0x0B], blurParam->m_initWOrk);
    pppInitBlendMode();
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
    blur->data[blurActiveOffset] = 1;
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
void pppFrameScreenBlur(_pppPObject*, void*, _pppCtrlTable*)
{
    if (gPppCalcDisabled == 0) {
        return;
    }
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
void pppDesScreenBlur(_pppPObjLink*, _pppCtrlTable*)
{
    InitBlurParameter__8CGraphicFv(Graphic);
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
void pppCon2ScreenBlur(pppScreenBlur*)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x801555d8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConScreenBlur(pppScreenBlur* blur, _pppCtrlTable* ctrlTable)
{
    s32 blurOffset = ctrlTable->m_serializedDataOffsets[1] + 0x80;

    InitBlurParameter__8CGraphicFv(Graphic);
    blur->data[blurOffset] = 0;
}
