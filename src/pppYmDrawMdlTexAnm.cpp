#include "ffcc/pppYmDrawMdlTexAnm.h"
#include "dolphin/os.h"
#include "ffcc/ppp_linkage.h"

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

extern f32 FLOAT_80330548;
extern f32 FLOAT_8033054c;
extern char DAT_801d9c54[];
extern char s_PerU___0_2f_PerV___0_2f_801d9c38[];

void pppSetBlendMode(unsigned char);

extern "C" {
void pppUnitMatrix__FR10pppFMATRIX(pppFMATRIX* matrix);
void pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(pppFMATRIX* out, pppFMATRIX* a, pppFMATRIX* b);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void* color, void* matrix, f32 z, u8 a3, u8 a4, u8 a5,
                                                                 u8 a6, u8 a7, u8 a8, u8 a9);

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
void pppConstructYmDrawMdlTexAnm(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    CMapMeshUVLayout* uvLayout;
    s32 uvByteOffset;
    s16 uvValue;
    int i;

    work = (pppYmDrawMdlTexAnmWork*)((u8*)object + 0x80 + ctrl->m_serializedDataOffsets[2]);
    work->m_frame = 0;
    work->m_wait = 0x200;

    OSReport(DAT_801d9c54);

    mapMesh = ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[0];
    work->m_perU = FLOAT_8033054c;
    work->m_perV = work->m_perU;

    if (mapMesh != NULL) {
        uvLayout = (CMapMeshUVLayout*)mapMesh;
        uvByteOffset = 0;

        for (i = 0; i < (s32)(u16)uvLayout->m_uvCount; i++) {
            uvValue = *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset);
            if (work->m_perU < (f32)uvValue) {
                work->m_perU = (f32)uvValue;
            }

            uvValue = *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2);
            if (work->m_perV < (f32)uvValue) {
                work->m_perV = (f32)uvValue;
            }

            uvByteOffset += 4;
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
void pppDestructYmDrawMdlTexAnm(_pppPObjLink* object, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnmWork* work;
    CMapMeshUVLayout* uvLayout;
    s32 uvByteOffset;
    u32 frameU;
    s32 i;

    work = (pppYmDrawMdlTexAnmWork*)((u8*)object + 0x80 + ctrl->m_serializedDataOffsets[2]);
    if ((work->m_frame != 0) && ((uvLayout = (CMapMeshUVLayout*)((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[0]) != NULL)) {
        uvByteOffset = 0;
        for (i = 0; i < (s32)(u16)uvLayout->m_uvCount; i++) {
            s32 uvByteOffsetV = uvByteOffset + 2;
            frameU = work->m_frame / work->m_tilesU;
            u32 frameModU = work->m_frame - frameU * work->m_tilesU;

            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset) =
                (s16)(int)-(((f32)frameModU * work->m_perU) -
                            (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset));
            uvByteOffset += 4;
            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffsetV) =
                (s16)(int)-(((f32)frameU * work->m_perV) -
                            (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffsetV));
        }

        DCFlushRange(uvLayout->m_uvPairs, (u32)(u16)uvLayout->m_uvCount << 2);
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
void pppFrameYmDrawMdlTexAnm(_pppPObject* object, pppYmDrawMdlTexAnmStep* step, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    CMapMeshUVLayout* uvLayout;
    s32* payload;
    s32 uvByteOffset;
    s32 i;

    work = (pppYmDrawMdlTexAnmWork*)((u8*)object + 0x80 + ctrl->m_serializedDataOffsets[2]);
    if (gPppCalcDisabled != 0) {
        return;
    }

    payload = (s32*)step->m_payload;
    work->m_wait -= payload[0];
    work->m_tilesU = (u32)payload[1];
    work->m_tilesV = (u32)payload[2];

    if ((s32)work->m_wait > 0) {
        return;
    }

    mapMesh = ((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[step->m_dataValIndex];
    if ((work->m_perU == FLOAT_8033054c) || (work->m_perV == FLOAT_8033054c)) {
        if (mapMesh == NULL) {
            return;
        }

        uvLayout = (CMapMeshUVLayout*)mapMesh;
        uvByteOffset = 0;
        for (i = 0; i < (s32)(u16)uvLayout->m_uvCount; i++) {
            if (work->m_perU < (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset)) {
                work->m_perU = (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset);
            }
            if (work->m_perV < (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2)) {
                work->m_perV = (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2);
            }
            uvByteOffset += 4;
        }
        OSReport(s_PerU___0_2f_PerV___0_2f_801d9c38, work->m_perU, work->m_perV);
    }

    uvLayout = (CMapMeshUVLayout*)mapMesh;
    work->m_frame += 1;
    work->m_wait = 0x200;

    uvByteOffset = 0;
    for (i = 0; i < (s32)(u16)uvLayout->m_uvCount; i++) {
        *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset) = (s16)((f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset) + work->m_perU);
        if ((work->m_frame % (u32)payload[1]) == 0) {
            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset) = (s16)(-((work->m_perU * (f32)(u32)payload[1]) -
                                                                         (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset)));
            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2) =
                (s16)((f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2) + work->m_perV);
        }
        if ((u32)(payload[1] * payload[2]) <= work->m_frame) {
            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2) = (s16)(-((work->m_perV * (f32)(u32)payload[2]) -
                                                                             (f32)*(s16*)((u8*)uvLayout->m_uvPairs +
                                                                                          uvByteOffset + 2)));
        }
        uvByteOffset += 4;
    }

    DCFlushRange(uvLayout->m_uvPairs, (u32)(u16)uvLayout->m_uvCount << 2);

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
void pppRenderYmDrawMdlTexAnm(_pppPObject* object, pppYmDrawMdlTexAnmStep* step, _pppCtrlTable* ctrl)
{
    pppYmDrawMdlTexAnm* ymDrawMdlTexAnm;
    pppModelSt* model;
    pppFMATRIX matrix0;
    pppFMATRIX matrix1;
    pppFMATRIX matrix2;
    pppFMATRIX matrix3;
    pppFMATRIX matrix4;
    u8* initBytes;
    u8* stepBytes;
    s32 colorOffset;

    ymDrawMdlTexAnm = (pppYmDrawMdlTexAnm*)object;
    model = (pppModelSt*)((CMapMesh**)pppEnvStPtr->m_mapMeshPtr)[step->m_dataValIndex];
    if (model == NULL) {
        return;
    }

    colorOffset = ctrl->m_serializedDataOffsets[0];

    pppUnitMatrix__FR10pppFMATRIX(&matrix0);
    matrix2 = matrix0;
    matrix2.value[2][2] *= FLOAT_80330548;

    matrix1 = object->m_localMatrix;
    matrix0.value[2][2] = matrix2.value[2][2];
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX(&matrix0, &matrix1, &matrix2);

    matrix4 = matrix0;
    matrix3 = *(pppFMATRIX*)&ppvCameraMatrix02;
    pppMulMatrix__FR10pppFMATRIX10pppFMATRIX10pppFMATRIX((pppFMATRIX*)((u8*)ymDrawMdlTexAnm + 0x40), &matrix3, &matrix4);

    initBytes = (u8*)&step->m_initWOrk;
    stepBytes = (u8*)&step->m_stepValue;
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc((u8*)ymDrawMdlTexAnm + 0x88 + colorOffset, (u8*)ymDrawMdlTexAnm + 0x40,
                                                               step->m_arg3, step->m_payload[0xC], initBytes[2],
                                                               initBytes[1], initBytes[3], stepBytes[0], stepBytes[1],
                                                               stepBytes[2]);

    pppSetBlendMode(initBytes[1]);
    pppDrawMesh__FP10pppModelStP3Veci(model, *(Vec**)((u8*)ymDrawMdlTexAnm + 0x70), 1);
}

}
