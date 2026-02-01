// Function: CalcSelectWait__8CMenuPcsFv
// Entry: 8013473c
// Size: 2844 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcSelectWait__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  short sVar2;
  bool bVar3;
  double dVar4;
  float fVar5;
  double dVar6;
  uint uVar7;
  ushort uVar8;
  ushort uVar10;
  uint uVar9;
  short *psVar11;
  int *piVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  short local_118;
  short local_116;
  Vec local_114;
  Vec local_108;
  Mtx MStack_fc;
  Mtx MStack_cc;
  Mtx MStack_9c;
  Mtx MStack_6c;
  undefined8 local_38;
  undefined8 local_30;
  
  fVar1 = FLOAT_80331eb0;
  iVar17 = *DAT_8032eea8;
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    iVar13 = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
    iVar19 = 0;
    while( true ) {
      psVar11 = *(short **)&menuPcs->field_0x84c;
      sVar2 = *psVar11;
      if (sVar2 <= iVar13) break;
      iVar13 = iVar13 + 1;
      *(float *)((int)psVar11 + iVar19 + 0x18) = fVar1;
      *(undefined4 *)((int)psVar11 + iVar19 + 0x34) = 3;
      iVar19 = iVar19 + 0x40;
    }
    psVar11 = psVar11 + sVar2 * 0x20 + 4;
    psVar11[0xe] = 0;
    fVar5 = FLOAT_80331eb0;
    fVar1 = FLOAT_80331eac;
    psVar11[0xf] = 0x20;
    *psVar11 = psVar11[iVar17 * -0x40] + -3;
    psVar11[1] = (psVar11 + iVar17 * -0x40)[1] + -8;
    psVar11[2] = 0x40;
    psVar11[3] = 0x30;
    *(float *)(psVar11 + 4) = fVar1;
    *(float *)(psVar11 + 6) = fVar1;
    psVar11[0x12] = 0;
    psVar11[0x13] = 0;
    psVar11[0x14] = 0;
    psVar11[0x15] = 8;
    *(float *)(psVar11 + 10) = fVar5;
    psVar11[0x16] = 0;
    psVar11[0x17] = 0;
    **(short **)&menuPcs->field_0x84c = sVar2 + 1;
    *(undefined4 *)(*(int *)&menuPcs->field_0x84c + 0xb4) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 4;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x18) = 0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x84c + 6) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
  }
  iVar13 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar14 = *(int *)&menuPcs->field_0x82c;
  iVar18 = (int)*(short *)(iVar14 + 0x22);
  piVar12 = DAT_8032eea8;
  iVar19 = iVar17;
  if (0 < iVar17) {
    do {
      if ((int)*(short *)(iVar14 + 0xe) == piVar12[0xd]) break;
      piVar12 = piVar12 + 0xb;
      iVar13 = iVar13 + 1;
      iVar19 = iVar19 + -1;
    } while (iVar19 != 0);
  }
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x848 + 10);
  if (sVar2 == 3) {
    if ((*(short *)(iVar14 + 0x1a) == 0) && (*(short *)(iVar14 + 0xe) < iVar17)) {
      bVar3 = false;
      uVar7 = DAT_8032eea8[iVar13 * 0xb + 7];
      if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
        bVar3 = true;
      }
      if (bVar3) {
        uVar10 = 0;
      }
      else {
        uVar10 = *(ushort *)
                  (&Pad.field_0x14 +
                  (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      bVar3 = false;
      if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
        bVar3 = true;
      }
      if (bVar3) {
        uVar8 = 0;
      }
      else {
        uVar8 = *(ushort *)
                 (&Pad.field_0x8 +
                 (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((uVar10 & 9) == 0) {
        if ((uVar10 & 6) != 0) {
          *(short *)(iVar14 + 0x26) = *(short *)(iVar14 + 0x26) + -1;
          if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x26) < 0) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 7;
          }
          PlaySe__6CSoundFiiii(&Sound,0x4e,0x40,0x7f,0);
        }
      }
      else {
        *(short *)(iVar14 + 0x26) = *(short *)(iVar14 + 0x26) + 1;
        if (7 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x26)) {
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
        }
        PlaySe__6CSoundFiiii(&Sound,0x4e,0x40,0x7f,0);
      }
      if ((uVar10 & 0xf) == 0) {
        if ((uVar8 & 0x100) == 0) {
          if ((uVar8 & 0x200) != 0) {
            GetWinSize__8CMenuPcsFiPsPsi(menuPcs,0x18,&local_116,&local_118,1);
            SetMcWinInfo__8CMenuPcsFii(menuPcs,(int)local_116,(int)local_118);
            *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 1;
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
        }
        else if ((((int)(char)(*(byte *)(DAT_8032eea8 + 2) | *(byte *)((int)DAT_8032eea8 + 9)) |
                  DAT_8032eea8[iVar13 * 0xb + 0xe]) &
                 1 << (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26)) == 0) {
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
          *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
          PlaySe__6CSoundFiiii(&Sound,0x4f,0x40,0x7f,0);
        }
        else {
          PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
        }
      }
    }
    else if (*(short *)(iVar14 + 0xe) < iVar17) {
      *(short *)(iVar14 + 0x1a) = *(short *)(iVar14 + 0x1a) + -1;
      iVar19 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar19 + 0x1a) == 0) {
        if ('\0' < *(char *)(iVar19 + 8)) {
          *(byte *)(DAT_8032eea8 + 2) =
               *(byte *)(DAT_8032eea8 + 2) | (byte)(1 << (int)*(short *)(iVar19 + 0x26));
          DAT_8032eea8[iVar13 * 0xb + 0x10] = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
          DAT_8032eea8[iVar13 * 0xb + 0xf] =
               (int)*(short *)((int)DAT_8032eea8 +
                              *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 2 + 10);
        }
        sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0xe);
        if (sVar2 < iVar17) {
          *(short *)(*(int *)&menuPcs->field_0x82c + 0xe) = sVar2 + 1;
        }
        *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0;
      }
    }
    else {
      *(undefined2 *)(iVar14 + 0x1a) = 0;
    }
  }
  else if (sVar2 == 1) {
    bVar3 = false;
    uVar7 = DAT_8032eea8[iVar13 * 0xb + 7];
    if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
      bVar3 = true;
    }
    if (bVar3) {
      uVar10 = 0;
    }
    else {
      uVar10 = *(ushort *)
                (&Pad.field_0x14 +
                (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    bVar3 = false;
    if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
      bVar3 = true;
    }
    if (bVar3) {
      uVar8 = 0;
    }
    else {
      uVar8 = *(ushort *)
               (&Pad.field_0x8 +
               (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    if ((uVar10 & 3) == 0) {
      if ((uVar8 & 0x100) == 0) {
        if ((uVar8 & 0x200) != 0) {
          *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 1;
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        }
      }
      else {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      }
    }
    else {
      *(ushort *)(iVar14 + 0x28) = *(ushort *)(iVar14 + 0x28) ^ 1;
      PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
    }
  }
  else if (((sVar2 == 2) && (*(short *)(*(int *)&menuPcs->field_0x848 + 8) + -1 < 1)) &&
          (*(short *)(iVar14 + 0x28) == 0)) {
    *(undefined2 *)(iVar14 + 0x1a) = 10;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 0xff;
  }
  psVar11 = *(short **)&menuPcs->field_0x84c;
  iVar19 = (int)*(float *)(DAT_8032eeb0 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 8 + 8);
  local_38 = (double)(longlong)iVar19;
  psVar11[0x44] = (short)iVar19;
  iVar19 = (int)*(float *)(DAT_8032eeb0 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 8 + 0xc
                          );
  local_30 = (double)(longlong)iVar19;
  psVar11[0x45] = (short)iVar19;
  if ((int)*(uint *)(psVar11 + 0x54) < (int)*(uint *)(psVar11 + 0x58)) {
    local_30 = (double)CONCAT44(0x43300000,*(uint *)(psVar11 + 0x54) ^ 0x80000000);
    local_38 = (double)CONCAT44(0x43300000,*(uint *)(psVar11 + 0x58) ^ 0x80000000);
    *(float *)(psVar11 + 0x4c) =
         (float)(local_30 - DOUBLE_80331e88) / (float)(local_38 - DOUBLE_80331e88);
    *(int *)(psVar11 + 0x54) = *(int *)(psVar11 + 0x54) + 1;
  }
  else {
    *(float *)(psVar11 + 0x4c) = FLOAT_80331eb0;
  }
  dVar6 = DOUBLE_80331f30;
  dVar4 = DOUBLE_80331e88;
  iVar19 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0xe);
  psVar11 = (short *)(*(int *)&menuPcs->field_0x84c + (*psVar11 + -1) * 0x40 + 8);
  if (iVar19 < iVar17) {
    iVar13 = iVar18 / 0x14 + (iVar18 >> 0x1f);
    *psVar11 = psVar11[(iVar17 * 2 - iVar19) * -0x20] + -3;
    uVar7 = (iVar18 + (iVar13 - (iVar13 >> 0x1f)) * -0x14) - 10;
    uVar9 = (int)uVar7 >> 0x1f;
    psVar11[1] = (psVar11 + (iVar17 * 2 - iVar19) * -0x20)[1] + -8;
    local_30 = (double)(CONCAT44(0x43300000,(uVar9 ^ uVar7) - uVar9) ^ 0x80000000);
    *(float *)(psVar11 + 8) = (float)((local_30 - dVar4) / dVar6);
  }
  else {
    *(float *)(psVar11 + 8) = FLOAT_80331eac;
  }
  iVar19 = 0;
  iVar13 = 0;
  do {
    if (iVar17 + 8 <= iVar19) {
      iVar19 = *(int *)&menuPcs->field_0x82c;
      if ((iVar17 <= *(short *)(iVar19 + 0xe)) && (*(short *)(iVar19 + 0x1a) == 0)) {
        if (*(short *)(iVar19 + 0x18) < 10) {
          *(short *)(iVar19 + 0x18) = *(short *)(iVar19 + 0x18) + 1;
        }
        else {
          *(undefined2 *)(iVar19 + 0x18) = 0;
          iVar13 = 0;
          *(undefined2 *)(*(int *)&menuPcs->field_0x84c + 6) = 1;
          for (iVar19 = 0; iVar19 < iVar17; iVar19 = iVar19 + 1) {
            iVar14 = *(int *)((int)DAT_8032eea8 + iVar13 + 0x3c);
            iVar18 = *(int *)((int)DAT_8032eea8 + iVar13 + 0x1c);
            if (0 < iVar14) {
              if (iVar14 < 0xff) {
                *(short *)(Game.game.m_scriptFoodBase[iVar18] + (iVar14 + -0x9f) * 2 + 0x136) =
                     (short)iVar14;
              }
              else {
                AddItem__12CCaravanWorkFiPi
                          ((CCaravanWork *)Game.game.m_scriptFoodBase[iVar18],(short)iVar14,0);
              }
            }
            iVar13 = iVar13 + 0x2c;
          }
        }
      }
      return;
    }
    iVar18 = *(int *)&menuPcs->field_0x84c;
    iVar14 = (int)DAT_8032eeae;
    if (iVar19 < iVar17) {
      iVar15 = *(int *)((int)DAT_8032eea8 + iVar13 + 0x44);
      iVar16 = *(int *)((int)DAT_8032eea8 + iVar13 + 0x20);
      fVar1 = *(float *)(&DAT_801dd56c + iVar15 * 4);
      PSMTXScale(fVar1,fVar1,fVar1,&MStack_6c);
LAB_80134ff8:
      if (iVar19 < iVar17) {
        MStack_6c.value[1][3] = *(float *)(&DAT_801dd55c + iVar15 * 4);
        MStack_6c.value[0][3] = FLOAT_80331eac;
      }
      else {
        local_30 = (double)CONCAT44(0x43300000,iVar19 - iVar17 ^ 0x80000000);
        local_108.x = DAT_801dd57c;
        local_108.y = FLOAT_80331eac;
        local_108.z = FLOAT_80331eac;
        PSMTXRotRad(FLOAT_80331f04 * (float)(DOUBLE_80331f08 * (local_30 - DOUBLE_80331e88)),
                    &MStack_9c,0x7a);
        PSMTXMultVecSR(&MStack_9c,&local_108,&local_114);
        if (*(int *)(iVar16 + 4) == 0x44) {
          PSMTXRotRad(FLOAT_80331f10,&MStack_cc,0x79);
          PSMTXConcat(&MStack_6c,&MStack_cc,&MStack_6c);
          PSMTXRotRad(FLOAT_80331f14,&MStack_fc,0x78);
          PSMTXConcat(&MStack_6c,&MStack_fc,&MStack_6c);
        }
        MStack_6c.value[0][3] = local_114.x;
        iVar15 = *(int *)(iVar16 + 4);
        MStack_6c.value[1][3] = (float)((double)(FLOAT_80331f18 * local_114.y) - DOUBLE_80331f20);
        if ((iVar15 == 0x41) || (iVar15 == 0x37)) {
          MStack_6c.value[1][3] = MStack_6c.value[1][3] + FLOAT_80331f28;
        }
        else if (iVar15 == 0x44) {
          MStack_6c.value[1][3] = MStack_6c.value[1][3] + FLOAT_80331f2c;
        }
      }
      MStack_6c.value[2][3] = FLOAT_80331eac;
      *(byte *)(*(int *)(iVar16 + 0x168) + 0x10c) =
           *(byte *)(*(int *)(iVar16 + 0x168) + 0x10c) & 0x7f | 0x80;
      SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(iVar16 + 0x168),&MStack_6c);
      CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(iVar16 + 0x168));
      CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(iVar16 + 0x168));
      *(undefined4 *)(*(int *)(iVar16 + 0x168) + 0x9c) =
           *(undefined4 *)(iVar18 + (iVar14 + iVar19) * 0x40 + 0x18);
    }
    else {
      iVar15 = iVar19 + iVar17;
      iVar16 = *(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar15 * 4);
      if (iVar16 != 0) {
        PSMTXScale(FLOAT_80331f00,FLOAT_80331f00,FLOAT_80331f00,&MStack_6c);
        goto LAB_80134ff8;
      }
    }
    iVar13 = iVar13 + 0x2c;
    iVar19 = iVar19 + 1;
  } while( true );
}

