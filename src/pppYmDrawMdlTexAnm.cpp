#include "ffcc/pppYmDrawMdlTexAnm.h"
#include "dolphin/os.h"
#include "ffcc/ppp_linkage.h"

struct pppCVECTOR {
    u8 m_rgba[4];
};

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

struct pppYmDrawMdlTexAnmObject {
    s32 m_graphId;
    u8 _pad4[0xC];
    pppFMATRIX m_localMatrix;
    pppFMATRIX m_modelViewMatrix;
    Vec* m_drawMatrixPtr;
    u8 _pad74[0xC];
};

struct pppYmDrawMdlTexAnmColorBlock {
    u8 _pad0[8];
    pppCVECTOR m_color;
};

extern "C" {
extern f32 FLOAT_80330548;
extern f32 FLOAT_8033054c;
extern const char s_PerU___0_2f_PerV___0_2f_801d9c38[] = "PerU: %0.2f PerV: %0.2f\n";
extern const char DAT_801d9c54[0x14] = {
    (char)0x83, (char)0x52, (char)0x83, (char)0x93, (char)0x83,
    (char)0x58, (char)0x83, (char)0x67, (char)0x83, (char)0x89,
    (char)0x83, (char)0x4E, (char)0x83, (char)0x5E, '\n',
    '\0',       '\0',       '\0',       '\0',       '\0',
};
}

void pppSetBlendMode(unsigned char);

static inline CMapMesh** GetMapMeshTable()
{
    return *(CMapMesh***)((u8*)pppEnvStPtr + 8);
}

static inline pppYmDrawMdlTexAnmWork* GetYmDrawMdlTexAnmWork(pppYmDrawMdlTexAnmObject* object, _pppCtrlTable* ctrl)
{
    return (pppYmDrawMdlTexAnmWork*)((u8*)object + 0x80 + ctrl->m_serializedDataOffsets[2]);
}

static inline pppYmDrawMdlTexAnmColorBlock* GetYmDrawMdlTexAnmColorBlock(pppYmDrawMdlTexAnmObject* object,
                                                                         _pppCtrlTable* ctrl)
{
    return (pppYmDrawMdlTexAnmColorBlock*)((u8*)object + 0x80 + ctrl->m_serializedDataOffsets[0]);
}

static inline void SetUpPerUV(pppModelSt* model, f32& perU, f32& perV)
{
    CMapMeshUVLayout* uvLayout;
    s32 uvByteOffset;
    s32 i;

    uvLayout = (CMapMeshUVLayout*)model;
    for (i = 0, uvByteOffset = i; i < (s32)(u16)uvLayout->m_uvCount; i++) {
        if (perU < (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset)) {
            perU = (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset);
        }

        if (perV < (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2)) {
            perV = (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2);
        }

        uvByteOffset += 4;
    }

    OSReport(s_PerU___0_2f_PerV___0_2f_801d9c38, perU, perV);
}

void pppUnitMatrix(pppFMATRIX&);
void pppMulMatrix(pppFMATRIX&, pppFMATRIX, pppFMATRIX);

