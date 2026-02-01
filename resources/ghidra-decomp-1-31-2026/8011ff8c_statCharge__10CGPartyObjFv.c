// Function: statCharge__10CGPartyObjFv
// Entry: 8011ff8c
// Size: 2560 bytes

/* WARNING: Removing unreachable block (ram,0x80120970) */
/* WARNING: Removing unreachable block (ram,0x8011ff9c) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void statCharge__10CGPartyObjFv(CGame *param_1)

{
  bool bVar1;
  float fVar2;
  uint8_t (*paauVar3) [8] [8];
  uint8_t (*pauVar4) [8];
  int iVar5;
  uint uVar6;
  Vec *pVVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined2 *puVar11;
  undefined2 *puVar12;
  ushort uVar13;
  int unaff_r29;
  double dVar14;
  double dVar15;
  double dVar16;
  Vec local_e4;
  Vec local_d8;
  Vec local_cc;
  Vec local_c0;
  CVector CStack_b4;
  CVector CStack_a8;
  CVector CStack_9c;
  Vec local_90;
  Vec local_84;
  CVector CStack_78;
  CVector local_6c;
  Vec VStack_60;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  iVar5 = *(int *)((param_1->m_gameWork).m_linkTable[2][2][0] + 4);
  if (iVar5 == 1) {
    if (*(int *)(param_1->m_gameWork).m_linkTable[2][2][1] == 0) {
      reqAnim__8CGPrgObjFiii
                ((CGPrgObj *)param_1,*(undefined4 *)((param_1->m_gameWork).m_linkTable[2][2][5] + 4)
                 ,1,0);
    }
    if ((*(int *)(param_1->m_gameWork).m_linkTable[2][7][0] == 0) &&
       (*(int *)((param_1->m_gameWork).m_linkTable[2][7][4] + 4) <
        *(int *)(param_1->m_gameWork).m_linkTable[2][2][1])) {
      putTargetParticle__10CGPartyObjFii(param_1,0,1);
      paauVar3 = (param_1->m_gameWork).m_linkTable[2];
      *(uint8_t *)((int)(paauVar3[7] + 0) + 0) = '\0';
      *(uint8_t *)((int)(paauVar3[7] + 0) + 1) = '\0';
      *(uint8_t *)((int)(paauVar3[7] + 0) + 2) = '\0';
      *(uint8_t *)((int)(paauVar3[7] + 0) + 3) = '\x01';
    }
    if (*(int *)(param_1->m_gameWork).m_linkTable[2][7][0] != 0) {
      checkTargetParticle__10CGPartyObjFv(param_1);
    }
    if (*(int *)(param_1->m_gameWork).m_linkTable[2][2][7] == 0x206) {
      iVar5 = *(int *)((param_1->m_gameWork).m_linkTable[2][7][4] + 4);
      iVar10 = *(int *)((param_1->m_gameWork).m_linkTable[2][6][7] + 4);
      if (iVar10 == iVar5 * 3) {
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_80331a54,(CGPrgObj *)param_1,0x578,0,(CGObject *)param_1,0x80d);
      }
      else if (iVar10 == iVar5 << 1) {
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_80331a54,(CGPrgObj *)param_1,0x577,0,(CGObject *)param_1,0x80d);
      }
    }
    *(int *)((param_1->m_gameWork).m_linkTable[2][6][7] + 4) =
         *(int *)((param_1->m_gameWork).m_linkTable[2][6][7] + 4) + 1;
  }
  else if (iVar5 < 1) {
    if (-1 < iVar5) {
      if (*(int *)(param_1->m_gameWork).m_linkTable[2][2][1] == 0) {
        pauVar4 = (param_1->m_gameWork).m_linkTable[2][6];
        *(uint8_t *)((int)(pauVar4 + 7) + 4) = '\0';
        *(uint8_t *)((int)(pauVar4 + 7) + 5) = '\0';
        *(uint8_t *)((int)(pauVar4 + 7) + 6) = '\0';
        *(uint8_t *)((int)(pauVar4 + 7) + 7) = '\0';
        reqAnim__8CGPrgObjFiii
                  ((CGPrgObj *)param_1,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][2][5],0,0
                  );
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_80331a54,(CGPrgObj *)param_1,0x210,
                   *(int *)(param_1->m_gameWork).m_linkTable[2][3][1],(CGObject *)param_1,0x7ee);
      }
      iVar5 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)param_1);
      if (iVar5 != 0) {
        changeSubStat__8CGPrgObjFi((CGPrgObj *)param_1,1);
        return;
      }
    }
  }
  else if (iVar5 < 3) {
    if (*(int *)(param_1->m_gameWork).m_linkTable[2][2][1] == 0) {
      endPSlotBit__10CGCharaObjFi(param_1,8);
      (**(code **)((param_1->m_gameWork).m_bossArtifactStageTable[6] + 0x4c))(param_1,0x18,0,0);
    }
    if ((*(int *)(param_1->m_gameWork).m_linkTable[2][2][1] == 5) &&
       (-1 < *(int *)((param_1->m_gameWork).m_linkTable[2][7][3] + 4))) {
      endPSlotBit__10CGCharaObjFi(param_1,0x20);
      ResetParticleWork__13CFlatRuntime2Fii
                ((CFlatRuntime2 *)&CFlat,
                 *(int *)((param_1->m_gameWork).m_linkTable[2][7][3] + 4) +
                 (uint)*(ushort *)((param_1->m_gameWork).m_bossArtifactStageTable[10] + 0x3e0) * 5 +
                 0x1c | 0x400,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][3][2]);
      SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject
                ((CFlatRuntime2 *)&CFlat,param_1);
      PutParticleWork__13CFlatRuntime2Fv((CFlatRuntime2 *)&CFlat);
      playSe3D__8CGPrgObjFiiiiP3Vec
                ((CGPrgObj *)param_1,
                 *(int *)((param_1->m_gameWork).m_linkTable[2][7][3] + 4) + 0x7eb,0x32,0x96,0,0);
    }
    if (*(int *)((param_1->m_gameWork).m_linkTable[2][7][3] + 4) == -1) {
      uVar6 = *(uint *)(param_1->m_gameWork).m_linkTable[2][2][1];
    }
    else {
      uVar6 = *(int *)(param_1->m_gameWork).m_linkTable[2][2][1] - 0x10;
    }
    uVar13 = *(ushort *)
              (Game.game.unkCFlatData0[2] +
               *(int *)(param_1->m_gameWork).m_linkTable[2][2][7] * 0x48 + 10) & 0xff;
    if (uVar6 == 0) {
      if (*(int *)(param_1->m_gameWork).m_linkTable[3][0][0] != 0) {
        sendCombiToScript__10CGCharaObjFP10CGCharaObjii
                  (param_1,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][7][6],
                   *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][7][6] + 4));
      }
      resetIgnoreHit__10CGCharaObjFv(param_1);
      putParticleFromItem__10CGCharaObjFiiiP3Vec
                (param_1,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][2][7],0,
                 *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][2][7] + 4),0);
      putParticleFromItem__10CGCharaObjFiiiP3Vec
                (param_1,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][2][7],1,
                 *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][2][7] + 4),0);
      putParticleFromItem__10CGCharaObjFiiiP3Vec
                (param_1,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][2][7],2,
                 *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][2][7] + 4),0);
      reqAnim__8CGPrgObjFiii
                ((CGPrgObj *)param_1,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][2][6],0,0);
      endPSlotBit__10CGCharaObjFi(param_1,0x10);
      iVar5 = *(int *)(param_1->m_gameWork).m_linkTable[2][2][7];
      if ((iVar5 == 0x1fc) || (iVar5 == 0x23d)) {
        if (iVar5 == 0x23d) {
          unaff_r29 = 0x6f;
        }
        else if ((iVar5 < 0x23d) && (iVar5 == 0x1fc)) {
          unaff_r29 = 0x1b;
        }
        if (1 < *(ushort *)((param_1->m_gameWork).m_bossArtifactStageTable[10] + 0x1c)) {
          addHp__10CGCharaObjFiP8CGPrgObj((CGCharaObj *)param_1,0xffffffff,(CGPrgObj *)0x0);
        }
        putParticle__8CGPrgObjFiiP8CGObjectfi
                  ((double)FLOAT_80331a54,(CGPrgObj *)param_1,
                   unaff_r29 +
                   (uint)*(ushort *)((param_1->m_gameWork).m_bossArtifactStageTable[10] + 0x3e2) |
                   0x500,0,(CGObject *)param_1,0);
      }
    }
    iVar5 = *(int *)(param_1->m_gameWork).m_linkTable[2][2][7];
    if (uVar6 == *(ushort *)(Game.game.unkCFlatData0[2] + iVar5 * 0x48 + 0x20)) {
      putParticleFromItem__10CGCharaObjFiiiP3Vec
                (param_1,iVar5,3,*(undefined4 *)((param_1->m_gameWork).m_linkTable[2][2][7] + 4),0);
    }
    iVar5 = (param_1->m_gameWork).m_bossArtifactStageTable[10];
    iVar10 = 0;
    puVar12 = (undefined2 *)
              (Game.game.unk_flat3_field_30_0xc7e0 +
              ((uint)*(ushort *)(iVar5 + 0x3e2) + (uint)*(ushort *)(iVar5 + 0x3e0) * 2) * 0x1ca +
              ((int)(uint)*(ushort *)
                           (Game.game.unkCFlatData0[2] +
                            *(int *)(param_1->m_gameWork).m_linkTable[2][2][7] * 0x48 + 10) >> 8) *
              0x42 + 0x36);
    puVar11 = puVar12;
    do {
      if ((uVar6 == (ushort)puVar11[3]) && (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x17))
      {
        uVar9 = ((uint)(ushort)puVar11[4] - (uint)(ushort)puVar11[3]) + 1;
        if ((iVar10 == 0) && ((uVar13 == 2 || (uVar13 == 3)))) {
          PSVECSubtract((Vec *)((param_1->m_gameWork).m_linkTable[2][7][0] + 4),
                        (Vec *)((param_1->m_gameWork).m_linkTable[0][2][6] + 4),&VStack_60);
          dVar14 = (double)PSVECMag(&VStack_60);
          __ct__7CVectorFRC3Vec(&local_6c,(Vec *)((param_1->m_gameWork).m_linkTable[2][7][0] + 4));
          if ((*(ushort *)
                (Game.game.unkCFlatData0[2] +
                *(int *)(param_1->m_gameWork).m_linkTable[2][2][7] * 0x48 + 0x32) & 0x10) != 0) {
            local_50 = 0x43300000;
            uVar8 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x70);
            uStack_4c = uVar8;
            if (dVar14 <= (double)(float)((double)CONCAT44(0x43300000,uVar8) - DOUBLE_80331a68)) {
              dVar14 = (double)FLOAT_80331a78;
            }
            else {
              pVVar7 = (Vec *)__ct__7CVectorFRC3Vec(&CStack_9c,&VStack_60);
              __ct__7CVectorFv(&local_e4);
              local_50 = 0x43300000;
              uStack_4c = uVar8;
              PSVECScale((float)(dVar14 - (double)(float)((double)CONCAT44(0x43300000,uVar8) -
                                                         DOUBLE_80331a68)),pVVar7,&local_e4);
              local_90.x = local_e4.x;
              local_90.y = local_e4.y;
              local_90.z = local_e4.z;
              __ct__7CVectorFv(&local_d8);
              PSVECScale((float)((double)FLOAT_80331a54 / dVar14),&local_90,&local_d8);
              local_84.x = local_d8.x;
              local_84.y = local_d8.y;
              local_84.z = local_d8.z;
              pVVar7 = (Vec *)__ct__7CVectorFRC3Vec
                                        (&CStack_78,
                                         (Vec *)((param_1->m_gameWork).m_linkTable[0][2][6] + 4));
              __ct__7CVectorFv(&local_c0);
              PSVECAdd(pVVar7,&local_84,&local_c0);
              local_6c.x = local_c0.x;
              local_6c.y = local_c0.y;
              local_6c.z = local_c0.z;
              uStack_44 = (uint)*(ushort *)(Game.game.unk_flat3_field_8_0xc7dc + 0x70);
              local_48 = 0x43300000;
              dVar14 = (double)(float)(dVar14 - (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_44) -
                                                               DOUBLE_80331a68));
            }
          }
          if ((double)FLOAT_80331a78 != dVar14) {
            uStack_44 = uVar9 ^ 0x80000000;
            local_48 = 0x43300000;
            Move__8CGObjectFP3Vecfiiiii
                      ((double)(float)(dVar14 / (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_44) -
                                                               DOUBLE_80331a60)),(CGObject *)param_1
                       ,&local_6c,uVar9,1,1,0,1);
          }
        }
        else {
          uStack_44 = (uint)(ushort)puVar11[5];
          local_48 = 0x43300000;
          moveVectorRot__8CGObjectFfffi
                    ((double)*(float *)((param_1->m_gameWork).m_linkTable[0][4][1] + 4),
                     (double)FLOAT_80331a78,
                     (double)(FLOAT_80331adc *
                             (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331a68)),
                     (CGObject *)param_1,uVar9);
        }
      }
      if (uVar6 == (ushort)puVar11[1]) {
        (**(code **)((param_1->m_gameWork).m_bossArtifactStageTable[6] + 0x90))
                  (param_1,1,1,*puVar11);
      }
      if (uVar6 == (ushort)puVar11[2]) {
        (**(code **)((param_1->m_gameWork).m_bossArtifactStageTable[6] + 0x90))(param_1,0,0,0);
      }
      iVar10 = iVar10 + 1;
      puVar11 = puVar11 + 6;
    } while (iVar10 < 5);
    if ((-1 < (int)uVar6) && (iVar5 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)param_1), iVar5 != 0)) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)param_1,0,0,0);
      return;
    }
    uVar9 = (uint)(ushort)puVar12[0x1e];
    if (uVar9 != 0) {
      local_48 = 0x43300000;
      dVar14 = (double)(FLOAT_80331ae0 *
                       (float)((double)CONCAT44(0x43300000,uVar9) - DOUBLE_80331a68));
      uStack_44 = uVar9;
      if (uVar6 == (ushort)puVar12[0x1f]) {
        __ct__7CVectorFRC3Vec(&CStack_b4,(Vec *)((param_1->m_gameWork).m_linkTable[0][2][6] + 4));
        pVVar7 = (Vec *)__ct__7CVectorFRC3Vec
                                  (&CStack_a8,
                                   (Vec *)((param_1->m_gameWork).m_linkTable[2][7][0] + 4));
        __ct__7CVectorFv(&local_cc);
        PSVECSubtract(pVVar7,(Vec *)&CStack_b4,&local_cc);
        fVar2 = local_cc.z * local_cc.z + local_cc.x * local_cc.x;
        dVar15 = (double)fVar2;
        if (dVar15 <= (double)FLOAT_80331a78) {
          if (DOUBLE_80331af8 <= dVar15) {
            uVar6 = (uint)fVar2 & 0x7f800000;
            if (uVar6 == 0x7f800000) {
              if (((uint)fVar2 & 0x7fffff) == 0) {
                iVar5 = 2;
              }
              else {
                iVar5 = 1;
              }
            }
            else if ((uVar6 < 0x7f800000) && (uVar6 == 0)) {
              if (((uint)fVar2 & 0x7fffff) == 0) {
                iVar5 = 3;
              }
              else {
                iVar5 = 5;
              }
            }
            else {
              iVar5 = 4;
            }
            if (iVar5 == 1) {
              dVar15 = (double)DAT_8032ec20;
            }
          }
          else {
            dVar15 = (double)DAT_8032ec20;
          }
        }
        else {
          dVar16 = 1.0 / SQRT(dVar15);
          dVar16 = DOUBLE_80331ae8 * dVar16 * -(dVar15 * dVar16 * dVar16 - DOUBLE_80331af0);
          dVar16 = DOUBLE_80331ae8 * dVar16 * -(dVar15 * dVar16 * dVar16 - DOUBLE_80331af0);
          dVar15 = (double)(float)(dVar15 * DOUBLE_80331ae8 * dVar16 *
                                            -(dVar15 * dVar16 * dVar16 - DOUBLE_80331af0));
        }
        if (((double)FLOAT_80331a78 != (double)local_cc.y) && ((double)FLOAT_80331a78 != dVar15)) {
          dVar16 = (double)atan2();
          dVar15 = -dVar14;
          dVar16 = -(double)(float)dVar16;
          if ((dVar15 <= dVar16) && (dVar15 = dVar16, dVar14 < dVar16)) {
            dVar15 = dVar14;
          }
          *(float *)((param_1->m_gameWork).m_linkTable[2][1][2] + 4) = (float)dVar15;
        }
      }
      else if (uVar6 == (ushort)puVar12[0x20]) {
        *(float *)((param_1->m_gameWork).m_linkTable[2][1][2] + 4) = FLOAT_80331a78;
      }
    }
  }
  iVar5 = *(int *)((param_1->m_gameWork).m_linkTable[2][2][0] + 4);
  if (iVar5 < 2) {
    bVar1 = false;
    uVar6 = (uint)(char)(param_1->m_gameWork).m_linkTable[0][0][7][2];
    if ((Pad._452_4_ != 0) || ((uVar6 == 0 && (Pad._448_4_ != -1)))) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar13 = 0;
    }
    else {
      uVar13 = *(ushort *)
                (&Pad.field_0x4 +
                (uVar6 & ~((int)~(Pad._448_4_ - uVar6 | uVar6 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    if ((uVar13 & 0x100) == 0) {
      if ((iVar5 == 0) ||
         ((iVar5 == 1 && (*(int *)(param_1->m_gameWork).m_linkTable[2][7][0] == 0)))) {
        changeStat__8CGPrgObjFiii((CGPrgObj *)param_1,0,0,0);
      }
      else {
        *(int *)(param_1->m_gameWork).m_linkTable[2][6][7] =
             *(int *)(param_1->m_gameWork).m_linkTable[2][6][7] + 1;
      }
    }
    else {
      bVar1 = false;
      if ((Pad._452_4_ != 0) || ((uVar6 == 0 && (Pad._448_4_ != -1)))) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar13 = 0;
      }
      else {
        uVar13 = *(ushort *)
                  (&Pad.field_0x4 +
                  (uVar6 & ~((int)~(Pad._448_4_ - uVar6 | uVar6 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((uVar13 & 0x200) != 0) {
        changeStat__8CGPrgObjFiii((CGPrgObj *)param_1,0,0,0);
      }
    }
  }
  return;
}

