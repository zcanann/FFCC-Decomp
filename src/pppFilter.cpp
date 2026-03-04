#include "ffcc/pppFilter.h"
#include "ffcc/mapmesh.h"
#include "ffcc/util.h"
#include <stddef.h>

class CMaterialSet;
struct _pppEnvStLite {
    void* m_stagePtr;
    CMaterialSet* m_materialSetPtr;
    CMapMesh** m_mapMeshPtr;
};

extern _pppEnvStLite* lbl_8032ED54;
extern float lbl_803320C8;
extern float lbl_803320CC;
extern float lbl_803320D0;
extern CUtil lbl_8032EC70;
extern int lbl_8032ED70;

struct _pppFilterSerializedData {
    unsigned int m_unk80;
    unsigned int m_unk84;
    _GXColor m_color;
};

struct _pppTextureInfo {
    char padding_0x00[0x28];
    _GXTexObj m_texObj;
};

extern "C" {
int GetTexture__8CMapMeshFP12CMaterialSetRi(CMapMesh* mapMesh, CMaterialSet* materialSet, int& textureIndex);
void RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor(
    CUtil* util, float x0, float y0, float x1, float y1, _GXTexObj* texObj, Vec2d* uv0, Vec2d* uv1, _GXColor* color,
    _GXBlendFactor srcFactor, _GXBlendFactor dstFactor);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppConstructFilter(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDestructFilter(void)
{
	// TODO
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
void pppFrameFilter(void)
{
	volatile int* stateFlag = &lbl_8032ED70;
	if (*stateFlag == 0) {
		return;
	}
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
void pppRenderFilter(pppFilter* pppFilterObj, UnkB* param_2, UnkC* param_3)
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
        lbl_8032EC70.RenderColorQuad(
            lbl_803320C8, lbl_803320C8, lbl_803320CC, lbl_803320D0, serializedData->m_color);
        return;
    }

    int textureIndex = 0;
    _pppTextureInfo* textureInfo = (_pppTextureInfo*)GetTexture__8CMapMeshFP12CMaterialSetRi(
        lbl_8032ED54->m_mapMeshPtr[step->dataValIndex], lbl_8032ED54->m_materialSetPtr, textureIndex);
    RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor(
        &lbl_8032EC70, lbl_803320C8, lbl_803320C8, lbl_803320CC, lbl_803320D0, &textureInfo->m_texObj, 0, 0,
        &serializedData->m_color, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
}
