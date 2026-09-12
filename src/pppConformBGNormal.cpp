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
void pppFrameConformBGNormal(pppConformBGNormal* conformBG, pppConformBGNormalStep* step, struct _pppCtrlTable* ctrl)
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
    ConformBgNormalCylinder emitterProbeCylinder;
    ConformBgNormalCylinder ownerProbeCylinder;
    Vec tangentAxis;
    Vec bitangentAxis;
    Vec normalAxis;
    Vec surfaceNormal;
    Vec hitPosition;
    Vec emitterProbeRay;
    Quaternion prevNormalQuat;
    Quaternion targetNormalQuat;
    Quaternion blendedNormalQuat;
    Vec ownerProbeRay;
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
    dataOffset = GetConformBgNormalDataOffsets(ctrl)->m_stateOffset;
    state = (ConformBgNormalState*)(conformBG->m_workArea + dataOffset);

    if (((s32)Game.m_currentSceneId != 7) || (step->m_stepValue == 2)) {
        mode = step->m_stepValue;

        if (mode == 0) {
            if ((s8)((s32)((u32)(owner->m_stateFlags0 & 0xc0) << 24) >> 31) != 0) {
                surfaceNormal = *ConformBgNormalHitNormal(owner);
            } else {
                surfaceNormal.x = 0.0f;
                surfaceNormal.y = 1.0f;
                surfaceNormal.z = 0.0f;
            }
        } else if (mode == 1) {
            hitFound = 1;
            Game.GetTargetCursor(ppvMng->m_hitParams.m_particleIndex, hitPosition, surfaceNormal);
        } else if (mode == 2) {
            emitterProbeRay.x = 0.0f;
            emitterProbeRay.y = -2000.0f;
            emitterProbeRay.z = 0.0f;

            cylinderY = matrixY + step->m_arg3;
            emitterProbeCylinder.m_boundsMin.z = 10000000000.0f;
            emitterProbeCylinder.m_boundsMin.y = 10000000000.0f;
            emitterProbeCylinder.m_boundsMin.x = 10000000000.0f;
            emitterProbeCylinder.m_boundsMax.z = -10000000000.0f;
            emitterProbeCylinder.m_boundsMax.y = -10000000000.0f;
            emitterProbeCylinder.m_boundsMax.x = -10000000000.0f;
            emitterProbeCylinder.m_bottom.x = matrixX;
            emitterProbeCylinder.m_bottom.y = cylinderY;
            emitterProbeCylinder.m_bottom.z = matrixZ;
            emitterProbeCylinder.m_axis.x = 0.0f;
            emitterProbeCylinder.m_axis.y = -2000.0f;
            emitterProbeCylinder.m_axis.z = 0.0f;
            emitterProbeCylinder.m_radius = 0.0f;

            checkResult = MapMng.CheckHitCylinderNear((CMapCylinder*)&emitterProbeCylinder, &emitterProbeRay, 0xffffffff);
            hitFound = checkResult;
            if (checkResult != 0) {
                MapMng.m_hitMapObj->CalcHitPosition(&hitPosition);
                MapMng.m_hitMapObj->GetHitFaceNormal(&surfaceNormal);
                if ((matrixY - 10.0f) > hitPosition.y) {
                    hitPosition.y = matrixY;
                }
            } else {
                surfaceNormal.x = 0.0f;
                surfaceNormal.y = 1.0f;
                surfaceNormal.z = 0.0f;
                hitPosition.x = matrixX;
                hitPosition.y = matrixY;
                hitPosition.z = matrixZ;
            }
        }

        if (state->m_initialized == 0) {
            state->m_initialized = 1;
            state->m_normal.x = surfaceNormal.x;
            state->m_normal.y = surfaceNormal.y;
            state->m_normal.z = surfaceNormal.z;
        }

        prevNormalQuat.x = state->m_normal.x;
        prevNormalQuat.y = state->m_normal.y;
        prevNormalQuat.z = state->m_normal.z;
        prevNormalQuat.w = 1.0f;
        targetNormalQuat.x = surfaceNormal.x;
        targetNormalQuat.y = surfaceNormal.y;
        targetNormalQuat.z = surfaceNormal.z;
        targetNormalQuat.w = prevNormalQuat.w;
        C_QUATSlerp(&prevNormalQuat, &targetNormalQuat, &blendedNormalQuat, step->m_initWOrk);
        state->m_normal.x = blendedNormalQuat.x;
        state->m_normal.y = blendedNormalQuat.y;
        state->m_normal.z = blendedNormalQuat.z;

        PSVECNormalize(&state->m_normal, &normalAxis);

        if ((step->m_stepValue == 0) && (owner != NULL)) {
            trigValue = sin((f64)owner->m_rotBaseY);
            bitangentAxis.x = (f32)trigValue;
            bitangentAxis.y = 0.0f;
            trigValue = cos((f64)owner->m_rotBaseY);
            bitangentAxis.z = (f32)trigValue;
            PSVECCrossProduct(&bitangentAxis, &normalAxis, &tangentAxis);
            PSVECNormalize(&tangentAxis, &tangentAxis);
            PSVECCrossProduct(&normalAxis, &tangentAxis, &bitangentAxis);
            PSVECNormalize(&bitangentAxis, &bitangentAxis);
        } else {
            tangentAxis.x = 1.0f;
            tangentAxis.z = tangentAxis.y = 0.0f;
            PSVECCrossProduct(&normalAxis, &tangentAxis, &bitangentAxis);
            PSVECNormalize(&bitangentAxis, &bitangentAxis);
            PSVECCrossProduct(&bitangentAxis, &normalAxis, &tangentAxis);
            PSVECNormalize(&tangentAxis, &tangentAxis);
        }

        PSMTXIdentity(basisMtx);
        basisMtx[0][0] = tangentAxis.x;
        basisMtx[0][1] = bitangentAxis.x;
        basisMtx[0][2] = normalAxis.x;
        basisMtx[1][0] = tangentAxis.y;
        basisMtx[1][1] = bitangentAxis.y;
        basisMtx[1][2] = normalAxis.y;
        basisMtx[2][0] = tangentAxis.z;
        basisMtx[2][1] = bitangentAxis.z;
        basisMtx[2][2] = normalAxis.z;

        PSMTXCopy(basisMtx, ppvMng->m_matrix.value);
        PSMTXScale(scaleMtx, ppvMng->m_scale.x, ppvMng->m_scale.y, ppvMng->m_scale.z);
        PSMTXConcat(scaleMtx, ppvMng->m_matrix.value, ppvMng->m_matrix.value);

        mode = step->m_stepValue;
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
                ownerProbeRay.x = 0.0f;
                ownerProbeRay.y = -2000.0f;
                ownerProbeRay.z = 0.0f;

                ownerProbeCylinder.m_boundsMin.z = 10000000000.0f;
                ownerProbeCylinder.m_boundsMin.y = 10000000000.0f;
                ownerProbeCylinder.m_boundsMin.x = 10000000000.0f;
                ownerProbeCylinder.m_boundsMax.z = -10000000000.0f;
                ownerProbeCylinder.m_boundsMax.y = -10000000000.0f;
                ownerProbeCylinder.m_boundsMax.x = -10000000000.0f;
                ownerProbeCylinder.m_bottom.x = bottomX;
                ownerProbeCylinder.m_bottom.y = bottomY;
                ownerProbeCylinder.m_bottom.z = bottomZ;
                ownerProbeCylinder.m_axis.x = 0.0f;
                ownerProbeCylinder.m_axis.y = -2000.0f;
                ownerProbeCylinder.m_axis.z = 0.0f;
                ownerProbeCylinder.m_radius = 0.0f;

                hitFound = MapMng.CheckHitCylinderNear((CMapCylinder*)&ownerProbeCylinder, &ownerProbeRay, 0xffffffff);
                if (hitFound != 0) {
                    MapMng.m_hitMapObj->CalcHitPosition(&hitPosition);
                    ppvMng->m_matrix.value[0][3] = hitPosition.x;
                    ppvMng->m_matrix.value[1][3] = hitPosition.y;
                    ppvMng->m_matrix.value[2][3] = hitPosition.z;
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
                ppvMng->m_matrix.value[0][3] = hitPosition.x;
                ppvMng->m_matrix.value[1][3] = hitPosition.y;
                ppvMng->m_matrix.value[2][3] = hitPosition.z;
            } else {
                ppvMng->m_matrix.value[0][3] = matrixX;
                ppvMng->m_matrix.value[1][3] = matrixY;
                ppvMng->m_matrix.value[2][3] = matrixZ;
            }
        } else if (mode == 2) {
            ppvMng->m_matrix.value[0][3] = hitPosition.x;
            ppvMng->m_matrix.value[1][3] = hitPosition.y;
            ppvMng->m_matrix.value[2][3] = hitPosition.z;
        }

        ppvMng->m_matrix.value[1][3] += step->m_dataValIndex;
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
void pppConstructConformBGNormal(pppConformBGNormal* conformBG, struct _pppCtrlTable* ctrl)
{
    ConformBgNormalState* state;
    f32 scale;

    state = (ConformBgNormalState*)(conformBG->m_workArea + GetConformBgNormalDataOffsets(ctrl)->m_stateOffset);
    scale = 0.0f;
    state->m_normal.z = scale;
    state->m_normal.y = scale;
    state->m_normal.x = scale;
    state->m_initialized = 0;
}
