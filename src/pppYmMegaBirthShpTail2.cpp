#include "global.h"
#include "ffcc/pppYmMegaBirthShpTail2.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppGetRotMatrixXYZ.h"
#include "ffcc/pppShape.h"

#include <dolphin/mtx.h>
#include <string.h>

struct _PARTICLE_DATA
{
    Vec m_position;          // 0x00
    u8 _pad0C[0x04];
    Vec m_direction;         // 0x10
    u16 m_frameTimer;        // 0x1c
    u16 m_shapeFrame;        // 0x1e
    u16 m_drawFrame;         // 0x20
    u16 m_life;              // 0x22
    u8 _pad24[0x04];
    float m_speed;           // 0x28
    float m_tailSpeed;       // 0x2c
    float m_alphaFade;       // 0x30
    u8 m_age;                // 0x34
    u8 m_fadeInFrames;       // 0x35
    u8 m_fadeOutFrames;      // 0x36
    u8 m_historyCount;       // 0x37
    u8 m_historyIndex;       // 0x38
    u8 _pad39;
    u16 m_unk3A[3];          // 0x3a
    Vec m_history[31];       // 0x40
    u8 _pad1B4[0x04];
}; // Size 0x1b8

STATIC_ASSERT(sizeof(_PARTICLE_DATA) == 0x1b8);
STATIC_ASSERT(offsetof(_PARTICLE_DATA, m_history) == 0x40);

struct VYmMegaBirthShpTail2
{
    pppFMATRIX m_emitterMatrix;
    Vec m_tailScaleDirection;
    _PARTICLE_DATA* m_particles;
    _PARTICLE_WMAT* m_wmats;
    _PARTICLE_COLOR* m_colors;
    unsigned int m_maxParticles;
    unsigned short m_emitTimer;
    unsigned short m_pathIndex;
};

static pppFMATRIX g_matUnit;

static const char s_pppYmMegaBirthShpTail2_cpp[] = "pppYmMegaBirthShpTail2.cpp";

STATIC_ASSERT(sizeof(PYmMegaBirthShpTail2) == 0x90);
STATIC_ASSERT(sizeof(VYmMegaBirthShpTail2) == 0x50);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_particles) == 0x3C);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_wmats) == 0x40);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_colors) == 0x44);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_maxParticles) == 0x48);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_emitTimer) == 0x4C);
STATIC_ASSERT(offsetof(VYmMegaBirthShpTail2, m_pathIndex) == 0x4E);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_shapeIndex) == 0x4);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_frameStep) == 0x8);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_maxParticles) == 0xe);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_life) == 0x14);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_spawnMode) == 0x18);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_baseDirection) == 0x20);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_tailDirection) == 0x30);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_speed) == 0x40);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_spawnScale) == 0x58);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_randType) == 0x68);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_pathIndex) == 0x6c);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_colorStart) == 0x78);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_segmentLength) == 0x80);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_drawCount) == 0x84);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_depth) == 0x88);
STATIC_ASSERT(offsetof(PYmMegaBirthShpTail2, m_matrixMode) == 0x8d);

STATIC_ASSERT(sizeof(YmMegaBirthShpTail2DataOffsets) == 0xC);
STATIC_ASSERT(offsetof(YmMegaBirthShpTail2DataOffsets, m_colorOffset) == 0x4);
STATIC_ASSERT(offsetof(YmMegaBirthShpTail2DataOffsets, m_workOffset) == 0x8);

static inline YmMegaBirthShpTail2DataOffsets* GetYmMegaBirthShpTail2DataOffsets(_pppCtrlTable* offsets)
{
    return reinterpret_cast<YmMegaBirthShpTail2DataOffsets*>(offsets->m_serializedDataOffsets);
}

inline void U8ToF32(pppFVECTOR4* dest, u8* src)
{
    dest->x = src[0];
    dest->y = src[1];
    dest->z = src[2];
    dest->w = src[3];
}

static inline s8 alloc_check(VYmMegaBirthShpTail2* work, PYmMegaBirthShpTail2* param)
{
    if (work->m_particles == 0) {
        return 0;
    }
    if (work->m_wmats == 0) {
        return 0;
    }
    if ((param->m_enableParticleColor != 0) && (work->m_colors == 0)) {
        return 0;
    }
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8008ca1c
 * PAL Size: 124b
 * EN Address: 0x8008C3B8
 * EN Size: 124b
 * JP Address: 0x8008BE34
 * JP Size: 124b
 */
void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, _pppCtrlTable* param2)
{
    VYmMegaBirthShpTail2* work = reinterpret_cast<VYmMegaBirthShpTail2*>(
        param1->m_workArea + GetYmMegaBirthShpTail2DataOffsets(param2)->m_workOffset);

    pppUnitMatrix(work->m_emitterMatrix);
    work->m_tailScaleDirection.x = work->m_tailScaleDirection.y = work->m_tailScaleDirection.z = 0.0f;
    work->m_particles = 0;
    work->m_wmats = 0;
    work->m_colors = 0;
    work->m_maxParticles = 0;
    work->m_emitTimer = 0;
    work->m_pathIndex = 0;
    work->m_emitTimer = 10000;
    pppUnitMatrix(g_matUnit);
}

