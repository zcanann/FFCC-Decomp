#include "ffcc/pppCorona.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/linkage.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct CoronaWork {
    s16 m_shapeX;
    s16 m_shapeY;
    s16 m_shapeZ;
    u8 _pad0[2];
    float m_scaleX;
    float m_scaleY;
    float m_scaleZ;
    u8 _pad1[0x24];
    u8 m_alpha;
};

struct CoronaVecWork {
    u8 _pad0[0x10];
    Vec m_cameraOffset;
    u8 _pad1[4];
    Vec m_translate;
    u8 _pad2[6];
    u8 m_alpha;
};

STATIC_ASSERT(offsetof(CoronaWork, m_shapeX) == 0x0);
STATIC_ASSERT(offsetof(CoronaWork, m_scaleX) == 0x8);
STATIC_ASSERT(offsetof(CoronaVecWork, m_cameraOffset) == 0x10);
STATIC_ASSERT(offsetof(CoronaVecWork, m_translate) == 0x20);
STATIC_ASSERT(offsetof(CoronaVecWork, m_alpha) == 0x32);
STATIC_ASSERT(sizeof(CoronaDataOffsets) == 0x10);
STATIC_ASSERT(offsetof(CoronaDataOffsets, m_vecWorkOffset) == 0x8);
STATIC_ASSERT(offsetof(CoronaDataOffsets, m_workOffset) == 0xC);

static inline CoronaDataOffsets* GetCoronaDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<CoronaDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline CoronaWork* GetCoronaWork(_pppPObject* object, _pppCtrlTable* ctrl)
{
    CoronaDataOffsets* offsets = GetCoronaDataOffsets(ctrl);
    return reinterpret_cast<CoronaWork*>(object->m_workArea + offsets->m_workOffset);
}

static inline CoronaVecWork* GetCoronaVecWork(_pppPObject* object, _pppCtrlTable* ctrl)
{
    CoronaDataOffsets* offsets = GetCoronaDataOffsets(ctrl);
    return reinterpret_cast<CoronaVecWork*>(object->m_workArea + offsets->m_vecWorkOffset);
}

/*
 * --INFO--
 * PAL Address: 0x800df320
 * PAL Size: 464b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderCorona(_pppPObject* object, CoronaParam* data, _pppCtrlTable* ctrl)
{
    CoronaWork* work;
    CoronaVecWork* vecWork;
    pppCVECTOR color;
    pppFMATRIX mtx;
    Vec fromOrigin;
    Vec viewDir;
    pppShapeSt* shape;
    s32 shapeId;
    float mag;
    float scale;
    float distScale;

    work = GetCoronaWork(object, ctrl);
    vecWork = GetCoronaVecWork(object, ctrl);

    shapeId = data->m_dataValIndex;
    if (shapeId == 0xFFFF) {
        return;
    }

    shape = ppvEnv->m_resourceTables.m_shapeTablePtr[shapeId];

    PSMTXIdentity(mtx.value);

    viewDir.x = 320.0f;
    viewDir.y = 224.0f;
    viewDir.z = 0.0f;
    PSVECSubtract(&vecWork->m_cameraOffset, &viewDir, &fromOrigin);

    mag = PSVECMag(&fromOrigin);
    scale = data->m_distMin;
    if (mag < data->m_distRange) {
        distScale = data->m_distMax - data->m_distMin;
        distScale *= 1.0f - (mag / data->m_distRange);
        scale = data->m_distMin + distScale;
    }

    mtx.value[0][0] = ppvMng->m_scale.x * object->m_drawMatrix.value[0][0] * scale;
    mtx.value[1][1] = ppvMng->m_scale.y * object->m_drawMatrix.value[1][1] * scale;
    mtx.value[2][2] = ppvMng->m_scale.z * object->m_drawMatrix.value[2][2] * scale;
    mtx.value[0][3] = vecWork->m_translate.x;
    mtx.value[1][3] = vecWork->m_translate.y;
    mtx.value[2][3] = vecWork->m_translate.z;

    GXLoadPosMtxImm(mtx.value, 0);

    scale = work->m_scaleX * (f32)vecWork->m_alpha;
    u8 alpha = (u8)(s32)scale;
    color.rgba[0] = data->m_colorR;
    color.rgba[1] = data->m_colorG;
    color.rgba[2] = data->m_colorB;
    color.rgba[3] = alpha;

    pppSetDrawEnv(&color, (pppFMATRIX*)0, 0.0f, data->m_drawA, data->m_drawB, data->m_blendMode, 0, 1,
                  1, 0);
    pppSetBlendMode(data->m_blendMode);
    pppDrawShp(static_cast<long*>(shape->m_animData), work->m_shapeY, ppvEnv->m_materialSetPtr, data->m_blendMode);
}

/*
 * --INFO--
 * PAL Address: 0x800df4f0
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameCorona(_pppPObject* object, CoronaParam* data, _pppCtrlTable* ctrl)
{
    CoronaWork* work;
    pppShapeSt* shape;
    s32 shapeId;

    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetCoronaWork(object, ctrl);
    work->m_scaleY = work->m_scaleY + work->m_scaleZ;
    work->m_scaleX = work->m_scaleX + work->m_scaleY;

    shapeId = data->m_dataValIndex;
    if (shapeId == 0xFFFF) {
        return;
    }

    shape = ppvEnv->m_resourceTables.m_shapeTablePtr[shapeId];
    pppCalcFrameShape(static_cast<long*>(shape->m_animData), work->m_shapeX, work->m_shapeY, work->m_shapeZ, data->m_shapeStep);

    if (data->m_graphId == object->m_graphId) {
        work->m_scaleX += data->m_addX;
        work->m_scaleY += data->m_addY;
        work->m_scaleZ += data->m_addZ;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800df5e0
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructCorona(_pppPObject*, _pppCtrlTable*)
{
}

/*
 * --INFO--
 * PAL Address: 0x800df5e4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCorona(_pppPObject* object, _pppCtrlTable* ctrl)
{
    float fVar1 = 0.0f;
    CoronaWork* work = GetCoronaWork(object, ctrl);
    work->m_shapeZ = 0;
    work->m_shapeY = 0;
    work->m_shapeX = 0;
    work->m_scaleZ = fVar1;
    work->m_scaleY = fVar1;
    work->m_scaleX = fVar1;
}
