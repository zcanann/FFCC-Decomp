#include "ffcc/pppFilter.h"
#include "ffcc/mapmesh.h"
#include "ffcc/textureman.h"
extern "C" {
extern const float kConstrainCameraDirScaleOne = 1.0f;
extern const float kConstrainCameraDirBaseFov = 25.0f;
extern const float kConstrainCameraDirWideAspect = 1.3333f;
extern const float kConstrainCameraDirZero = 0.0f;
extern const float kPppFilterScreenMin;
extern const float kPppFilterScreenMaxX;
extern const float kPppFilterScreenMaxY[2];
}
#include "ffcc/util.h"
#include <stddef.h>

struct _pppFilterSerializedData {
    unsigned int m_unk80;
    unsigned int m_unk84;
    _GXColor m_color;
};

struct pppFilterUnkB {
    unsigned int m_unk0;
    int m_dataValIndex;
};

/*
 * --INFO--
 * PAL Address: 0x8015a788
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderFilter(_pppPObject* pppFilterObj, pppFilterUnkB* param_2, _pppCtrlTable* param_3)
{
    int* serializedDataOffsets = param_3->m_serializedDataOffsets;
    int serializedOffset = *serializedDataOffsets;
    _pppFilterSerializedData* serializedData =
        (_pppFilterSerializedData*)(pppFilterObj->m_workArea + serializedOffset);

    if (param_2->m_dataValIndex == 0xFFFF) {
        gUtil.RenderColorQuad(
            kPppFilterScreenMin, kPppFilterScreenMin, kPppFilterScreenMaxX, kPppFilterScreenMaxY[0],
            serializedData->m_color);
        return;
    }

    int textureIndex = 0;
    CTexture* textureInfo = (CTexture*)ppvEnv->m_mapMeshPtr[param_2->m_dataValIndex]->GetTexture(
        ppvEnv->m_materialSetPtr, textureIndex);
    gUtil.RenderTextureQuad(
        kPppFilterScreenMin, kPppFilterScreenMin, kPppFilterScreenMaxX, kPppFilterScreenMaxY[0], &textureInfo->m_texObj,
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
void pppFrameFilter(_pppPObject*, void*, _pppCtrlTable*)
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