/*
 * --INFO--
 * PAL Address: 0x8008c9a0
 * PAL Size: 124b
 * EN Address: 0x8008C33C
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* param1, _pppCtrlTable* param2)
{
    VYmMegaBirthShpTail2* work = reinterpret_cast<VYmMegaBirthShpTail2*>(
        param1->m_workArea + GetYmMegaBirthShpTail2DataOffsets(param2)->m_workOffset);

    if (work->m_particles != 0) {
        pppMemFree(work->m_particles);
        work->m_particles = 0;
    }
    if (work->m_wmats != 0) {
        pppMemFree(work->m_wmats);
        work->m_wmats = 0;
    }
    if (work->m_colors != 0) {
        pppMemFree(work->m_colors);
        work->m_colors = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8008bb28
 * PAL Size: 3704b
 * EN Address: 0x8008B4C4
 * EN Size: 3704b
 * JP Address: TODO
 * JP Size: TODO
 */
static void birth(_pppPObject* pppPObject, VYmMegaBirthShpTail2* vYmMegaBirthShpTail2,
           PYmMegaBirthShpTail2* pYmMegaBirthShpTail2, VColor* vColor,
           _PARTICLE_DATA* particleData, _PARTICLE_WMAT* particleWMat,
           _PARTICLE_COLOR* particleColor)
{
    float vx;
    float vy;
    float vz;
    float spread = (float)pYmMegaBirthShpTail2->m_spread;
    float spreadRange = 2.0f * spread;

    memset(particleData, 0, sizeof(_PARTICLE_DATA));
    if (particleWMat != 0) {
        memset(particleWMat, 0, sizeof(_PARTICLE_WMAT));
    }
    if (particleColor != 0) {
        memset(particleColor, 0, sizeof(_PARTICLE_COLOR));
    }

    switch (pYmMegaBirthShpTail2->m_spawnMode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7: {
        pppFVECTOR4 baseDir;
        pppIVECTOR4 angles;
        pppFMATRIX rot;

        baseDir.x = pYmMegaBirthShpTail2->m_baseDirection.x;
        baseDir.y = pYmMegaBirthShpTail2->m_baseDirection.y;
        baseDir.z = pYmMegaBirthShpTail2->m_baseDirection.z;
        angles.x = (s32)(spreadRange * Math.RandF() - spread);
        angles.x = (s32)((float)(angles.x << 15) / 180.0f);
        angles.y = (s32)(spreadRange * Math.RandF() - spread);
        angles.y = (s32)((float)(angles.y << 15) / 180.0f);
        angles.z = (s32)(spreadRange * Math.RandF() - spread);
        angles.z = (s32)((float)(angles.z << 15) / 180.0f);
        if ((pYmMegaBirthShpTail2->m_spawnMode == 2) || (pYmMegaBirthShpTail2->m_spawnMode == 3)) {
            angles.x = 0;
            angles.y = 0;
        }

        pppGetRotMatrixXYZ(rot, &angles);
        PSMTXMultVecSR(rot.value, (Vec*)&baseDir, &particleData->m_direction);
        particleData->m_direction.x *= pYmMegaBirthShpTail2->m_spawnScale.x;
        particleData->m_direction.y *= pYmMegaBirthShpTail2->m_spawnScale.y;
        particleData->m_direction.z *= pYmMegaBirthShpTail2->m_spawnScale.z;
        pppNormalize(particleData->m_direction,
                     particleData->m_direction);
        break;
    }
    }

    switch (pYmMegaBirthShpTail2->m_spawnMode) {
    default:
    {
        if (0.0f != pYmMegaBirthShpTail2->m_spawnRange) {
            float scale;

            switch (pYmMegaBirthShpTail2->m_randType) {
            default:
                scale = pYmMegaBirthShpTail2->m_spawnRange;
                break;
            case 1:
                Math.RandF();
                scale = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
                break;
            case 2:
            {
                scale = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF() * Math.RandF();
                break;
            }
            case 3:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                scale = pYmMegaBirthShpTail2->m_spawnRange * rand2;
                scale = pYmMegaBirthShpTail2->m_spawnRange - 0.7f * (scale * rand1);
                break;
            }
            case 4:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                float rand4 = Math.RandF();
                scale = pYmMegaBirthShpTail2->m_spawnRange * rand2;
                scale = rand4 * (rand3 * (scale * rand1));
                break;
            }
            case 5:
            {
                float rand1 = Math.RandF();
                float rand2 = Math.RandF();
                float rand3 = Math.RandF();
                scale = pYmMegaBirthShpTail2->m_spawnRange * rand2;
                scale = pYmMegaBirthShpTail2->m_spawnRange - 0.5f * (rand3 * (scale * rand1));
                break;
            }
            }

            Vec velocity = particleData->m_direction;
            pppScaleVectorXYZ(particleData->m_position, velocity, scale);
        }
        break;
    }

    case 4:
    case 5:
    {
        if (0.0f == pYmMegaBirthShpTail2->m_spawnRange) {
            break;
        }
        float speedRandHalf = 0.5f * pYmMegaBirthShpTail2->m_spawnRange;

        {
        float rand1;
        float rand2;
        float rand3;
        float rand4;
        switch (pYmMegaBirthShpTail2->m_randType) {
        default:
            particleData->m_position.x = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_position.x -= speedRandHalf;
            particleData->m_position.y = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_position.y -= speedRandHalf;
            particleData->m_position.z = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_position.z -= speedRandHalf;
            break;
        case 1:
            Math.RandF();
            particleData->m_position.x = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_position.x -= speedRandHalf;
            particleData->m_position.y = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_position.y -= speedRandHalf;
            particleData->m_position.z = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF();
            particleData->m_position.z -= speedRandHalf;
            break;
        case 2:
            particleData->m_position.x = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF() * Math.RandF();
            particleData->m_position.x -= speedRandHalf;
            particleData->m_position.y = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF() * Math.RandF();
            particleData->m_position.y -= speedRandHalf;
            particleData->m_position.z = pYmMegaBirthShpTail2->m_spawnRange * Math.RandF() * Math.RandF();
            particleData->m_position.z -= speedRandHalf;
            break;
        case 3:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_position.x = pYmMegaBirthShpTail2->m_spawnRange - 0.7f * (rand2 * rand1);
            particleData->m_position.x -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_position.y = pYmMegaBirthShpTail2->m_spawnRange - 0.7f * (rand2 * rand1);
            particleData->m_position.y -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_position.z = pYmMegaBirthShpTail2->m_spawnRange - 0.7f * (rand2 * rand1);
            particleData->m_position.z -= speedRandHalf;
            break;
        case 4:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand4 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_position.x = rand4 * (rand3 * (rand2 * rand1));
            particleData->m_position.x -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand4 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_position.y = rand4 * (rand3 * (rand2 * rand1));
            particleData->m_position.y -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand4 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_position.z = rand4 * (rand3 * (rand2 * rand1));
            particleData->m_position.z -= speedRandHalf;
            break;
        case 5:
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_position.x = pYmMegaBirthShpTail2->m_spawnRange - 0.5f * (rand3 * (rand2 * rand1));
            particleData->m_position.x -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_position.y = pYmMegaBirthShpTail2->m_spawnRange - 0.5f * (rand3 * (rand2 * rand1));
            particleData->m_position.y -= speedRandHalf;
            rand1 = Math.RandF();
            rand2 = Math.RandF();
            rand3 = Math.RandF();
            rand2 = pYmMegaBirthShpTail2->m_spawnRange * rand2;
            particleData->m_position.z = pYmMegaBirthShpTail2->m_spawnRange - 0.5f * (rand3 * (rand2 * rand1));
            particleData->m_position.z -= speedRandHalf;
            break;
        }
        }

        particleData->m_position.x *= pYmMegaBirthShpTail2->m_spawnScale.x;
        particleData->m_position.y *= pYmMegaBirthShpTail2->m_spawnScale.y;
        particleData->m_position.z *= pYmMegaBirthShpTail2->m_spawnScale.z;
        break;
    }

    case 6:
    case 7:
    case 8:
    case 9:
    {
        Vec* pathBase = pppPObject->m_drawMatrixPtr;

        if (pYmMegaBirthShpTail2->m_pathIndex >= 0) {
            pppShapeGroupRaw* pathInfo = &ppvEnv->m_shapeGroupPtr[pYmMegaBirthShpTail2->m_pathIndex];

            if (pathBase == 0) {
                pathBase = ppvEnv->m_mapMeshPtr[pathInfo->m_meshIndex]->m_vertices;
            }

            {
                float sampleT;

                switch (pYmMegaBirthShpTail2->m_randType) {
                default:
                    if ((int)vYmMegaBirthShpTail2->m_pathIndex >= pathInfo->m_vertexCount) {
                        vYmMegaBirthShpTail2->m_pathIndex = 0;
                    }

                    if (pathBase != 0) {
                        u16 sampleIndex = vYmMegaBirthShpTail2->m_pathIndex;
                        u16* indices = pathInfo->m_vertexIndices;
                        vYmMegaBirthShpTail2->m_pathIndex = sampleIndex + 1;

                        Vec* pathVec = &pathBase[indices[sampleIndex]];
                        vx = pathVec->x;
                        vy = pathVec->y;
                        vz = pathVec->z;
                    }
                    goto path_store;
                case 1:
                    Math.RandF();
                    sampleT = Math.RandF();
                    break;
                case 2:
                {
                    float r0 = Math.RandF();
                    float r1 = Math.RandF();
                    float r2 = Math.RandF();
                    sampleT = r2 * (r1 * r0);
                    break;
                }
                case 3:
                {
                    float r0 = Math.RandF();
                    float r1 = Math.RandF();
                    float r2 = Math.RandF();
                    sampleT = static_cast<float>(1.0 - (r2 * (r1 * r0)));
                    break;
                }
                case 4:
                {
                    float r0 = Math.RandF();
                    float r1 = Math.RandF();
                    float r2 = Math.RandF();
                    float r3 = Math.RandF();
                    sampleT = r3 * (r2 * (r1 * r0));
                    break;
                }
                case 5:
                {
                    float r0 = Math.RandF();
                    float r1 = Math.RandF();
                    float r2 = Math.RandF();
                    float r3 = Math.RandF();
                    float r4 = Math.RandF();
                    sampleT = static_cast<float>(1.0 - (r4 * (r3 * (r2 * (r1 * r0)))));
                    break;
                }
                }

                if ((int)vYmMegaBirthShpTail2->m_pathIndex >= pathInfo->m_vertexCount) {
                    vYmMegaBirthShpTail2->m_pathIndex = 0;
                }

                if (pathBase != 0) {
                    int sampleIndex = (int)(sampleT * (float)pathInfo->m_vertexCount);
                    Vec* pathVec = &pathBase[pathInfo->m_vertexIndices[sampleIndex]];
                    vx = pathVec->x;
                    vy = pathVec->y;
                    vz = pathVec->z;
                }
                path_store:

                particleData->m_position.x = vx * pYmMegaBirthShpTail2->m_spawnScale.x;
                particleData->m_position.y = vy * pYmMegaBirthShpTail2->m_spawnScale.y;
                particleData->m_position.z = vz * pYmMegaBirthShpTail2->m_spawnScale.z;

                if ((pYmMegaBirthShpTail2->m_spawnMode == 8) || (pYmMegaBirthShpTail2->m_spawnMode == 9)) {
                    Vec velocity = particleData->m_position;
                    pppNormalize(particleData->m_direction, velocity);
                }
            }
        }
        break;
    }

    }


    if (pYmMegaBirthShpTail2->m_fadeInFrames != 0) {
        particleData->m_alphaFade = (float)vColor->m_color.rgba[3];
        particleData->m_fadeInFrames = pYmMegaBirthShpTail2->m_fadeInFrames;
    }
    if (pYmMegaBirthShpTail2->m_fadeOutFrames != 0) {
        particleData->m_fadeOutFrames = pYmMegaBirthShpTail2->m_fadeOutFrames;
    }

    particleData->m_speed = pYmMegaBirthShpTail2->m_speed;
    particleData->m_tailSpeed = pYmMegaBirthShpTail2->m_tailSpeed;
    if (pYmMegaBirthShpTail2->m_speedRandom != 0.0f) {
        float rand1 = Math.RandF();
        particleData->m_speed +=
            (2.0f * pYmMegaBirthShpTail2->m_speedRandom) * rand1 -
            pYmMegaBirthShpTail2->m_speedRandom;
    }

    if (pYmMegaBirthShpTail2->m_life == 0) {
        particleData->m_life = 0xFFFF;
    } else {
        particleData->m_life = pYmMegaBirthShpTail2->m_life;
    }
    particleData->m_age = 0;

    switch (pYmMegaBirthShpTail2->m_matrixMode) {
    case 0:
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, vYmMegaBirthShpTail2->m_emitterMatrix);
        break;
    case 1:
        pppCopyMatrix(*(pppFMATRIX*)particleWMat, vYmMegaBirthShpTail2->m_emitterMatrix);
        break;
    }

    particleData->m_unk3A[0] = 0;
    particleData->m_unk3A[1] = 0;
    particleData->m_unk3A[2] = 0;
    particleData->m_historyIndex = 0;
    particleData->m_historyCount = 0x1f;

    pppFVECTOR4 zeroVec;
    zeroVec.z = 0.0f;
    zeroVec.y = 0.0f;
    zeroVec.x = 0.0f;
    Vec* history = particleData->m_history;
    for (int i = 0x1e; i >= 0; i--) {
        pppCopyVector(*history, *(Vec*)&zeroVec);
        history++;
    }

    particleData->m_historyIndex = particleData->m_historyCount;
    particleData->m_historyIndex = particleData->m_historyIndex - 1;
}

