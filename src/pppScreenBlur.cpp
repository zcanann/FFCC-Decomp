#include "ffcc/pppScreenBlur.h"
#include "ffcc/graphic.h"
#include "ffcc/pppPart.h"
#include "global.h"
#include <dolphin/gx.h>

typedef struct {
    int unk0;
    int unk1;
    int unk2;
    int* m_serializedDataOffsets;
} UnkC;

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
    UnkC* param = (UnkC*)param2;
    int iVar1 = param->m_serializedDataOffsets[1] + 0x80;

    Graphic.InitBlurParameter();

    ((u8*)param1)[iVar1] = 0;
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
    extern int lbl_8032ED70;
    if (lbl_8032ED70 == 0) {
        return;
    }
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
    UnkC* param = (UnkC*)param3;
    int iVar3 = param->m_serializedDataOffsets[1];
    int iVar2 = param->m_serializedDataOffsets[0];
    u8* param2_base = (u8*)param2;
    u8* pppScreenBlur = (u8*)param1;
    u8* blurState = pppScreenBlur + iVar3 + 0x80;
    u8* blurData = pppScreenBlur + iVar2 + 0x80;
    u32 uVar1;

    param2_base[6] = 0;
    uVar1 = __cntlzw((u32)blurState[0]);

    Graphic.RenderBlur(uVar1 >> 5, param2_base[4], param2_base[5], param2_base[6], blurData[0xb], *(s16*)&param2_base[8]);
    pppInitBlendMode();

    extern float ppvScreenMatrix[4][4];
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);

    blurState[0] = 1;
}
