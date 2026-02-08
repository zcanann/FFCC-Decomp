#include "ffcc/pppRain.h"
#include "ffcc/memory.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "dolphin/gx.h"

extern float lbl_80331018;
extern float FLOAT_8033101c;
extern float FLOAT_80331020;
extern double DOUBLE_80331028;
extern s32 DAT_8032ed70;
extern char DAT_8032ed78;
extern void* DAT_8032ec70;
extern _pppMngSt* pppMngStPtr;

extern struct {
    float _212_4_, _216_4_, _220_4_;
} CameraPcs;

extern "C" {
int rand(void);
void* pppMemAlloc__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, u8, u8, u8, u8, u8, u8, u8);
void pppSetBlendMode__FUc(u8);
void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);
void SetVtxFmt_POS_CLR_TEX__5CUtilFv(void*);
}

struct RainWork {
    float* drops;
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
    s32 m_graphId;
    u8 pad0[0x10 - 0x4];
    float fallY;
    u16 lifeBase;
    u16 lifeRange;
    u8 pad1[0x1c - 0x18];
    float minX;
    float minZ;
    float maxX;
    float maxY;
    float maxZ;
    float driftY;
    float lengthBase;
    float lengthRand;
    u8 lineWidth;
    u8 colB;
    u8 colG;
    u8 blendMode;
    u8 colA;
    u8 colR;
    u8 drawA;
    u8 drawB;
};

static void InitDrop(const RainParam* rain, RainDrop* drop) {
    u32 randA = (u32)rand();
    u32 randB = (u32)rand();
    float unitA = FLOAT_80331020 * (float)randA;
    float unitB = FLOAT_80331020 * (float)randB;
    u32 signBit = randA >> 31;
    u32 flip = (randA & 1U) ^ signBit;
    float lengthDelta = unitA * rain->lengthRand;
    s16 lifeJitter = (s16)(randA % rain->lifeRange);

    drop->posX = unitA * (rain->maxX - rain->minX) + rain->minX;
    drop->posY = rain->maxY;
    drop->posZ = unitB * (rain->maxZ - rain->minZ) + rain->minZ;

    drop->dirX = -rain->fallY;
    drop->dirY = rain->driftY;
    drop->dirZ = -rain->fallY;
    PSVECNormalize((Vec*)&drop->dirX, (Vec*)&drop->dirX);

    if (flip != signBit) {
        lengthDelta = -lengthDelta;
        lifeJitter = -lifeJitter;
    }
    drop->length = rain->lengthBase + lengthDelta;
    drop->life = (s16)(rain->lifeBase + lifeJitter);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void InitRainData(VRain*, PRain*, RAIN_DATA*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void UpdateRain(VRain*, PRain*, RAIN_DATA*)
{
	// TODO
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
    
    fVar1 = lbl_80331018;
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
    u16 count;
    RainWork* work;
    RainDrop* drop;
    RainParam* rain;

    if (DAT_8032ed70 != 0) {
        return;
    }

    rain = (RainParam*)param_2;
    count = *(u16*)&param_2->payload[0];
    work = (RainWork*)((u8*)pppRain + 0x80 + param_3->m_serializedDataOffsets[2]);
    if (work->drops == 0) {
        work->drops = (float*)pppMemAlloc__FUlPQ27CMemory6CStagePci(
            (u32)count * sizeof(RainDrop),
            pppEnvStPtr->m_stagePtr,
            (char*)"pppRain.cpp",
            0x7f);
        drop = (RainDrop*)work->drops;
        for (i = 0; i < count; i++) {
            InitDrop(rain, drop);
            drop++;
        }
    }

    work->accelY += work->accelZ;
    work->moveY += work->accelY;
    if (rain->m_graphId == *(s32*)pppRain) {
        work->moveY += *(float*)&param_2->payload[4];
        work->accelY += *(float*)&param_2->payload[8];
        work->accelZ += *(float*)&param_2->payload[0xc];
    }

    drop = (RainDrop*)work->drops;
    for (i = 0; i < count; i++) {
        drop->posX = -(drop->dirX * work->moveY - drop->posX);
        drop->posY -= rain->driftY;
        drop->posZ = -(drop->dirZ * work->moveY - drop->posZ);
        drop->life--;
        if (drop->life < 1) {
            InitDrop(rain, drop);
        }
        drop++;
    }

    if (DAT_8032ed78 == 0) {
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
    u16 count;
    s32 colorOffset;
    s32 workOffset;
    RainWork* work;
    RainDrop* drop;
    RainParam* rain;
    double baseX;
    double baseY;
    double baseZ;
    Vec segment;

    rain = (RainParam*)param_2;
    count = *(u16*)&param_2->payload[0];
    colorOffset = param_3->m_serializedDataOffsets[1];
    workOffset = param_3->m_serializedDataOffsets[2];

    pppSetBlendMode__FUc(rain->blendMode);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (u8*)pppRain + 0x88 + colorOffset,
        &ppvCameraMatrix0,
        lbl_80331018,
        rain->drawA,
        rain->drawB,
        rain->blendMode,
        0,
        1,
        1,
        0);

    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetLineWidth(rain->lineWidth, GX_TO_ZERO);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);

    work = (RainWork*)((u8*)pppRain + 0x80 + workOffset);
    drop = (RainDrop*)work->drops;
    baseX = (double)pppMngStPtr->m_matrix.value[0][3];
    baseY = (double)pppMngStPtr->m_matrix.value[1][3];
    baseZ = (double)pppMngStPtr->m_matrix.value[2][3];

    GXBegin((GXPrimitive)0xA8, GX_VTXFMT7, (u16)(count << 1));
    for (i = 0; i < count; i++) {
        float x = (float)(baseX + (double)drop->posX);
        float y = (float)(baseY + (double)drop->posY);
        float z = (float)(baseZ + (double)drop->posZ);

        PSVECScale((Vec*)&drop->dirX, &segment, drop->length);
        GXPosition3f32(x, y, z);
        GXColor1u32(*(u32*)((u8*)pppRain + 0x88 + colorOffset));
        GXTexCoord2f32(lbl_80331018, lbl_80331018);

        GXPosition3f32(x + segment.x, y + segment.y, z + segment.z);
        GXColor1u32(*(u32*)((u8*)pppRain + 0x88 + colorOffset));
        GXTexCoord2f32(FLOAT_8033101c, FLOAT_8033101c);
        drop++;
    }
    GXSetLineWidth(8, GX_TO_ZERO);
}
