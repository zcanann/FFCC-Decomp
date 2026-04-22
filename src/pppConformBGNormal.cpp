#include "ffcc/pppConformBGNormal.h"
#include "types.h"
#include "ffcc/map.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/gobject.h"
extern "C" {
extern const f32 kPppConformBgNormalZero;
extern const f32 kPppConformBgNormalOne;
extern int gPppCalcDisabled;
double sin(double);
double cos(double);
}

static const f32 kPppConformBgNormalDownRayY = -2000.0f;
static const f32 kPppConformBgNormalCylinderRadius = 10000000000.0f;
static const f32 kPppConformBgNormalCylinderHeight = -10000000000.0f;
static const f32 kPppConformBgNormalGroundSnapLimit = 10.0f;
#include "dolphin/mtx.h"
#include "dolphin/gx.h"

struct ConformCylinderQuery {
    Vec m_pos;
    Vec m_fieldC;
    Vec m_field18;
    Vec m_field24;
    f32 m_field30;
};

void pppSetFpMatrix(_pppMngSt*);

extern "C" {
s32 CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, u32);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
void GetHitFaceNormal__7CMapObjFP3Vec(void*, Vec*);

}

struct CMapCylinderRaw {
    Vec m_bottom;
    u8 m_pad0C[0x0C];
    Vec m_direction;
    f32 m_radius;
    Vec m_top;
    Vec m_direction2;
};

