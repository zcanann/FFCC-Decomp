#include "ffcc/pppFilter.h"
#include "ffcc/mapmesh.h"
#include "ffcc/textureman.h"
extern "C" {
extern const float kPppFilterScreenMin;
extern const float kPppFilterScreenMaxX;
extern const float kPppFilterScreenMaxY;
extern int gPppCalcDisabled;
}
#include "ffcc/util.h"
#include <stddef.h>

struct _pppFilterSerializedData {
    unsigned int m_unk80;
    unsigned int m_unk84;
    _GXColor m_color;
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
void pppRenderFilter(pppFilter* pppFilterObj, pppFilterUnkB* param_2, _pppCtrlTable* param_3)
{
    struct FilterStep {
        unsigned int unk0;
        int dataValIndex;
    };

    FilterStep* step = (FilterStep*)param_2;
    int* serializedDataOffsets = param_3->m_serializedDataOffsets;
    int serializedOffset = *serializedDataOffsets;
    _pppFilterSerializedData* serializedData = (_pppFilterSerializedData*)((unsigned char*)pppFilterObj + serializedOffset + 0x80);

    if (step->dataValIndex == 0xFFFF) {
        gUtil.RenderColorQuad(
            kPppFilterScreenMin, kPppFilterScreenMin, kPppFilterScreenMaxX, kPppFilterScreenMaxY, serializedData->m_color);
        return;
    }

    int textureIndex = 0;
    CTexture* textureInfo = (CTexture*)pppEnvStPtr->m_mapMeshPtr[step->dataValIndex]->GetTexture(
        pppEnvStPtr->m_materialSetPtr, textureIndex);
    gUtil.RenderTextureQuad(
        kPppFilterScreenMin, kPppFilterScreenMin, kPppFilterScreenMaxX, kPppFilterScreenMaxY, &textureInfo->m_texObj,
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
	volatile int* stateFlag = &gPppCalcDisabled;
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
