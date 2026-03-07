#include "ffcc/pppConformBGNormal.h"
#include "types.h"
#include "ffcc/map.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "ffcc/symbols_shared.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"
#include <math.h>

extern int gPppCalcDisabled;

struct ConformState {
    Vec m_normal;
    u8 m_initialized;
    u8 _pad[3];
};

struct ConformCylinderQuery {
    Vec m_pos;
    Vec m_fieldC;
    Vec m_field18;
    Vec m_field24;
    f32 m_field30;
};

extern "C" {
s32 CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, u32);
void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
void GetHitFaceNormal__7CMapObjFP3Vec(void*, Vec*);
void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);
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
void pppConstructConformBGNormal(struct pppConformBGNormal* conformBG, struct pppConformBGNormalUnkC* param2)
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

/*
 * --INFO--
 * PAL Address: 0x801091d4
 * PAL Size: 1552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameConformBGNormal(struct pppConformBGNormal* pppConformBGNormal, struct pppConformBGNormalUnkB* param2, struct pppConformBGNormalUnkC* param3)
{
    u8 mode;
    f32 matrixX;
    f32 matrixY;
    f32 matrixZ;
    f32 ownerY;
    _pppMngSt* pppMngSt;
    s32 hitFound;
    ConformState* state;
    u8* owner;
    f64 trigValue;
    Quaternion local_1ac;
    Quaternion local_19c;
    Quaternion local_18c;
    Vec local_170;
    Vec local_164;
    Vec local_158;
    Vec local_14c;
    Vec local_140;
    ConformCylinderQuery local_dc;
    ConformCylinderQuery local_134;
    Mtx scaleMtx;
    Mtx basisMtx;

    pppMngSt = pppMngStPtr;
    if (gPppCalcDisabled == 0) {
        owner = *(u8**)((u8*)pppMngStPtr + 0xd8);
        hitFound = 0;
        matrixX = pppMngStPtr->m_matrix.value[0][3];
        matrixY = pppMngStPtr->m_matrix.value[1][3];
        matrixZ = pppMngStPtr->m_matrix.value[2][3];
        state = (ConformState*)((u8*)pppConformBGNormal + 0x80 + *param3->m_serializedDataOffsets);

        if ((Game.game.m_currentSceneId != 7) || (param2->m_stepValue == 2)) {
            mode = param2->m_stepValue;

            if (mode == 0) {
                if (((s32)((u32)*(u8*)(owner + 0x50) << 24) < 0)) {
                    local_164.x = *(f32*)(owner + 0x4ec);
                    local_164.y = *(f32*)(owner + 0x4f0);
                    local_164.z = *(f32*)(owner + 0x4f4);
                } else {
                    local_164.x = kPppConformBgNormalZero;
                    local_164.y = kPppConformBgNormalOne;
                    local_164.z = kPppConformBgNormalZero;
                }
            } else if (mode == 1) {
                hitFound = 1;
                Game.game.GetTargetCursor(*(s32*)((u8*)pppMngStPtr + 0x130), local_170, local_164);
            } else if (mode == 2) {
                local_dc.m_pos.x = matrixX;
                local_dc.m_pos.y = matrixY + param2->m_arg3;
                local_dc.m_pos.z = matrixZ;
                local_dc.m_fieldC.x = kPppConformBgNormalCylinderRadius;
                local_dc.m_fieldC.y = kPppConformBgNormalCylinderRadius;
                local_dc.m_fieldC.z = kPppConformBgNormalCylinderRadius;
                local_dc.m_field18.x = kPppConformBgNormalCylinderHeight;
                local_dc.m_field18.y = kPppConformBgNormalCylinderHeight;
                local_dc.m_field18.z = kPppConformBgNormalCylinderHeight;
                local_dc.m_field24.x = kPppConformBgNormalZero;
                local_dc.m_field24.y = kPppConformBgNormalDownRayY;
                local_dc.m_field24.z = kPppConformBgNormalZero;
                local_dc.m_field30 = kPppConformBgNormalZero;

                hitFound = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
                    &MapMng, (CMapCylinder*)&local_dc, &local_dc.m_field24, 0xffffffff);
                if (hitFound == 0) {
                    local_164.x = kPppConformBgNormalZero;
                    local_164.y = kPppConformBgNormalOne;
                    local_164.z = kPppConformBgNormalZero;
                    local_170.x = matrixX;
                    local_170.y = matrixY;
                    local_170.z = matrixZ;
                } else {
                    CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &local_170);
                    GetHitFaceNormal__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &local_164);
                    if (local_170.y < matrixY - kPppConformBgNormalGroundSnapLimit) {
                        local_170.y = matrixY;
                    }
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
            local_18c.w = kPppConformBgNormalOne;
            local_19c.x = local_164.x;
            local_19c.y = local_164.y;
            local_19c.z = local_164.z;
            local_19c.w = kPppConformBgNormalOne;
            C_QUATSlerp(&local_18c, &local_19c, &local_1ac, param2->m_initWOrk);
            state->m_normal.x = local_1ac.x;
            state->m_normal.y = local_1ac.y;
            state->m_normal.z = local_1ac.z;

            local_164.x = state->m_normal.x;
            local_164.y = state->m_normal.y;
            local_164.z = state->m_normal.z;
            PSVECNormalize(&local_164, &local_158);

            if ((param2->m_stepValue == 0) && (owner != NULL)) {
                trigValue = sin((f64)*(f32*)(owner + 0x1a8));
                local_14c.x = (f32)trigValue;
                local_14c.y = kPppConformBgNormalZero;
                trigValue = cos((f64)*(f32*)(owner + 0x1a8));
                local_14c.z = (f32)trigValue;
                PSVECCrossProduct(&local_14c, &local_158, &local_140);
                PSVECNormalize(&local_140, &local_140);
                PSVECCrossProduct(&local_158, &local_140, &local_14c);
                PSVECNormalize(&local_14c, &local_14c);
            } else {
                local_140.x = kPppConformBgNormalOne;
                local_140.y = kPppConformBgNormalZero;
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
                if ((s32)((u32)*(u8*)(owner + 0x50) << 24) < 0) {
                    pppMngStPtr->m_matrix.value[0][3] = *(f32*)(owner + 0x15c);
                    pppMngStPtr->m_matrix.value[1][3] = *(f32*)(owner + 0x160);
                    pppMngStPtr->m_matrix.value[2][3] = *(f32*)(owner + 0x164);
                } else if (((*(u8*)(owner + 0x9a) & 1) == 0) || (*(s32*)(owner + 0x18c) == 0)) {
                    local_134.m_pos.x = *(f32*)(owner + 0x15c);
                    local_134.m_pos.y = *(f32*)(owner + 0x160);
                    local_134.m_pos.z = *(f32*)(owner + 0x164);
                    local_134.m_fieldC.x = kPppConformBgNormalZero;
                    local_134.m_fieldC.y = kPppConformBgNormalDownRayY;
                    local_134.m_fieldC.z = kPppConformBgNormalZero;
                    local_134.m_field18.x = kPppConformBgNormalCylinderRadius;
                    local_134.m_field18.y = kPppConformBgNormalCylinderRadius;
                    local_134.m_field18.z = kPppConformBgNormalCylinderRadius;
                    local_134.m_field24.x = kPppConformBgNormalCylinderHeight;
                    local_134.m_field24.y = kPppConformBgNormalCylinderHeight;
                    local_134.m_field24.z = kPppConformBgNormalCylinderHeight;
                    local_134.m_field30 = kPppConformBgNormalZero;

                    hitFound = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
                        &MapMng, (CMapCylinder*)&local_134, &local_134.m_fieldC, 0xffffffff);
                    if (hitFound == 0) {
                        pppMngStPtr->m_matrix.value[0][3] = *(f32*)(owner + 0x15c);
                        pppMngStPtr->m_matrix.value[1][3] = matrixY;
                        pppMngStPtr->m_matrix.value[2][3] = *(f32*)(owner + 0x164);
                    } else {
                        CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &local_170);
                        pppMngStPtr->m_matrix.value[0][3] = local_170.x;
                        pppMngStPtr->m_matrix.value[1][3] = local_170.y;
                        pppMngStPtr->m_matrix.value[2][3] = local_170.z;
                    }
                } else {
                    ownerY = *(f32*)(*(s32*)(owner + 0x18c) + 0x160);
                    pppMngStPtr->m_matrix.value[0][3] = *(f32*)(owner + 0x15c);
                    pppMngStPtr->m_matrix.value[1][3] = ownerY;
                    pppMngStPtr->m_matrix.value[2][3] = *(f32*)(owner + 0x164);
                }
            } else if (mode == 1) {
                if (hitFound == 0) {
                    pppMngStPtr->m_matrix.value[0][3] = matrixX;
                    pppMngStPtr->m_matrix.value[1][3] = matrixY;
                    pppMngStPtr->m_matrix.value[2][3] = matrixZ;
                } else {
                    pppMngStPtr->m_matrix.value[0][3] = local_170.x;
                    pppMngStPtr->m_matrix.value[1][3] = local_170.y;
                    pppMngStPtr->m_matrix.value[2][3] = local_170.z;
                }
            } else if (mode == 2) {
                pppMngStPtr->m_matrix.value[0][3] = local_170.x;
                pppMngStPtr->m_matrix.value[1][3] = local_170.y;
                pppMngStPtr->m_matrix.value[2][3] = local_170.z;
            }

            pppMngStPtr->m_matrix.value[1][3] += param2->m_dataValIndex;
            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        }
    }
}






