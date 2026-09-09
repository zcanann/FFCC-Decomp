#include "ffcc/ptrarray.h"
#include "global.h"
#include "ffcc/pppConformBGNormal.h"
#include "types.h"
#include "ffcc/game.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/gobject.h"

#include "dolphin/mtx.h"
#include "dolphin/gx.h"
#include <math.h>

struct ConformBgNormalState {
    Vec m_normal;
    u8 m_initialized;
};

struct ConformBgNormalCylinder {
    Vec m_bottom;
    Vec m_top;
    Vec m_axis;
    float m_radius;
    Vec m_boundsMin;
    Vec m_boundsMax;
};

STATIC_ASSERT(sizeof(ConformBgNormalDataOffsets) == 0x4);
STATIC_ASSERT(offsetof(ConformBgNormalDataOffsets, m_stateOffset) == 0x0);

static inline ConformBgNormalDataOffsets* GetConformBgNormalDataOffsets(_pppCtrlTable* ctrl)
{
    return reinterpret_cast<ConformBgNormalDataOffsets*>(ctrl->m_serializedDataOffsets);
}

static inline Vec* ConformBgNormalHitNormal(CGObject* owner)
{
    return &owner->HitFaceNormal();
}

/*
 * --INFO--
 * PAL Address: 0x801091d4
 * PAL Size: 1552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConformBGNormal(pppConformBGNormal* pppConformBGNormal, pppConformBGNormalStep* param2, struct _pppCtrlTable* param3)
{
    u8 mode;
    f32 matrixX;
    f32 matrixY;
    f32 matrixZ;
    f32 ownerX;
    f32 ownerY;
    f32 ownerZ;
    f32 bottomX;
    f32 bottomY;
    f32 bottomZ;
    f32 cylinderY;
    ConformBgNormalState* state;
    _pppMngSt* pppMngSt;
    s32 checkResult;
    CGObject* owner;
    s32 hitFound;
    f64 trigValue;
    Mtx basisMtx;
    Mtx scaleMtx;
    ConformBgNormalCylinder firstCylinder;
    ConformBgNormalCylinder secondCylinder;
    Vec local_140;
    Vec local_14c;
    Vec local_158;
    Vec local_164;
    Vec local_170;
    Vec firstRayDirection;
    Quaternion local_18c;
    Quaternion local_19c;
    Quaternion local_1ac;
    Vec secondRayDirection;
    s32 dataOffset;

    if (ppvUserStopPartF != 0) {
        return;
    }

    pppMngSt = ppvMng;
    owner = (CGObject*)pppMngSt->m_lookTarget;
    hitFound = 0;
    matrixX = pppMngSt->m_matrix.value[0][3];
    matrixY = pppMngSt->m_matrix.value[1][3];
    matrixZ = pppMngSt->m_matrix.value[2][3];
    dataOffset = GetConformBgNormalDataOffsets(param3)->m_stateOffset;
    state = (ConformBgNormalState*)(pppConformBGNormal->m_workArea + dataOffset);

    if (((s32)Game.m_currentSceneId != 7) || (param2->m_stepValue == 2)) {
            mode = param2->m_stepValue;

            if (mode == 0) {
                if ((s8)((s32)((u32)(owner->m_stateFlags0 & 0xc0) << 24) >> 31) != 0) {
                    local_164 = *ConformBgNormalHitNormal(owner);
                } else {
                    local_164.x = 0.0f;
                    local_164.y = 1.0f;
                    local_164.z = 0.0f;
                }
            } else if (mode == 1) {
                hitFound = 1;
                Game.GetTargetCursor(ppvMng->m_hitParams.m_particleIndex, local_170, local_164);
            } else if (mode == 2) {
                firstRayDirection.x = 0.0f;
                firstRayDirection.y = -2000.0f;
                firstRayDirection.z = 0.0f;

                cylinderY = matrixY + param2->m_arg3;
                firstCylinder.m_boundsMin.z = 10000000000.0f;
                firstCylinder.m_boundsMin.y = 10000000000.0f;
                firstCylinder.m_boundsMin.x = 10000000000.0f;
                firstCylinder.m_boundsMax.z = -10000000000.0f;
                firstCylinder.m_boundsMax.y = -10000000000.0f;
                firstCylinder.m_boundsMax.x = -10000000000.0f;
                firstCylinder.m_bottom.x = matrixX;
                firstCylinder.m_bottom.y = cylinderY;
                firstCylinder.m_bottom.z = matrixZ;
                firstCylinder.m_axis.x = 0.0f;
                firstCylinder.m_axis.y = -2000.0f;
                firstCylinder.m_axis.z = 0.0f;
                firstCylinder.m_radius = 0.0f;

                checkResult = MapMng.CheckHitCylinderNear((CMapCylinder*)&firstCylinder, &firstRayDirection, 0xffffffff);
                hitFound = checkResult;
                if (checkResult != 0) {
                    MapMng.m_hitMapObj->CalcHitPosition(&local_170);
                    MapMng.m_hitMapObj->GetHitFaceNormal(&local_164);
                    if ((matrixY - 10.0f) > local_170.y) {
                        local_170.y = matrixY;
                    }
                } else {
                    local_164.x = 0.0f;
                    local_164.y = 1.0f;
                    local_164.z = 0.0f;
                    local_170.x = matrixX;
                    local_170.y = matrixY;
                    local_170.z = matrixZ;
                }
            }

            if (state->m_initialized == 0) {
                state->m_initialized = 1;
                state->m_normal.x = local_164.x;
                state->m_normal.y = local_164.y;
                state->m_normal.z = local_164.z;
            }

            local_18c.x = state->m_normal.x;
            local_18c.y = state->m_normal.y;
            local_18c.z = state->m_normal.z;
            local_18c.w = 1.0f;
            local_19c.x = local_164.x;
            local_19c.y = local_164.y;
            local_19c.z = local_164.z;
            local_19c.w = local_18c.w;
            C_QUATSlerp(&local_18c, &local_19c, &local_1ac, param2->m_initWOrk);
            state->m_normal.x = local_1ac.x;
            state->m_normal.y = local_1ac.y;
            state->m_normal.z = local_1ac.z;

            PSVECNormalize(&state->m_normal, &local_158);

            if ((param2->m_stepValue == 0) && (owner != NULL)) {
                trigValue = sin((f64)owner->m_rotBaseY);
                local_14c.x = (f32)trigValue;
                local_14c.y = 0.0f;
                trigValue = cos((f64)owner->m_rotBaseY);
                local_14c.z = (f32)trigValue;
                PSVECCrossProduct(&local_14c, &local_158, &local_140);
                PSVECNormalize(&local_140, &local_140);
                PSVECCrossProduct(&local_158, &local_140, &local_14c);
                PSVECNormalize(&local_14c, &local_14c);
            } else {
                local_140.x = 1.0f;
                local_140.z = local_140.y = 0.0f;
                PSVECCrossProduct(&local_158, &local_140, &local_14c);
                PSVECNormalize(&local_14c, &local_14c);
                PSVECCrossProduct(&local_14c, &local_158, &local_140);
                PSVECNormalize(&local_140, &local_140);
            }

            PSMTXIdentity(basisMtx);
            basisMtx[0][0] = local_140.x;
            basisMtx[0][1] = local_14c.x;
            basisMtx[0][2] = local_158.x;
            basisMtx[1][0] = local_140.y;
            basisMtx[1][1] = local_14c.y;
            basisMtx[1][2] = local_158.y;
            basisMtx[2][0] = local_140.z;
            basisMtx[2][1] = local_14c.z;
            basisMtx[2][2] = local_158.z;

            PSMTXCopy(basisMtx, ppvMng->m_matrix.value);
            PSMTXScale(scaleMtx, ppvMng->m_scale.x, ppvMng->m_scale.y, ppvMng->m_scale.z);
            PSMTXConcat(scaleMtx, ppvMng->m_matrix.value, ppvMng->m_matrix.value);

            mode = param2->m_stepValue;
            if (mode == 0) {
                if ((s8)((s32)((u32)(owner->m_stateFlags0 & 0xc0) << 24) >> 31) != 0) {
                    ppvMng->m_matrix.value[0][3] = owner->m_worldPosition.x;
                    ppvMng->m_matrix.value[1][3] = owner->m_worldPosition.y;
                    ppvMng->m_matrix.value[2][3] = owner->m_worldPosition.z;
                } else if ((owner->m_weaponNodeFlagBits.m_attached != 0) && (owner->m_attachOwner != NULL)) {
                    ownerX = owner->m_worldPosition.x;
                    ownerY = owner->m_attachOwner->m_worldPosition.y;
                    ownerZ = owner->m_worldPosition.z;
                    ppvMng->m_matrix.value[0][3] = ownerX;
                    ppvMng->m_matrix.value[1][3] = ownerY;
                    ppvMng->m_matrix.value[2][3] = ownerZ;
                } else {
                    bottomX = owner->m_worldPosition.x;
                    bottomY = owner->m_worldPosition.y;
                    bottomZ = owner->m_worldPosition.z;
                    secondRayDirection.x = 0.0f;
                    secondRayDirection.y = -2000.0f;
                    secondRayDirection.z = 0.0f;

                    secondCylinder.m_boundsMin.z = 10000000000.0f;
                    secondCylinder.m_boundsMin.y = 10000000000.0f;
                    secondCylinder.m_boundsMin.x = 10000000000.0f;
                    secondCylinder.m_boundsMax.z = -10000000000.0f;
                    secondCylinder.m_boundsMax.y = -10000000000.0f;
                    secondCylinder.m_boundsMax.x = -10000000000.0f;
                    secondCylinder.m_bottom.x = bottomX;
                    secondCylinder.m_bottom.y = bottomY;
                    secondCylinder.m_bottom.z = bottomZ;
                    secondCylinder.m_axis.x = 0.0f;
                    secondCylinder.m_axis.y = -2000.0f;
                    secondCylinder.m_axis.z = 0.0f;
                    secondCylinder.m_radius = 0.0f;

                    hitFound = MapMng.CheckHitCylinderNear((CMapCylinder*)&secondCylinder, &secondRayDirection, 0xffffffff);
                    if (hitFound != 0) {
                        MapMng.m_hitMapObj->CalcHitPosition(&local_170);
                        ppvMng->m_matrix.value[0][3] = local_170.x;
                        ppvMng->m_matrix.value[1][3] = local_170.y;
                        ppvMng->m_matrix.value[2][3] = local_170.z;
                    } else {
                        ownerZ = owner->m_worldPosition.z;
                        ownerX = owner->m_worldPosition.x;
                        ppvMng->m_matrix.value[0][3] = ownerX;
                        ppvMng->m_matrix.value[1][3] = matrixY;
                        ppvMng->m_matrix.value[2][3] = ownerZ;
                    }
                }
            } else if (mode == 1) {
                if (hitFound != 0) {
                    ppvMng->m_matrix.value[0][3] = local_170.x;
                    ppvMng->m_matrix.value[1][3] = local_170.y;
                    ppvMng->m_matrix.value[2][3] = local_170.z;
                } else {
                    ppvMng->m_matrix.value[0][3] = matrixX;
                    ppvMng->m_matrix.value[1][3] = matrixY;
                    ppvMng->m_matrix.value[2][3] = matrixZ;
                }
            } else if (mode == 2) {
                ppvMng->m_matrix.value[0][3] = local_170.x;
                ppvMng->m_matrix.value[1][3] = local_170.y;
                ppvMng->m_matrix.value[2][3] = local_170.z;
            }

            ppvMng->m_matrix.value[1][3] += param2->m_dataValIndex;
            pppSetFpMatrix(pppMngSt);
    }
}

/*
 * --INFO--
 * PAL Address: 0x801097e4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructConformBGNormal(pppConformBGNormal* conformBG, struct _pppCtrlTable* param2)
{
    ConformBgNormalState* state;
    f32 scale;

    state = (ConformBgNormalState*)(conformBG->m_workArea + GetConformBgNormalDataOffsets(param2)->m_stateOffset);
    scale = 0.0f;
    state->m_normal.z = scale;
    state->m_normal.y = scale;
    state->m_normal.x = scale;
    state->m_initialized = 0;
}
