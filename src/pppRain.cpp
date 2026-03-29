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
static char s_pppRain_cpp_801DB610[] = "pppRain.cpp";

extern "C" {
int rand(void);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);

void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
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
    float pad0;
    float moveYDelta;
    float accelYDelta;
    float accelZDelta;
    float driftY;
    u16 lifeBase;
    u16 lifeRange;
    u8 pad1[0x1c - 0x18];
    float minX;
    float padMinY;
    float minZ;
    float padMaxW;
    float maxX;
    float maxY;
    float maxZ;
    u8 pad2[0x3c - 0x38];
    u8 lineWidth;
    u8 pad3[3];
    float lengthBase;
    float lengthRand;
    u8 blendMode;
    u8 fogIndex;
    u8 lightTarget;
    u8 pad4;
};

struct RainColorData {
    u8 pad[8];
    pppCVECTOR color;
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
    int randA;
    int randB;
    RainWork* work;
    RainDrop* drop;
    RainParam* rain;
    float unitA;
    float unitB;
    float lengthDelta;
    s16 lifeJitter;

    if (gPppCalcDisabled != 0) {
        return;
    }

    rain = (RainParam*)param_2->m_payload;
    work = (RainWork*)((u8*)pppRain + 0x80 + param_3->m_serializedDataOffsets[2]);
    if (work->drops == 0) {
        work->drops = (RainDrop*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            param_2->m_dataValIndex * sizeof(RainDrop),
            pppEnvStPtr->m_stagePtr,
            s_pppRain_cpp_801DB610,
            0x7f);
        drop = work->drops;
        for (i = 0; i < (int)param_2->m_dataValIndex; i++) {
            randA = rand();
            randB = rand();
            unitA = FLOAT_80331020 * (float)randA;
            unitB = FLOAT_80331020 * (float)randB;
            drop->posX = unitA * (rain->maxX - rain->minX) + rain->minX;
            drop->posY = rain->maxY;
            drop->posZ = unitB * (rain->maxZ - rain->minZ) + rain->minZ;
            drop->dirX = -param_2->m_initWOrk;
            drop->dirY = rain->driftY;
            drop->dirZ = -param_2->m_arg3;
            PSVECNormalize((Vec*)&drop->dirX, (Vec*)&drop->dirX);

            lengthDelta = unitA * rain->lengthRand;
            drop->length = rain->lengthBase;
            if (randA % 2 != 0) {
                lengthDelta = -lengthDelta;
            }
            drop->length += lengthDelta;

            drop->life = (s16)rain->lifeBase;
            lifeJitter = (s16)(randA % rain->lifeRange);
            if (randA % 2 != 0) {
                lifeJitter = -lifeJitter;
            }
            drop->life = (s16)(drop->life + lifeJitter);
            drop++;
        }
    }

    work->accelY += work->accelZ;
    work->moveY += work->accelY;
    if (param_2->m_graphId == *(s32*)pppRain) {
        work->moveY += rain->moveYDelta;
        work->accelY += rain->accelYDelta;
        work->accelZ += rain->accelZDelta;
    }

    drop = work->drops;
    for (i = 0; i < (int)param_2->m_dataValIndex; i++) {
        drop->posX = -(drop->dirX * work->moveY - drop->posX);
        drop->posY -= rain->driftY;
        drop->posZ = -(drop->dirZ * work->moveY - drop->posZ);
        drop->life--;
        if (drop->life < 1) {
            randA = rand();
            randB = rand();
            unitA = FLOAT_80331020 * (float)randA;
            unitB = FLOAT_80331020 * (float)randB;
            drop->posX = unitA * (rain->maxX - rain->minX) + rain->minX;
            drop->posY = rain->maxY;
            drop->posZ = unitB * (rain->maxZ - rain->minZ) + rain->minZ;
            drop->dirX = -param_2->m_initWOrk;
            drop->dirY = rain->driftY;
            drop->dirZ = -param_2->m_arg3;
            PSVECNormalize((Vec*)&drop->dirX, (Vec*)&drop->dirX);

            lengthDelta = unitA * rain->lengthRand;
            drop->length = rain->lengthBase;
            if (randA % 2 != 0) {
                lengthDelta = -lengthDelta;
            }
            drop->length += lengthDelta;

            drop->life = (s16)rain->lifeBase;
            lifeJitter = (s16)(randA % rain->lifeRange);
            if (randA % 2 != 0) {
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
        if (Game.m_currentSceneId == 7) {
            posX = ppvCameraMatrix0[0][3];
            posY = ppvCameraMatrix0[1][3];
            posZ = ppvCameraMatrix0[2][3];
        }
        pppMngStPtr->m_matrix.value[0][3] = posX;
        pppMngStPtr->m_matrix.value[1][3] = posY;
        pppMngStPtr->m_matrix.value[2][3] = posZ;
        pppSetFpMatrix(pppMngStPtr);
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
    u8* colorBase;
    RainParam* rain;
    RainDrop* drops;
    RainDrop* drop;
    float tex0;
    float baseX;
    float baseY;
    float baseZ;
    float tex1;
    Vec segment;

    colorOffset = param_3->m_serializedDataOffsets[1] + 0x80;
    workOffset = param_3->m_serializedDataOffsets[2] + 0x80;
    colorBase = (u8*)pppRain + colorOffset;
    rain = (RainParam*)param_2->m_payload;
    pppSetBlendMode(rain->blendMode);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (pppCVECTOR*)(colorBase + 8),
        ppvCameraMatrix02,
        kPppRainTexCoordBase,
        rain->lightTarget,
        rain->fogIndex,
        rain->blendMode,
        0,
        1,
        1,
        0);

    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0xFF, 4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    GXSetLineWidth(rain->lineWidth, GX_TO_ZERO);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&gUtil);

    drops = *(RainDrop**)((u8*)pppRain + workOffset);
    baseX = pppMngStPtr->m_matrix.value[0][3];
    baseY = pppMngStPtr->m_matrix.value[1][3];
    baseZ = pppMngStPtr->m_matrix.value[2][3];
    GXBegin((GXPrimitive)0xA8, GX_VTXFMT7, (u16)((param_2->m_dataValIndex & 0x7fff) << 1));
    tex0 = kPppRainTexCoordBase;
    drop = drops;
    tex1 = FLOAT_8033101c;
    i = 0;
    while (i < (int)(u32)param_2->m_dataValIndex) {
        float x = baseX + drop->posX;
        float y = baseY + drop->posY;
        float z = baseZ + drop->posZ;

        PSVECScale((Vec*)&drop->dirX, &segment, drop->length);
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
        GXWGFifo.f32 = z;
        GXWGFifo.u32 = *(u32*)(colorBase + 8);
        GXWGFifo.f32 = tex0;
        GXWGFifo.f32 = tex0;

        GXWGFifo.f32 = x + segment.x;
        GXWGFifo.f32 = y + segment.y;
        GXWGFifo.f32 = z + segment.z;
        GXWGFifo.u32 = *(u32*)(colorBase + 8);
        GXWGFifo.f32 = tex1;
        GXWGFifo.f32 = tex1;
        drop++;
        i++;
    }
    GXSetLineWidth(8, GX_TO_ZERO);
}