extern "C" {
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(pppCVECTOR* color, pppFMATRIX* matrix, f32 z, u8 a3, u8 a4,
                                                               u8 a5, u8 a6, u8 a7, u8 a8, u8 a9);

void pppDrawMesh__FP10pppModelStP3Veci(pppModelSt* model, Vec* matrixPtr, s32 flag);

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
    pppYmDrawMdlTexAnmObject* ymDrawMdlTexAnm;
    pppYmDrawMdlTexAnmColorBlock* colorBlock;
    pppModelSt* model;
    pppFMATRIX matrix0;
    pppFMATRIX matrix2;
    u8* initBytes;
    u8* stepBytes;
    ymDrawMdlTexAnm = (pppYmDrawMdlTexAnmObject*)object;
    model = (pppModelSt*)GetMapMeshTable()[step->m_dataValIndex];
    if (model == NULL) {
        return;
    }

    colorBlock = GetYmDrawMdlTexAnmColorBlock(ymDrawMdlTexAnm, ctrl);

    pppUnitMatrix(matrix2);
    matrix2.value[2][2] *= FLOAT_80330548;

    pppMulMatrix(matrix0, ymDrawMdlTexAnm->m_localMatrix, matrix2);
    pppMulMatrix(ymDrawMdlTexAnm->m_modelViewMatrix, *(pppFMATRIX*)&ppvCameraMatrix02, matrix0);

    initBytes = (u8*)&step->m_initWOrk;
    stepBytes = (u8*)&step->m_stepValue;
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(&colorBlock->m_color, &ymDrawMdlTexAnm->m_modelViewMatrix,
                                                               step->m_arg3, step->m_payload[0xC], initBytes[2], initBytes[1],
                                                               initBytes[3], stepBytes[0], stepBytes[1], stepBytes[2]);

    pppSetBlendMode(initBytes[1]);
    pppDrawMesh__FP10pppModelStP3Veci(model, ymDrawMdlTexAnm->m_drawMatrixPtr, 1);
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
    pppYmDrawMdlTexAnmObject* ymDrawMdlTexAnm;
    pppYmDrawMdlTexAnmWork* work;
    CMapMesh* mapMesh;
    CMapMeshUVLayout* uvLayout;
    f32 perU;
    f32 perV;
    s32 uvByteOffset;
    s32 i;

    ymDrawMdlTexAnm = (pppYmDrawMdlTexAnmObject*)object;
    work = GetYmDrawMdlTexAnmWork(ymDrawMdlTexAnm, ctrl);
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
            SetUpPerUV((pppModelSt*)mapMesh, work->m_perU, work->m_perV);
        } else {
            return;
        }
    }

    uvLayout = (CMapMeshUVLayout*)mapMesh;
    work->m_frame += 1;
    work->m_wait = 0x200;

    for (uvByteOffset = i = 0; i < (s32)(u16)uvLayout->m_uvCount; i++) {
        *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset) = (s16)((f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset) + perU);
        if ((work->m_frame % *(u32*)(step->m_payload + 4)) == 0) {
            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset) = (s16)(-((perU * (f32)*(u32*)(step->m_payload + 4)) -
                                                                         (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset)));
            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2) =
                (s16)((f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2) + perV);
        }
        if (work->m_frame >= (u32)(*(s32*)(step->m_payload + 4) * *(s32*)(step->m_payload + 8))) {
            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset + 2) = (s16)(-((perV * (f32)*(u32*)(step->m_payload + 8)) -
                                                                             (f32)*(s16*)((u8*)uvLayout->m_uvPairs +
                                                                                          uvByteOffset + 2)));
        }
        uvByteOffset += 4;
    }

    DCFlushRange(uvLayout->m_uvPairs, (uvLayout->m_uvCount & 0xFFFF) << 2);

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
    pppYmDrawMdlTexAnmObject* ymDrawMdlTexAnm;
    pppYmDrawMdlTexAnmWork* work;
    CMapMeshUVLayout* uvLayout;
    s32 uvByteOffset;
    s32 frameU;
    s32 i;

    ymDrawMdlTexAnm = (pppYmDrawMdlTexAnmObject*)object;
    work = GetYmDrawMdlTexAnmWork(ymDrawMdlTexAnm, ctrl);
    if ((work->m_frame != 0) && ((uvLayout = (CMapMeshUVLayout*)GetMapMeshTable()[0]) != NULL)) {
        for (uvByteOffset = i = 0; i < (s32)(u16)uvLayout->m_uvCount; i++) {
            s32 uvByteOffsetV = uvByteOffset + 2;
            frameU = work->m_frame / work->m_tilesU;
            s32 frameModU = work->m_frame - frameU * work->m_tilesU;

            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset) =
                (s16)(int)-(((f32)frameModU * work->m_perU) -
                            (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffset));
            uvByteOffset += 4;
            *(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffsetV) =
                (s16)(int)-(((f32)frameU * work->m_perV) -
                            (f32)*(s16*)((u8*)uvLayout->m_uvPairs + uvByteOffsetV));
        }
        DCFlushRange(uvLayout->m_uvPairs, (uvLayout->m_uvCount & 0xFFFF) << 2);
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
    pppYmDrawMdlTexAnmObject* ymDrawMdlTexAnm;
    pppYmDrawMdlTexAnmWork* work;
    pppModelSt* model;
    f32 per;

    ymDrawMdlTexAnm = (pppYmDrawMdlTexAnmObject*)object;
    work = GetYmDrawMdlTexAnmWork(ymDrawMdlTexAnm, ctrl);
    work->m_frame = 0;
    work->m_wait = 0x200;

    OSReport(DAT_801d9c54);

    model = (pppModelSt*)GetMapMeshTable()[0];
    per = FLOAT_8033054c;
    work->m_perU = per;
    work->m_perV = per;

    if (model != NULL) {
        SetUpPerUV(model, work->m_perU, work->m_perV);
    }
}
}
