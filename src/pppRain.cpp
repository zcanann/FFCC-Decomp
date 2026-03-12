#include "ffcc/pppRain.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/util.h"
#include "dolphin/gx.h"
const float FLOAT_8033101c = 1.0f;
const float FLOAT_80331020 = 3.0518509e-05f;
const double DOUBLE_80331028 = 4503601774854144.0;
static char s_pppRain_cpp_801db610[] = "pppRain.cpp";

extern "C" {
int rand(void);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void pppSetBlendMode__FUc(u8);
void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);
void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
}

struct RainDrop;

struct RainWork {
    RainDrop* drops;
    float moveY;
    float accelY;
    float accelZ;
};

struct RainDrop {
    float posX;
    float posY;
    float posZ;
    float dirX;
    float dirY;
    float dirZ;
    float length;
    s16 life;
    s16 pad;
};

struct RainParam {
    u8 pad0[0x10];
    float driftY;
    u16 lifeBase;
    u16 lifeRange;
    u8 pad1[0x1c - 0x18];
    float minX;
    float minZ;
    float maxX;
    float maxY;
    float maxZ;
    u8 pad2[0x40 - 0x38];
    float lengthBase;
    float lengthRand;
};

/*
 * --INFO--
 * PAL Address: 0x800ddacc
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructRain(struct pppRain* pppRain, struct RAIN_DATA* param_2)
{
    float fVar1;
    float* puVar2;
    
    fVar1 = kPppRainTexCoordBase;
    puVar2 = (float*)((u8*)pppRain + 0x80 + param_2->m_serializedDataOffsets[2]);
    *(u32*)puVar2 = 0;
    puVar2[3] = fVar1;
    puVar2[2] = fVar1;
    puVar2[1] = fVar1;
}

/*
 * --INFO--
 * PAL Address: 0x800dda78
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructRain(struct pppRain* pppRain, struct RAIN_DATA* param_2)
{
    int iVar1;
    
    iVar1 = param_2->m_serializedDataOffsets[2];
    if (*(void**)((u8*)pppRain + 0x80 + iVar1) != 0) {
        pppHeapUseRate((CMemory::CStage*)*(void**)((u8*)pppRain + 0x80 + iVar1));
        *(u32*)((u8*)pppRain + 0x80 + iVar1) = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800dd648
 * PAL Size: 1072b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameRain(struct pppRain* pppRain, struct PRain* param_2, struct RAIN_DATA* param_3)
{
    int i;
    u32 randA;
    u32 randB;
    u16 lifeBase;
    u16 lifeRange;
    RainWork* work;
    RainDrop* drop;
    RainParam* rain;
    float unitA;
    float unitB;
    float lengthDelta;
    s16 lifeJitter;
    u32 signBit;
    u32 flip;

    if (gPppCalcDisabled != 0) {
        return;
    }

    rain = (RainParam*)param_2->m_payload;
    work = (RainWork*)((u8*)pppRain + 0x80 + param_3->m_serializedDataOffsets[2]);
    if (work->drops == 0) {
        work->drops = (RainDrop*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (u32)param_2->m_dataValIndex * sizeof(RainDrop),
            pppEnvStPtr->m_stagePtr,
            s_pppRain_cpp_801db610,
            0x7f);
        drop = work->drops;
        for (i = 0; i < (int)(u32)param_2->m_dataValIndex; i++) {
            randA = (u32)rand();
            randB = (u32)rand();
            unitA = (float)((double)(u32)randA * (double)FLOAT_80331020);
            unitB = (float)((double)(u32)randB * (double)FLOAT_80331020);
            drop->posX = unitA * (rain->maxX - rain->minX) + rain->minX;
            drop->posY = rain->maxY;
            drop->posZ = unitB * (rain->maxZ - rain->minZ) + rain->minZ;
            drop->dirX = -param_2->m_initWOrk;
            drop->dirY = rain->driftY;
            drop->dirZ = -param_2->m_arg3;
            PSVECNormalize((Vec*)&drop->dirX, (Vec*)&drop->dirX);

            signBit = randA >> 31;
            flip = (randA & 1U) ^ signBit;
            lengthDelta = unitA * rain->lengthRand;
            drop->length = rain->lengthBase;
            if (flip != signBit) {
                lengthDelta = -lengthDelta;
            }
            drop->length += lengthDelta;

            lifeBase = rain->lifeBase;
            lifeRange = rain->lifeRange;
            drop->life = (s16)lifeBase;
            lifeJitter = (s16)randA - (s16)(((s32)randA / (s32)(u32)lifeRange) * (s32)(u32)lifeRange);
            if (flip != signBit) {
                lifeJitter = -lifeJitter;
            }
            drop->life = (s16)(drop->life + lifeJitter);
            drop++;
        }
    }

    work->accelY += work->accelZ;
    work->moveY += work->accelY;
    if (param_2->m_graphId == *(s32*)pppRain) {
        work->moveY += *(float*)&param_2->m_payload[4];
        work->accelY += *(float*)&param_2->m_payload[8];
        work->accelZ += *(float*)&param_2->m_payload[0xc];
    }

    drop = work->drops;
    for (i = 0; i < (int)(u32)param_2->m_dataValIndex; i++) {
        drop->posX = -(drop->dirX * work->moveY - drop->posX);
        drop->posY -= rain->driftY;
        drop->posZ = -(drop->dirZ * work->moveY - drop->posZ);
        drop->life--;
        if (drop->life < 1) {
            randA = (u32)rand();
            randB = (u32)rand();
            unitA = (float)((double)(u32)randA * (double)FLOAT_80331020);
            unitB = (float)((double)(u32)randB * (double)FLOAT_80331020);
            drop->posX = unitA * (rain->maxX - rain->minX) + rain->minX;
            drop->posY = rain->maxY;
            drop->posZ = unitB * (rain->maxZ - rain->minZ) + rain->minZ;
            drop->dirX = -param_2->m_initWOrk;
            drop->dirY = rain->driftY;
            drop->dirZ = -param_2->m_arg3;
            PSVECNormalize((Vec*)&drop->dirX, (Vec*)&drop->dirX);

            signBit = randA >> 31;
            flip = (randA & 1U) ^ signBit;
            lengthDelta = unitA * rain->lengthRand;
            drop->length = rain->lengthBase;
            if (flip != signBit) {
                lengthDelta = -lengthDelta;
            }
            drop->length += lengthDelta;

            lifeBase = rain->lifeBase;
            lifeRange = rain->lifeRange;
            drop->life = (s16)lifeBase;
            lifeJitter = (s16)randA - (s16)(((s32)randA / (s32)(u32)lifeRange) * (s32)(u32)lifeRange);
            if (flip != signBit) {
                lifeJitter = -lifeJitter;
            }
            drop->life = (s16)(drop->life + lifeJitter);
        }
        drop++;
    }

    if (gPppInConstructor == 0) {
        float posX = CameraPcs._212_4_;
        float posY = CameraPcs._216_4_;
        float posZ = CameraPcs._220_4_;
        if (Game.game.m_currentSceneId == 7) {
            posX = ppvCameraMatrix0[0][3];
            posY = ppvCameraMatrix0[1][3];
            posZ = ppvCameraMatrix0[2][3];
        }
        pppMngStPtr->m_matrix.value[0][3] = posX;
        pppMngStPtr->m_matrix.value[1][3] = posY;
        pppMngStPtr->m_matrix.value[2][3] = posZ;
        pppSetFpMatrix__FP9_pppMngSt(pppMngStPtr);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800dd424
 * PAL Size: 548b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderRain(struct pppRain* pppRain, struct PRain* param_2, struct RAIN_DATA* param_3)
{
    int i;
    int colorOffset;
    int workOffset;
    RainWork* work;
    float* drop;
    u8* colorPtr;
    u32 color;
    double baseX;
    double baseY;
    double baseZ;
    float tex0;
    float tex1;
    Vec segment[2];

    colorOffset = param_3->m_serializedDataOffsets[1];
    workOffset = param_3->m_serializedDataOffsets[2];
    colorPtr = (u8*)pppRain + 0x88 + colorOffset;
    work = (RainWork*)((u8*)pppRain + 0x80 + workOffset);
    pppSetBlendMode__FUc(param_2->m_payload[0x48]);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        colorPtr,
        ppvCameraMatrix0,
        kPppRainTexCoordBase,
        param_2->m_payload[0x4a],
        param_2->m_payload[0x49],
        param_2->m_payload[0x48],
        0,
        1,
        1,
        0);

    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetLineWidth(param_2->m_payload[0x3c], GX_TO_ZERO);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&gUtil);

    drop = (float*)work->drops;
    color = *(u32*)colorPtr;
    baseX = (double)pppMngStPtr->m_matrix.value[0][3];
    baseY = (double)pppMngStPtr->m_matrix.value[1][3];
    baseZ = (double)pppMngStPtr->m_matrix.value[2][3];
    GXBegin((GXPrimitive)0xA8, GX_VTXFMT7, (u16)((param_2->m_dataValIndex & 0x7fff) << 1));
    tex0 = kPppRainTexCoordBase;
    tex1 = FLOAT_8033101c;
    i = 0;
    while (i < (int)(u32)param_2->m_dataValIndex) {
        double x = (double)(float)(baseX + (double)drop[0]);
        double y = (double)(float)(baseY + (double)drop[1]);
        double z = (double)(float)(baseZ + (double)drop[2]);

        PSVECScale((Vec*)(drop + 3), &segment[0], drop[6]);
        GXPosition3f32((float)x, (float)y, (float)z);
        GXColor1u32(color);
        GXTexCoord2f32(tex0, tex0);

        GXPosition3f32(
            (float)(x + (double)segment[0].x),
            (float)(y + (double)segment[0].y),
            (float)(z + (double)segment[0].z));
        GXColor1u32(color);
        GXTexCoord2f32(tex1, tex1);
        drop += sizeof(RainDrop) / sizeof(float);
        i++;
    }
    GXSetLineWidth(8, GX_TO_ZERO);
}
