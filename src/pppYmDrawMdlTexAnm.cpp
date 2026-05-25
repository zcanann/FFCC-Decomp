#include "ffcc/pppYmDrawMdlTexAnm.h"
#include "dolphin/os.h"
#include "ffcc/mapmesh.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_linkage.h"

struct pppYmDrawMdlTexAnmWork {
    u32 m_frame;
    u32 m_wait;
    u32 m_tilesU;
    u32 m_tilesV;
    f32 m_perU;
    f32 m_perV;
};

struct pppYmDrawMdlTexAnmColorBlock {
    u8 _pad0[8];
    pppCVECTOR m_color;
};

extern "C" {
extern f32 FLOAT_80330548;
extern f32 FLOAT_8033054c;
extern const char s_PerU___0_2f_PerV___0_2f_801d9c38[] = "PerU: %0.2f PerV: %0.2f\n";
extern const char s_YmDrawMdlTexAnmConstructorJp[0x10] = {
    (char)0x83, (char)0x52, (char)0x83, (char)0x93, (char)0x83,
    (char)0x58, (char)0x83, (char)0x67, (char)0x83, (char)0x89,
    (char)0x83, (char)0x4E, (char)0x83, (char)0x5E, '\n',
    '\0',
};
}

static inline CMapMesh** GetMapMeshTable()
{
    return ppvEnv->m_mapMeshPtr;
}

static inline pppYmDrawMdlTexAnmWork* GetYmDrawMdlTexAnmWork(_pppPObject* object, _pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppYmDrawMdlTexAnmWork*>(object->m_workArea + ctrl->m_serializedDataOffsets[2]);
}

static inline pppYmDrawMdlTexAnmColorBlock* GetYmDrawMdlTexAnmColorBlock(_pppPObject* object,
                                                                         _pppCtrlTable* ctrl)
{
    return reinterpret_cast<pppYmDrawMdlTexAnmColorBlock*>(object->m_workArea + ctrl->m_serializedDataOffsets[0]);
}

static inline void SetUpPerUV(CMapMesh* mapMesh, f32& perU, f32& perV)
{
    s32 uvByteOffset;
    s32 i;

    for (i = 0, uvByteOffset = i; i < (s32)(u16)mapMesh->m_uvCount; i++) {
        if (perU < (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset)) {
            perU = (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset);
        }

        if (perV < (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset + 2)) {
            perV = (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset + 2);
        }

        uvByteOffset += 4;
    }

    OSReport(s_PerU___0_2f_PerV___0_2f_801d9c38, perU, perV);
}

void pppUnitMatrix(pppFMATRIX&);
void pppMulMatrix(pppFMATRIX&, pppFMATRIX, pppFMATRIX);

