#include "ffcc/pppEraseCharaParts.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"

#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>

typedef CChara::CMesh::CDisplayList EraseCharaPartsDisplayList;
typedef CChara::CMesh::CRefData EraseCharaPartsMeshData;
typedef CChara::CMesh EraseCharaPartsMesh;

static inline u8* GetEraseCharaPartsWork(pppEraseCharaParts* eraseCharaParts, s32 offset)
{
    return eraseCharaParts->m_object.m_workArea + offset;
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
void pppFrameEraseCharaParts(pppEraseCharaParts* pppEraseCharaParts, pppEraseCharaPartsUnkB* param_2,
                             pppEraseCharaPartsUnkC* param_3)
{
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    s32* offsets;
    int colorIndex;
    u8* dstColor;
    u8* srcColor;

    if (gPppCalcDisabled == 0) {
        offsets = param_3->m_serializedDataOffsets;
        colorIndex = offsets[0];
        dstColor = GetEraseCharaPartsWork(pppEraseCharaParts, offsets[1]);
        srcColor = GetEraseCharaPartsWork(pppEraseCharaParts, colorIndex);
        handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(ppvMng->m_owner), 0);
        model = GetCharaModelPtr(handle);

        model->SetCallbackContext(dstColor, param_2);

        dstColor[0] = srcColor[8];
        dstColor[1] = srcColor[9];
        dstColor[2] = srcColor[10];
        dstColor[3] = srcColor[11];

        DCFlushRange(dstColor, 4);
    }
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
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;

    handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(ppvMng->m_owner), 0);
    model = GetCharaModelPtr(handle);
    model->SetCallbackContext(0, 0);
    model->SetDrawMeshDLCallback(0);
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
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    u8* colorPtr;
    void* gObject;

    serializedDataOffsets = param_2->m_serializedDataOffsets;
    colorPtr = GetEraseCharaPartsWork(pppEraseCharaParts, serializedDataOffsets[1]);
    gObject = ppvMng->m_owner;
    colorPtr[0] = 0x80;
    colorPtr[1] = 0x80;
    colorPtr[2] = 0x80;
    colorPtr[3] = 0x80;

    handle = GetCharaHandlePtr(reinterpret_cast<CGObject*>(gObject), 0);
    model = GetCharaModelPtr(handle);
    model->SetDrawMeshDLCallback(EraseCharaParts_DrawMeshDLCallback);
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
    u8* colorArray = (u8*)param_2;
    pppEraseCharaPartsUnkB* callbackData = (pppEraseCharaPartsUnkB*)param_3;
    CMaterialMan* materialMan = &MaterialMan;
    EraseCharaPartsMesh* mesh = model->m_meshes;
    mesh += meshIndex;
    EraseCharaPartsMeshData* meshData = mesh->m_data;
    EraseCharaPartsDisplayList* displayList = meshData->m_displayLists;

    displayList += param_5;
    materialMan->SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);

    if ((callbackData->m_meshIndex != 0xFF) && (meshIndex == callbackData->m_meshIndex)) {
        GXSetArray((GXAttr)0xB, colorArray, 4);
    }

    GXCallDisplayList(displayList->m_data, displayList->m_size);
}
