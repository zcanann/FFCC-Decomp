#include "ffcc/pppYmDrawMdlTexAnm.h"
#include "dolphin/os.h"

struct pppYmDrawMdlTexAnmWork {
    u32 m_frame;
    u32 m_wait;
    u32 m_tilesU;
    u32 m_tilesV;
    f32 m_perU;
    f32 m_perV;
};

struct CMapMeshUVLayout {
    u8 _pad0[0x06];
    u16 m_uvCount;
    u8 _pad1[0x30];
    s16* m_uvPairs;
};

extern s32 DAT_8032ed70;
extern f32 FLOAT_80330548;
extern f32 FLOAT_8033054c;
extern _pppEnvSt* pppEnvStPtr;
extern char DAT_801d9c54[];
extern char s_PerU___0_2f_PerV___0_2f_801d9c38[];

extern "C" {
void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX* matrix);
void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX* out, pppFMATRIX* a, pppFMATRIX* b);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void* color, void* matrix, f32 z, u8 a3, u8 a4, u8 a5,
                                                                 u8 a6, u8 a7, u8 a8, u8 a9);
void pppSetBlendMode__FUc(u8 mode);
void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt* model, Vec* matrixPtr, s32 flag);

/*
 * --INFO--
 * PAL Address: 0x8008aa84
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmOffsets* param2, void* param3)
{
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    CMapMeshUVLayout* uvLayout;
    s16* uvPairs;
    int i;

    (void)param3;
    work = (pppYmDrawMdlTexAnmWork*)((u8*)param1 + 0x80 + param2->m_serializedDataOffsets[2]);
    work->m_frame = 0;
    work->m_wait = 0x200;

    OSReport(DAT_801d9c54);

    work->m_perU = FLOAT_8033054c;
    work->m_perV = FLOAT_8033054c;

    mapMesh = pppEnvStPtr->m_mapMeshPtr;
    if (mapMesh != NULL) {
        uvLayout = (CMapMeshUVLayout*)mapMesh;
        uvPairs = uvLayout->m_uvPairs;
        for (i = 0; i < (int)uvLayout->m_uvCount; i++) {
            if (work->m_perU < (f32)uvPairs[0]) {
                work->m_perU = (f32)uvPairs[0];
            }
            if (work->m_perV < (f32)uvPairs[1]) {
                work->m_perV = (f32)uvPairs[1];
            }
            uvPairs += 2;
        }
        OSReport(s_PerU___0_2f_PerV___0_2f_801d9c38, work->m_perU, work->m_perV);
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
void pppDestructYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmOffsets* param2, void* param3)
{
    (void)param3;
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    CMapMeshUVLayout* uvLayout;
    s16* uvPairs;
    u32 frameIndex;
    u32 i;

    work = (pppYmDrawMdlTexAnmWork*)((u8*)param1 + 0x80 + param2->m_serializedDataOffsets[2]);
    frameIndex = work->m_frame;
    if ((frameIndex != 0) && ((mapMesh = pppEnvStPtr->m_mapMeshPtr) != NULL)) {
        uvLayout = (CMapMeshUVLayout*)mapMesh;
        uvPairs = uvLayout->m_uvPairs;
        for (i = 0; i < (u32)uvLayout->m_uvCount; i++) {
            u32 frameU = frameIndex / work->m_tilesU;
            uvPairs[0] = (s16)((f32)uvPairs[0] - ((f32)(frameIndex - frameU * work->m_tilesU) * work->m_perU));
            uvPairs[1] = (s16)((f32)uvPairs[1] - ((f32)frameU * work->m_perV));
            uvPairs += 2;
        }

        DCFlushRange(uvLayout->m_uvPairs, (u32)uvLayout->m_uvCount << 2);
    }

    work->m_frame = 0;
    work->m_tilesV = 0;
    work->m_tilesU = 0;
    work->m_wait = 0x200;
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
void pppFrameYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmStep* param2, pppYmDrawMdlTexAnmOffsets* param3)
{
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    CMapMeshUVLayout* uvLayout;
    s16* uvPairs;
    s32* payload;
    s32 i;

    work = (pppYmDrawMdlTexAnmWork*)((u8*)param1 + 0x80 + param3->m_serializedDataOffsets[2]);
    if (DAT_8032ed70 != 0) {
        return;
    }

    payload = (s32*)param2->m_payload;
    work->m_wait -= payload[0];
    work->m_tilesU = (u32)payload[1];
    work->m_tilesV = (u32)payload[2];

    if ((s32)work->m_wait > 0) {
        return;
    }

    mapMesh = ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param2->m_dataValIndex];
    if ((work->m_perU == FLOAT_8033054c) || (work->m_perV == FLOAT_8033054c)) {
        if (mapMesh == NULL) {
            return;
        }

        uvLayout = (CMapMeshUVLayout*)mapMesh;
        uvPairs = uvLayout->m_uvPairs;
        for (i = 0; i < (s32)(u32)uvLayout->m_uvCount; i++) {
            if (work->m_perU < (f32)uvPairs[0]) {
                work->m_perU = (f32)uvPairs[0];
            }
            if (work->m_perV < (f32)uvPairs[1]) {
                work->m_perV = (f32)uvPairs[1];
            }
            uvPairs += 2;
        }
        OSReport(s_PerU___0_2f_PerV___0_2f_801d9c38, work->m_perU, work->m_perV);
    }

    uvLayout = (CMapMeshUVLayout*)mapMesh;
    uvPairs = uvLayout->m_uvPairs;

    work->m_frame += 1;
    work->m_wait = 0x200;

    for (i = 0; i < (s32)(u32)uvLayout->m_uvCount; i++) {
        uvPairs[0] = (s16)((f32)uvPairs[0] + work->m_perU);
        if (work->m_frame == (work->m_frame / (u32)payload[1]) * (u32)payload[1]) {
            uvPairs[0] = (s16)(-((work->m_perU * (f32)(u32)payload[1]) - (f32)uvPairs[0]));
            uvPairs[1] = (s16)((f32)uvPairs[1] + work->m_perV);
        }
        if ((u32)(payload[1] * payload[2]) <= work->m_frame) {
            uvPairs[1] = (s16)(-((work->m_perV * (f32)(u32)payload[2]) - (f32)uvPairs[1]));
        }
        uvPairs += 2;
    }

    DCFlushRange(uvLayout->m_uvPairs, (u32)uvLayout->m_uvCount << 2);

    if ((u32)(payload[1] * payload[2]) <= work->m_frame) {
        work->m_frame = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 8008a38c
 * PAL Size: 632b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmDrawMdlTexAnm(pppYmDrawMdlTexAnm* param1, pppYmDrawMdlTexAnmStep* param2, pppYmDrawMdlTexAnmOffsets* param3)
{
    pppModelSt* model;
    pppFMATRIX matrix0;
    pppFMATRIX matrix1;
    pppFMATRIX matrix2;
    pppFMATRIX matrix3;
    pppFMATRIX matrix4;
    u8* initBytes;
    u8* stepBytes;
    s32 colorOffset;

    model = (pppModelSt*)((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[param2->m_dataValIndex];
    if (model == NULL) {
        return;
    }

    colorOffset = param3->m_serializedDataOffsets[0];

    pppUnitMatrix__FR10pppFMATRIX(&matrix4);
    matrix2 = matrix4;
    matrix2.value[2][2] *= FLOAT_80330548;

    matrix3 = param1->field0_0x0.m_localMatrix;
    matrix4.value[2][2] = matrix2.value[2][2];
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&matrix4, &matrix3, &matrix2);

    matrix0 = matrix4;
    matrix1 = *(pppFMATRIX*)&ppvCameraMatrix0;
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX((pppFMATRIX*)((u8*)param1 + 0x40), &matrix1, &matrix0);

    initBytes = (u8*)&param2->m_initWOrk;
    stepBytes = (u8*)&param2->m_stepValue;
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc((u8*)param1 + 0x88 + colorOffset, (u8*)param1 + 0x40,
                                                               param2->m_arg3, param2->m_payload[0xC], initBytes[2],
                                                               initBytes[1], initBytes[3], stepBytes[0], stepBytes[1],
                                                               stepBytes[2]);

    pppSetBlendMode__FUc(initBytes[1]);
    pppDrawMesh__FP10pppModelStP3Veci(model, *(Vec**)((u8*)param1 + 0x70), 1);
}

}
