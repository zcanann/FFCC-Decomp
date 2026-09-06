#include "global.h"
#include "ffcc/pppFilter.h"
#include "ffcc/mapmesh.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include <stddef.h>

struct _pppFilterSerializedData {
    unsigned int m_unk80;
    unsigned int m_unk84;
    _GXColor m_color;
};

STATIC_ASSERT(sizeof(pppFilterDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(pppFilterDataOffsets, m_serializedDataOffset) == 0x0);

static inline pppFilterDataOffsets* GetFilterDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppFilterDataOffsets*>(ctrl->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x8015a788
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderFilter(_pppPObject* pppFilterObj, pppFilterStep* param_2, _pppCtrlTable* param_3)
{
    int serializedOffset = GetFilterDataOffsets(param_3)->m_serializedDataOffset;
    _pppFilterSerializedData* serializedData =
        (_pppFilterSerializedData*)(pppFilterObj->m_workArea + serializedOffset);

    if (param_2->m_dataValIndex == 0xFFFF) {
        gUtil.RenderColorQuad(
            0.0f, 0.0f, 640.0f, 448.0f,
            serializedData->m_color);
        return;
    }

    int textureIndex = 0;
    CTexture* textureInfo = (CTexture*)ppvEnv->m_mapMeshPtr[param_2->m_dataValIndex]->GetTexture(
        ppvEnv->m_materialSetPtr, textureIndex);
    gUtil.RenderTextureQuad(
        0.0f, 0.0f, 640.0f, 448.0f, &textureInfo->m_texObj,
        0, 0, &serializedData->m_color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
}





/*
 * --INFO--
 * PAL Address: 0x8015a8c8
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameFilter(_pppPObject*, pppFilterStep*, _pppCtrlTable*)
{
	volatile int* stateFlag = &ppvUserStopPartF;
	if (*stateFlag == 0) {
		return;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructFilter(_pppPObjLink*, _pppCtrlTable*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructFilter(_pppPObjLink*, _pppCtrlTable*)
{
	// TODO
}
