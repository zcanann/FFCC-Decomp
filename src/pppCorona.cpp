#include "ffcc/pppCorona.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "ffcc/linkage.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct CoronaWork {
    s16 m_shapeFrame0;
    s16 m_shapeFrame1;
    s16 m_shapeFrame2;
    u8 _pad0[2];
    float m_alphaScale;
    float m_alphaScaleVelocity;
    float m_alphaScaleAccel;
    u8 _pad1[0x24];
    u8 m_alpha;
};

struct CoronaVecWork {
    u8 _pad0[0x10];
    Vec m_projected;
    u8 _pad1[4];
    Vec m_viewPosition;
    u8 _pad2[6];
    u8 m_alpha;
};

STATIC_ASSERT(offsetof(CoronaWork, m_shapeFrame0) == 0x0);
STATIC_ASSERT(offsetof(CoronaWork, m_alphaScale) == 0x8);
STATIC_ASSERT(offsetof(CoronaVecWork, m_projected) == 0x10);
STATIC_ASSERT(offsetof(CoronaVecWork, m_viewPosition) == 0x20);
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
    Vec fromScreenCenter;
    Vec screenCenter;
    pppShapeSt* shape;
    s32 shapeId;
    float centerDist;
    float scale;
    float distScale;

    work = GetCoronaWork(object, ctrl);
    vecWork = GetCoronaVecWork(object, ctrl);

    shapeId = data->m_dataValIndex;
    if (shapeId == 0xFFFF) {
        return;
    }

    shape = ppvEnv->m_shapeTablePtr[shapeId];

    PSMTXIdentity(mtx.value);

    screenCenter.x = 320.0f;
    screenCenter.y = 224.0f;
    screenCenter.z = 0.0f;
    PSVECSubtract(&vecWork->m_projected, &screenCenter, &fromScreenCenter);

    centerDist = PSVECMag(&fromScreenCenter);
    scale = data->m_distMin;
    if (centerDist < data->m_distRange) {
        distScale = data->m_distMax - data->m_distMin;
        distScale *= 1.0f - (centerDist / data->m_distRange);
        scale = data->m_distMin + distScale;
    }

    mtx.value[0][0] = ppvMng->m_scale.x * object->m_drawMatrix.value[0][0] * scale;
    mtx.value[1][1] = ppvMng->m_scale.y * object->m_drawMatrix.value[1][1] * scale;
    mtx.value[2][2] = ppvMng->m_scale.z * object->m_drawMatrix.value[2][2] * scale;
    mtx.value[0][3] = vecWork->m_viewPosition.x;
    mtx.value[1][3] = vecWork->m_viewPosition.y;
    mtx.value[2][3] = vecWork->m_viewPosition.z;

    GXLoadPosMtxImm(mtx.value, 0);

    u8 alpha = (u8)(s32)(work->m_alphaScale * (f32)vecWork->m_alpha);
    color.rgba[0] = data->m_colorR;
    color.rgba[1] = data->m_colorG;
    color.rgba[2] = data->m_colorB;
    color.rgba[3] = alpha;

    pppSetDrawEnv(&color, (pppFMATRIX*)0, 0.0f, data->m_drawA, data->m_drawB, data->m_blendMode, 0, 1,
                  1, 0);
    pppSetBlendMode(data->m_blendMode);
    pppDrawShp(static_cast<long*>(shape->m_animData), work->m_shapeFrame1, ppvEnv->m_materialSetPtr, data->m_blendMode);
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
    work->m_alphaScaleVelocity = work->m_alphaScaleVelocity + work->m_alphaScaleAccel;
    work->m_alphaScale = work->m_alphaScale + work->m_alphaScaleVelocity;

    shapeId = data->m_dataValIndex;
    if (shapeId == 0xFFFF) {
        return;
    }

    shape = ppvEnv->m_shapeTablePtr[shapeId];
    pppCalcFrameShape(static_cast<long*>(shape->m_animData), work->m_shapeFrame0, work->m_shapeFrame1, work->m_shapeFrame2, data->m_shapeStep);

    if (data->m_graphId == object->m_graphId) {
        work->m_alphaScale += data->m_alphaScaleAdd;
        work->m_alphaScaleVelocity += data->m_alphaScaleVelocityAdd;
        work->m_alphaScaleAccel += data->m_alphaScaleAccelAdd;
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
    float initValue = 0.0f;
    CoronaWork* work = GetCoronaWork(object, ctrl);
    work->m_shapeFrame2 = 0;
    work->m_shapeFrame1 = 0;
    work->m_shapeFrame0 = 0;
    work->m_alphaScaleAccel = initValue;
    work->m_alphaScaleVelocity = initValue;
    work->m_alphaScale = initValue;
}
