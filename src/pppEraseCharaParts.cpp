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

STATIC_ASSERT(sizeof(EraseCharaPartsDataOffsets) == 0x8);
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
void pppFrameEraseCharaParts(pppEraseCharaParts* eraseCharaParts, pppEraseCharaPartsStep* step,
                             _pppCtrlTable* ctrl)
{
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    EraseCharaPartsDataOffsets* offsets;
    int sourceColorOffset;
    u8* callbackColor;
    u8* sourceColor;

    if (ppvUserStopPartF == 0) {
        offsets = GetEraseCharaPartsDataOffsets(ctrl);
        sourceColorOffset = offsets->m_sourceColorOffset;
        callbackColor = GetEraseCharaPartsWork(eraseCharaParts, offsets->m_callbackColorOffset);
        sourceColor = GetEraseCharaPartsWork(eraseCharaParts, sourceColorOffset);
        handle = GetCharaHandlePtr(ppvMng->m_owner, 0);
        model = GetCharaModelPtr(handle);

        model->SetCallbackContext(callbackColor, step);

        callbackColor[0] = sourceColor[8];
        callbackColor[1] = sourceColor[9];
        callbackColor[2] = sourceColor[10];
        callbackColor[3] = sourceColor[11];

        DCFlushRange(callbackColor, 4);
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
void pppConstructEraseCharaParts(pppEraseCharaParts* eraseCharaParts, _pppCtrlTable* ctrl)
{
    EraseCharaPartsDataOffsets* offsets;
    CCharaPcs::CHandle* handle;
    CChara::CModel* model;
    u8* callbackColor;
    CGObject* owner;

    offsets = GetEraseCharaPartsDataOffsets(ctrl);
    callbackColor = GetEraseCharaPartsWork(eraseCharaParts, offsets->m_callbackColorOffset);
    owner = ppvMng->m_owner;
    callbackColor[0] = 0x80;
    callbackColor[1] = 0x80;
    callbackColor[2] = 0x80;
    callbackColor[3] = 0x80;

    handle = GetCharaHandlePtr(owner, 0);
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
void EraseCharaParts_DrawMeshDLCallback(CChara::CModel* model, void* callbackContext, void* callbackParam,
                                        int meshIndex, int displayListIndex, float (*) [4])
{
    u8* callbackColor = (u8*)callbackContext;
    pppEraseCharaPartsStep* step = (pppEraseCharaPartsStep*)callbackParam;
    EraseCharaPartsMesh* mesh = model->m_meshes;
    mesh += meshIndex;
    EraseCharaPartsMeshData* meshData = mesh->m_data;
    EraseCharaPartsDisplayList* displayList = meshData->m_displayLists;

    displayList += displayListIndex;
    MaterialMan.SetMaterial(model->m_data->m_materialSet, displayList->m_material, 0, (_GXTevScale)0);

    if ((step->m_meshIndex != 0xFF) && (meshIndex == step->m_meshIndex)) {
        GXSetArray(GX_VA_CLR0, callbackColor, 4);
    }

    GXCallDisplayList(displayList->m_data, displayList->m_size);
}
