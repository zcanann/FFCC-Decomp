#include "ffcc/pppEraseCharaParts.h"
#include "global.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/partMng.h"
#include "ffcc/pppYmEnv.h"

#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>

typedef CChara::CMesh::CDisplayList EraseCharaPartsDisplayList;
typedef CChara::CMesh::CRefData EraseCharaPartsMeshData;
typedef CChara::CMesh EraseCharaPartsMesh;

struct EraseCharaPartsDataOffsets {
    s32 m_sourceColorOffset;
    s32 m_callbackColorOffset;
};

STATIC_ASSERT(offsetof(EraseCharaPartsDataOffsets, m_sourceColorOffset) == 0x0);
STATIC_ASSERT(offsetof(EraseCharaPartsDataOffsets, m_callbackColorOffset) == 0x4);

void EraseCharaParts_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);

static inline EraseCharaPartsDataOffsets* GetEraseCharaPartsDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<EraseCharaPartsDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline u8* GetEraseCharaPartsWork(pppEraseCharaParts* eraseCharaParts, s32 offset)
{
    return eraseCharaParts->m_workArea + offset;
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
void pppFrameEraseCharaParts(pppEraseCharaParts* pppEraseCharaParts, pppEraseCharaPartsStep* param_2,
                             _pppCtrlTable* param_3)
{
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    EraseCharaPartsDataOffsets* offsets;
    int colorIndex;
    u8* dstColor;
    u8* srcColor;

    if (ppvUserStopPartF == 0) {
        offsets = GetEraseCharaPartsDataOffsets(param_3);
        colorIndex = offsets->m_sourceColorOffset;
        dstColor = GetEraseCharaPartsWork(pppEraseCharaParts, offsets->m_callbackColorOffset);
        srcColor = GetEraseCharaPartsWork(pppEraseCharaParts, colorIndex);
        handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
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
void pppDestructEraseCharaParts(pppEraseCharaParts*, _pppCtrlTable*)
{
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;

    handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
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
void pppConstructEraseCharaParts(pppEraseCharaParts* pppEraseCharaParts, _pppCtrlTable* param_2)
{
    EraseCharaPartsDataOffsets* serializedDataOffsets;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    u8* colorPtr;
    void* gObject;

    serializedDataOffsets = GetEraseCharaPartsDataOffsets(param_2);
    colorPtr = GetEraseCharaPartsWork(pppEraseCharaParts, serializedDataOffsets->m_callbackColorOffset);
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
    pppEraseCharaPartsStep* callbackData = (pppEraseCharaPartsStep*)param_3;
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
