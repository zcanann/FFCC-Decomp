#include "ffcc/pppConformBGNormal.h"
#include "types.h"
#include "ffcc/map.h"
#include "ffcc/p_game.h"
#include "ffcc/partMng.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"
#include <math.h>

extern int gPppCalcDisabled;
extern f32 lbl_80331908;
extern f32 lbl_8033190C;
extern f32 lbl_80331910;
extern f32 lbl_80331914;
extern f32 lbl_80331918;
extern f32 lbl_8033191C;

extern "C" {
s32 CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, void*, void*, u32);
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
    scale = lbl_80331908;
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
    f32* serializedState;
    Vec* owner;
    f64 trigValue;
    f32 local_1b8;
    f32 local_1b4;
    f32 local_1b0;
    Quaternion local_1ac;
    Quaternion local_19c;
    Quaternion local_18c;
    f32 local_17c;
    f32 local_178;
    f32 local_174;
    Vec local_170;
    Vec local_164;
    Vec local_158;
    Vec local_14c;
    Vec local_140;
    f32 local_134;
    f32 local_130;
    f32 local_12c;
    f32 local_11c;
    f32 local_118;
    f32 local_114;
    f32 local_110;
    f32 local_10c;
    f32 local_108;
    f32 local_104;
    f32 local_100;
    f32 local_fc;
    f32 local_f8;
    f32 local_f4;
    f32 local_f0;
    f32 local_ec;
    f32 local_dc;
    f32 local_d8;
    f32 local_d4;
    f32 local_d0;
    f32 local_cc;
    f32 local_c8;
    f32 local_c4;
    f32 local_c0;
    f32 local_bc;
    f32 local_b8;
    Mtx scaleMtx;
    Mtx basisMtx;

    pppMngSt = pppMngStPtr;
    if (gPppCalcDisabled == 0) {
        owner = *(Vec**)((u8*)pppMngStPtr + 0xd8);
        hitFound = 0;
        matrixX = pppMngStPtr->m_matrix.value[0][3];
        matrixY = pppMngStPtr->m_matrix.value[1][3];
        matrixZ = pppMngStPtr->m_matrix.value[2][3];
        serializedState = (f32*)((u8*)pppConformBGNormal + 0x80 + *param3->m_serializedDataOffsets);

        if ((Game.game.m_currentSceneId != 7) || (param2->m_stepValue == 2)) {
            mode = param2->m_stepValue;

            if (mode == 0) {
                if (((s32)((u32)*(u8*)((u8*)owner + 0x50) << 24) < 0)) {
                    local_164.x = *(f32*)((u8*)owner + 0x4ec);
                    local_164.y = *(f32*)((u8*)owner + 0x4f0);
                    local_164.z = *(f32*)((u8*)owner + 0x4f4);
                } else {
                    local_164.x = lbl_80331908;
                    local_164.y = lbl_8033190C;
                    local_164.z = lbl_80331908;
                }
            } else if (mode == 1) {
                hitFound = 1;
                Game.game.GetTargetCursor(*(s32*)((u8*)pppMngStPtr + 0x130), local_170, local_164);
            } else if (mode == 2) {
                local_17c = lbl_80331908;
                local_178 = lbl_80331910;
                local_174 = lbl_80331908;
                local_f0 = matrixY + param2->m_arg3;
                local_c4 = lbl_80331914;
                local_c8 = lbl_80331914;
                local_cc = lbl_80331914;
                local_b8 = lbl_80331918;
                local_bc = lbl_80331918;
                local_c0 = lbl_80331918;
                local_dc = lbl_80331908;
                local_d8 = lbl_80331910;
                local_d4 = lbl_80331908;
                local_d0 = lbl_80331908;
                local_f4 = matrixX;
                local_ec = matrixZ;

                hitFound = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
                    &MapMng, &local_f4, &local_17c, 0xffffffff);
                if (hitFound == 0) {
                    local_164.x = lbl_80331908;
                    local_164.y = lbl_8033190C;
                    local_164.z = lbl_80331908;
                    local_170.x = matrixX;
                    local_170.y = matrixY;
                    local_170.z = matrixZ;
                } else {
                    CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &local_170);
                    GetHitFaceNormal__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &local_164);
                    if (local_170.y < matrixY - lbl_8033191C) {
                        local_170.y = matrixY;
                    }
                }
            }

            if (*(u8*)(serializedState + 3) == 0) {
                *(u8*)(serializedState + 3) = 1;
                serializedState[0] = local_164.x;
                serializedState[1] = local_164.y;
                serializedState[2] = local_164.z;
            }

            local_18c.x = serializedState[0];
            local_18c.y = serializedState[1];
            local_18c.z = serializedState[2];
            local_18c.w = lbl_8033190C;
            local_19c.x = local_164.x;
            local_19c.y = local_164.y;
            local_19c.z = local_164.z;
            local_19c.w = lbl_8033190C;
            C_QUATSlerp(&local_18c, &local_19c, &local_1ac, param2->m_initWOrk);
            serializedState[0] = local_1ac.x;
            serializedState[1] = local_1ac.y;
            serializedState[2] = local_1ac.z;

            local_164.x = serializedState[0];
            local_164.y = serializedState[1];
            local_164.z = serializedState[2];
            PSVECNormalize(&local_164, &local_158);

            if ((param2->m_stepValue == 0) && (owner != NULL)) {
                trigValue = sin((f64)*(f32*)((u8*)owner + 0x1a8));
                local_14c.x = (f32)trigValue;
                local_14c.y = lbl_80331908;
                trigValue = cos((f64)*(f32*)((u8*)owner + 0x1a8));
                local_14c.z = (f32)trigValue;
                PSVECCrossProduct(&local_14c, &local_158, &local_140);
                PSVECNormalize(&local_140, &local_140);
                PSVECCrossProduct(&local_158, &local_140, &local_14c);
                PSVECNormalize(&local_14c, &local_14c);
            } else {
                local_140.x = lbl_8033190C;
                local_140.y = lbl_80331908;
                local_140.z = lbl_80331908;
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
                if ((s32)((u32)*(u8*)((u8*)owner + 0x50) << 24) < 0) {
                    pppMngStPtr->m_matrix.value[0][3] = *(f32*)((u8*)owner + 0x15c);
                    pppMngStPtr->m_matrix.value[1][3] = *(f32*)((u8*)owner + 0x160);
                    pppMngStPtr->m_matrix.value[2][3] = *(f32*)((u8*)owner + 0x164);
                } else if ((((*(u8*)((u8*)owner + 0x9a) & 1) == 0) || (*(s32*)((u8*)owner + 0x18c) == 0))) {
                    local_134 = *(f32*)((u8*)owner + 0x15c);
                    local_130 = *(f32*)((u8*)owner + 0x160);
                    local_12c = *(f32*)((u8*)owner + 0x164);
                    local_1b8 = lbl_80331908;
                    local_1b4 = lbl_80331910;
                    local_1b0 = lbl_80331908;
                    local_104 = lbl_80331914;
                    local_108 = lbl_80331914;
                    local_10c = lbl_80331914;
                    local_f8 = lbl_80331918;
                    local_fc = lbl_80331918;
                    local_100 = lbl_80331918;
                    local_11c = lbl_80331908;
                    local_118 = lbl_80331910;
                    local_114 = lbl_80331908;
                    local_110 = lbl_80331908;

                    hitFound = CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
                        &MapMng, &local_134, &local_1b8, 0xffffffff);
                    if (hitFound == 0) {
                        pppMngStPtr->m_matrix.value[0][3] = *(f32*)((u8*)owner + 0x15c);
                        pppMngStPtr->m_matrix.value[1][3] = matrixY;
                        pppMngStPtr->m_matrix.value[2][3] = *(f32*)((u8*)owner + 0x164);
                    } else {
                        CalcHitPosition__7CMapObjFP3Vec(*(void**)((u8*)&MapMng + 0x22A88), &local_170);
                        pppMngStPtr->m_matrix.value[0][3] = local_170.x;
                        pppMngStPtr->m_matrix.value[1][3] = local_170.y;
                        pppMngStPtr->m_matrix.value[2][3] = local_170.z;
                    }
                } else {
                    ownerY = *(f32*)(*(s32*)((u8*)owner + 0x18c) + 0x160);
                    pppMngStPtr->m_matrix.value[0][3] = *(f32*)((u8*)owner + 0x15c);
                    pppMngStPtr->m_matrix.value[1][3] = ownerY;
                    pppMngStPtr->m_matrix.value[2][3] = *(f32*)((u8*)owner + 0x164);
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

