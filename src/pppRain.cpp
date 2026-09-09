#include "ffcc/pppRain.h"
#include "ffcc/memory.h"
#include "ffcc/gxfunc.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include "ffcc/util.h"
#include "dolphin/gx.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
static const char s_pppRain_cpp[] = "pppRain.cpp";

struct RAIN_DATA {
    Vec position;
    Vec direction;
    f32 length;
    s16 life;
    s16 pad;
};

struct VRain {
    RAIN_DATA* drops;
    f32 moveY;
    f32 accelY;
    f32 accelZ;
};

STATIC_ASSERT(offsetof(VRain, drops) == 0x0);
STATIC_ASSERT(offsetof(VRain, moveY) == 0x4);
STATIC_ASSERT(offsetof(VRain, accelY) == 0x8);
STATIC_ASSERT(offsetof(VRain, accelZ) == 0xC);
STATIC_ASSERT(sizeof(VRain) == 0x10);
STATIC_ASSERT(offsetof(VColor, m_color) == 0x8);
STATIC_ASSERT(sizeof(RAIN_DATA) == 0x20);
STATIC_ASSERT(sizeof(_pppCtrlTable) == 0x10);
STATIC_ASSERT(offsetof(_pppCtrlTable, m_serializedDataOffsets) == 0xC);
STATIC_ASSERT(sizeof(RainDataOffsets) == 0xC);
STATIC_ASSERT(offsetof(RainDataOffsets, m_colorDataOffset) == 0x4);
STATIC_ASSERT(offsetof(RainDataOffsets, m_workOffset) == 0x8);

static inline RainDataOffsets* GetRainDataOffsets(_pppCtrlTable* data)
{
    return reinterpret_cast<RainDataOffsets*>(data->m_serializedDataOffsets);
}

static inline VRain* GetRainWork(pppRain* rain, _pppCtrlTable* data)
{
    return reinterpret_cast<VRain*>(rain->m_workArea + GetRainDataOffsets(data)->m_workOffset);
}

