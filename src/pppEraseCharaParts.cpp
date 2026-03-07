#include "ffcc/pppEraseCharaParts.h"
#include "ffcc/materialman.h"
#include "ffcc/partMng.h"

#include <dolphin/gx.h>

extern CMaterialMan MaterialMan;
extern int gPppCalcDisabled;

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
void DCFlushRange(void* ptr, unsigned long size);
}

struct EraseCharaPartsDisplayList {
    u32 m_size;
    void* m_data;
    u16 m_material;
};

struct EraseCharaPartsMeshData {
    u8 _pad0[0x50];
    EraseCharaPartsDisplayList* m_displayLists;
};

struct EraseCharaPartsMesh {
    u8 _pad0[0x8];
    EraseCharaPartsMeshData* m_data;
    u8 _padC[0x8];
};

struct EraseCharaPartsModelData {
    u8 _pad0[0x24];
    CMaterialSet* m_materialSet;
};

struct EraseCharaPartsModelView {
    u8 _pad0[0xA4];
    EraseCharaPartsModelData* m_data;
    u8 _padA8[0x4];
    EraseCharaPartsMesh* m_meshes;
};

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
    s8 callbackMeshIndex = ((pppEraseCharaPartsUnkB*)param_3)->m_meshIndex;
    EraseCharaPartsDisplayList* displayList =
        ((EraseCharaPartsModelView*)model)->m_meshes[meshIndex].m_data->m_displayLists + param_5;

    MaterialMan.SetMaterial(((EraseCharaPartsModelView*)model)->m_data->m_materialSet,
                            displayList->m_material, 0, (_GXTevScale)0);

    if ((callbackMeshIndex != -1) && (meshIndex == callbackMeshIndex)) {
        GXSetArray((GXAttr)0xB, param_2, 4);
    }

    GXCallDisplayList(displayList->m_data, displayList->m_size);
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
void pppConstructEraseCharaParts(pppEraseCharaParts* pppEraseCharaParts, pppEraseCharaPartsUnkC* param_2)
{
    s32* serializedDataOffsets;
    void* handle;
    int model;
    u8* colorPtr;
    void* gObject;

    serializedDataOffsets = param_2->m_serializedDataOffsets;
    colorPtr = (u8*)pppEraseCharaParts + 0x80 + serializedDataOffsets[1];
    gObject = pppMngStPtr->m_programInfoTable;
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
void pppDestructEraseCharaParts(pppEraseCharaParts*, pppEraseCharaPartsUnkC*)
{
    void* handle;
    int model;

    handle = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_programInfoTable, 0);
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
void pppFrameEraseCharaParts(pppEraseCharaParts* pppEraseCharaParts, pppEraseCharaPartsUnkB* param_2, pppEraseCharaPartsUnkC* param_3)
{
    void* handle;
    int model;
    s32* offsets;
    int colorIndex;
    u8* dstColor;
    u8* srcColor;

    if (gPppCalcDisabled == 0) {
        offsets = param_3->m_serializedDataOffsets;
        colorIndex = offsets[0];
        dstColor = (u8*)((char*)pppEraseCharaParts + 0x80 + offsets[1]);
        srcColor = (u8*)((char*)pppEraseCharaParts + 0x80 + colorIndex);
        handle = GetCharaHandlePtr__FP8CGObjectl(pppMngStPtr->m_programInfoTable, 0);
        model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

        *(u8**)(model + 0xE4) = dstColor;
        *(pppEraseCharaPartsUnkB**)(model + 0xE8) = param_2;

        dstColor[0] = srcColor[0];
        dstColor[1] = srcColor[1];
        dstColor[2] = srcColor[2];
        dstColor[3] = srcColor[3];

        DCFlushRange(dstColor, 4);
    }
}
