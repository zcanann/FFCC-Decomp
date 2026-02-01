// Function: FUN_8011548c
// Entry: 8011548c
// Size: 1908 bytes

/* WARNING: Removing unreachable block (ram,0x80115be4) */
/* WARNING: Removing unreachable block (ram,0x80115bdc) */
/* WARNING: Removing unreachable block (ram,0x801154a4) */
/* WARNING: Removing unreachable block (ram,0x8011549c) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int FUN_8011548c(int param_1,int param_2)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  CGPartyObj *pCVar9;
  int iVar10;
  int iVar11;
  ushort uVar12;
  int iVar13;
  uint *puVar14;
  int iVar15;
  uint *puVar16;
  double dVar17;
  double dVar18;
  int local_b8 [4];
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  uint local_98 [7];
  undefined4 local_7c;
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  
  iVar13 = -1;
  iVar5 = __ptmf_test(*(int *)(param_1 + 0x708) + 0x84);
  if (iVar5 != 0) {
    iVar5 = __ptmf_scall(param_1,param_2,*(undefined4 *)(param_1 + 0x708));
    if (iVar5 == -2) {
      return -1;
    }
    if (iVar5 != -1) {
      return iVar5;
    }
  }
  dVar18 = (double)*(float *)(param_1 + param_2 * 4 + 0x5d0);
  if (*(short *)(param_1 + 0x6e4) == 0) {
    iVar5 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
  }
  else {
    iVar5 = Game.game.unkCFlatData0[1] +
            ((int)*(short *)(param_1 + 0x6e4) +
            (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) * 0x1d0 + 0x10;
  }
  sVar2 = *(short *)(iVar5 + 0x108);
  if (sVar2 == -1) {
    iVar6 = -1;
  }
  else {
    puVar16 = local_98;
    iVar15 = 0;
    local_98[0] = DAT_801dc978;
    local_98[1] = DAT_801dc97c;
    local_98[2] = DAT_801dc980;
    local_98[3] = DAT_801dc984;
    local_98[4] = DAT_801dc988;
    local_98[5] = DAT_801dc98c;
    local_98[6] = DAT_801dc990;
    local_7c = DAT_801dc994;
    local_b8[0] = DAT_801dc998;
    local_b8[1] = DAT_801dc99c;
    local_b8[2] = DAT_801dc9a0;
    local_b8[3] = DAT_801dc9a4;
    local_a8 = DAT_801dc9a8;
    local_a4 = DAT_801dc9ac;
    local_a0 = DAT_801dc9b0;
    local_9c = DAT_801dc9b4;
    iVar5 = 0;
    puVar14 = puVar16;
    do {
      iVar6 = iVar5;
      sVar1 = *(short *)(param_1 + 0x6e4);
      iVar5 = (int)sVar1;
      if (sVar1 == 0) {
        iVar10 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
      }
      else {
        iVar10 = Game.game.unkCFlatData0[1] +
                 (iVar5 + (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) *
                 0x1d0 + 0x10;
      }
      uVar3 = *(ushort *)(iVar10 + iVar15 + 0x110);
      if (uVar3 == 0xffff) {
        if (iVar6 == 0) {
          return -2;
        }
      }
      else {
        iVar10 = *(int *)(param_1 + 0x58);
        iVar11 = *(int *)(iVar10 + 0x24);
        if (*(short *)(iVar11 + 0x10c) == 1) {
          uVar12 = uVar3 & 3;
        }
        else {
          if (sVar1 != 0) {
            iVar11 = Game.game.unkCFlatData0[1] +
                     (iVar5 + (uint)*(ushort *)(iVar11 + 0x100)) * 0x1d0 + 0x10;
          }
          uVar12 = *(ushort *)(iVar11 + iVar15 + 0x118);
        }
        if ((uVar12 != 3) || (Game.game.m_gameWork.m_menuStageMode == '\0')) {
          if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf) {
            iVar7 = Game.game.m_gameWork.m_bossArtifactStageTable
                    [Game.game.m_gameWork.m_bossArtifactStageIndex];
            iVar11 = 2;
            if (iVar7 < 2) {
              iVar11 = iVar7;
            }
          }
          else {
            iVar11 = 0;
          }
          if (((uVar12 != 1) || (0 < iVar11)) && ((uVar12 != 2 || (1 < iVar11)))) {
            if ((uVar3 & 0x40) != 0) {
              if (sVar1 == 0) {
                iVar5 = *(int *)(iVar10 + 0x24);
              }
              else {
                iVar5 = Game.game.unkCFlatData0[1] +
                        (iVar5 + (uint)*(ushort *)(*(int *)(iVar10 + 0x24) + 0x100)) * 0x1d0 + 0x10;
              }
              uStack_74 = (uint)*(ushort *)(iVar5 + iVar15 + 0x118);
              local_78 = 0x43300000;
              dVar17 = (double)DstRot__5CMathFff((double)*(float *)(param_1 + param_2 * 4 + 0x610),
                                                 (double)(FLOAT_80331a20 *
                                                          (float)((double)CONCAT44(0x43300000,
                                                                                   uStack_74) -
                                                                 DOUBLE_803319e0) +
                                                         *(float *)(param_1 + 0x1a8)),&Math);
              dVar17 = (double)(float)ABS(dVar17);
              Printf__7CSystemFPce
                        ((double)(float)((double)FLOAT_80331a24 * dVar17),&System,&DAT_801dca0c);
              if (*(short *)(param_1 + 0x6e4) == 0) {
                iVar5 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
              }
              else {
                iVar5 = Game.game.unkCFlatData0[1] +
                        ((int)*(short *)(param_1 + 0x6e4) +
                        (uint)*(ushort *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) *
                        0x1d0 + 0x10;
              }
              uStack_6c = (uint)*(ushort *)(iVar5 + iVar15 + 0x11a);
              local_70 = 0x43300000;
              if ((double)(FLOAT_80331a20 *
                          (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_803319e0)) <=
                  dVar17) goto LAB_80115aa0;
              Printf__7CSystemFPce(&System,&DAT_80331a28);
            }
            if (sVar2 == 0) {
              sVar1 = *(short *)(param_1 + 0x6e4);
              iVar5 = (int)sVar1;
              if (sVar1 == 0) {
                iVar10 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
              }
              else {
                iVar10 = Game.game.unkCFlatData0[1] +
                         (iVar5 + (uint)*(ushort *)
                                         (*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) *
                         0x1d0 + 0x10;
              }
              if (sVar1 == 0) {
                iVar11 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
              }
              else {
                iVar11 = Game.game.unkCFlatData0[1] +
                         (iVar5 + (uint)*(ushort *)
                                         (*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) *
                         0x1d0 + 0x10;
              }
              uStack_6c = (uint)*(ushort *)(iVar11 + iVar15 + 0x112);
              local_70 = 0x43300000;
              if (sVar1 == 0) {
                iVar5 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
              }
              else {
                iVar5 = Game.game.unkCFlatData0[1] +
                        (iVar5 + (uint)*(ushort *)
                                        (*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x100)) * 0x1d0
                        + 0x10;
              }
              uStack_74 = *(ushort *)(iVar10 + iVar15 + 0x114) ^ 0x80000000;
              local_78 = 0x43300000;
              uVar3 = *(ushort *)(iVar5 + iVar15 + 0x116);
              if ((dVar18 < (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_80331a08
                                           )) &&
                 ((double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_803319e0) < dVar18
                 )) {
                pCVar9 = Game.game.m_partyObjArr[param_2];
                bVar4 = false;
                iVar5 = (pCVar9->gCharaObj).gPrgObj.m_lastStateId;
                if (((iVar5 == 1) || (iVar5 == 7)) &&
                   (dVar17 = (double)DstRot__5CMathFff((double)*(float *)(param_1 + 0x1a8),
                                                       (double)(pCVar9->gCharaObj).gPrgObj.object.
                                                               m_rotBaseY,&Math),
                   FLOAT_80331a30 < (float)ABS(dVar17))) {
                  iVar5 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
                  if (*(short *)(iVar5 + 0x10c) == 1) {
                    if (*(short *)(param_1 + 0x6e4) != 0) {
                      iVar5 = Game.game.unkCFlatData0[1] +
                              ((int)*(short *)(param_1 + 0x6e4) + (uint)*(ushort *)(iVar5 + 0x100))
                              * 0x1d0 + 0x10;
                    }
                    if (*(int *)(param_1 + 0x6e8) != (int)*(short *)(iVar5 + iVar15 + 0x11e))
                    goto LAB_801159d8;
                  }
                  else {
LAB_801159d8:
                    if ((*(short *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x10c) == 1) ||
                       (*(int *)(param_1 + 0x6e8) != iVar6)) goto LAB_801159f8;
                  }
                  bVar4 = true;
                }
LAB_801159f8:
                if (((bVar4) || (uVar8 = Rand__5CMathFUl(&Math,100), uVar8 <= uVar3)) &&
                   ((*(short *)(*(int *)(*(int *)(param_1 + 0x58) + 0x24) + 0x10c) == 1 ||
                    (iVar13 = iVar6, bVar4)))) break;
              }
            }
            else {
              iVar5 = *(int *)(*(int *)(param_1 + 0x58) + 0x24);
              if (*(short *)(iVar5 + 0x10c) == 1) {
                uVar8 = uVar3 >> 2 & 7;
              }
              else {
                if (*(short *)(param_1 + 0x6e4) != 0) {
                  iVar5 = Game.game.unkCFlatData0[1] +
                          ((int)*(short *)(param_1 + 0x6e4) + (uint)*(ushort *)(iVar5 + 0x100)) *
                          0x1d0 + 0x10;
                }
                uVar8 = (uint)*(ushort *)(iVar5 + iVar15 + 0x11a);
              }
              iVar5 = local_b8[uVar8];
              *puVar14 = uVar8;
              local_b8[uVar8] = iVar5 + 1;
            }
          }
        }
      }
LAB_80115aa0:
      iVar5 = iVar6 + 1;
      puVar14 = puVar14 + 1;
      iVar15 = iVar15 + 0x10;
      iVar6 = iVar13;
    } while (iVar5 < 8);
    if (sVar2 == 1) {
      while (local_b8[*(int *)(param_1 + 0x6cc)] == 0) {
        *(int *)(param_1 + 0x6cc) = *(int *)(param_1 + 0x6cc) + 1;
        if (7 < *(int *)(param_1 + 0x6cc)) {
          *(undefined4 *)(param_1 + 0x6cc) = 0;
        }
      }
      iVar13 = Rand__5CMathFUl(&Math);
      iVar5 = 0;
      iVar15 = 0;
      iVar10 = 2;
      do {
        if (*(uint *)(param_1 + 0x6cc) == *puVar16) {
          if (iVar5 == iVar13) {
            *(uint *)(param_1 + 0x6cc) = *(uint *)(param_1 + 0x6cc) + 1;
            return iVar15;
          }
          iVar5 = iVar5 + 1;
        }
        if (*(uint *)(param_1 + 0x6cc) == puVar16[1]) {
          if (iVar5 == iVar13) {
            *(uint *)(param_1 + 0x6cc) = *(uint *)(param_1 + 0x6cc) + 1;
            return iVar15 + 1;
          }
          iVar5 = iVar5 + 1;
        }
        if (*(uint *)(param_1 + 0x6cc) == puVar16[2]) {
          if (iVar5 == iVar13) {
            *(uint *)(param_1 + 0x6cc) = *(uint *)(param_1 + 0x6cc) + 1;
            return iVar15 + 2;
          }
          iVar5 = iVar5 + 1;
        }
        if (*(uint *)(param_1 + 0x6cc) == puVar16[3]) {
          if (iVar5 == iVar13) {
            *(uint *)(param_1 + 0x6cc) = *(uint *)(param_1 + 0x6cc) + 1;
            return iVar15 + 3;
          }
          iVar5 = iVar5 + 1;
        }
        puVar16 = puVar16 + 4;
        iVar15 = iVar15 + 4;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
    }
  }
  return iVar6;
}

