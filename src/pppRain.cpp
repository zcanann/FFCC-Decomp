#include "ffcc/pppRain.h"
#include "ffcc/memory.h"
#include "ffcc/gxfunc.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
extern "C" {
extern const float kPppRainTexCoordBase;
extern const float kPppRainTexCoordOne;
extern const float kPppRainRandomUnitScale;
}
#include "ffcc/util.h"
#include "dolphin/gx.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
static const char s_pppRain_cpp[] = "pppRain.cpp";

struct RainColorData {
    u8 pad[8];
    pppCVECTOR color;
};

struct RainDrop {
    f32 posX;
    f32 posY;
    f32 posZ;
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    f32 length;
    s16 life;
    s16 pad;
};

struct VRain {
    RainDrop* drops;
    f32 moveY;
    f32 accelY;
    f32 accelZ;
};

STATIC_ASSERT(offsetof(VRain, drops) == 0x0);
STATIC_ASSERT(offsetof(VRain, moveY) == 0x4);
STATIC_ASSERT(offsetof(VRain, accelY) == 0x8);
STATIC_ASSERT(offsetof(VRain, accelZ) == 0xC);
STATIC_ASSERT(sizeof(VRain) == 0x10);
STATIC_ASSERT(offsetof(RainColorData, color) == 0x8);
STATIC_ASSERT(sizeof(RainDrop) == 0x20);
STATIC_ASSERT(sizeof(RAIN_DATA) == 0x10);
STATIC_ASSERT(offsetof(RAIN_DATA, m_serializedDataOffsets) == 0xC);
STATIC_ASSERT(sizeof(RainDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(RainDataOffsets, m_colorDataOffset) == 0x4);
STATIC_ASSERT(offsetof(RainDataOffsets, m_workOffset) == 0x8);

static inline RainDataOffsets* GetRainDataOffsets(RAIN_DATA* data)
{
    return reinterpret_cast<RainDataOffsets*>(data->m_serializedDataOffsets);
}

static inline VRain* GetRainWork(pppRain* rain, RAIN_DATA* data)
{
    return reinterpret_cast<VRain*>(rain->m_workArea + GetRainDataOffsets(data)->m_workOffset);
}

static inline RainColorData* GetRainColorData(pppRain* rain, RAIN_DATA* data)
{
    return reinterpret_cast<RainColorData*>(rain->m_workArea + GetRainDataOffsets(data)->m_colorDataOffset);
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
void pppRenderRain(pppRain* pppRain, PRain* param_2, RAIN_DATA* param_3)
{
    int i;
    RainColorData* colorData;
    VRain* work;
    RainDrop* drop;
    float tex1;
    float tex0;
    float baseX;
    float baseY;
    float baseZ;
    Vec segment;

    work = GetRainWork(pppRain, param_3);
    colorData = GetRainColorData(pppRain, param_3);
    pppSetBlendMode(param_2->m_blendMode);
    pppSetDrawEnv(
        &colorData->color,
        reinterpret_cast<pppFMATRIX*>(&ppvCameraMatrix),
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
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetLineWidth(param_2->m_lineWidth, GX_TO_ZERO);
    gUtil.SetVtxFmt_POS_CLR_TEX();

    drop = work->drops;
    baseX = ppvMng->m_matrix.value[0][3];
    baseY = ppvMng->m_matrix.value[1][3];
    baseZ = ppvMng->m_matrix.value[2][3];
    tex0 = kPppRainTexCoordBase;
    GXBegin((GXPrimitive)0xA8, GX_VTXFMT7, (u16)((param_2->m_dataValIndex & 0x7fff) << 1));
    tex0 = kPppRainTexCoordBase;
    tex1 = kPppRainTexCoordOne;
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
            GXWGFifo.u32 = *(u32*)&colorData->color;
            GXWGFifo.f32 = tex0;
            GXWGFifo.f32 = tex0;

            GXWGFifo.f32 = x + segment.x;
            GXWGFifo.f32 = y + segment.y;
            GXWGFifo.f32 = z + segment.z;
            GXWGFifo.u32 = *(u32*)&colorData->color;
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
void pppFrameRain(pppRain* pppRain, PRain* param_2, RAIN_DATA* param_3)
{
    VRain* work;
    RainDrop* drop;
    int i;
    int randA;
    int randB;
    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetRainWork(pppRain, param_3);
    if (work->drops == 0) {
        work->drops = (RainDrop*)pppMemAlloc(
            param_2->m_dataValIndex * sizeof(RainDrop),
            ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppRain_cpp),
            0x7f);
        drop = work->drops;
        for (i = 0; i < (int)param_2->m_dataValIndex; i++) {
            float minX;
            float maxX;
            float zRange;
            float unitA;
            float unitB;
            float lengthDelta;
            s16 lifeBase;
            u16 lifeRange;
            int lifeJitter;
            int lifeRemainder;

            randA = rand();
            randB = rand();
            unitA = kPppRainRandomUnitScale * (float)randA;
            unitB = kPppRainRandomUnitScale * (float)randB;
            minX = param_2->m_minX;
            maxX = param_2->m_maxX;
            zRange = param_2->m_maxZ - param_2->m_minZ;
            drop->posX = unitA * (maxX - minX) + minX;
            drop->posY = param_2->m_maxY;
            drop->posZ = unitB * zRange + param_2->m_minZ;
            drop->dirX = -param_2->m_initWOrk;
            drop->dirY = param_2->m_driftY;
            drop->dirZ = -param_2->m_arg3;
            PSVECNormalize((Vec*)&drop->dirX, (Vec*)&drop->dirX);

            lengthDelta = unitA * param_2->m_lengthRand;
            drop->length = param_2->m_lengthBase;
            lengthDelta = (randA % 2 == 0) ? lengthDelta : -lengthDelta;
            drop->length += lengthDelta;

            lifeRange = param_2->m_lifeRange;
            lifeBase = param_2->m_lifeBase;
            lifeRemainder = randA % lifeRange;
            drop->life = lifeBase;
            lifeJitter = -lifeRemainder;
            if (randA % 2 == 0) {
                lifeJitter = lifeRemainder;
            }
            drop->life = (s16)(drop->life + lifeJitter);
            drop++;
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
            float minX;
            float maxX;
            float zRange;
            float unitA;
            float unitB;
            float lengthDelta;
            s16 lifeBase;
            u16 lifeRange;
            int lifeJitter;
            int lifeRemainder;

            randA = rand();
            randB = rand();
            unitA = kPppRainRandomUnitScale * (float)randA;
            unitB = kPppRainRandomUnitScale * (float)randB;
            minX = param_2->m_minX;
            maxX = param_2->m_maxX;
            zRange = param_2->m_maxZ - param_2->m_minZ;
            drop->posX = unitA * (maxX - minX) + minX;
            drop->posY = param_2->m_maxY;
            drop->posZ = unitB * zRange + param_2->m_minZ;
            drop->dirX = -param_2->m_initWOrk;
            drop->dirY = param_2->m_driftY;
            drop->dirZ = -param_2->m_arg3;
            PSVECNormalize((Vec*)&drop->dirX, (Vec*)&drop->dirX);

            lengthDelta = unitA * param_2->m_lengthRand;
            drop->length = param_2->m_lengthBase;
            lengthDelta = (randA % 2 == 0) ? lengthDelta : -lengthDelta;
            drop->length += lengthDelta;

            lifeRange = param_2->m_lifeRange;
            lifeBase = param_2->m_lifeBase;
            lifeRemainder = randA % lifeRange;
            drop->life = lifeBase;
            lifeJitter = -lifeRemainder;
            if (randA % 2 == 0) {
                lifeJitter = lifeRemainder;
            }
            drop->life = (s16)(drop->life + lifeJitter);
        }
        drop++;
    }

    if (ppvIsLoopCalc == 0) {
        float posX;
        float posY;
        float posZ;

        if ((int)Game.m_currentSceneId == 7) {
            posX = ppvCameraMatrix[0][3];
            posY = ppvCameraMatrix[1][3];
            posZ = ppvCameraMatrix[2][3];
        } else {
            posX = CameraPcs.m_targetX;
            posY = CameraPcs.m_targetY;
            posZ = CameraPcs.m_targetZ;
        }
        ppvMng->m_matrix.value[0][3] = posX;
        ppvMng->m_matrix.value[1][3] = posY;
        ppvMng->m_matrix.value[2][3] = posZ;
        pppSetFpMatrix(ppvMng);
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
void pppDestructRain(pppRain* pppRain, RAIN_DATA* param_2)
{
    VRain* work;

    work = GetRainWork(pppRain, param_2);
    if (work->drops != 0) {
        pppHeapUseRate((CMemory::CStage*)work->drops);
        work->drops = 0;
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
void pppConstructRain(pppRain* pppRain, RAIN_DATA* param_2)
{
    float fVar1;
    VRain* work;

    fVar1 = kPppRainTexCoordBase;
    work = GetRainWork(pppRain, param_2);
    work->drops = 0;
    work->accelZ = fVar1;
    work->accelY = fVar1;
    work->moveY = fVar1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void UpdateRain(VRain* work, PRain* rain, RAIN_DATA*)
{
    work->accelY += work->accelZ;
    work->moveY += work->accelY;
    work->moveY += rain->m_moveYDelta;
    work->accelY += rain->m_accelYDelta;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void InitRainData(VRain* work, PRain* rain, RAIN_DATA*)
{
    RainDrop* drop;

    drop = work->drops;
    for (int i = 0; i < (int)rain->m_dataValIndex; i++) {
        int randA = rand();
        int randB = rand();
        float unitA = kPppRainRandomUnitScale * (float)randA;
        float unitB = kPppRainRandomUnitScale * (float)randB;
        float lengthDelta;
        int lifeRemainder;

        drop->posX = unitA * (rain->m_maxX - rain->m_minX) + rain->m_minX;
        drop->posY = rain->m_maxY;
        drop->posZ = unitB * (rain->m_maxZ - rain->m_minZ) + rain->m_minZ;
        drop->dirX = -rain->m_initWOrk;
        drop->dirY = rain->m_driftY;
        drop->dirZ = -rain->m_arg3;
        PSVECNormalize((Vec*)&drop->dirX, (Vec*)&drop->dirX);

        lengthDelta = unitA * rain->m_lengthRand;
        drop->length = rain->m_lengthBase;
        lengthDelta = ((randA & 1) == 0) ? lengthDelta : -lengthDelta;
        drop->length += lengthDelta;

        lifeRemainder = randA % rain->m_lifeRange;
        if ((randA & 1) != 0) {
            lifeRemainder = -lifeRemainder;
        }
        drop->life = (s16)(rain->m_lifeBase + lifeRemainder);
        drop++;
    }
}

extern const float kPppCrystalCoordMin = -1.0f;
extern const float kPppCrystalZero = 0.0f;
extern const double kPppNewtonSqrtHalf = 0.5;
