#include "ffcc/pppYmDrawMdlTexAnm.h"
#include "global.h"
#include "dolphin/os.h"
#include "ffcc/mapmesh.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_linkage.h"

static const char sYmDrawMdlTexAnmUvPeriodReportFmt[] = "PerU: %0.2f PerV: %0.2f\n";
static const char s_YmDrawMdlTexAnmConstructorJp[0x10] = {
    (char)0x83, (char)0x52, (char)0x83, (char)0x93, (char)0x83,
    (char)0x58, (char)0x83, (char)0x67, (char)0x83, (char)0x89,
    (char)0x83, (char)0x4E, (char)0x83, (char)0x5E, '\n',
    '\0',
};

struct pppYmDrawMdlTexAnmWork {
    u32 m_frame;
    s32 m_wait;
    u32 m_tilesU;
    u32 m_tilesV;
    f32 m_perU;
    f32 m_perV;
};

STATIC_ASSERT(sizeof(pppYmDrawMdlTexAnmStep) == 0x24);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_graphId) == 0x0);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_dataValIndex) == 0x4);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_blendMode) == 0x9);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_fogIndex) == 0xa);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_cullMode) == 0xb);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_zEnable) == 0xc);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_colorUpdate) == 0xd);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_zWrite) == 0xe);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_depth) == 0x10);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_waitStep) == 0x14);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_tilesU) == 0x18);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_tilesV) == 0x1c);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmStep, m_lightTarget) == 0x20);
STATIC_ASSERT(sizeof(pppYmDrawMdlTexAnmWork) == 0x18);

STATIC_ASSERT(sizeof(pppYmDrawMdlTexAnmDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmDataOffsets, m_colorBlockOffset) == 0x0);
STATIC_ASSERT(offsetof(pppYmDrawMdlTexAnmDataOffsets, m_workOffset) == 0x8);

static inline CMapMesh** GetMapMeshTable()
{
    return ppvEnv->m_mapMeshPtr;
}

static inline pppYmDrawMdlTexAnmDataOffsets* GetYmDrawMdlTexAnmDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppYmDrawMdlTexAnmDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline pppYmDrawMdlTexAnmWork* GetYmDrawMdlTexAnmWork(_pppPObject* object, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnmDataOffsets* offsets = GetYmDrawMdlTexAnmDataOffsets(ctrl);
    return reinterpret_cast<pppYmDrawMdlTexAnmWork*>(object->m_workArea + offsets->m_workOffset);
}

static inline pppYmDrawMdlTexAnmWork* GetYmDrawMdlTexAnmWork(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    return GetYmDrawMdlTexAnmWork(reinterpret_cast<_pppPObject*>(object), ctrl);
}