extern "C" {
/*
 * --INFO--
 * PAL Address: 8008a38c
 * PAL Size: 632b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDrawMdlTexAnm(_pppPObject* object, pppYmDrawMdlTexAnmStep* step, _pppCtrlTable* ctrl)
{
    pppModelSt* model;
    u8* colorBase;
    pppFMATRIX matrix;
    u8* initBytes;
    u8* stepBytes;

    model = (pppModelSt*)GetMapMeshTable()[step->m_dataValIndex];
    if (model == NULL) {
        return;
    }

    colorBase = reinterpret_cast<u8*>(GetYmDrawMdlTexAnmColorBlock(object, ctrl));

    pppUnitMatrix(matrix);
    matrix.value[2][2] *= FLOAT_80330548;

    pppMulMatrix(matrix, object->m_localMatrix, matrix);
    pppMulMatrix(object->m_drawMatrix, *(pppFMATRIX*)&ppvCameraMatrix, matrix);

    initBytes = (u8*)&step->m_initWOrk;
    stepBytes = (u8*)&step->m_stepValue;
    pppSetDrawEnv(
        reinterpret_cast<pppCVECTOR*>(colorBase + 8), &object->m_drawMatrix, step->m_arg3,
        step->m_payload[0xC], initBytes[2], initBytes[1], initBytes[3], stepBytes[0], stepBytes[1], stepBytes[2]);

    pppSetBlendMode(initBytes[1]);
    pppDrawMesh(model, object->m_drawMatrixPtr, 1);
}

/*
 * --INFO--
 * PAL Address: 8008a604
 * PAL Size: 824b
 * EN Address: TODO
 * EN Size: TODO
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
    s32 uvByteOffset;
    s32 i;

    work = GetYmDrawMdlTexAnmWork(object, ctrl);
    if (gPppCalcDisabled != 0) {
        return;
    }

    work->m_wait -= *(s32*)step->m_payload;
    work->m_tilesU = *(u32*)(step->m_payload + 4);
    work->m_tilesV = *(u32*)(step->m_payload + 8);

    if ((s32)work->m_wait > 0) {
        return;
    }

    mapMesh = GetMapMeshTable()[step->m_dataValIndex];
    perU = work->m_perU;
    perV = work->m_perV;
    if ((perU == FLOAT_8033054c) || (perV == FLOAT_8033054c)) {
        if (mapMesh != NULL) {
            SetUpPerUV(mapMesh, work->m_perU, work->m_perV);
        } else {
            return;
        }
    }

    work->m_frame += 1;
    work->m_wait = 0x200;

    for (uvByteOffset = i = 0; i < (s32)(u16)mapMesh->m_uvCount; i++) {
        uv = (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset);
        *(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset) = (s16)(uv + perU);
        if ((work->m_frame % *(u32*)(step->m_payload + 4)) == 0) {
            *(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset) = (s16)(-((perU * (f32)*(u32*)(step->m_payload + 4)) -
                                                                       (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset)));
            uv = (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset + 2);
            *(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset + 2) = (s16)(uv + perV);
        }
        if (work->m_frame >= (u32)(*(s32*)(step->m_payload + 4) * *(s32*)(step->m_payload + 8))) {
            *(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset + 2) =
                (s16)(-((perV * (f32)*(u32*)(step->m_payload + 8)) -
                        (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset + 2)));
        }
        uvByteOffset += 4;
    }

    DCFlushRange(mapMesh->m_uvPairs, (mapMesh->m_uvCount & 0xFFFF) << 2);

    if (work->m_frame >= (u32)(*(s32*)(step->m_payload + 4) * *(s32*)(step->m_payload + 8))) {
        work->m_frame = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 8008a93c
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmDrawMdlTexAnm(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnmWork* work;
    s32 uvByteOffset;
    s32 uvByteOffsetV;
    CMapMesh* mapMesh;
    s32 i;
    s32 frameU;
    u32 tilesU;

    work = GetYmDrawMdlTexAnmWork(reinterpret_cast<_pppPObject*>(object), ctrl);
    if ((work->m_frame != 0) && ((mapMesh = GetMapMeshTable()[0]) != NULL)) {
        for (uvByteOffset = i = 0; i < (s32)(u16)mapMesh->m_uvCount; i++) {
            uvByteOffsetV = uvByteOffset + 2;
            tilesU = work->m_tilesU;
            frameU = work->m_frame / tilesU;
            s32 frameModU = work->m_frame - frameU * tilesU;

            *(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset) =
                (s16)(int)-(((f32)frameModU * work->m_perU) -
                            (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffset));
            uvByteOffset += 4;
            *(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffsetV) =
                (s16)(int)-(((f32)frameU * work->m_perV) -
                            (f32)*(s16*)((u8*)mapMesh->m_uvPairs + uvByteOffsetV));
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDrawMdlTexAnm(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnmWork* work;
    pppModelSt* model;
    f32 per;

    work = GetYmDrawMdlTexAnmWork(reinterpret_cast<_pppPObject*>(object), ctrl);
    work->m_frame = 0;
    work->m_wait = 0x200;

    OSReport(s_YmDrawMdlTexAnmConstructorJp);

    model = (pppModelSt*)GetMapMeshTable()[0];
    per = FLOAT_8033054c;
    work->m_perU = per;
    work->m_perV = per;

    if (model != NULL) {
        SetUpPerUV((CMapMesh*)model, work->m_perU, work->m_perV);
    }
}
}
