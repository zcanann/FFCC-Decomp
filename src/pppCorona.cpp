#include "ffcc/pppCorona.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

extern _pppEnvSt* lbl_8032ED54;
extern float lbl_803310C0;
extern float lbl_803310C4;
extern float lbl_803310C8;
extern float lbl_803310CC;
extern double lbl_803310D0;

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
    Vec m_translate;
};

/*
 * --INFO--
 * PAL Address: 0x800df5e4
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructCorona(pppCorona* param1, UnkC* param2)
{
    float fVar1 = lbl_803310C8;
    u16* puVar2 = (u16*)((u8*)param1 + 0x80 + param2->m_serializedDataOffsets[3]);
    puVar2[2] = 0;
    puVar2[1] = 0;
    puVar2[0] = 0;
    *(float*)(puVar2 + 8) = fVar1;
    *(float*)(puVar2 + 6) = fVar1;
    *(float*)(puVar2 + 4) = fVar1;
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
void pppDestructCorona(void)
{
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
void pppFrameCorona(pppCorona* param1, CoronaParam* param2, UnkC* param3)
{
    CoronaWork* work;
    long** shape;
    s32 shapeId;

    if (lbl_8032ED70 != 0) {
        return;
    }

    work = (CoronaWork*)((u8*)param1 + 0x80 + param3->m_serializedDataOffsets[3]);
    work->m_scaleY = work->m_scaleY + work->m_scaleZ;
    work->m_scaleX = work->m_scaleX + work->m_scaleY;

    shapeId = param2->m_dataValIndex;
    if (shapeId == 0xFFFF) {
        return;
    }

    shape = *(long***)(*(u32*)((u8*)lbl_8032ED54 + 0xC) + shapeId * 4);
    pppCalcFrameShape(*shape, work->m_shapeX, work->m_shapeY, work->m_shapeZ, param2->m_shapeStep);

    if (param2->m_graphId == *(s32*)((u8*)param1 + 0xC)) {
        work->m_scaleX += param2->m_addX;
        work->m_scaleY += param2->m_addY;
        work->m_scaleZ += param2->m_addZ;
    }
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
void pppRenderCorona(pppCorona* param1, CoronaParam* param2, UnkC* param3)
{
    CoronaWork* work;
    CoronaVecWork* vecWork;
    pppCVECTOR color;
    pppFMATRIX mtx;
    Vec viewDir;
    Vec fromOrigin;
    long** shape;
    s32 shapeId;
    float mag;
    float scale;

    work = (CoronaWork*)((u8*)param1 + 0x80 + param3->m_serializedDataOffsets[3]);
    vecWork = (CoronaVecWork*)((u8*)param1 + 0x80 + param3->m_serializedDataOffsets[2]);

    shapeId = param2->m_dataValIndex;
    if (shapeId == 0xFFFF) {
        return;
    }

    shape = *(long***)(*(u32*)((u8*)lbl_8032ED54 + 0xC) + shapeId * 4);

    PSMTXIdentity(mtx.value);

    viewDir.x = lbl_803310C0;
    viewDir.y = lbl_803310C4;
    viewDir.z = lbl_803310C8;
    PSVECSubtract(&vecWork->m_cameraOffset, &viewDir, &fromOrigin);

    mag = PSVECMag(&fromOrigin);
    scale = param2->m_distMin;
    if (mag < param2->m_distRange) {
        scale = param2->m_distMin +
                (param2->m_distMax - param2->m_distMin) * (lbl_803310CC - (mag / param2->m_distRange));
    }

    mtx.value[0][0] = *(float*)((u8*)lbl_8032ED50 + 0x28) * *(float*)((u8*)param1 + 0x40) * scale;
    mtx.value[1][1] = *(float*)((u8*)lbl_8032ED50 + 0x2C) * *(float*)((u8*)param1 + 0x54) * scale;
    mtx.value[2][2] = *(float*)((u8*)lbl_8032ED50 + 0x30) * *(float*)((u8*)param1 + 0x68) * scale;
    mtx.value[0][3] = vecWork->m_translate.x;
    mtx.value[1][3] = vecWork->m_translate.y;
    mtx.value[2][3] = vecWork->m_translate.z;

    GXLoadPosMtxImm(mtx.value, 0);

    color.rgba[0] = param2->m_colorR;
    color.rgba[1] = param2->m_colorG;
    color.rgba[2] = param2->m_colorB;
    color.rgba[3] = (u8)(s32)(work->m_scaleX * (f32)((f64)work->m_alpha - lbl_803310D0));

    pppSetDrawEnv(&color, (pppFMATRIX*)0, lbl_803310C8, param2->m_drawA, param2->m_drawB, param2->m_blendMode, 0, 1,
                  1, 0);
    pppSetBlendMode(param2->m_blendMode);
    pppDrawShp(*shape, work->m_shapeY, lbl_8032ED54->m_materialSetPtr, param2->m_blendMode);
}
