#include "ffcc/pppEraseCharaParts.h"
#include "ffcc/materialman.h"
#include "ffcc/partMng.h"

#include <dolphin/gx.h>

extern CMaterialMan MaterialMan;
extern unsigned int DAT_8032ed70;

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
void DCFlushRange(void* ptr, unsigned long size);
}

/*
 * --INFO--
 * PAL Address: 0x8010400C
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void EraseCharaParts_DrawMeshDLCallback(CChara::CModel* model, void* param_2, void* param_3,
                                        int meshIndex, int param_5, float (*) [4])
{
    void* meshData;
    void* displayList;
    int modelData;
    int meshList;

    meshList = *(int*)((char*)model + 0xAC);
    meshData = *(void**)(meshList + meshIndex * 0x14 + 8);
    displayList = (void*)(*(int*)((char*)meshData + 0x50) + param_5 * 0xC);

    modelData = *(int*)((char*)model + 0xA4);
    MaterialMan.SetMaterial(*(CMaterialSet**)(modelData + 0x24), *(u16*)((char*)displayList + 8), 0,
                            (_GXTevScale)0);

    if ((*(s8*)((char*)param_3 + 4) != -1) && (meshIndex == *(s8*)((char*)param_3 + 4))) {
        GXSetArray((GXAttr)0xB, param_2, 4);
    }

    GXCallDisplayList(*(void**)displayList, *(u32*)((char*)displayList + 4));
}

/*
 * --INFO--
 * PAL Address: 0x80103FA8
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructEraseCharaParts(pppEraseCharaParts* pppEraseCharaParts, UnkC* param_2)
{
    void* handle;
    int model;
    u8* colorPtr;
    void* gObject;

    gObject = *(void**)((char*)pppMngStPtr + 0x8);
    colorPtr = (u8*)((int)(&pppEraseCharaParts->field0_0x0 + 2) + param_2->m_serializedDataOffsets[1]);
    colorPtr[0] = 0x80;
    colorPtr[1] = 0x80;
    colorPtr[2] = 0x80;
    colorPtr[3] = 0x80;

    handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(void (**)(CChara::CModel*, void*, void*, int, int, float (*)[4]))(model + 0xFC) =
        EraseCharaParts_DrawMeshDLCallback;
}

/*
 * --INFO--
 * PAL Address: 0x80103F68
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructEraseCharaParts(void)
{
    void* handle;
    int model;

    handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)pppMngStPtr + 0x8), 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(void**)(model + 0xE4) = 0;
    *(void**)(model + 0xE8) = 0;
    *(void**)(model + 0xFC) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80103EC0
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameEraseCharaParts(pppEraseCharaParts* pppEraseCharaParts, UnkB* param_2, UnkC* param_3)
{
    void* handle;
    int model;
    int colorIndex;
    u8* colorPtr;

    if (DAT_8032ed70 == 0) {
        colorIndex = *param_3->m_serializedDataOffsets;
        colorPtr =
            (u8*)((int)(&pppEraseCharaParts->field0_0x0 + 2) + param_3->m_serializedDataOffsets[1]);
        handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)pppMngStPtr + 0x8), 0);
        model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

        *(u8**)(model + 0xE4) = colorPtr;
        *(UnkB**)(model + 0xE8) = param_2;

        colorPtr[0] = pppEraseCharaParts->field_0x88[colorIndex];
        colorPtr[1] = pppEraseCharaParts->field_0x88[colorIndex + 1];
        colorPtr[2] = pppEraseCharaParts->field_0x88[colorIndex + 2];
        colorPtr[3] = pppEraseCharaParts->field_0x88[colorIndex + 3];

        DCFlushRange(colorPtr, 4);
    }
}
