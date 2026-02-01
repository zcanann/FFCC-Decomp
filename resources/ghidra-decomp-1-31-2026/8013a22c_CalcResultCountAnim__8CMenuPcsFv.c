// Function: CalcResultCountAnim__8CMenuPcsFv
// Entry: 8013a22c
// Size: 1736 bytes

/* WARNING: Removing unreachable block (ram,0x8013a8d8) */
/* WARNING: Removing unreachable block (ram,0x8013a23c) */

void CalcResultCountAnim__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  short sVar2;
  bool bVar3;
  float fVar4;
  ushort uVar5;
  int iVar6;
  short sVar8;
  CMenuPcs *pCVar7;
  int iVar9;
  ushort uVar10;
  short *psVar11;
  short sVar13;
  int *piVar12;
  int iVar14;
  uint unaff_r25;
  uint uVar15;
  int iVar16;
  double dVar17;
  double dVar18;
  Mtx MStack_e8;
  Mtx MStack_b8;
  Mtx MStack_88;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  fVar4 = FLOAT_80331eb0;
  fVar1 = FLOAT_80331eac;
  dVar18 = DOUBLE_80331e88;
  iVar14 = *DAT_8032eea8;
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    iVar9 = 0;
    iVar6 = 0;
    sVar2 = **(short **)&menuPcs->field_0x84c;
    sVar8 = 0x28;
    iVar16 = iVar14;
    if (0 < iVar14) {
      do {
        unaff_r25 = *(uint *)((int)DAT_8032eea8 + iVar6 + 0x34);
        psVar11 = (short *)(*(int *)&menuPcs->field_0x84c + (sVar2 + iVar9) * 0x40 + 8);
        psVar11[0xe] = 0;
        psVar11[0xf] = 0x19;
        bVar3 = false;
        if ((0 < iVar9) && (iVar9 < 3)) {
          bVar3 = true;
        }
        sVar13 = 0x20;
        if (bVar3) {
          sVar13 = 8;
        }
        *psVar11 = sVar13;
        psVar11[1] = sVar8;
        iVar9 = iVar9 + 1;
        psVar11[2] = 0x38;
        iVar6 = iVar6 + 0x2c;
        sVar8 = sVar8 + 0x60;
        psVar11[3] = 0x28;
        local_58 = 0x43300000;
        local_50 = 0x43300000;
        local_48 = 0x43300000;
        uStack_54 = unaff_r25 * (int)psVar11[2] ^ 0x80000000;
        *(float *)(psVar11 + 4) = (float)((double)CONCAT44(0x43300000,uStack_54) - dVar18);
        *(float *)(psVar11 + 6) = fVar1;
        psVar11[0x12] = 0;
        psVar11[0x13] = 9999;
        psVar11[0x14] = 0;
        psVar11[0x15] = 4;
        *(float *)(psVar11 + 10) = fVar4;
        *(float *)(psVar11 + 0x18) = fVar1;
        *(float *)(psVar11 + 0x1a) = fVar1;
        uStack_4c = (int)*psVar11 - 0x60U ^ 0x80000000;
        *(float *)(psVar11 + 0x1c) = (float)((double)CONCAT44(0x43300000,uStack_4c) - dVar18);
        uStack_44 = (int)psVar11[1] - 0x40U ^ 0x80000000;
        *(float *)(psVar11 + 0x1e) = (float)((double)CONCAT44(0x43300000,uStack_44) - dVar18);
        psVar11[0x10] = 0;
        psVar11[0x11] = 0;
        iVar16 = iVar16 + -1;
      } while (iVar16 != 0);
    }
    fVar1 = FLOAT_80331eac;
    iVar16 = 3;
    pCVar7 = menuPcs;
    do {
      if (*(int *)&pCVar7->field_0x774 != 0) {
        *(float *)(*(int *)(*(int *)&pCVar7->field_0x774 + 0x168) + 0x9c) = fVar1;
      }
      if (*(int *)&pCVar7->field_0x778 != 0) {
        *(float *)(*(int *)(*(int *)&pCVar7->field_0x778 + 0x168) + 0x9c) = fVar1;
      }
      if (*(int *)&pCVar7->field_0x77c != 0) {
        *(float *)(*(int *)(*(int *)&pCVar7->field_0x77c + 0x168) + 0x9c) = fVar1;
      }
      if (*(int *)&pCVar7->field_0x780 != 0) {
        *(float *)(*(int *)(*(int *)&pCVar7->field_0x780 + 0x168) + 0x9c) = fVar1;
      }
      if (*(int *)&pCVar7->field_0x784 != 0) {
        *(float *)(*(int *)(*(int *)&pCVar7->field_0x784 + 0x168) + 0x9c) = fVar1;
      }
      if (*(int *)&pCVar7->field_0x788 != 0) {
        *(float *)(*(int *)(*(int *)&pCVar7->field_0x788 + 0x168) + 0x9c) = fVar1;
      }
      if (*(int *)&pCVar7->field_0x78c != 0) {
        *(float *)(*(int *)(*(int *)&pCVar7->field_0x78c + 0x168) + 0x9c) = fVar1;
      }
      if (*(int *)&pCVar7->field_0x790 != 0) {
        *(float *)(*(int *)(*(int *)&pCVar7->field_0x790 + 0x168) + 0x9c) = fVar1;
      }
      pCVar7 = (CMenuPcs *)&pCVar7->m_mcCtrl;
      iVar16 = iVar16 + -1;
    } while (iVar16 != 0);
    **(short **)&menuPcs->field_0x84c = sVar2 + (short)iVar14;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  }
  iVar16 = *(int *)&menuPcs->field_0x82c;
  if (*(short *)(iVar16 + 0x10) == 0) {
    *(short *)(iVar16 + 0x22) = *(short *)(iVar16 + 0x22) + 1;
  }
  iVar6 = 0;
  sVar2 = **(short **)&menuPcs->field_0x84c;
  uVar15 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) - 8;
  for (iVar16 = 0; fVar4 = FLOAT_80331eb0, fVar1 = FLOAT_80331eac, iVar16 < iVar14;
      iVar16 = iVar16 + 1) {
    psVar11 = (short *)(*(int *)&menuPcs->field_0x84c + ((sVar2 - iVar14) + iVar16) * 0x40 + 8);
    if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 0) {
      if (uVar15 == *(uint *)((int)DAT_8032eea8 + iVar6 + 0x28)) {
        PlaySe__6CSoundFiiii(&Sound,0x4b,0x40,0x7f,0);
        *(uint *)(psVar11 + 0x12) = uVar15;
      }
      if ((int)uVar15 < *(int *)(psVar11 + 0x12)) {
        *(float *)(psVar11 + 8) = FLOAT_80331eac;
      }
      else {
        unaff_r25 = uVar15 - *(int *)(psVar11 + 0x12);
        *(float *)(psVar11 + 8) = FLOAT_80331eb0;
        fVar1 = FLOAT_80331eac;
        if ((int)unaff_r25 < (int)*(uint *)(psVar11 + 0x14)) {
          uStack_54 = unaff_r25 ^ 0x80000000;
          uStack_3c = *(uint *)(psVar11 + 0x14) ^ 0x80000000;
          local_58 = 0x43300000;
          uStack_4c = (int)*psVar11 ^ 0x80000000;
          local_40 = 0x43300000;
          uStack_44 = (int)psVar11[1] ^ 0x80000000;
          local_50 = 0x43300000;
          local_48 = 0x43300000;
          dVar18 = (double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331e88;
          dVar17 = DOUBLE_80331ed8 -
                   (double)((float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80331e88) /
                           (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331e88));
          *(float *)(psVar11 + 0x18) =
               (float)((double)(*(float *)(psVar11 + 0x1c) -
                               (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80331e88)) *
                      dVar17);
          *(float *)(psVar11 + 0x1a) =
               (float)((double)(*(float *)(psVar11 + 0x1e) - (float)dVar18) * dVar17);
        }
        else {
          *(float *)(psVar11 + 0x18) = FLOAT_80331eac;
          *(float *)(psVar11 + 0x1a) = fVar1;
        }
      }
    }
    else {
      *(float *)(psVar11 + 0x18) = FLOAT_80331eac;
      *(float *)(psVar11 + 0x1a) = fVar1;
      *(float *)(psVar11 + 8) = fVar4;
    }
    iVar6 = iVar6 + 0x2c;
  }
  dVar18 = (double)FLOAT_80331eb0;
  iVar6 = 0;
  for (iVar16 = 0; iVar16 < iVar14 << 1; iVar16 = iVar16 + 1) {
    if (iVar16 < iVar14) {
      iVar9 = *(int *)((int)DAT_8032eea8 + iVar6 + 0x20);
      unaff_r25 = *(uint *)((int)DAT_8032eea8 + iVar6 + 0x44);
      fVar1 = *(float *)(&DAT_801dd56c + unaff_r25 * 4);
      PSMTXScale(fVar1,fVar1,fVar1,&MStack_88);
    }
    else {
      iVar9 = *(int *)((int)menuPcs + (iVar16 - iVar14) * 4 + 0x774);
      PSMTXScale(FLOAT_80331eb0,FLOAT_80331eb0,FLOAT_80331eb0,&MStack_88);
    }
    if (iVar16 / iVar14 == 1) {
      PSMTXRotRad(FLOAT_80331f94,&MStack_b8,0x78);
      PSMTXConcat(&MStack_88,&MStack_b8,&MStack_88);
      PSMTXRotRad(FLOAT_80331f04 * **(float **)&menuPcs->field_0x82c,&MStack_e8,0x79);
      PSMTXConcat(&MStack_88,&MStack_e8,&MStack_88);
    }
    if (iVar16 < iVar14) {
      MStack_88.value[1][3] = *(float *)(&DAT_801dd55c + unaff_r25 * 4);
    }
    else {
      MStack_88.value[1][3] = FLOAT_80331eac;
    }
    MStack_88.value[0][3] = FLOAT_80331eac;
    *(byte *)(*(int *)(iVar9 + 0x168) + 0x10c) =
         *(byte *)(*(int *)(iVar9 + 0x168) + 0x10c) & 0x7f | 0x80;
    MStack_88.value[2][3] = MStack_88.value[0][3];
    SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(iVar9 + 0x168),&MStack_88);
    CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(iVar9 + 0x168));
    CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(iVar9 + 0x168));
    iVar6 = iVar6 + 0x2c;
    *(float *)(*(int *)(iVar9 + 0x168) + 0x9c) = (float)dVar18;
  }
  if (((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 0) && (-1 < (int)uVar15)) &&
     ((int)uVar15 <= DAT_8032eea8[1])) {
    PlaySe__6CSoundFiiii(&Sound,0x4a,0x40,0x7f,0);
  }
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if ((sVar2 == 0) && (-1 < (int)uVar15)) {
    uStack_44 = uVar15 ^ 0x80000000;
    local_40 = 0x43300000;
    uStack_3c = DAT_8032eea8[1] ^ 0x80000000;
    local_48 = 0x43300000;
    if (DOUBLE_80331f98 + ((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80331e88) <=
        (double)CONCAT44(0x43300000,uStack_44) - DOUBLE_80331e88) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x10) = 1;
      return;
    }
  }
  if (sVar2 != 0) {
    uVar10 = 0;
    iVar14 = *DAT_8032eea8;
    piVar12 = DAT_8032eea8;
    if (0 < iVar14) {
      do {
        uVar15 = piVar12[7];
        bVar3 = false;
        if ((Pad._452_4_ != 0) || ((uVar15 == 0 && (Pad._448_4_ != -1)))) {
          bVar3 = true;
        }
        if (bVar3) {
          uVar5 = 0;
        }
        else {
          uVar5 = *(ushort *)
                   (&Pad.field_0x8 +
                   (uVar15 & ~((int)~(Pad._448_4_ - uVar15 | uVar15 - Pad._448_4_) >> 0x1f)) * 0x54)
          ;
        }
        piVar12 = piVar12 + 0xb;
        uVar10 = uVar10 | uVar5;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
    }
    if ((uVar10 & 0x300) != 0) {
      PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      *(undefined2 *)(*(int *)&menuPcs->field_0x84c + 6) = 1;
    }
  }
  return;
}