/*
 * --INFO--
 * PAL Address: 0x8008b824
 * PAL Size: 772b
 * EN Address: 0x8008B1C0
 * EN Size: 772b
 * JP Address: TODO
 * JP Size: TODO
 */
static void calc(_pppPObject* pppPObject, VYmMegaBirthShpTail2* vYmMegaBirthShpTail2,
          PYmMegaBirthShpTail2* pYmMegaBirthShpTail2, _PARTICLE_DATA* particleData,
          VColor* vColor, _PARTICLE_COLOR* particleColor)
{
    s32 alpha = vColor->m_color.rgba[3];
    u8 frameWindow;
    u8 fadeOutFrames;
    u8 historyIndex;
    u16 frameIndex;
    pppShapeAnimData* shapeAnim;
    pppShapeAnimFrame* frameEntry;
    Vec scaled;

    particleData->m_speed = particleData->m_speed + pYmMegaBirthShpTail2->m_speedStep;
    particleData->m_tailSpeed = particleData->m_tailSpeed + pYmMegaBirthShpTail2->m_tailSpeedStep;

    pppScaleVectorXYZ(scaled, particleData->m_direction, particleData->m_speed);
    pppAddVector(particleData->m_position, particleData->m_position, scaled);

    pppScaleVectorXYZ(scaled, vYmMegaBirthShpTail2->m_tailScaleDirection, particleData->m_tailSpeed);
    pppAddVector(particleData->m_position, particleData->m_position, scaled);

    if (pYmMegaBirthShpTail2->m_life != 0) {
        particleData->m_life = particleData->m_life - 1;
    }

    particleData->m_age = particleData->m_age + 1;
    frameWindow = particleData->m_fadeInFrames;
    if ((frameWindow != 0) && (particleData->m_age <= frameWindow)) {
        particleData->m_alphaFade = particleData->m_alphaFade - ((float)alpha / (float)frameWindow);
        if (particleData->m_alphaFade < 0.0f) {
            particleData->m_alphaFade = 0.0f;
        }
    }

    if ((particleData->m_fadeOutFrames != 0) && (particleData->m_life <= particleData->m_fadeOutFrames)) {
        fadeOutFrames = pYmMegaBirthShpTail2->m_fadeOutFrames;
        particleData->m_alphaFade = particleData->m_alphaFade + ((float)alpha / (float)fadeOutFrames);
        if (particleData->m_alphaFade > 127.0f) {
            particleData->m_alphaFade = 127.0f;
        }
    }

    if (particleData->m_historyIndex == 0) {
        particleData->m_historyIndex = particleData->m_historyCount;
    }
    particleData->m_historyIndex = particleData->m_historyIndex - 1;
    historyIndex = particleData->m_historyIndex;

    PSMTXMultVec(pppPObject->m_localMatrix.value, &particleData->m_position,
                 &particleData->m_history[historyIndex]);

    frameIndex = particleData->m_shapeFrame;
    shapeAnim =
        static_cast<pppShapeAnimData*>(
        ppvEnv->m_shapeTablePtr[pYmMegaBirthShpTail2->m_shapeIndex]
            ->m_animData);
    particleData->m_drawFrame = frameIndex;

    frameEntry = &shapeAnim->m_frames[frameIndex];
    particleData->m_frameTimer =
        particleData->m_frameTimer + pYmMegaBirthShpTail2->m_frameStep;
    int elapsedFrame = particleData->m_frameTimer;
    int frameDuration = frameEntry->m_duration;
    if ((int)elapsedFrame < frameDuration) {
        return;
    }

    particleData->m_frameTimer = (u16)(elapsedFrame - frameDuration);
    particleData->m_shapeFrame = particleData->m_shapeFrame + 1;
    if ((int)particleData->m_shapeFrame >= shapeAnim->m_frameCount) {
        if ((frameEntry->m_flags & 0x80) != 0) {
            particleData->m_shapeFrame = 0;
            particleData->m_frameTimer = 0;
        } else {
            particleData->m_frameTimer = 0;
            particleData->m_shapeFrame = particleData->m_shapeFrame - 1;
        }
    }
}