/*
 * --INFO--
 * PAL Address: 0x801091d4
 * PAL Size: 1552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConformBGNormal(struct pppConformBGNormal* pppConformBGNormal, struct pppConformBGNormalUnkB* param2, struct _pppCtrlTable* param3)
{
    u8 mode;
    f32 matrixX;
    f32 matrixY;
    f32 matrixZ;
    f32 ownerY;
    f32 ownerX;
    f32 ownerZ;
    f32 cylinderY;
    _pppMngSt* pppMngSt;
    s32 hitFound;
    CGObject* owner;
    f64 trigValue;
    Mtx basisMtx;
    Mtx scaleMtx;
    CMapCylinderRaw firstCylinder;
    CMapCylinderRaw secondCylinder;
    Vec local_140;
    Vec local_14c;
    Vec local_158;
    Vec local_164;
    Vec* stateNormal;
    Vec local_170;
    Vec firstRayDirection;
    Quaternion local_18c;
    Quaternion local_19c;
    Quaternion local_1ac;
    Vec secondRayDirection;
    s32 dataOffset;
    u8* stateInitialized;

    if (gPppCalcDisabled != 0) {
        return;
    }

    pppMngSt = pppMngStPtr;
    owner = (CGObject*)pppMngSt->m_lookTarget;
    hitFound = 0;
    matrixX = pppMngSt->m_matrix.value[0][3];
    matrixY = pppMngSt->m_matrix.value[1][3];
    matrixZ = pppMngSt->m_matrix.value[2][3];
    dataOffset = *param3->m_serializedDataOffsets;
    stateNormal = (Vec*)((u8*)pppConformBGNormal + 0x80 + dataOffset);
    stateInitialized = (u8*)&stateNormal[1].x;

    if (((s32)Game.m_currentSceneId != 7) || (param2->m_stepValue == 2)) {
            mode = param2->m_stepValue;

            if (mode == 0) {
                if ((s8)((s32)((u32)owner->m_stateFlags0 << 24) >> 31) != 0) {
                    local_164.x = *(f32*)((u8*)owner + 0x4ec);
                    local_164.y = *(f32*)((u8*)owner + 0x4f0);
                    local_164.z = *(f32*)((u8*)owner + 0x4f4);
                } else {
                    local_164.x = kPppConformBgNormalZero;
                    local_164.y = kPppConformBgNormalOne;
                    local_164.z = kPppConformBgNormalZero;
                }
            } else if (mode == 1) {
                hitFound = 1;
                Game.GetTargetCursor(*(s32*)((u8*)pppMngStPtr + 0x130), local_170, local_164);
            } else if (mode == 2) {
                firstRayDirection.x = kPppConformBgNormalZero;
                firstRayDirection.y = kPppConformBgNormalDownRayY;
                firstRayDirection.z = kPppConformBgNormalZero;

                cylinderY = matrixY + param2->m_arg3;
                firstCylinder.m_top.z = kPppConformBgNormalCylinderRadius;
                firstCylinder.m_top.y = kPppConformBgNormalCylinderRadius;
                firstCylinder.m_top.x = kPppConformBgNormalCylinderRadius;
                firstCylinder.m_direction2.z = kPppConformBgNormalCylinderHeight;
                firstCylinder.m_direction2.y = kPppConformBgNormalCylinderHeight;
                firstCylinder.m_direction2.x = kPppConformBgNormalCylinderHeight;
                firstCylinder.m_bottom.x = matrixX;
                firstCylinder.m_bottom.y = cylinderY;
                firstCylinder.m_bottom.z = matrixZ;
                firstCylinder.m_direction.x = kPppConformBgNormalZero;
                firstCylinder.m_direction.y = kPppConformBgNormalDownRayY;
                firstCylinder.m_direction.z = kPppConformBgNormalZero;
                firstCylinder.m_radius = kPppConformBgNormalZero;

                hitFound = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
                    &MapMng, (CMapCylinder*)&firstCylinder, &firstRayDirection, 0xffffffff);
                if (hitFound != 0) {
                    CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &local_170);
                    GetHitFaceNormal__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &local_164);
                    if ((matrixY - kPppConformBgNormalGroundSnapLimit) > local_170.y) {
                        local_170.y = matrixY;
                    }
                } else {
                    local_164.x = kPppConformBgNormalZero;
                    local_164.y = kPppConformBgNormalOne;
                    local_164.z = kPppConformBgNormalZero;
                    local_170.x = matrixX;
                    local_170.y = matrixY;
                    local_170.z = matrixZ;
                }
            }

            if (*stateInitialized == 0) {
                *stateInitialized = 1;
                stateNormal->x = local_164.x;
                stateNormal->y = local_164.y;
                stateNormal->z = local_164.z;
            }

            local_18c.x = stateNormal->x;
            local_18c.y = stateNormal->y;
            local_18c.z = stateNormal->z;
            local_18c.w = kPppConformBgNormalOne;
            local_19c.x = local_164.x;
            local_19c.y = local_164.y;
            local_19c.z = local_164.z;
            local_19c.w = kPppConformBgNormalOne;
            C_QUATSlerp(&local_18c, &local_19c, &local_1ac, param2->m_initWOrk);
            stateNormal->x = local_1ac.x;
            stateNormal->y = local_1ac.y;
            stateNormal->z = local_1ac.z;

            PSVECNormalize(stateNormal, &local_158);

            if ((param2->m_stepValue == 0) && (owner != NULL)) {
                trigValue = sin((f64)owner->m_rotBaseY);
                local_14c.x = (f32)trigValue;
                local_14c.y = kPppConformBgNormalZero;
                trigValue = cos((f64)owner->m_rotBaseY);
                local_14c.z = (f32)trigValue;
                PSVECCrossProduct(&local_14c, &local_158, &local_140);
                PSVECNormalize(&local_140, &local_140);
                PSVECCrossProduct(&local_158, &local_140, &local_14c);
                PSVECNormalize(&local_14c, &local_14c);
            } else {
                local_140.y = kPppConformBgNormalZero;
                local_140.x = kPppConformBgNormalOne;
                local_140.z = kPppConformBgNormalZero;
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

            PSMTXCopy(basisMtx, pppMngStPtr->m_matrix.value);
            PSMTXScale(scaleMtx, pppMngStPtr->m_scale.x, pppMngStPtr->m_scale.y, pppMngStPtr->m_scale.z);
            PSMTXConcat(scaleMtx, pppMngStPtr->m_matrix.value, pppMngStPtr->m_matrix.value);

            mode = param2->m_stepValue;
            if (mode == 0) {
                if ((s8)((s32)((u32)owner->m_stateFlags0 << 24) >> 31) != 0) {
                    pppMngStPtr->m_matrix.value[0][3] = owner->m_worldPosition.x;
                    pppMngStPtr->m_matrix.value[1][3] = owner->m_worldPosition.y;
                    pppMngStPtr->m_matrix.value[2][3] = owner->m_worldPosition.z;
                } else if (((s8)((s32)((u32)*(u8*)&owner->m_weaponNodeFlags << 31) >> 31) != 0) &&
                    (owner->m_attachOwner != NULL)) {
                    ownerY = owner->m_attachOwner->m_worldPosition.y;
                    ownerZ = owner->m_worldPosition.z;
                    ownerX = owner->m_worldPosition.x;
                    pppMngStPtr->m_matrix.value[0][3] = ownerX;
                    pppMngStPtr->m_matrix.value[1][3] = ownerY;
                    pppMngStPtr->m_matrix.value[2][3] = ownerZ;
                } else {
                    ownerX = owner->m_worldPosition.x;
                    ownerY = owner->m_worldPosition.y;
                    ownerZ = owner->m_worldPosition.z;
                    secondRayDirection.x = kPppConformBgNormalZero;
                    secondRayDirection.y = kPppConformBgNormalDownRayY;
                    secondRayDirection.z = kPppConformBgNormalZero;

                    secondCylinder.m_top.z = kPppConformBgNormalCylinderRadius;
                    secondCylinder.m_top.y = kPppConformBgNormalCylinderRadius;
                    secondCylinder.m_top.x = kPppConformBgNormalCylinderRadius;
                    secondCylinder.m_direction2.z = kPppConformBgNormalCylinderHeight;
                    secondCylinder.m_direction2.y = kPppConformBgNormalCylinderHeight;
                    secondCylinder.m_direction2.x = kPppConformBgNormalCylinderHeight;
                    secondCylinder.m_bottom.x = ownerX;
                    secondCylinder.m_bottom.y = ownerY;
                    secondCylinder.m_bottom.z = ownerZ;
                    secondCylinder.m_direction.x = kPppConformBgNormalZero;
                    secondCylinder.m_direction.y = kPppConformBgNormalDownRayY;
                    secondCylinder.m_direction.z = kPppConformBgNormalZero;
                    secondCylinder.m_radius = kPppConformBgNormalZero;

                    hitFound = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
                        &MapMng, (CMapCylinder*)&secondCylinder, &secondRayDirection, 0xffffffff);
                    if (hitFound != 0) {
                        CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A78), &local_170);
                        pppMngStPtr->m_matrix.value[0][3] = local_170.x;
                        pppMngStPtr->m_matrix.value[1][3] = local_170.y;
                        pppMngStPtr->m_matrix.value[2][3] = local_170.z;
                    } else {
                        pppMngStPtr->m_matrix.value[0][3] = owner->m_worldPosition.x;
                        pppMngStPtr->m_matrix.value[1][3] = matrixY;
                        pppMngStPtr->m_matrix.value[2][3] = owner->m_worldPosition.z;
                    }
                }
            } else if (mode == 1) {
                if (hitFound != 0) {
                    pppMngStPtr->m_matrix.value[0][3] = local_170.x;
                    pppMngStPtr->m_matrix.value[1][3] = local_170.y;
                    pppMngStPtr->m_matrix.value[2][3] = local_170.z;
                } else {
                    pppMngStPtr->m_matrix.value[0][3] = matrixX;
                    pppMngStPtr->m_matrix.value[1][3] = matrixY;
                    pppMngStPtr->m_matrix.value[2][3] = matrixZ;
                }
            } else if (mode == 2) {
                pppMngStPtr->m_matrix.value[0][3] = local_170.x;
                pppMngStPtr->m_matrix.value[1][3] = local_170.y;
                pppMngStPtr->m_matrix.value[2][3] = local_170.z;
            }

            pppMngStPtr->m_matrix.value[1][3] += param2->m_dataValIndex;
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
void pppConstructConformBGNormal(struct pppConformBGNormal* conformBG, struct _pppCtrlTable* param2)
{
    int* serializedDataOffsets;
    f32* pfVar2;
    f32 scale;

    serializedDataOffsets = *(int**)((u8*)param2 + 0xc);
    pfVar2 = (f32*)((u8*)conformBG + 0x80 + *serializedDataOffsets);
    scale = kPppConformBgNormalZero;
    pfVar2[2] = scale;
    pfVar2[1] = scale;
    pfVar2[0] = scale;
    *(u8*)(pfVar2 + 3) = 0;
}

extern const f32 FLOAT_80331920 = 1.0f;
extern const f32 FLOAT_80331924 = 0.0f;
