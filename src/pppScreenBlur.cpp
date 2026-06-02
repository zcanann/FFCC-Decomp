#include "ffcc/pppScreenBlur.h"
#include "ffcc/graphic.h"
#include "ffcc/pppPart.h"
#include "global.h"
#include <dolphin/gx.h>
#include "ffcc/ppp_linkage.h"

/*
 * --INFO--
 * PAL Address: 0x80155504
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderScreenBlur(_pppPObject* blur, pppScreenBlurUnkB* blurParam, _pppCtrlTable* ctrlTable)
{
    s32 blurActiveOffset = ctrlTable->m_serializedDataOffsets[1];
    u8* blurActive = blur->m_workArea + blurActiveOffset;
    u8* blurValuePtr = blur->m_workArea + ctrlTable->m_serializedDataOffsets[0];
    u32 blurMask;

    blurParam->m_blurB = 0;
    blurMask = __cntlzw((u32)*blurActive);
    Graphic.RenderBlur(blurMask >> 5, blurParam->m_blurR, blurParam->m_blurG, blurParam->m_blurB,
                       blurValuePtr[0x0B], blurParam->m_initWOrk);
    pppInitBlendMode();
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
    *blurActive = 1;
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
    if (ppvUserStopPartF == 0) {
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
    Graphic.InitBlurParameter();
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
void pppCon2ScreenBlur(_pppPObject*)
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
void pppConScreenBlur(_pppPObject* blur, _pppCtrlTable* ctrlTable)
{
    s32 blurOffset = ctrlTable->m_serializedDataOffsets[1];
    u8* blurActive = blur->m_workArea + blurOffset;

    Graphic.InitBlurParameter();
    *blurActive = 0;
}