static inline VColor* GetYmDrawMdlTexAnmColorBlock(_pppPObject* object, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<VColor*>(
        object->m_workArea + GetYmDrawMdlTexAnmDataOffsets(ctrl)->m_colorBlockOffset);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 224b
 * EN Address: 0x8009beb8
 * EN Size: 320b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void SetUpPerUV(pppModelSt* model, f32& perU, f32& perV)
{
    s32 i;

    CMapMesh* mapMesh = model;
    for (i = 0; i < (s32)(u16)mapMesh->m_uvCount; i++) {
        if (perU < (f32)mapMesh->m_uvPairs[i].m_u) {
            perU = (f32)mapMesh->m_uvPairs[i].m_u;
        }

        if (perV < (f32)mapMesh->m_uvPairs[i].m_v) {
            perV = (f32)mapMesh->m_uvPairs[i].m_v;
        }
    }

    OSReport(sYmDrawMdlTexAnmUvPeriodReportFmt, perU, perV);
}

extern "C" {
/*
 * --INFO--
 * PAL Address: 8008a38c
 * PAL Size: 632b
 * EN Address: 0x80089D28
 * EN Size: 632b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDrawMdlTexAnm(_pppPObject* object, pppYmDrawMdlTexAnmStep* step, _pppCtrlTable* ctrl)
{
    pppModelSt* model;
    VColor* color;
    pppFMATRIX matrix;

    model = (pppModelSt*)GetMapMeshTable()[step->m_dataValIndex];
    if (model == NULL) {
        return;
    }

    color = GetYmDrawMdlTexAnmColorBlock(object, ctrl);

    pppUnitMatrix(matrix);
    matrix.value[2][2] *= -1.0f;

    pppMulMatrix(matrix, object->m_localMatrix, matrix);
    pppMulMatrix(object->m_drawMatrix, *(pppFMATRIX*)&ppvCameraMatrix, matrix);

    pppSetDrawEnv(
        &color->m_color, &object->m_drawMatrix, step->m_depth,
        step->m_lightTarget, step->m_fogIndex, step->m_blendMode, step->m_cullMode,
        step->m_zEnable, step->m_colorUpdate, step->m_zWrite);

    pppSetBlendMode(step->m_blendMode);
    pppDrawMesh(model, object->m_drawMatrixPtr, 1);
}

/*
 * --INFO--
 * PAL Address: 8008a604
 * PAL Size: 824b
 * EN Address: 0x80089FA0
 * EN Size: 824b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmDrawMdlTexAnm(_pppPObject* object, pppYmDrawMdlTexAnmStep* step, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    f32 perU;
    f32 perV;
    f32 uv;
    s32 i;

    work = GetYmDrawMdlTexAnmWork(object, ctrl);
    if (ppvUserStopPartF != 0) {
        return;
    }

    work->m_wait -= step->m_waitStep;
    work->m_tilesU = step->m_tilesU;
    work->m_tilesV = step->m_tilesV;

    if (work->m_wait > 0) {
        return;
    }

    mapMesh = GetMapMeshTable()[step->m_dataValIndex];
    perU = work->m_perU;
    perV = work->m_perV;
    if (!perU || !perV) {
        if (mapMesh != NULL) {
            SetUpPerUV((pppModelSt*)mapMesh, work->m_perU, work->m_perV);
        } else {
            return;
        }
    }

    work->m_frame += 1;
    work->m_wait = 0x200;

    for (i = 0; i < (s32)(u16)mapMesh->m_uvCount; i++) {
        uv = (f32)mapMesh->m_uvPairs[i].m_u;
        mapMesh->m_uvPairs[i].m_u = (s16)(uv + perU);
        if ((work->m_frame % step->m_tilesU) == 0) {
            mapMesh->m_uvPairs[i].m_u = (s16)((f32)mapMesh->m_uvPairs[i].m_u - perU * (f32)step->m_tilesU);
            uv = (f32)mapMesh->m_uvPairs[i].m_v;
            mapMesh->m_uvPairs[i].m_v = (s16)(uv + perV);
        }
        if (work->m_frame >= (step->m_tilesU * step->m_tilesV)) {
            mapMesh->m_uvPairs[i].m_v = (s16)((f32)mapMesh->m_uvPairs[i].m_v - perV * (f32)step->m_tilesV);
        }
    }

    DCFlushRange(mapMesh->m_uvPairs, (mapMesh->m_uvCount & 0xFFFF) << 2);

    if (work->m_frame >= (step->m_tilesU * step->m_tilesV)) {
        work->m_frame = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 8008a93c
 * PAL Size: 328b
 * EN Address: 0x8008A2D8
 * EN Size: 328b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmDrawMdlTexAnm(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    s32 i;
    s32 frameU;

    work = GetYmDrawMdlTexAnmWork(object, ctrl);
    if ((work->m_frame != 0) && ((mapMesh = GetMapMeshTable()[0]) != NULL)) {
        for (i = 0; i < (s32)(u16)mapMesh->m_uvCount; i++) {
            frameU = work->m_frame / work->m_tilesU;
            s32 frameModU = work->m_frame - frameU * work->m_tilesU;

            mapMesh->m_uvPairs[i].m_u =
                (s16)((f32)mapMesh->m_uvPairs[i].m_u - (f32)frameModU * work->m_perU);
            mapMesh->m_uvPairs[i].m_v =
                (s16)((f32)mapMesh->m_uvPairs[i].m_v - (f32)frameU * work->m_perV);
        }
        DCFlushRange(mapMesh->m_uvPairs, (mapMesh->m_uvCount & 0xFFFF) << 2);
    }

    work->m_frame = 0;
    work->m_tilesV = 0;
    work->m_tilesU = 0;
    work->m_wait = 0x200;
}

/*
 * --INFO--
 * PAL Address: 0x8008aa84
 * PAL Size: 316b
 * EN Address: 0x8008A420
 * EN Size: 316b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDrawMdlTexAnm(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnmWork* work;
    pppModelSt* model;
    f32 per;

    work = GetYmDrawMdlTexAnmWork(object, ctrl);
    work->m_frame = 0;
    work->m_wait = 0x200;

    OSReport(s_YmDrawMdlTexAnmConstructorJp);

    model = (pppModelSt*)GetMapMeshTable()[0];
    per = 0.0f;
    work->m_perU = per;
    work->m_perV = per;

    if (model != NULL) {
        SetUpPerUV(model, work->m_perU, work->m_perV);
    }
}
}
