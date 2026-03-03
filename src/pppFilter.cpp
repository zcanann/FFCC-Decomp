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

extern _pppEnvStLite* pppEnvStPtr;
extern float FLOAT_803320c8;
extern float FLOAT_803320cc;
extern float FLOAT_803320d0;
extern CUtil DAT_8032ec70;
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
    int serializedOffset = *param_3->m_serializedDataOffsets;
    unsigned char* filterBytes = (unsigned char*)pppFilterObj;
    _pppFilterSerializedData* serializedData = (_pppFilterSerializedData*)(filterBytes + serializedOffset + 0x80);
    _GXColor* colorPtr = &serializedData->m_color;

    if (param_2->m_dataValIndex == 0xFFFF) {
        DAT_8032ec70.RenderColorQuad(FLOAT_803320c8, FLOAT_803320c8, FLOAT_803320cc, FLOAT_803320d0, *colorPtr);
        return;
    }

    int textureIndex = 0;
    _pppTextureInfo* textureInfo = (_pppTextureInfo*)GetTexture__8CMapMeshFP12CMaterialSetRi(
        pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex], pppEnvStPtr->m_materialSetPtr, textureIndex);
    RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor(
        &DAT_8032ec70, FLOAT_803320c8, FLOAT_803320c8, FLOAT_803320cc, FLOAT_803320d0, &textureInfo->m_texObj, 0, 0,
        colorPtr, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
}