static inline VColor* GetRainColorData(pppRain* rain, _pppCtrlTable* data)
{
    return reinterpret_cast<VColor*>(rain->m_workArea + GetRainDataOffsets(data)->m_colorDataOffset);
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
inline void InitRainData(VRain*, PRain* rain, RAIN_DATA* drop)
{
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

    int randA = rand();
    int randB = rand();
    unitA = (1.0f / RAND_MAX) * (float)randA;
    unitB = (1.0f / RAND_MAX) * (float)randB;
    minX = rain->m_minX;
    maxX = rain->m_maxX;
    zRange = rain->m_maxZ - rain->m_minZ;
    drop->position.x = unitA * (maxX - minX) + minX;
    drop->position.y = rain->m_maxY;
    drop->position.z = unitB * zRange + rain->m_minZ;
    drop->direction.x = -rain->m_fallDirX;
    drop->direction.y = rain->m_driftY;
    drop->direction.z = -rain->m_fallDirZ;
    PSVECNormalize(&drop->direction, &drop->direction);

    lengthDelta = unitA * rain->m_lengthRand;
    drop->length = rain->m_lengthBase;
    lengthDelta = (randA % 2 == 0) ? lengthDelta : -lengthDelta;
    drop->length += lengthDelta;

    lifeRange = rain->m_lifeRange;
    lifeBase = rain->m_lifeBase;
    lifeRemainder = randA % lifeRange;
    drop->life = lifeBase;
    lifeJitter = -lifeRemainder;
    if (randA % 2 == 0) {
        lifeJitter = lifeRemainder;
    }
    drop->life = (s16)(drop->life + lifeJitter);
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
inline void UpdateRain(VRain* work, PRain* rain, RAIN_DATA* drop)
{
    drop->position.x -= drop->direction.x * work->moveY;
    drop->position.y -= rain->m_driftY;
    drop->position.z -= drop->direction.z * work->moveY;
    drop->life--;
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
void pppRenderRain(pppRain* rain, PRain* pRain, _pppCtrlTable* data)
{
    int i;
    VRain* work;
    VColor* colorData;
    RAIN_DATA* drop;
    float tex1;
    float tex0;
    float baseX;
    float baseY;
    float baseZ;
    Vec segment;

    work = GetRainWork(rain, data);
    colorData = GetRainColorData(rain, data);
    pppSetBlendMode(pRain->m_blendMode);
    pppSetDrawEnv(
        &colorData->m_color,
        reinterpret_cast<pppFMATRIX*>(&ppvCameraMatrix),
        0.0f,
        pRain->m_lightTarget,
        pRain->m_fogIndex,
        pRain->m_blendMode,
        0,
        1,
        1,
        0);

    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetLineWidth(pRain->m_lineWidth, GX_TO_ZERO);
    gUtil.SetVtxFmt_POS_CLR_TEX();

    drop = work->drops;
    baseX = ppvMng->m_matrix.value[0][3];
    baseY = ppvMng->m_matrix.value[1][3];
    baseZ = ppvMng->m_matrix.value[2][3];
    tex0 = 0.0f;
    GXBegin((GXPrimitive)0xA8, GX_VTXFMT7, (u16)((pRain->m_dropCount & 0x7fff) << 1));
    tex0 = 0.0f;
    tex1 = 1.0f;
    {
        RAIN_DATA* currentDrop = drop;
        for (i = 0; i < (int)(u32)pRain->m_dropCount; i++, currentDrop++) {
            float x = baseX + currentDrop->position.x;
            float y = baseY + currentDrop->position.y;
            float z = baseZ + currentDrop->position.z;

            PSVECScale(&currentDrop->direction, &segment, currentDrop->length);
            GXWGFifo.f32 = x;
            GXWGFifo.f32 = y;
            GXWGFifo.f32 = z;
            GXWGFifo.u32 = *(u32*)&colorData->m_color;
            GXWGFifo.f32 = tex0;
            GXWGFifo.f32 = tex0;

            GXWGFifo.f32 = x + segment.x;
            GXWGFifo.f32 = y + segment.y;
            GXWGFifo.f32 = z + segment.z;
            GXWGFifo.u32 = *(u32*)&colorData->m_color;
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
void pppFrameRain(pppRain* rain, PRain* pRain, _pppCtrlTable* data)
{
    VRain* work;
    RAIN_DATA* drop;
    int i;
    if (ppvUserStopPartF != 0) {
        return;
    }

    work = GetRainWork(rain, data);
    if (work->drops == 0) {
        work->drops = (RAIN_DATA*)pppMemAlloc(
            pRain->m_dropCount * sizeof(RAIN_DATA),
            ppvEnv->m_stagePtr,
            const_cast<char*>(s_pppRain_cpp),
            0x7f);
        drop = work->drops;
        for (i = 0; i < (int)pRain->m_dropCount; i++) {
            InitRainData(work, pRain, drop);
            drop++;
        }
    }

    work->accelY += work->accelZ;
    work->moveY += work->accelY;
    if (pRain->m_graphId == rain->m_graphId) {
        work->moveY += pRain->m_moveYDelta;
        work->accelY += pRain->m_accelYDelta;
        work->accelZ += pRain->m_accelZDelta;
    }

    drop = work->drops;
    for (i = 0; i < (int)pRain->m_dropCount; i++) {
        UpdateRain(work, pRain, drop);
        if (drop->life <= 0) {
            InitRainData(work, pRain, drop);
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
void pppDestructRain(pppRain* rain, _pppCtrlTable* data)
{
    VRain* work;

    work = GetRainWork(rain, data);
    if (work->drops != 0) {
        pppMemFree(work->drops);
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
void pppConstructRain(pppRain* rain, _pppCtrlTable* data)
{
    float zero;
    VRain* work;

    zero = 0.0f;
    work = GetRainWork(rain, data);
    work->drops = 0;
    work->accelZ = zero;
    work->accelY = zero;
    work->moveY = zero;
}
