// Function: putParticleFromItem__10CGCharaObjFiiiP3Vec
// Entry: 8010cbc8
// Size: 2872 bytes

/* WARNING: Removing unreachable block (ram,0x8010d6e4) */
/* WARNING: Removing unreachable block (ram,0x8010d6dc) */
/* WARNING: Removing unreachable block (ram,0x8010cbe0) */
/* WARNING: Removing unreachable block (ram,0x8010cbd8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void putParticleFromItem__10CGCharaObjFiiiP3Vec
               (CGPrgObj *param_1,uint param_2,int param_3,undefined4 param_4,Vec *param_5)

{
  ushort uVar1;
  bool bVar2;
  CRef *pCVar3;
  undefined4 uVar4;
  Vec *pVVar5;
  float fVar6;
  int iVar7;
  float fVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  undefined4 unaff_r23;
  int iVar12;
  uint uVar13;
  ushort unaff_r27;
  double dVar14;
  double dVar15;
  Vec local_e8;
  CVector CStack_dc;
  CVector CStack_d0;
  CVector CStack_c4;
  Vec local_b8;
  Vec local_ac;
  Vec local_a0;
  Mtx MStack_94;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  
  iVar12 = param_2 * 0x48;
  uVar9 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x12);
  uVar13 = param_2;
  if (uVar9 == 0xfe) {
    pCVar3 = ((param_1->object).m_charaModelHandle)->m_pdtLoadRef;
    if (pCVar3 == (CRef *)0x0) {
      uVar9 = 0xffffffff;
    }
    else {
      uVar9 = pCVar3[2].refCount;
    }
  }
  else if (uVar9 < 0xfe) {
    if (0xfc < uVar9) {
      uVar9 = 0xffffffff;
    }
  }
  else if (uVar9 < 0x100) {
    bVar2 = false;
    goto LAB_8010cd08;
  }
  if (uVar9 == 0xffffffff) {
    bVar2 = false;
  }
  else {
    unaff_r27 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + param_3 * 2 + 0x14);
    if (unaff_r27 == 0xffff) {
      bVar2 = false;
    }
    else {
      uVar13 = unaff_r27 & 0xff;
      if ((unaff_r27 & 0x1000) == 0) {
        if ((unaff_r27 & 0x2000) == 0) {
          if ((unaff_r27 & 0x4000) == 0) {
            if ((uVar9 == 1) && (uVar13 < 8)) {
              uVar13 = uVar13 + *(ushort *)((param_1->object).m_scriptHandle + 0xf8);
            }
          }
          else {
            uVar9 = 3;
          }
        }
        else {
          uVar9 = 2;
        }
      }
      else {
        uVar9 = 1;
      }
      if ((unaff_r27 & 0x800) != 0) {
        uVar13 = uVar13 + *(ushort *)((int)(param_1->object).m_scriptHandle + 0x3e2);
      }
      bVar2 = true;
    }
  }
LAB_8010cd08:
  if (bVar2) {
    uVar9 = uVar9 << 8;
    ResetParticleWork__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,uVar9 | uVar13,param_4);
    local_60 = 0x43300000;
    uStack_5c = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x10);
    SetParticleWorkScale__13CFlatRuntime2Ff
              ((double)(FLOAT_80331984 *
                        (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331978) +
                       FLOAT_80331980),(CFlatRuntime2 *)&CFlat);
    SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject
              ((CFlatRuntime2 *)&CFlat,param_2,param_1);
    local_58 = 0x43300000;
    uStack_54 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x26);
    SetParticleWorkSpeed__13CFlatRuntime2Ff
              ((double)(FLOAT_80331984 *
                        (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80331978) +
                       FLOAT_80331980),(CFlatRuntime2 *)&CFlat);
    iVar10 = 0;
    iVar11 = iVar10;
    if (param_3 == 1) {
      uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x3c);
      if (uVar1 == 0xffff) {
        iVar7 = 0;
      }
      else {
        iVar7 = (uVar1 & 0xff) + (uint)(uVar1 >> 8) * 1000;
      }
      if ((iVar7 != 0) &&
         (uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x3e), iVar11 = iVar7,
         (uVar1 & 0x8000) != 0)) {
        SetParticleWorkSe__13CFlatRuntime2Fiii((CFlatRuntime2 *)&CFlat,iVar7,2,uVar1 & 0xff);
        iVar11 = iVar10;
      }
    }
    else if (param_3 < 1) {
      if (-1 < param_3) {
        uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x38);
        if (uVar1 == 0xffff) {
          iVar7 = 0;
        }
        else {
          iVar7 = (uVar1 & 0xff) + (uint)(uVar1 >> 8) * 1000;
        }
        if ((iVar7 != 0) &&
           (uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x3a), iVar11 = iVar7,
           (uVar1 & 0x8000) != 0)) {
          SetParticleWorkSe__13CFlatRuntime2Fiii((CFlatRuntime2 *)&CFlat,iVar7,2,uVar1 & 0xff);
          iVar11 = iVar10;
        }
      }
    }
    else if (param_3 < 3) {
      uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x40);
      if (uVar1 == 0xffff) {
        iVar7 = 0;
      }
      else {
        iVar7 = (uVar1 & 0xff) + (uint)(uVar1 >> 8) * 1000;
      }
      if ((iVar7 != 0) &&
         (iVar11 = iVar7, (*(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0xc) & 0x400) != 0)) {
        SetParticleWorkSe__13CFlatRuntime2Fiii((CFlatRuntime2 *)&CFlat,iVar7,2,0);
        iVar11 = iVar10;
      }
    }
    if (500 < (int)param_2) {
      uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 2);
      if (uVar1 == 4) {
        unaff_r23 = 4;
      }
      else if (uVar1 < 4) {
        if (uVar1 == 1) {
          unaff_r23 = 1;
        }
      }
      else if (uVar1 == 9) {
        unaff_r23 = 9;
      }
      else if ((uVar1 < 9) && (7 < uVar1)) {
        unaff_r23 = 8;
      }
      uStack_54 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 4);
      local_58 = 0x43300000;
      SetParticleWorkCol__13CFlatRuntime2Fiif
                ((double)(FLOAT_80331984 *
                          (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80331978) +
                         FLOAT_80331980),(CFlatRuntime2 *)&CFlat,unaff_r23,0xffffffff);
    }
    if ((unaff_r27 & 0x100) == 0) {
      if ((unaff_r27 & 0x200) == 0) {
        if (param_5 == (Vec *)0x0) {
          if ((unaff_r27 & 0x400) == 0) {
            SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                      ((double)(param_1->object).m_rotTargetY,(CFlatRuntime2 *)&CFlat,
                       &(param_1->object).m_worldPosition);
          }
          else {
            SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                      ((double)FLOAT_80331988,(CFlatRuntime2 *)&CFlat,
                       &param_1[1].object.m_jumpOffset);
          }
        }
        else {
          SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                    ((double)(param_1->object).m_rotTargetY,(CFlatRuntime2 *)&CFlat,param_5);
        }
      }
      else {
        local_58 = 0x43300000;
        uStack_54 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x2a);
        dVar15 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80331978);
        dVar14 = (double)sin((double)(param_1->object).m_rotTargetY);
        local_a0.x = (float)(dVar15 * (double)(float)dVar14 +
                            (double)(param_1->object).m_worldPosition.x);
        local_a0.y = (param_1->object).m_worldPosition.y;
        dVar14 = (double)cos((double)(param_1->object).m_rotTargetY);
        local_a0.z = (float)(dVar15 * (double)(float)dVar14 +
                            (double)(param_1->object).m_worldPosition.z);
        SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                  ((double)(param_1->object).m_rotTargetY,(CFlatRuntime2 *)&CFlat,&local_a0);
        SetParticleWorkVector__13CFlatRuntime2Fff
                  ((double)(param_1->object).m_rotTargetY,(double)FLOAT_80331988,
                   (CFlatRuntime2 *)&CFlat);
        if ((((*(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0xc) & 0x2000) != 0) &&
            (fVar6 = param_1[1].object.m_rotationX, -1 < (int)fVar6)) && ((int)fVar6 < 4)) {
          SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                    ((CFlatRuntime2 *)&CFlat,Game.game.m_partyObjArr[(int)fVar6]);
        }
        if ((*(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0xc) & 0x4000) != 0) {
          SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                    ((double)(param_1->object).m_rotTargetY,(CFlatRuntime2 *)&CFlat,
                     &(param_1->object).m_worldPosition);
          SetParticleWorkTarget__13CFlatRuntime2FR3Vec
                    ((CFlatRuntime2 *)&CFlat,&param_1[1].object.m_jumpOffset);
          SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                    ((CFlatRuntime2 *)&CFlat,param_1);
        }
      }
    }
    else {
      SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                ((CFlatRuntime2 *)&CFlat,param_1);
    }
    bVar2 = false;
    if (param_2 == 0x410) {
      if ((param_3 == 2) || (param_3 == 3)) {
        fVar6 = FLOAT_80331990;
        if (param_3 == 2) {
          fVar6 = FLOAT_8033198c;
        }
        dVar15 = (double)((param_1->object).m_rotTargetY + fVar6);
        dVar14 = (double)sin(dVar15);
        CFlat._5952_4_ = FLOAT_80331994 * (float)dVar14 + (param_1->object).m_worldPosition.x;
        dVar14 = (double)cos(dVar15);
        CFlat._5960_4_ = FLOAT_80331994 * (float)dVar14 + (param_1->object).m_worldPosition.z;
        SetParticleWorkVector__13CFlatRuntime2Fff
                  ((double)(param_1->object).m_rotTargetY,(double)FLOAT_80331988,
                   (CFlatRuntime2 *)&CFlat);
        PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        bVar2 = true;
      }
    }
    else if ((int)param_2 < 0x410) {
      if (param_2 == 0x3b4) {
        if (param_3 == 3) {
          if (param_5 == (Vec *)0x0) {
            return;
          }
          SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                    ((double)(param_1->object).m_rotTargetY,(CFlatRuntime2 *)&CFlat,param_5);
          PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
          bVar2 = true;
        }
      }
      else if ((int)param_2 < 0x3b4) {
        if (param_2 == 0x206) {
          if (param_3 == 2) {
            fVar6 = param_1[1].object.m_extraMoveVec.y;
            fVar8 = param_1[1].object.m_bodyOffset.y;
            if ((int)fVar8 < (int)fVar6 * 3) {
              if ((int)fVar6 << 1 <= (int)fVar8) {
                SetParticleWorkSe__13CFlatRuntime2Fiii((CFlatRuntime2 *)&CFlat,0x871,2,0);
              }
            }
            else {
              SetParticleWorkSe__13CFlatRuntime2Fiii((CFlatRuntime2 *)&CFlat,0x872,2,0);
            }
          }
          if (param_3 == 3) {
            fVar6 = param_1[1].object.m_extraMoveVec.y;
            fVar8 = param_1[1].object.m_bodyOffset.y;
            if ((int)fVar8 < (int)fVar6 * 3) {
              if ((int)fVar6 << 1 <= (int)fVar8) {
                SetParticleWorkNo__13CFlatRuntime2Fi
                          ((CFlatRuntime2 *)&CFlat,
                           uVar9 | *(ushort *)((int)(param_1->object).m_scriptHandle + 0x3e2) + 0x73
                          );
              }
            }
            else {
              SetParticleWorkNo__13CFlatRuntime2Fi
                        ((CFlatRuntime2 *)&CFlat,
                         uVar9 | *(ushort *)((int)(param_1->object).m_scriptHandle + 0x3e2) + 0x75);
            }
          }
        }
      }
      else if ((param_2 == 0x409) && (param_3 == 3)) {
        uVar13 = 3;
        do {
          SetParticleWorkNo__13CFlatRuntime2Fi((CFlatRuntime2 *)&CFlat,uVar9 | uVar13);
          PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
          uVar13 = uVar13 + 1;
        } while ((int)uVar13 < 9);
        bVar2 = true;
      }
    }
    else if ((int)param_2 < 0x479) {
      if ((int)param_2 < 0x46f) {
        if (0x46c < (int)param_2) {
          if (param_3 == 2) {
            if (0xf < param_1->m_stateFrame) {
              SetParticleWorkNo__13CFlatRuntime2Fi((CFlatRuntime2 *)&CFlat,uVar9 | 0x1d);
              dVar14 = (double)RandFPM__5CMathFf((double)FLOAT_80331998,&Math);
              dVar15 = (double)RandFPM__5CMathFf((double)FLOAT_80331998,&Math);
              __ct__7CVectorFfff((float)dVar15,FLOAT_80331988,(float)dVar14,&CStack_d0);
              pVVar5 = (Vec *)__ct__7CVectorFfff(FLOAT_80331988,FLOAT_8033199c,FLOAT_803319a0,
                                                 &CStack_c4);
              __ct__7CVectorFv(&local_e8);
              PSVECAdd(pVVar5,(Vec *)&CStack_d0,&local_e8);
              local_b8.x = local_e8.x;
              local_b8.y = local_e8.y;
              local_b8.z = local_e8.z;
              SetParticleWorkPos__13CFlatRuntime2FR3Vecf
                        ((double)(param_1->object).m_rotTargetY,(CFlatRuntime2 *)&CFlat,&local_b8);
              PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
            }
            bVar2 = true;
          }
          if (param_3 == 3) {
            uVar13 = 0xd;
            do {
              SetParticleWorkNo__13CFlatRuntime2Fi((CFlatRuntime2 *)&CFlat,uVar9 | uVar13);
              PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
              uVar13 = uVar13 + 1;
            } while ((int)uVar13 < 0x1d);
            bVar2 = true;
          }
        }
      }
      else if ((0x472 < (int)param_2) && (param_3 == 3)) {
        uVar13 = 7;
        do {
          SetParticleWorkNo__13CFlatRuntime2Fi((CFlatRuntime2 *)&CFlat,uVar9 | uVar13);
          PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
          uVar13 = uVar13 + 1;
        } while ((int)uVar13 < 0xc);
        bVar2 = true;
      }
    }
    else if ((((int)param_2 < 0x4a0) && (0x49c < (int)param_2)) && (param_3 == 2)) {
      iVar10 = 0;
      dVar14 = DOUBLE_80331968;
      do {
        PSMTXRotRad((param_1->object).m_rotTargetY,&MStack_94,0x79);
        uStack_54 = 0xffffffb4;
        if (iVar10 == 0) {
          uStack_54 = 0x4c;
        }
        uStack_54 = uStack_54 ^ 0x80000000;
        local_58 = 0x43300000;
        pVVar5 = (Vec *)__ct__7CVectorFfff((float)((double)CONCAT44(0x43300000,uStack_54) - dVar14),
                                           FLOAT_80331988,FLOAT_80331998,&CStack_dc);
        PSMTXMultVec(&MStack_94,pVVar5,&local_ac);
        CFlat._5952_4_ = (param_1->object).m_worldPosition.x + local_ac.x;
        CFlat._5956_4_ = (param_1->object).m_worldPosition.y + local_ac.y;
        CFlat._5960_4_ = (param_1->object).m_worldPosition.z + local_ac.z;
        SetParticleWorkVector__13CFlatRuntime2Fff
                  ((double)(param_1->object).m_rotTargetY,(double)FLOAT_80331988,
                   (CFlatRuntime2 *)&CFlat);
        PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        iVar10 = iVar10 + 1;
      } while (iVar10 < 2);
      bVar2 = true;
    }
    if (iVar11 != 0) {
      if (param_3 != 2) {
        param_5 = (Vec *)0x0;
      }
      uVar4 = playSe3D__8CGPrgObjFiiiiP3Vec(param_1,iVar11,0x32,0x96,0,param_5);
      SetSe3DGroup__6CSoundFii(&Sound,uVar4,(int)(param_1->object).base_object.object.m_particleId);
    }
    if (!bVar2) {
      uVar9 = (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x24);
      if ((param_3 == 3) && (1 < uVar9)) {
        dVar15 = (double)FLOAT_803319a4;
        dVar14 = DOUBLE_80331968;
        for (uVar13 = 0; (int)uVar13 < (int)uVar9; uVar13 = uVar13 + 1) {
          uStack_54 = uVar13 ^ 0x80000000;
          local_58 = 0x43300000;
          local_60 = 0x43300000;
          uStack_5c = uVar9 ^ 0x80000000;
          SetParticleWorkVector__13CFlatRuntime2Fff
                    ((double)((float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,uStack_54
                                                                               ) - dVar14)) /
                             (float)((double)CONCAT44(0x43300000,uVar9 ^ 0x80000000) - dVar14)),
                     (double)FLOAT_80331988,(CFlatRuntime2 *)&CFlat);
          PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
        }
      }
      else {
        PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
      }
    }
  }
  else if (param_3 == 2) {
    uVar1 = *(ushort *)(Game.game.unkCFlatData0[2] + iVar12 + 0x40);
    if (uVar1 == 0xffff) {
      iVar12 = 0;
    }
    else {
      iVar12 = (uVar1 & 0xff) + (uint)(uVar1 >> 8) * 1000;
    }
    if (iVar12 != 0) {
      uVar4 = playSe3D__8CGPrgObjFiiiiP3Vec(param_1,iVar12,0x32,0x96,0,param_5);
      SetSe3DGroup__6CSoundFii(&Sound,uVar4,(int)(param_1->object).base_object.object.m_particleId);
    }
  }
  return;
}

