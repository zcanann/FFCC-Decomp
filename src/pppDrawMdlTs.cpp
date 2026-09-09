#include "ffcc/pppDrawMdlTs.h"
#include "global.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/pppColor.h"
#include "ffcc/pppPart.h"
#include "dolphin/types.h"
#include "ffcc/ppp_linkage.h"

STATIC_ASSERT(sizeof(PDrawMdlTs) == 0x30);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_graphId) == 0x00);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_modelIndex) == 0x04);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_blendMode) == 0x09);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_fogIndex) == 0x0A);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_cullMode) == 0x0B);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_zEnable) == 0x0C);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_colorUpdate) == 0x0D);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_zWrite) == 0x0E);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_depth) == 0x10);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_texCoordAdd) == 0x14);
STATIC_ASSERT(offsetof(PDrawMdlTs, m_lightTarget) == 0x2C);
STATIC_ASSERT(offsetof(VColor, m_color) == 0x08);

STATIC_ASSERT(sizeof(DrawMdlTsDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(DrawMdlTsDataOffsets, m_colorWorkOffset) == 0x0);
STATIC_ASSERT(offsetof(DrawMdlTsDataOffsets, m_texCoordOffset) == 0x8);

static inline DrawMdlTsDataOffsets* PppDrawMdlTsDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<DrawMdlTsDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline f32* PppDrawMdlTsTexCoords(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<f32*>(obj->m_workArea + PppDrawMdlTsDataOffsets(ctrl)->m_texCoordOffset);
}

static inline pppCVECTOR* PppDrawMdlTsColor(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    VColor* colorWork =
        reinterpret_cast<VColor*>(obj->m_workArea + PppDrawMdlTsDataOffsets(ctrl)->m_colorWorkOffset);

    return &colorWork->m_color;
}

/*
 * --INFO--
 * PAL Address: 0x800880C0
 * PAL Size: 48b
 * EN Address: 0x80087A5C
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMdlTsCon(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    f32* texCoords = PppDrawMdlTsTexCoords(obj, ctrl);
    f32 zero = 0.0f;

    texCoords[5] = zero;
    texCoords[4] = zero;
    texCoords[3] = zero;
    texCoords[2] = zero;
    texCoords[1] = zero;
    texCoords[0] = zero;
}

/*
 * --INFO--
 * PAL Address: 0x800880A0
 * PAL Size: 32b
 * EN Address: 0x80087A3C
 * EN Size: 32b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMdlTsCon3(_pppPObject* obj, _pppCtrlTable* ctrl)
{
    f32* texCoords = PppDrawMdlTsTexCoords(obj, ctrl);
    f32 zero = 0.0f;

    texCoords[5] = zero;
    texCoords[2] = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80087FD0
 * PAL Size: 208b
 * EN Address: 0x8008796C
 * EN Size: 208b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMdlTs(struct _pppPObject* obj, struct PDrawMdlTs* data, struct _pppCtrlTable* ctrl)
{
    f32* texCoords = PppDrawMdlTsTexCoords(obj, ctrl);

    if (ppvUserStopPartF != 0) {
        return;
    }

    texCoords[1] += texCoords[2];
    texCoords[0] += texCoords[1];
    texCoords[4] += texCoords[5];
    texCoords[3] += texCoords[4];

    if (data->m_graphId != obj->m_graphId) {
        return;
    }

    texCoords[0] += data->m_texCoordAdd[0];
    texCoords[1] += data->m_texCoordAdd[1];
    texCoords[2] += data->m_texCoordAdd[2];
    texCoords[3] += data->m_texCoordAdd[3];
    texCoords[4] += data->m_texCoordAdd[4];
    texCoords[5] += data->m_texCoordAdd[5];
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void pppDrawDrawMdlTs0(_pppPObject* obj, PDrawMdlTs* data, _pppCtrlTable* ctrl)
{
    pppSetDrawEnv(
        PppDrawMdlTsColor(obj, ctrl),
        &obj->m_drawMatrix,
        data->m_depth,
        data->m_lightTarget,
        data->m_fogIndex,
        data->m_blendMode,
        data->m_cullMode,
        data->m_zEnable,
        data->m_colorUpdate,
        data->m_zWrite);

    f32* texCoords = PppDrawMdlTsTexCoords(obj, ctrl);
    MaterialMan.SetTexScroll(
        texCoords[0], texCoords[3], 0.0f, 0.0f);

    pppSetBlendMode(data->m_blendMode);

    pppDrawMesh((pppModelSt*)ppvEnv->m_mapMeshPtr[data->m_modelIndex], obj->m_drawMatrixPtr, 1);
}

/*
 * --INFO--
 * PAL Address: 0x80087EF0
 * PAL Size: 224b
 * EN Address: 0x8008788C
 * EN Size: 224b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawDrawMdlTs(struct _pppPObject* obj, struct PDrawMdlTs* data, struct _pppCtrlTable* ctrl)
{
    if ((s32)data->m_modelIndex == 0xFFFF) {
        return;
    }

    pppDrawDrawMdlTs0(obj, data, ctrl);
}