static inline void calc_particle(_pppPObject* pObject, VYmMegaBirthShpTail2* work, PYmMegaBirthShpTail2* param, VColor* colorWork)
{
    _PARTICLE_DATA* particleData;
    _PARTICLE_WMAT* worldMat;
    _PARTICLE_COLOR* particleColor;
    int spawnCount;
    u32 i;

    spawnCount = 0;
    particleData = work->m_particles;
    worldMat = work->m_wmats;
    particleColor = work->m_colors;

    if ((ppvUserStopPartF == 0) && (param->m_shapeIndex != 0xFFFF)) {
        work->m_emitTimer = work->m_emitTimer + 1;

        for (i = 0; i < work->m_maxParticles; i++) {
            if (particleData->m_life != 0) {
                calc(pObject, work, param, particleData, colorWork, particleColor);
            } else {
                if ((param->m_emitInterval <= work->m_emitTimer) &&
                    (spawnCount < param->m_emitCount)) {
                    birth(pObject, work, param, colorWork, particleData, worldMat,
                        particleColor);
                    spawnCount = spawnCount + 1;
                }
            }

            if (worldMat != 0) {
                worldMat = worldMat + 1;
            }
            if (particleColor != 0) {
                particleColor = particleColor + 1;
            }
            particleData++;
        }

        if (spawnCount > 0) {
            work->m_emitTimer = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8008b3f4
 * PAL Size: 1072b
 * EN Address: 0x8008AD90
 * EN Size: 1072b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* object, PYmMegaBirthShpTail2* param, _pppCtrlTable* offsets)
{
    int colorOffset;

    YmMegaBirthShpTail2DataOffsets* serializedOffsets = GetYmMegaBirthShpTail2DataOffsets(offsets);
    colorOffset = serializedOffsets->m_colorOffset;
    VYmMegaBirthShpTail2* const work =
        (VYmMegaBirthShpTail2*)(object->m_workArea + serializedOffsets->m_workOffset);
    VColor* const colorWork = (VColor*)(object->m_workArea + colorOffset);

    if (work->m_particles == 0) {
        work->m_maxParticles = param->m_maxParticles;
        work->m_particles = (_PARTICLE_DATA*)pppMemAlloc(
            work->m_maxParticles * sizeof(_PARTICLE_DATA), ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMegaBirthShpTail2_cpp), 0x30e);
        if (work->m_particles != 0) {
            memset(work->m_particles, 0, work->m_maxParticles * sizeof(_PARTICLE_DATA));
        }

        work->m_wmats = (_PARTICLE_WMAT*)pppMemAlloc(
            work->m_maxParticles * sizeof(_PARTICLE_WMAT), ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMegaBirthShpTail2_cpp), 0x316);
        if (work->m_wmats != 0) {
            memset(work->m_wmats, 0, work->m_maxParticles * sizeof(_PARTICLE_WMAT));
        }

        if (param->m_enableParticleColor != 0) {
            work->m_colors = (_PARTICLE_COLOR*)pppMemAlloc(
                work->m_maxParticles * sizeof(_PARTICLE_COLOR), ppvEnv->m_stagePtr, const_cast<char*>(s_pppYmMegaBirthShpTail2_cpp), 0x31e);
            if (work->m_colors != 0) {
                memset(work->m_colors, 0, work->m_maxParticles * sizeof(_PARTICLE_COLOR));
            }
        }

        work->m_tailScaleDirection = param->m_tailDirection;
        pppNormalize(work->m_tailScaleDirection, work->m_tailScaleDirection);
    }

    if (alloc_check(work, param)) {
        switch (param->m_spawnMode) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 9:
        {
            Vec firstCol;
            Vec secondCol;
            Vec thirdCol;

            PSMTXIdentity(work->m_emitterMatrix.value);
            firstCol.x = work->m_emitterMatrix.value[0][0];
            firstCol.y = work->m_emitterMatrix.value[1][0];
            firstCol.z = work->m_emitterMatrix.value[2][0];
            PSVECScale(&firstCol, &firstCol, ppvMng->m_scale.x);
            work->m_emitterMatrix.value[0][0] = firstCol.x;
            work->m_emitterMatrix.value[1][0] = firstCol.y;
            work->m_emitterMatrix.value[2][0] = firstCol.z;

            secondCol.x = work->m_emitterMatrix.value[0][1];
            secondCol.y = work->m_emitterMatrix.value[1][1];
            secondCol.z = work->m_emitterMatrix.value[2][1];
            PSVECScale(&secondCol, &secondCol, ppvMng->m_scale.x);
            work->m_emitterMatrix.value[0][1] = secondCol.x;
            work->m_emitterMatrix.value[1][1] = secondCol.y;
            work->m_emitterMatrix.value[2][1] = secondCol.z;

            thirdCol.x = work->m_emitterMatrix.value[0][2];
            thirdCol.y = work->m_emitterMatrix.value[1][2];
            thirdCol.z = work->m_emitterMatrix.value[2][2];
            PSVECScale(&thirdCol, &thirdCol, ppvMng->m_scale.x);
            work->m_emitterMatrix.value[0][2] = thirdCol.x;
            work->m_emitterMatrix.value[1][2] = thirdCol.y;
            work->m_emitterMatrix.value[2][2] = thirdCol.z;

            work->m_emitterMatrix.value[0][3] = ppvMng->m_position.x;
            work->m_emitterMatrix.value[1][3] = ppvMng->m_position.y;
            work->m_emitterMatrix.value[2][3] = ppvMng->m_position.z;
            break;
        }
        default:
            pppCopyMatrix(work->m_emitterMatrix, ppvMng->m_matrix);
            break;
        }

        calc_particle((_pppPObject*)object, work, param, colorWork);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8008acc4
 * PAL Size: 1840b
 * EN Address: 0x8008A660
 * EN Size: 1840b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2* object, PYmMegaBirthShpTail2* step, _pppCtrlTable* offsets)
{
    VYmMegaBirthShpTail2* work;
    VColor* colorWork;
    _PARTICLE_DATA* particle;
    _PARTICLE_WMAT* wmats;
    _PARTICLE_COLOR* colors;
    tagOAN3_SHAPE* shape;
    pppShapeAnimData* shapeAnim;
    u32 i;
    s32 count;
    s32 startIndex;
    float alphaMul;
    float curX;
    float curY;
    float colorStepG;
    float curZ;
    float colorStepB;
    float colorStepR;
    float nextX;
    float segDx;
    float segDy;
    float segDz;
    float nextY;
    float nextZ;
    float diffR;
    float diffB;
    float diffG;
    float segLen;
    float baseX;
    float colorStepA;
    float diffA;
    float baseY;
    float baseZ;
    float countMinusOne;
    float segCursor;
    float segRemain;
    float drawScale;
    float scaleStep;
    s32 nextIndex;
    s32 lastIndex;
    _PARTICLE_DATA* particlesBase;
    _PARTICLE_WMAT* wmatsBase;
    _PARTICLE_COLOR* colorsBase;
    Vec* history;
    u8 zEnable;
    pppFVECTOR4 colorStart;
    pppFVECTOR4 colorEnd;
    pppFMATRIX drawMtx;
    Vec zeroVec;
    Vec seg;
    pppFVECTOR4 camPos;
    pppFVECTOR4 pos;
    pppFVECTOR4 mngPos;
    Vec zeroVecB;
    Vec segB;
    GXColor amb;

    work = (VYmMegaBirthShpTail2*)(object->m_workArea + GetYmMegaBirthShpTail2DataOffsets(offsets)->m_workOffset);
    colorWork = (VColor*)(object->m_workArea + GetYmMegaBirthShpTail2DataOffsets(offsets)->m_colorOffset);
    particlesBase = work->m_particles;
    wmatsBase = work->m_wmats;
    colorsBase = work->m_colors;
    particle = particlesBase;
    wmats = wmatsBase;
    colors = colorsBase;

    if (!alloc_check(work, step)) {
        return;
    }
    if (step->m_shapeIndex == 0xFFFF) {
        return;
    }

    shapeAnim = static_cast<pppShapeAnimData*>(ppvEnv->m_shapeTablePtr[step->m_shapeIndex]->m_animData);
    if (step->m_disableDepthTest != 0) {
        zEnable = 0;
    } else {
        zEnable = 1;
    }
    pppSetDrawEnv(0, &object->m_drawMatrix, step->m_depth, step->m_lightTarget, step->m_fogIndex,
                  step->m_blendMode, 0, zEnable, 1, 0);
    pppSetBlendMode(step->m_blendMode);

    for (i = 0; i < work->m_maxParticles; i++) {
        if (particle->m_life != 0) {
            segCursor = 0.0f;
            count = step->m_drawCount;
            nextIndex = particle->m_historyIndex;
            shape = reinterpret_cast<tagOAN3_SHAPE*>(reinterpret_cast<u8*>(shapeAnim) +
                                                     shapeAnim->m_frames[particle->m_drawFrame].m_shapeOffset);
            lastIndex = particle->m_historyCount - 1;
            countMinusOne = (float)(count - 1);
            alphaMul = (float)colorWork->m_alpha / 16384.0f;
            U8ToF32(&colorStart, (u8*)&step->m_colorStart);
            U8ToF32(&colorEnd, (u8*)&step->m_colorEnd);
            colorStart.w *= alphaMul;
            colorEnd.w *= alphaMul;
            diffA = colorStart.w - colorEnd.w;
            diffR = colorStart.x - colorEnd.x;
            diffG = colorStart.y - colorEnd.y;
            diffB = colorStart.z - colorEnd.z;
            if (countMinusOne != segCursor) {
                colorStepR = diffR / countMinusOne;
                colorStepG = diffG / countMinusOne;
                colorStepB = diffB / countMinusOne;
                colorStepA = diffA / countMinusOne;
            } else {
                colorStepR = 0.5f;
                colorStepG = colorStepR;
                colorStepB = colorStepR;
                colorStepA = colorStepR;
            }

            pppUnitMatrix(drawMtx);
            drawScale = step->m_drawScaleStart;
            scaleStep = (drawScale - step->m_drawScaleEnd) / countMinusOne;

            history = particle->m_history;
            startIndex = particle->m_historyIndex;
            curX = history[nextIndex].x;
            curY = history[nextIndex].y;
            curZ = history[nextIndex].z;
            baseX = curX;
            baseY = curY;
            baseZ = curZ;
            if (nextIndex++ == lastIndex) {
                nextIndex = 0;
            }
            nextX = history[nextIndex].x;
            nextY = history[nextIndex].y;
            nextZ = history[nextIndex].z;
            segDx = nextX - curX;
            segDy = nextY - curY;
            segDz = nextZ - curZ;
            zeroVec.z = 0.0f;
            zeroVec.y = 0.0f;
            zeroVec.x = 0.0f;
            seg.x = segDx;
            seg.y = segDy;
            seg.z = segDz;
            segLen = PSVECDistance(&zeroVec, &seg);
            segRemain = segLen;

            if (step->m_drawHead == 0) {
                goto update_step;
            }

            for (count = step->m_drawCount; count > 0; count--) {
                if ((0.0f != particle->m_history[nextIndex].x) ||
                    (0.0f != particle->m_history[nextIndex].y) ||
                    (0.0f != particle->m_history[nextIndex].z)) {
                    pppUnitMatrix(drawMtx);
                    drawMtx.value[0][0] = drawScale * ppvMng->m_scale.x;
                    drawMtx.value[1][1] = drawScale * ppvMng->m_scale.y;
                    drawMtx.value[2][2] = drawScale * ppvMng->m_scale.z;
                    pos.x = curX;
                    pos.y = curY;
                    pos.z = curZ;

                    if (step->m_matrixMode == 0) {
                        PSMTXMultVec(ppvWorldMatrix, (Vec*)&pos, (Vec*)&camPos);
                    } else if (step->m_matrixMode == 1) {
                        mngPos.x = ppvMng->m_matrix.value[0][3];
                        mngPos.y = ppvMng->m_matrix.value[1][3];
                        mngPos.z = ppvMng->m_matrix.value[2][3];
                        PSVECAdd((Vec*)&mngPos, (Vec*)&pos, (Vec*)&pos);
                        PSMTXMultVec(ppvCameraMatrix, (Vec*)&pos, (Vec*)&camPos);
                    }

                    drawMtx.value[0][3] = camPos.x;
                    drawMtx.value[1][3] = camPos.y;
                    drawMtx.value[2][3] = camPos.z;
                    GXLoadPosMtxImm(drawMtx.value, 0);

                    amb.r = (u8)colorStart.x;
                    amb.g = (u8)colorStart.y;
                    amb.b = (u8)colorStart.z;
                    amb.a = (u8)(colorStart.w * (0.00787f * (127.0f - particle->m_alphaFade)));
                    GXSetChanAmbColor(GX_COLOR0A0, amb);
                    pppDrawShp(shape, ppvEnv->m_materialSetPtr, step->m_blendMode);

                update_step:
                    colorStart.x -= colorStepR;
                    colorStart.y -= colorStepG;
                    colorStart.z -= colorStepB;
                    colorStart.w -= colorStepA;
                    drawScale -= scaleStep;
                    if (step->m_segmentLength <= 0.0f) {
                        goto next_particle;
                    }

                advance_segment:
                    if (segRemain >= step->m_segmentLength) {
                        curX = (segDx * segCursor) / segLen;
                        curY = (segDy * segCursor) / segLen;
                        curZ = (segDz * segCursor) / segLen;
                        curX += baseX;
                        curY += baseY;
                        curZ += baseZ;
                        segCursor += step->m_segmentLength;
                        segRemain -= step->m_segmentLength;
                        continue;
                    }

                    if (nextIndex++ == lastIndex) {
                        nextIndex = 0;
                    }
                    if (nextIndex == startIndex) {
                        goto next_particle;
                    }

                    baseX = nextX;
                    baseY = nextY;
                    baseZ = nextZ;
                    segCursor -= segLen;
                    segDy = (nextY = history[nextIndex].y) - baseY;
                    segDz = (nextZ = history[nextIndex].z) - baseZ;
                    segDx = (nextX = history[nextIndex].x) - baseX;
                    zeroVecB.z = 0.0f;
                    zeroVecB.y = 0.0f;
                    zeroVecB.x = 0.0f;
                    segB.x = segDx;
                    segB.y = segDy;
                    segB.z = segDz;
                    segLen = PSVECDistance(&zeroVecB, &segB);
                    segRemain += segLen;
                    goto advance_segment;
                }
            }
        }
    next_particle:
        if (wmats != 0) {
            wmats = wmats + 1;
        }
        if (colors != 0) {
            colors = colors + 1;
        }
        particle++;
    }
}
