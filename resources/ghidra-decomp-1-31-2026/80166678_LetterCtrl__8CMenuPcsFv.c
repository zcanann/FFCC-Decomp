// Function: LetterCtrl__8CMenuPcsFv
// Entry: 80166678
// Size: 4556 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int LetterCtrl__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  char cVar2;
  byte bVar3;
  double dVar4;
  double dVar5;
  uint uVar6;
  short *psVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  char *pcVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int32_t iVar16;
  short sVar17;
  int iVar18;
  uint uVar19;
  short local_e0;
  short local_de;
  short local_dc;
  short local_da;
  char acStack_d8 [16];
  char acStack_c8 [16];
  undefined auStack_b8 [128];
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  iVar12 = 0;
  iVar18 = 0;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x32) =
       *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30);
  DAT_8032eeea = 0;
  iVar13 = *(int *)&menuPcs->field_0x82c;
  sVar17 = *(short *)(iVar13 + 0x12);
  if (sVar17 == 0) {
    sVar17 = *(short *)(iVar13 + 0x30);
    if (sVar17 == 0) {
      *(short *)(iVar13 + 0x22) = *(short *)(iVar13 + 0x22) + 1;
      iVar15 = (int)**(short **)&menuPcs->field_0x850;
      psVar7 = *(short **)&menuPcs->field_0x850 + 4;
      iVar14 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      iVar13 = iVar15;
      if (0 < iVar15) {
        do {
          dVar4 = DOUBLE_803330c8;
          fVar1 = FLOAT_803330bc;
          if (*(int *)(psVar7 + 0x12) <= iVar14) {
            if (iVar14 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
              *(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
              dVar5 = DOUBLE_803330e8;
              *(float *)(psVar7 + 8) =
                   (float)((DOUBLE_803330e8 /
                           (double)(float)((double)CONCAT44(0x43300000,
                                                            *(uint *)(psVar7 + 0x14) ^ 0x80000000) -
                                          dVar4)) *
                          (double)(float)((double)CONCAT44(0x43300000,
                                                           *(uint *)(psVar7 + 0x10) ^ 0x80000000) -
                                         dVar4));
              if ((*(uint *)(psVar7 + 0x16) & 2) == 0) {
                fVar1 = (float)((dVar5 / (double)(float)((double)CONCAT44(0x43300000,
                                                                          *(uint *)(psVar7 + 0x14) ^
                                                                          0x80000000) - dVar4)) *
                               (double)(float)((double)CONCAT44(0x43300000,
                                                                *(uint *)(psVar7 + 0x10) ^
                                                                0x80000000) - dVar4));
                *(float *)(psVar7 + 0x18) =
                     (*(float *)(psVar7 + 0x1c) -
                     (float)((double)CONCAT44(0x43300000,(int)*psVar7 ^ 0x80000000) - dVar4)) *
                     fVar1;
                *(float *)(psVar7 + 0x1a) =
                     (*(float *)(psVar7 + 0x1e) -
                     (float)((double)CONCAT44(0x43300000,(int)psVar7[1] ^ 0x80000000) - dVar4)) *
                     fVar1;
              }
            }
            else {
              iVar12 = iVar12 + 1;
              *(float *)(psVar7 + 8) = FLOAT_803330f8;
              *(float *)(psVar7 + 0x18) = fVar1;
              *(float *)(psVar7 + 0x1a) = fVar1;
            }
          }
          psVar7 = psVar7 + 0x20;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
      if (iVar15 == iVar12) {
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x34) =
             DAT_8032eee8 - *(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 1;
      }
    }
    else if (sVar17 == 1) {
      iVar12 = DAT_8032eee8 * 0xc + 0x3ec;
      bVar3 = *(byte *)(Game.game.m_scriptFoodBase[0] + iVar12);
      if (-1 < (char)bVar3) {
        *(byte *)(Game.game.m_scriptFoodBase[0] + iVar12) = bVar3 & 0x7f | 0x80;
      }
      iVar13 = 0;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
      iVar15 = (int)**(short **)&menuPcs->field_0x850;
      psVar7 = *(short **)&menuPcs->field_0x850 + 4;
      iVar14 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      iVar12 = iVar15;
      if (0 < iVar15) {
        do {
          dVar4 = DOUBLE_803330c8;
          fVar1 = FLOAT_803330bc;
          if (*(int *)(psVar7 + 0x12) <= iVar14) {
            if (iVar14 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
              local_20 = 0x43300000;
              *(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
              dVar5 = DOUBLE_803330e8;
              uStack_1c = *(uint *)(psVar7 + 0x14) ^ 0x80000000;
              local_28 = 0x43300000;
              uStack_24 = *(uint *)(psVar7 + 0x10) ^ 0x80000000;
              *(float *)(psVar7 + 8) =
                   (float)((DOUBLE_803330e8 /
                           (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - dVar4)) *
                          (double)(float)((double)CONCAT44(0x43300000,uStack_24) - dVar4));
              if ((*(uint *)(psVar7 + 0x16) & 2) == 0) {
                uStack_1c = *(uint *)(psVar7 + 0x14) ^ 0x80000000;
                uStack_24 = *(uint *)(psVar7 + 0x10) ^ 0x80000000;
                uStack_34 = (int)*psVar7 ^ 0x80000000;
                local_20 = 0x43300000;
                uStack_2c = (int)psVar7[1] ^ 0x80000000;
                local_28 = 0x43300000;
                local_38 = 0x43300000;
                local_30 = 0x43300000;
                fVar1 = (float)((dVar5 / (double)(float)((double)CONCAT44(0x43300000,uStack_1c) -
                                                        dVar4)) *
                               (double)(float)((double)CONCAT44(0x43300000,uStack_24) - dVar4));
                *(float *)(psVar7 + 0x18) =
                     (*(float *)(psVar7 + 0x1c) -
                     (float)((double)CONCAT44(0x43300000,uStack_34) - dVar4)) * fVar1;
                *(float *)(psVar7 + 0x1a) =
                     (*(float *)(psVar7 + 0x1e) -
                     (float)((double)CONCAT44(0x43300000,uStack_2c) - dVar4)) * fVar1;
              }
            }
            else {
              iVar13 = iVar13 + 1;
              *(float *)(psVar7 + 8) = FLOAT_803330f8;
              *(float *)(psVar7 + 0x18) = fVar1;
              *(float *)(psVar7 + 0x1a) = fVar1;
            }
          }
          psVar7 = psVar7 + 0x20;
          iVar12 = iVar12 + -1;
        } while (iVar12 != 0);
      }
      if (iVar15 == iVar13) {
        iVar12 = SingGetLetterAttachflg__8CMenuPcsFv(menuPcs);
        if (iVar12 < 0) {
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 1;
        }
        else {
          if (DAT_8032eef4 < 1) {
            DAT_8032eeed = '\x02';
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 3;
            *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) = (short)DAT_8032eeec;
          }
          else {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 5;
          }
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
          SingSetLetterAttachflg__8CMenuPcsFi(menuPcs,0xffffffff);
        }
      }
    }
    else if (sVar17 == 2) {
      if (*(char *)(iVar13 + 0xc) == '\0') {
        iVar12 = Game.game.m_scriptFoodBase[0] + DAT_8032eee8 * 0xc;
        if ((*(byte *)(iVar12 + 0x3ec) >> 3 & 1) == 0) {
          uVar6 = *(ushort *)(iVar12 + 0x3ee) & 0x1ff;
          if (Game.game.m_gameWork.m_languageId == '\x02') {
            iVar16 = Game.game.m_cFlatDataArr[1].m_table[0].index[uVar6 * 5 + 4];
            uVar8 = GetMenuStr__8CMenuPcsFi(menuPcs,0x22);
            uVar9 = GetMenuStr__8CMenuPcsFi(menuPcs,0x24);
            uVar10 = GetMenuStr__8CMenuPcsFi(menuPcs,0x23);
            sprintf(auStack_b8,s__s_s_s_s_801dee08,uVar10,iVar16,uVar9,uVar8);
          }
          else {
            iVar16 = Game.game.m_cFlatDataArr[1].m_table[0].index[uVar6 * 5 + 4];
            uVar8 = GetMenuStr__8CMenuPcsFi(menuPcs,0x22);
            sprintf(auStack_b8,&DAT_803331a0,uVar8,iVar16);
          }
        }
        else {
          sVar17 = (*(ushort *)(iVar12 + 0x3ee) & 0x1ff) * 100;
          if (Game.game.m_gameWork.m_languageId == '\x02') {
            uVar8 = GetMenuStr__8CMenuPcsFi(menuPcs,0x22);
            uVar9 = GetMenuStr__8CMenuPcsFi(menuPcs,4);
            sprintf(auStack_b8,s__d__s_s_80333198,sVar17,uVar9,uVar8);
          }
          else {
            uVar8 = GetMenuStr__8CMenuPcsFi(menuPcs,4);
            uVar9 = GetMenuStr__8CMenuPcsFi(menuPcs,0x22);
            sprintf(auStack_b8,s__s_d__s__801dee20,uVar9,sVar17,uVar8);
          }
        }
        strcpy(acStack_d8,&DAT_80333194);
        pcVar11 = (char *)GetMenuStr__8CMenuPcsFi(menuPcs,1);
        strcat(acStack_d8,pcVar11);
        strcpy(acStack_c8,&DAT_80333194);
        pcVar11 = (char *)GetMenuStr__8CMenuPcsFi(menuPcs,2);
        strcat(acStack_c8,pcVar11);
        SetSingDynamicWinMessInfo__8CMenuPcsFiPcPcPcPcPcPcPcPc
                  (menuPcs,3,auStack_b8,acStack_d8,acStack_c8,0,0,0,0,0);
        GetSingWinSize__8CMenuPcsFiPsPsi(menuPcs,0,&local_dc,&local_da,1);
        SetMcWinInfo__8CMenuPcsFii(menuPcs,(int)local_dc,(int)local_da);
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
      }
      if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 1;
      }
    }
    else if (sVar17 == 3) {
      iVar12 = LetterReplyWinOpen__8CMenuPcsFv();
      if (iVar12 != 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 1;
      }
    }
    else if (sVar17 == 4) {
      if (*(char *)(iVar13 + 0xc) == '\0') {
        GetSingWinSize__8CMenuPcsFiPsPsi(menuPcs,2,&local_e0,&local_de,0);
        SetMcWinInfo__8CMenuPcsFii(menuPcs,(int)local_e0,(int)local_de);
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 0xff;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 1;
      }
      if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 1;
      }
    }
    else if ((sVar17 == 5) && (iVar12 = LetterConfirmOpen__8CMenuPcsFv(), iVar12 != 0)) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 1;
    }
  }
  else if (sVar17 == 1) {
    iVar18 = LetterCtrlCur__8CMenuPcsFv(menuPcs);
  }
  else if (sVar17 == 2) {
    sVar17 = *(short *)(iVar13 + 0x30);
    if (sVar17 == 0) {
      *(short *)(iVar13 + 0x22) = *(short *)(iVar13 + 0x22) + 1;
      iVar15 = (int)**(short **)&menuPcs->field_0x850;
      psVar7 = *(short **)&menuPcs->field_0x850 + 4;
      iVar14 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
      iVar13 = iVar15;
      if (0 < iVar15) {
        do {
          dVar4 = DOUBLE_803330c8;
          fVar1 = FLOAT_803330bc;
          if (*(int *)(psVar7 + 0x12) <= iVar14) {
            if (iVar14 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
              local_20 = 0x43300000;
              *(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
              dVar5 = DOUBLE_803330e8;
              uStack_1c = *(uint *)(psVar7 + 0x14) ^ 0x80000000;
              local_28 = 0x43300000;
              uStack_24 = *(uint *)(psVar7 + 0x10) ^ 0x80000000;
              *(float *)(psVar7 + 8) =
                   (float)-((DOUBLE_803330e8 /
                            (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - dVar4)) *
                            (double)(float)((double)CONCAT44(0x43300000,uStack_24) - dVar4) -
                           DOUBLE_803330e8);
              if ((*(uint *)(psVar7 + 0x16) & 2) == 0) {
                uStack_1c = *(uint *)(psVar7 + 0x14) ^ 0x80000000;
                uStack_24 = *(uint *)(psVar7 + 0x10) ^ 0x80000000;
                uStack_34 = (int)*psVar7 ^ 0x80000000;
                local_20 = 0x43300000;
                uStack_2c = (int)psVar7[1] ^ 0x80000000;
                local_28 = 0x43300000;
                local_38 = 0x43300000;
                local_30 = 0x43300000;
                fVar1 = (float)-((dVar5 / (double)(float)((double)CONCAT44(0x43300000,uStack_1c) -
                                                         dVar4)) *
                                 (double)(float)((double)CONCAT44(0x43300000,uStack_24) - dVar4) -
                                dVar5);
                *(float *)(psVar7 + 0x18) =
                     (*(float *)(psVar7 + 0x1c) -
                     (float)((double)CONCAT44(0x43300000,uStack_34) - dVar4)) * fVar1;
                *(float *)(psVar7 + 0x1a) =
                     (*(float *)(psVar7 + 0x1e) -
                     (float)((double)CONCAT44(0x43300000,uStack_2c) - dVar4)) * fVar1;
              }
            }
            else {
              iVar12 = iVar12 + 1;
              *(float *)(psVar7 + 8) = FLOAT_803330bc;
              *(float *)(psVar7 + 0x18) = fVar1;
              *(float *)(psVar7 + 0x1a) = fVar1;
            }
          }
          psVar7 = psVar7 + 0x20;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
      if (iVar15 == iVar12) {
        LetterInit1__8CMenuPcsFv(menuPcs);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
      }
    }
    else if (sVar17 == 1) {
      cVar2 = *(char *)(iVar13 + 8);
      if (cVar2 < '\x01') {
        *(short *)(iVar13 + 0x22) = *(short *)(iVar13 + 0x22) + 1;
        iVar15 = (int)**(short **)&menuPcs->field_0x850;
        psVar7 = *(short **)&menuPcs->field_0x850 + 4;
        iVar14 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
        iVar13 = iVar15;
        if (0 < iVar15) {
          do {
            dVar4 = DOUBLE_803330c8;
            fVar1 = FLOAT_803330bc;
            if (*(int *)(psVar7 + 0x12) <= iVar14) {
              if (iVar14 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
                local_20 = 0x43300000;
                *(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
                dVar5 = DOUBLE_803330e8;
                uStack_1c = *(uint *)(psVar7 + 0x14) ^ 0x80000000;
                local_28 = 0x43300000;
                uStack_24 = *(uint *)(psVar7 + 0x10) ^ 0x80000000;
                *(float *)(psVar7 + 8) =
                     (float)-((DOUBLE_803330e8 /
                              (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - dVar4)) *
                              (double)(float)((double)CONCAT44(0x43300000,uStack_24) - dVar4) -
                             DOUBLE_803330e8);
                if ((*(uint *)(psVar7 + 0x16) & 2) == 0) {
                  uStack_1c = *(uint *)(psVar7 + 0x14) ^ 0x80000000;
                  uStack_24 = *(uint *)(psVar7 + 0x10) ^ 0x80000000;
                  uStack_34 = (int)*psVar7 ^ 0x80000000;
                  local_20 = 0x43300000;
                  uStack_2c = (int)psVar7[1] ^ 0x80000000;
                  local_28 = 0x43300000;
                  local_38 = 0x43300000;
                  local_30 = 0x43300000;
                  fVar1 = (float)-((dVar5 / (double)(float)((double)CONCAT44(0x43300000,uStack_1c) -
                                                           dVar4)) *
                                   (double)(float)((double)CONCAT44(0x43300000,uStack_24) - dVar4) -
                                  dVar5);
                  *(float *)(psVar7 + 0x18) =
                       (*(float *)(psVar7 + 0x1c) -
                       (float)((double)CONCAT44(0x43300000,uStack_34) - dVar4)) * fVar1;
                  *(float *)(psVar7 + 0x1a) =
                       (*(float *)(psVar7 + 0x1e) -
                       (float)((double)CONCAT44(0x43300000,uStack_2c) - dVar4)) * fVar1;
                }
              }
              else {
                iVar12 = iVar12 + 1;
                *(float *)(psVar7 + 8) = FLOAT_803330bc;
                *(float *)(psVar7 + 0x18) = fVar1;
                *(float *)(psVar7 + 0x1a) = fVar1;
              }
            }
            psVar7 = psVar7 + 0x20;
            iVar13 = iVar13 + -1;
          } while (iVar13 != 0);
        }
        if (iVar15 == iVar12) {
          if (DAT_8032eeed == '\x02') {
            memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
            fVar1 = FLOAT_803330f8;
            iVar12 = *(int *)&menuPcs->field_0x850 + 8;
            iVar13 = 8;
            do {
              *(float *)(iVar12 + 0x14) = fVar1;
              *(float *)(iVar12 + 0x54) = fVar1;
              *(float *)(iVar12 + 0x94) = fVar1;
              *(float *)(iVar12 + 0xd4) = fVar1;
              *(float *)(iVar12 + 0x114) = fVar1;
              *(float *)(iVar12 + 0x154) = fVar1;
              *(float *)(iVar12 + 0x194) = fVar1;
              *(float *)(iVar12 + 0x1d4) = fVar1;
              iVar12 = iVar12 + 0x200;
              iVar13 = iVar13 + -1;
            } while (iVar13 != 0);
            iVar12 = *(int *)&menuPcs->field_0x850;
            *(undefined4 *)(iVar12 + 0x24) = 0;
            *(undefined4 *)(iVar12 + 0x2c) = 0;
            *(undefined4 *)(iVar12 + 0x30) = 10;
            iVar12 = *(int *)&menuPcs->field_0x850;
            *(undefined4 *)(iVar12 + 100) = 0;
            *(uint *)(iVar12 + 0x6c) =
                 ~((-(int)(char)menuPcs->field_0x872 | (int)(char)menuPcs->field_0x872) >> 0x1f) &
                 10;
            *(undefined4 *)(iVar12 + 0x70) = 10;
            **(undefined2 **)&menuPcs->field_0x850 = 2;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
            *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
          }
          else {
            iVar18 = 1;
          }
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 0;
        }
      }
      else {
        if (cVar2 == '\x01') {
          *(undefined2 *)(iVar13 + 0x30) = 2;
        }
        else if (cVar2 == '\x02') {
          *(undefined2 *)(iVar13 + 0x28) = 0;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 3;
        }
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
      }
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
    }
    else if (sVar17 == 2) {
      if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3) {
        *(undefined *)(iVar13 + 0xc) = 0;
        iVar12 = *(int *)&menuPcs->field_0x82c;
        if (*(char *)(iVar12 + 8) < '\x01') {
          *(undefined2 *)(iVar12 + 0x30) = 1;
        }
        else {
          *(undefined2 *)(iVar12 + 0x30) = 3;
        }
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 0;
      }
    }
    else if (sVar17 == 3) {
      if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3) {
        *(undefined *)(iVar13 + 0xc) = 0;
        iVar12 = *(int *)&menuPcs->field_0x82c;
        if (*(char *)(iVar12 + 8) < '\x01') {
          *(undefined2 *)(iVar12 + 0x30) = 1;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 1;
        }
        else {
          *(undefined2 *)(iVar12 + 0x30) = 4;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
        }
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
      }
    }
    else if (sVar17 == 4) {
      if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3) {
        *(undefined *)(iVar13 + 0xc) = 0;
        iVar12 = *(int *)&menuPcs->field_0x82c;
        if (*(char *)(iVar12 + 8) < '\x01') {
          *(undefined2 *)(iVar12 + 0x30) = 3;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) = (short)DAT_8032eeec;
        }
        else {
          if (DAT_8032eeed == '\x02') {
            *(undefined2 *)(iVar12 + 0x30) = 5;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
          }
          else {
            if (DAT_8032eeed == '\0') {
              SingSetLetterAttachflg__8CMenuPcsFi(menuPcs,1);
            }
            else {
              SingSetLetterAttachflg__8CMenuPcsFi(menuPcs,5);
            }
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 1;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 2;
            fVar1 = FLOAT_803330f8;
            *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
            iVar12 = *(int *)&menuPcs->field_0x850;
            *(undefined4 *)(iVar12 + 0x2c) = 0;
            *(undefined4 *)(iVar12 + 0x30) = 10;
            iVar12 = *(int *)&menuPcs->field_0x850;
            *(undefined4 *)(iVar12 + 0x6c) = 0;
            *(undefined4 *)(iVar12 + 0x70) = 10;
            uVar6 = (uint)**(short **)&menuPcs->field_0x850;
            psVar7 = *(short **)&menuPcs->field_0x850 + 4;
            if (0 < (int)uVar6) {
              uVar19 = uVar6 >> 3;
              if (uVar19 != 0) {
                do {
                  psVar7[0x10] = 0;
                  psVar7[0x11] = 0;
                  *(float *)(psVar7 + 8) = fVar1;
                  psVar7[0x30] = 0;
                  psVar7[0x31] = 0;
                  *(float *)(psVar7 + 0x28) = fVar1;
                  psVar7[0x50] = 0;
                  psVar7[0x51] = 0;
                  *(float *)(psVar7 + 0x48) = fVar1;
                  psVar7[0x70] = 0;
                  psVar7[0x71] = 0;
                  *(float *)(psVar7 + 0x68) = fVar1;
                  psVar7[0x90] = 0;
                  psVar7[0x91] = 0;
                  *(float *)(psVar7 + 0x88) = fVar1;
                  psVar7[0xb0] = 0;
                  psVar7[0xb1] = 0;
                  *(float *)(psVar7 + 0xa8) = fVar1;
                  psVar7[0xd0] = 0;
                  psVar7[0xd1] = 0;
                  *(float *)(psVar7 + 200) = fVar1;
                  psVar7[0xf0] = 0;
                  psVar7[0xf1] = 0;
                  *(float *)(psVar7 + 0xe8) = fVar1;
                  psVar7 = psVar7 + 0x100;
                  uVar19 = uVar19 - 1;
                } while (uVar19 != 0);
                uVar6 = uVar6 & 7;
                if (uVar6 == 0) goto LAB_801674c8;
              }
              do {
                psVar7[0x10] = 0;
                psVar7[0x11] = 0;
                *(float *)(psVar7 + 8) = fVar1;
                psVar7 = psVar7 + 0x20;
                uVar6 = uVar6 - 1;
              } while (uVar6 != 0);
            }
LAB_801674c8:
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
          }
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
        }
      }
    }
    else if ((sVar17 == 5) && (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 3)) {
      *(undefined *)(iVar13 + 0xc) = 0;
      if (*(char *)(*(int *)&menuPcs->field_0x82c + 8) < '\x01') {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 3;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) = (short)DAT_8032eeec;
      }
      else {
        DAT_8032eeed = '\x02';
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 1;
        fVar1 = FLOAT_803330f8;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 2;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
        iVar12 = *(int *)&menuPcs->field_0x850;
        *(undefined4 *)(iVar12 + 0x2c) = 0;
        *(undefined4 *)(iVar12 + 0x30) = 10;
        iVar12 = *(int *)&menuPcs->field_0x850;
        *(undefined4 *)(iVar12 + 0x6c) = 0;
        *(undefined4 *)(iVar12 + 0x70) = 10;
        uVar6 = (uint)**(short **)&menuPcs->field_0x850;
        psVar7 = *(short **)&menuPcs->field_0x850 + 4;
        if (0 < (int)uVar6) {
          uVar19 = uVar6 >> 3;
          if (uVar19 != 0) {
            do {
              psVar7[0x10] = 0;
              psVar7[0x11] = 0;
              *(float *)(psVar7 + 8) = fVar1;
              psVar7[0x30] = 0;
              psVar7[0x31] = 0;
              *(float *)(psVar7 + 0x28) = fVar1;
              psVar7[0x50] = 0;
              psVar7[0x51] = 0;
              *(float *)(psVar7 + 0x48) = fVar1;
              psVar7[0x70] = 0;
              psVar7[0x71] = 0;
              *(float *)(psVar7 + 0x68) = fVar1;
              psVar7[0x90] = 0;
              psVar7[0x91] = 0;
              *(float *)(psVar7 + 0x88) = fVar1;
              psVar7[0xb0] = 0;
              psVar7[0xb1] = 0;
              *(float *)(psVar7 + 0xa8) = fVar1;
              psVar7[0xd0] = 0;
              psVar7[0xd1] = 0;
              *(float *)(psVar7 + 200) = fVar1;
              psVar7[0xf0] = 0;
              psVar7[0xf1] = 0;
              *(float *)(psVar7 + 0xe8) = fVar1;
              psVar7 = psVar7 + 0x100;
              uVar19 = uVar19 - 1;
            } while (uVar19 != 0);
            uVar6 = uVar6 & 7;
            if (uVar6 == 0) goto LAB_80167654;
          }
          do {
            psVar7[0x10] = 0;
            psVar7[0x11] = 0;
            *(float *)(psVar7 + 8) = fVar1;
            psVar7 = psVar7 + 0x20;
            uVar6 = uVar6 - 1;
          } while (uVar6 != 0);
        }
LAB_80167654:
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xc) = 0;
      }
    }
  }
  fVar1 = FLOAT_803330f8;
  if (iVar18 == 0) {
    return 0;
  }
  if (DAT_8032eeed == '\x02') {
    iVar12 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar12 + 0x24) = 0;
    *(undefined4 *)(iVar12 + 0x2c) = 10;
    *(undefined4 *)(iVar12 + 0x30) = 10;
    iVar12 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar12 + 100) = 0;
    *(undefined4 *)(iVar12 + 0x6c) = 0;
    *(undefined4 *)(iVar12 + 0x70) = 10;
    uVar6 = (uint)**(short **)&menuPcs->field_0x850;
    psVar7 = *(short **)&menuPcs->field_0x850 + 4;
    if (0 < (int)uVar6) {
      uVar19 = uVar6 >> 3;
      if (uVar19 != 0) {
        do {
          psVar7[0x10] = 0;
          psVar7[0x11] = 0;
          *(float *)(psVar7 + 8) = fVar1;
          psVar7[0x30] = 0;
          psVar7[0x31] = 0;
          *(float *)(psVar7 + 0x28) = fVar1;
          psVar7[0x50] = 0;
          psVar7[0x51] = 0;
          *(float *)(psVar7 + 0x48) = fVar1;
          psVar7[0x70] = 0;
          psVar7[0x71] = 0;
          *(float *)(psVar7 + 0x68) = fVar1;
          psVar7[0x90] = 0;
          psVar7[0x91] = 0;
          *(float *)(psVar7 + 0x88) = fVar1;
          psVar7[0xb0] = 0;
          psVar7[0xb1] = 0;
          *(float *)(psVar7 + 0xa8) = fVar1;
          psVar7[0xd0] = 0;
          psVar7[0xd1] = 0;
          *(float *)(psVar7 + 200) = fVar1;
          psVar7[0xf0] = 0;
          psVar7[0xf1] = 0;
          *(float *)(psVar7 + 0xe8) = fVar1;
          psVar7 = psVar7 + 0x100;
          uVar19 = uVar19 - 1;
        } while (uVar19 != 0);
        uVar6 = uVar6 & 7;
        if (uVar6 == 0) goto LAB_80167820;
      }
      do {
        psVar7[0x10] = 0;
        psVar7[0x11] = 0;
        *(float *)(psVar7 + 8) = fVar1;
        psVar7 = psVar7 + 0x20;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
LAB_80167820:
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    return iVar18;
  }
  iVar12 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar12 + 0x24) = 0;
  *(undefined4 *)(iVar12 + 0x2c) = 0;
  *(undefined4 *)(iVar12 + 0x30) = 10;
  **(undefined2 **)&menuPcs->field_0x850 = 1;
  uVar6 = (uint)**(short **)&menuPcs->field_0x850;
  psVar7 = *(short **)&menuPcs->field_0x850 + 4;
  if (0 < (int)uVar6) {
    uVar19 = uVar6 >> 3;
    if (uVar19 != 0) {
      do {
        psVar7[0x10] = 0;
        psVar7[0x11] = 0;
        *(float *)(psVar7 + 8) = fVar1;
        psVar7[0x30] = 0;
        psVar7[0x31] = 0;
        *(float *)(psVar7 + 0x28) = fVar1;
        psVar7[0x50] = 0;
        psVar7[0x51] = 0;
        *(float *)(psVar7 + 0x48) = fVar1;
        psVar7[0x70] = 0;
        psVar7[0x71] = 0;
        *(float *)(psVar7 + 0x68) = fVar1;
        psVar7[0x90] = 0;
        psVar7[0x91] = 0;
        *(float *)(psVar7 + 0x88) = fVar1;
        psVar7[0xb0] = 0;
        psVar7[0xb1] = 0;
        *(float *)(psVar7 + 0xa8) = fVar1;
        psVar7[0xd0] = 0;
        psVar7[0xd1] = 0;
        *(float *)(psVar7 + 200) = fVar1;
        psVar7[0xf0] = 0;
        psVar7[0xf1] = 0;
        *(float *)(psVar7 + 0xe8) = fVar1;
        psVar7 = psVar7 + 0x100;
        uVar19 = uVar19 - 1;
      } while (uVar19 != 0);
      uVar6 = uVar6 & 7;
      if (uVar6 == 0) goto LAB_8016773c;
    }
    do {
      psVar7[0x10] = 0;
      psVar7[0x11] = 0;
      *(float *)(psVar7 + 8) = fVar1;
      psVar7 = psVar7 + 0x20;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
LAB_8016773c:
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
  return iVar18;
}

