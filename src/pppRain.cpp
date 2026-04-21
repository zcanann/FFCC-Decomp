#include "ffcc/pppRain.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
extern "C" {
extern const float kPppRainTexCoordBase;
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
}
#include "ffcc/util.h"
#include "dolphin/gx.h"
const float FLOAT_80331020 = 3.0518509e-05f;
const double DOUBLE_80331028 = 4503601774854144.0;
static const char s_pppRain_cpp_801DB610[] = "pppRain.cpp";

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

struct RainColorData {
    u8 pad[8];
    pppCVECTOR color;
};

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
    RainDrop* drop;
    float tex0;
    float baseX;
    float baseY;
    float baseZ;
    float tex1;
    Vec segment;

    colorOffset = param_3->m_serializedDataOffsets[1];
    workOffset = param_3->m_serializedDataOffsets[2] + 0x80;
    colorBase = (u8*)pppRain + colorOffset + 0x80;
    pppSetBlendMode(param_2->m_blendMode);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (pppCVECTOR*)(colorBase + 8),
        ppvCameraMatrix02,
        kPppRainTexCoordBase,
        param_2->m_lightTarget,
        param_2->m_fogIndex,
        param_2->m_blendMode,
        0,
        1,
        1,
        0);

    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0xFF, 4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    GXSetLineWidth(param_2->m_lineWidth, GX_TO_ZERO);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&gUtil);

    drop = *(RainDrop**)((u8*)pppRain + workOffset);
    baseX = pppMngStPtr->m_matrix.value[0][3];
    baseY = pppMngStPtr->m_matrix.value[1][3];
    baseZ = pppMngStPtr->m_matrix.value[2][3];
    tex0 = kPppRainTexCoordBase;
    GXBegin((GXPrimitive)0xA8, GX_VTXFMT7, (u16)((param_2->m_dataValIndex & 0x7fff) << 1));
    tex0 = kPppRainTexCoordBase;
    tex1 = 1.0f;
    {
        RainDrop* currentDrop = drop;
        for (i = 0; i < (int)(u32)param_2->m_dataValIndex; i++, currentDrop++) {
            float x = baseX + currentDrop->posX;
            float y = baseY + currentDrop->posY;
            float z = baseZ + currentDrop->posZ;

            PSVECScale((Vec*)&currentDrop->dirX, &segment, currentDrop->length);
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
        }
    }
    GXSetLineWidth(8, GX_TO_ZERO);
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
    if (gPppCalcDisabled != 0) {
        return;
    }

    work = (RainWork*)((u8*)pppRain + 0x80 + param_3->m_serializedDataOffsets[2]);
    if (work->drops == 0) {
        float* dropData;

        work->drops = (RainDrop*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            param_2->m_dataValIndex * sizeof(RainDrop),
            pppEnvStPtr->m_stagePtr,
            const_cast<char*>(s_pppRain_cpp_801DB610),
            0x7f);
        dropData = (float*)work->drops;
        for (i = 0; i < (int)param_2->m_dataValIndex; i++) {
            float minX;
            float maxX;
            float minZ;
            float maxZ;
            float unitA;
            float unitB;
            float lengthDelta;
            int lifeJitter;
            int lifeRemainder;

            randA = rand();
            randB = rand();
            unitA = FLOAT_80331020 * (float)randA;
            unitB = FLOAT_80331020 * (float)randB;
            maxX = param_2->m_maxX;
            minX = param_2->m_minX;
            maxZ = param_2->m_maxZ;
            minZ = param_2->m_minZ;
            dropData[0] = unitA * (maxX - minX) + minX;
            dropData[1] = param_2->m_maxY;
            dropData[2] = unitB * (maxZ - minZ) + minZ;
            dropData[3] = -param_2->m_initWOrk;
            dropData[4] = param_2->m_driftY;
            dropData[5] = -param_2->m_arg3;
            PSVECNormalize((Vec*)(dropData + 3), (Vec*)(dropData + 3));

            lengthDelta = unitA * param_2->m_lengthRand;
            dropData[6] = param_2->m_lengthBase;
            lengthDelta = (randA % 2 == 0) ? lengthDelta : -lengthDelta;
            dropData[6] += lengthDelta;

            *(s16*)(dropData + 7) = (s16)param_2->m_lifeBase;
            lifeRemainder = randA % param_2->m_lifeRange;
            lifeJitter = -lifeRemainder;
            if (randA % 2 == 0) {
                lifeJitter = lifeRemainder;
            }
            *(s16*)(dropData + 7) = (s16)(*(s16*)(dropData + 7) + lifeJitter);
            dropData += 8;
        }
    }

    work->accelY += work->accelZ;
    work->moveY += work->accelY;
    if (param_2->m_graphId == pppRain->m_graphId) {
        work->moveY += param_2->m_moveYDelta;
        work->accelY += param_2->m_accelYDelta;
        work->accelZ += param_2->m_accelZDelta;
    }

    drop = work->drops;
    for (i = 0; i < (int)param_2->m_dataValIndex; i++) {
        drop->posX = -(drop->dirX * work->moveY - drop->posX);
        drop->posY -= param_2->m_driftY;
        drop->posZ = -(drop->dirZ * work->moveY - drop->posZ);
        drop->life--;
        if (drop->life <= 0) {
            float* dropData;
            float minX;
            float maxX;
            float minZ;
            float maxZ;
            float unitA;
            float unitB;
            float lengthDelta;
            int lifeJitter;
            int lifeRemainder;

            randA = rand();
            randB = rand();
            dropData = (float*)drop;
            unitA = FLOAT_80331020 * (float)randA;
            unitB = FLOAT_80331020 * (float)randB;
            maxX = param_2->m_maxX;
            minX = param_2->m_minX;
            maxZ = param_2->m_maxZ;
            minZ = param_2->m_minZ;
            dropData[0] = unitA * (maxX - minX) + minX;
            dropData[1] = param_2->m_maxY;
            dropData[2] = unitB * (maxZ - minZ) + minZ;
            dropData[3] = -param_2->m_initWOrk;
            dropData[4] = param_2->m_driftY;
            dropData[5] = -param_2->m_arg3;
            PSVECNormalize((Vec*)(dropData + 3), (Vec*)(dropData + 3));

            lengthDelta = unitA * param_2->m_lengthRand;
            dropData[6] = param_2->m_lengthBase;
            lengthDelta = (randA % 2 == 0) ? lengthDelta : -lengthDelta;
            dropData[6] += lengthDelta;

            *(s16*)(dropData + 7) = (s16)param_2->m_lifeBase;
            lifeRemainder = randA % param_2->m_lifeRange;
            lifeJitter = -lifeRemainder;
            if (randA % 2 == 0) {
                lifeJitter = lifeRemainder;
            }
            *(s16*)(dropData + 7) = (s16)(*(s16*)(dropData + 7) + lifeJitter);
        }
        drop++;
    }

    if (gPppInConstructor == 0) {
        float posX;
        float posY;
        float posZ;

        if ((s32)Game.m_currentSceneId == 7) {
            posX = ppvCameraMatrix02[0][3];
            posY = ppvCameraMatrix02[1][3];
            posZ = ppvCameraMatrix02[2][3];
        } else {
            posX = CameraPcs._212_4_;
            posY = CameraPcs._216_4_;
            posZ = CameraPcs._220_4_;
        }
        pppMngStPtr->m_matrix.value[0][3] = posX;
        pppMngStPtr->m_matrix.value[1][3] = posY;
        pppMngStPtr->m_matrix.value[2][3] = posZ;
        pppSetFpMatrix(pppMngStPtr);
    }
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
