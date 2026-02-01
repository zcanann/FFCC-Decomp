// Function: CalcMCardMenu__8CMenuPcsFv
// Entry: 800fec40
// Size: 6552 bytes

/* WARNING: Removing unreachable block (ram,0x801005bc) */
/* WARNING: Removing unreachable block (ram,0x800fec50) */
/* WARNING: Removing unreachable block (ram,0x80100214) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcMCardMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  float fVar2;
  ushort uVar3;
  ushort uVar6;
  int *piVar4;
  short sVar7;
  undefined2 uVar8;
  uint32_t *puVar5;
  uint uVar9;
  char *pcVar10;
  uint32_t uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  short sVar16;
  undefined4 uVar17;
  int *piVar18;
  CFont *pCVar19;
  undefined4 uVar20;
  int iVar21;
  double dVar22;
  double dVar23;
  undefined8 local_58;
  double local_50;
  double local_48;
  double local_40;
  
  bVar1 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar3 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar3 = Pad._8_2_;
  }
  uVar6 = GetButtonRepeat__8CMenuPcsFi(menuPcs,0);
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 8) == '\0') {
    (menuPcs->m_mcCtrl).m_previousState = 0;
    (menuPcs->m_mcCtrl).m_state = 0;
    (menuPcs->m_mcCtrl).m_lastResult = 0;
    (menuPcs->m_mcCtrl).m_iteration = 0;
    (menuPcs->m_mcCtrl).m_userBuffer = (void *)0x0;
    (menuPcs->m_mcCtrl).m_createFlag = 0;
    if ((DAT_8032ee20 < '\0') || (1 < DAT_8032ee20)) {
      (menuPcs->m_mcCtrl).m_cardChannel = 0;
    }
    else {
      (menuPcs->m_mcCtrl).m_cardChannel = (int)DAT_8032ee20;
    }
    if ((cRam8032ee21 < '\0') || (3 < cRam8032ee21)) {
      (menuPcs->m_mcCtrl).m_saveIndex = 0;
    }
    else {
      (menuPcs->m_mcCtrl).m_saveIndex = (int)cRam8032ee21;
    }
    memset(menuPcs->m_unk0x838,0,0x120);
    iVar14 = *(int *)&menuPcs->field_0x82c;
    Game.game.m_gameWork.m_wmBackupParams[0] = (int32_t)*(short *)(iVar14 + 0x36);
    Game.game.m_gameWork.m_wmBackupParams[1] = (int32_t)*(short *)(iVar14 + 0x38);
    Game.game.m_gameWork.m_wmBackupParams[2] = (int32_t)*(short *)(iVar14 + 0x3a);
    Game.game.m_gameWork.m_wmBackupParams[3] = (int32_t)*(short *)(iVar14 + 0x3c);
    *(undefined *)(iVar14 + 10) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
  }
  dVar23 = DOUBLE_80331408;
  iVar14 = *(int *)&menuPcs->field_0x82c;
  sVar7 = *(short *)(iVar14 + 0x10);
  if (sVar7 == 0) {
    uVar15 = (int)*(short *)(iVar14 + 0x22) - 10;
  }
  else if ((sVar7 < 1) || (3 < sVar7)) {
    uVar15 = -(int)*(short *)(iVar14 + 0x22);
  }
  else {
    uVar15 = 0;
  }
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
  iVar14 = *(int *)&menuPcs->field_0x820;
  local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar14 + 8) + (int)*(short *)(iVar14 + 4))
                     ^ 0x80000000);
  *(short *)(iVar14 + 0x20) = (short)(int)(FLOAT_803313e0 - (float)(local_58 - dVar23));
  if ((int)uVar15 < 0) {
    local_50 = (double)(CONCAT44(0x43300000,
                                 (int)*(short *)(*(int *)&menuPcs->field_0x820 + 8) +
                                 (int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^ 0x80000000);
    dVar22 = (double)(float)(local_50 - dVar23);
    if (-0xb < (int)uVar15) {
      uVar9 = (int)uVar15 >> 0x1f;
      local_50 = (double)(CONCAT44(0x43300000,(uVar9 ^ uVar15) - uVar9) ^ 0x80000000);
      uVar9 = (uVar9 ^ uVar15) - uVar9;
      dVar23 = (double)(float)(dVar22 * DOUBLE_803314e8 * (local_50 - dVar23));
      if ((int)uVar9 < 0) {
        uVar9 = 0;
      }
      if (10 < (int)uVar9) {
        uVar9 = 10;
      }
      local_58 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
      dVar22 = (double)sin((double)(FLOAT_803314bc *
                                   (float)(local_58 - DOUBLE_80331408) * FLOAT_803316d4));
      dVar22 = (double)(float)(dVar23 * (double)(float)dVar22);
    }
    dVar23 = DOUBLE_80331408;
    local_50 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^
                       0x80000000);
    *(short *)(*(int *)&menuPcs->field_0x820 + 4) =
         (short)(int)((double)(float)(local_50 - DOUBLE_80331408) - dVar22);
    local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x820 + 0x20)) ^
                       0x80000000);
    *(short *)(*(int *)&menuPcs->field_0x820 + 0x20) =
         (short)(int)((double)(float)(local_48 - dVar23) + dVar22);
  }
  fVar2 = FLOAT_803313e8;
  iVar14 = *(int *)&menuPcs->field_0x82c;
  if (*(short *)(iVar14 + 0x10) != 2) {
    return;
  }
  iVar12 = (int)*(short *)(iVar14 + 0x16);
  switch(iVar12) {
  case 0:
  case 2:
    if (*(char *)(iVar14 + 9) == '\0') {
      *(short *)(iVar14 + 0x26) = (short)(menuPcs->m_mcCtrl).m_cardChannel;
      pCVar19 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(fVar2,pCVar19);
      SetShadow__5CFontFi(pCVar19,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar19);
      iVar12 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,0);
      iVar14 = 0;
      piVar4 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,0);
      piVar18 = piVar4;
      for (iVar21 = 0; iVar21 < *piVar4; iVar21 = iVar21 + 1) {
        pcVar10 = *(char **)(iVar12 + *(short *)(piVar18 + 1) * 4);
        if (pcVar10 != (char *)0x0) {
          if (*pcVar10 == '$') {
            pcVar10 = pcVar10 + 1;
          }
          dVar23 = (double)GetWidth__5CFontFPc(pCVar19,pcVar10);
          if (iVar14 < (int)dVar23) {
            iVar14 = (int)dVar23;
          }
        }
        piVar18 = (int *)((int)piVar18 + 2);
      }
      iVar12 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar7 = (short)iVar12 - (short)(iVar12 >> 0x1f);
      if (iVar14 != (iVar12 - (iVar12 >> 0x1f)) * 0x16) {
        sVar7 = sVar7 + 1;
      }
      sVar7 = (sVar7 + 2) * 0x16 + 0x40;
      sVar16 = (short)*piVar4 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar7) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar16) ^ 0x80000000);
      dVar23 = (double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) * DOUBLE_803313f8;
      **(undefined2 **)&menuPcs->field_0x848 =
           (short)(int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)(int)dVar23;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar7;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar16;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
      memset(menuPcs->m_unk0x838,0,0x120);
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 10) = 0;
    }
    if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) &&
       (iVar14 = *(int *)&menuPcs->field_0x82c, *(short *)(iVar14 + 0x1a) == 0)) {
      if ((uVar6 & 3) == 0) {
        if ((uVar3 & 0x100) == 0) {
          if ((uVar3 & 0x200) != 0) {
            *(undefined2 *)(iVar14 + 0xe) = 0xffff;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 1;
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
        }
        else {
          *(undefined2 *)(iVar14 + 0xe) = 1;
          (menuPcs->m_mcCtrl).m_cardChannel = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
          if ((int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26) == (int)DAT_8032ee20) {
            (menuPcs->m_mcCtrl).m_saveIndex = (int)cRam8032ee21;
          }
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        }
      }
      else {
        *(ushort *)(iVar14 + 0x26) = *(ushort *)(iVar14 + 0x26) ^ 1;
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
    }
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      sVar7 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar7 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar7 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 3:
    uVar8 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
    break;
  case 4:
    if (*(char *)(iVar14 + 9) == '\0') {
      pCVar19 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(FLOAT_803313e8,pCVar19);
      SetShadow__5CFontFi(pCVar19,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar19);
      iVar12 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,0);
      iVar14 = 0;
      piVar4 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,6);
      piVar18 = piVar4;
      for (iVar21 = 0; iVar21 < *piVar4; iVar21 = iVar21 + 1) {
        pcVar10 = *(char **)(iVar12 + *(short *)(piVar18 + 1) * 4);
        if (pcVar10 != (char *)0x0) {
          if (*pcVar10 == '$') {
            pcVar10 = pcVar10 + 1;
          }
          dVar23 = (double)GetWidth__5CFontFPc(pCVar19,pcVar10);
          if (iVar14 < (int)dVar23) {
            iVar14 = (int)dVar23;
          }
        }
        piVar18 = (int *)((int)piVar18 + 2);
      }
      iVar12 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar7 = (short)iVar12 - (short)(iVar12 >> 0x1f);
      if (iVar14 != (iVar12 - (iVar12 >> 0x1f)) * 0x16) {
        sVar7 = sVar7 + 1;
      }
      sVar7 = (sVar7 + 2) * 0x16 + 0x40;
      sVar16 = (short)*piVar4 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar7) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar16) ^ 0x80000000);
      dVar23 = (double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) * DOUBLE_803313f8;
      **(undefined2 **)&menuPcs->field_0x848 =
           (short)(int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)(int)dVar23;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar7;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar16;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
      (menuPcs->m_mcCtrl).m_previousState = 0;
      (menuPcs->m_mcCtrl).m_state = 0;
      (menuPcs->m_mcCtrl).m_lastResult = 0;
      (menuPcs->m_mcCtrl).m_iteration = 0;
      (menuPcs->m_mcCtrl).m_userBuffer = (void *)0x0;
      (menuPcs->m_mcCtrl).m_createFlag = 0;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
    }
    else if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) &&
            (*(short *)(iVar14 + 0x1a) == 0)) {
      uVar8 = ChkEmpty__6McCtrlFi(&menuPcs->m_mcCtrl,0);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
      if (-1 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x2e)) break;
      MemoryCardMan.m_opDoneFlag = '\x01';
      MemoryCardMan.m_currentSlot = 0xff;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0xffff;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
    }
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      sVar7 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar7 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar7 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 5:
  case 6:
  case 7:
  case 9:
  case 10:
  case 0xe:
  case 0xf:
  case 0x14:
  case 0x15:
  case 0x1b:
  case 0x1c:
    if (*(char *)(iVar14 + 9) == '\0') {
      bVar1 = true;
      uVar20 = 0;
      if (iVar12 == 5) {
        uVar17 = 1;
      }
      else if (iVar12 == 6) {
        uVar17 = 2;
      }
      else if (iVar12 == 7) {
        uVar17 = 3;
      }
      else if (iVar12 == 9) {
        uVar17 = 10;
      }
      else if (iVar12 == 10) {
        uVar17 = 0xb;
      }
      else if (iVar12 == 0xe) {
        uVar17 = 0xc;
      }
      else if (iVar12 == 0xf) {
        uVar17 = 0xd;
      }
      else if (iVar12 == 0x1c) {
        uVar20 = 1;
        uVar17 = 0x1b;
      }
      else if (iVar12 == 0x1b) {
        uVar20 = 1;
        uVar17 = 0x1c;
      }
      else if (iVar12 == 0x15) {
        bVar1 = false;
        uVar17 = 0xe;
      }
      else {
        uVar17 = 0xf;
      }
      pCVar19 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(FLOAT_803313e8,pCVar19);
      SetShadow__5CFontFi(pCVar19,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar19);
      iVar12 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,uVar20);
      iVar14 = 0;
      piVar4 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,uVar17);
      piVar18 = piVar4;
      for (iVar21 = 0; iVar21 < *piVar4; iVar21 = iVar21 + 1) {
        pcVar10 = *(char **)(iVar12 + *(short *)(piVar18 + 1) * 4);
        if (pcVar10 != (char *)0x0) {
          if (*pcVar10 == '$') {
            pcVar10 = pcVar10 + 1;
          }
          dVar23 = (double)GetWidth__5CFontFPc(pCVar19,pcVar10);
          if (iVar14 < (int)dVar23) {
            iVar14 = (int)dVar23;
          }
        }
        piVar18 = (int *)((int)piVar18 + 2);
      }
      iVar12 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar7 = (short)iVar12 - (short)(iVar12 >> 0x1f);
      if (iVar14 != (iVar12 - (iVar12 >> 0x1f)) * 0x16) {
        sVar7 = sVar7 + 1;
      }
      sVar7 = (sVar7 + 2) * 0x16 + 0x40;
      sVar16 = (short)*piVar4 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar7) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar16) ^ 0x80000000);
      dVar23 = (double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) * DOUBLE_803313f8;
      **(undefined2 **)&menuPcs->field_0x848 =
           (short)(int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)(int)dVar23;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar7;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar16;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 0;
      if (bVar1) {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
    }
    if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) &&
       (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
      sVar7 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x16);
      if ((sVar7 == 0xe) || (sVar7 == 0x15)) {
        uVar8 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x2e) < 0) goto LAB_800ff5f0;
      }
      else if (sVar7 == 5) {
        uVar8 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
LAB_800ff5f0:
        iVar14 = *(int *)&menuPcs->field_0x82c;
        sVar7 = *(short *)(iVar14 + 0x16);
        if (sVar7 == 5) {
          sVar16 = -1;
        }
        else if (sVar7 == 6) {
          sVar16 = -3;
        }
        else if (sVar7 == 7) {
          sVar16 = -4;
        }
        else {
          sVar16 = 0;
        }
        if (sVar7 == 7) {
          sVar7 = *(short *)(iVar14 + 0x2e);
          if (((sVar7 != 0) && (sVar7 != sVar16)) && (sVar7 != 1)) {
            *(undefined2 *)(iVar14 + 0xe) = 0xffff;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 1;
            break;
          }
        }
        else if ((*(short *)(iVar14 + 0x2e) != sVar16) && (*(short *)(iVar14 + 0x2e) != 1)) {
          *(undefined2 *)(iVar14 + 0xe) = 0xffff;
          *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 1;
          break;
        }
      }
      if ((uVar3 & 0x300) != 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x16) == 0x15) {
          PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
        }
        else {
          PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
        }
      }
    }
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      sVar7 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar7 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar7 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 8:
  case 0xb:
  case 0x12:
  case 0x19:
    if (*(char *)(iVar14 + 9) == '\0') {
      uVar20 = 0;
      if (iVar12 == 8) {
        *(undefined2 *)(iVar14 + 0x26) = 0;
        uVar17 = 4;
      }
      else if (iVar12 == 0xb) {
        uVar17 = 5;
        *(undefined2 *)(iVar14 + 0x26) = 1;
      }
      else if (iVar12 == 0x19) {
        uVar20 = 1;
        uVar17 = 0x19;
        *(undefined2 *)(iVar14 + 0x26) = 1;
      }
      else {
        uVar17 = 0x12;
        *(undefined2 *)(iVar14 + 0x26) = 1;
      }
      pCVar19 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(FLOAT_803313e8,pCVar19);
      SetShadow__5CFontFi(pCVar19,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar19);
      iVar12 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,uVar20);
      iVar14 = 0;
      piVar4 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,uVar17);
      piVar18 = piVar4;
      for (iVar21 = 0; iVar21 < *piVar4; iVar21 = iVar21 + 1) {
        pcVar10 = *(char **)(iVar12 + *(short *)(piVar18 + 1) * 4);
        if (pcVar10 != (char *)0x0) {
          if (*pcVar10 == '$') {
            pcVar10 = pcVar10 + 1;
          }
          dVar23 = (double)GetWidth__5CFontFPc(pCVar19,pcVar10);
          if (iVar14 < (int)dVar23) {
            iVar14 = (int)dVar23;
          }
        }
        piVar18 = (int *)((int)piVar18 + 2);
      }
      iVar12 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar7 = (short)iVar12 - (short)(iVar12 >> 0x1f);
      if (iVar14 != (iVar12 - (iVar12 >> 0x1f)) * 0x16) {
        sVar7 = sVar7 + 1;
      }
      sVar7 = (sVar7 + 2) * 0x16 + 0x40;
      sVar16 = (short)*piVar4 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar7) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar16) ^ 0x80000000);
      dVar23 = (double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) * DOUBLE_803313f8;
      **(undefined2 **)&menuPcs->field_0x848 =
           (short)(int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)(int)dVar23;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar7;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar16;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
    }
    if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) &&
       (iVar14 = *(int *)&menuPcs->field_0x82c, *(short *)(iVar14 + 0x1a) == 0)) {
      if (*(short *)(iVar14 + 0x16) == 0x19) {
        *(undefined2 *)(iVar14 + 0xe) = 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 0x5a;
        break;
      }
      uVar8 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
      iVar14 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar14 + 0x2e) == 0) {
        if ((uVar6 & 3) == 0) {
          if ((uVar3 & 0x100) == 0) {
            if ((uVar3 & 0x200) != 0) {
              *(undefined2 *)(iVar14 + 0x26) = 1;
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0xffff;
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
              PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
            }
          }
          else {
            if (*(short *)(iVar14 + 0x26) == 0) {
              *(undefined2 *)(iVar14 + 0xe) = 1;
            }
            else {
              *(undefined2 *)(iVar14 + 0xe) = 0xffff;
            }
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
        }
        else {
          *(ushort *)(iVar14 + 0x26) = *(ushort *)(iVar14 + 0x26) ^ 1;
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else {
        *(undefined2 *)(iVar14 + 0xe) = 0xffff;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
      }
    }
    if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) &&
       (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) != 0)) {
      if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x16) == 0x19) {
        uVar8 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
      }
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) =
           *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) + -1;
      if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 0xc:
    if (*(char *)(iVar14 + 9) == '\0') {
      *(undefined *)(iVar14 + 9) = 1;
      memset(menuPcs->m_unk0x838,0,0x120);
      (menuPcs->m_mcCtrl).m_previousState = 0;
      (menuPcs->m_mcCtrl).m_state = 0;
      (menuPcs->m_mcCtrl).m_lastResult = 0;
      (menuPcs->m_mcCtrl).m_iteration = 0;
      (menuPcs->m_mcCtrl).m_userBuffer = (void *)0x0;
      (menuPcs->m_mcCtrl).m_createFlag = 0;
    }
    if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) &&
       (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
      uVar8 = LoadMcList__6McCtrlFv(&menuPcs->m_mcCtrl);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
      iVar14 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar14 + 0x2e) == 0) break;
      if (*(short *)(iVar14 + 0x1c) == 8) {
        iVar21 = 0;
        iVar12 = 4;
        iVar13 = 0;
        do {
          if ((*(char *)((int)menuPcs->m_unk0x838 + iVar13 + 0x42) == '\0') &&
             (0 < *(int *)((int)menuPcs->m_unk0x838 + iVar13 + 8))) {
            iVar21 = iVar21 + 1;
          }
          iVar13 = iVar13 + 0x48;
          iVar12 = iVar12 + -1;
        } while (iVar12 != 0);
        if (iVar21 == 0) {
          *(undefined2 *)(iVar14 + 0x2e) = 0xfc19;
        }
      }
      if ((cRam8032ee21 < '\0') || ((int)DAT_8032ee20 != (menuPcs->m_mcCtrl).m_cardChannel)) {
LAB_801002d4:
        puVar5 = menuPcs->m_unk0x838;
        uVar15 = 0;
        if ((*(char *)((int)puVar5 + 0x42) == '\0') && (0 < (int)puVar5[2])) {
          uVar15 = 1;
          if ((*(char *)((int)puVar5 + 0x8a) == '\0') && (0 < (int)puVar5[0x14])) {
            uVar15 = 2;
            if ((*(char *)((int)puVar5 + 0xd2) == '\0') && (0 < (int)puVar5[0x26])) {
              uVar15 = 3;
              if ((*(char *)((int)puVar5 + 0x11a) == '\0') && (0 < (int)puVar5[0x38])) {
                uVar15 = 4;
              }
              else {
                (menuPcs->m_mcCtrl).m_saveIndex = 3;
              }
            }
            else {
              (menuPcs->m_mcCtrl).m_saveIndex = 2;
            }
          }
          else {
            (menuPcs->m_mcCtrl).m_saveIndex = 1;
          }
        }
        else {
          (menuPcs->m_mcCtrl).m_saveIndex = 0;
        }
        if (3 < uVar15) {
          (menuPcs->m_mcCtrl).m_saveIndex = 0;
        }
        *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)(menuPcs->m_mcCtrl).m_saveIndex;
      }
      else {
        uVar11 = (menuPcs->m_mcCtrl).m_serialLo;
        uVar15 = DAT_8032ee2c ^ (menuPcs->m_mcCtrl).m_serialHi;
        if (uVar15 != 0 || DAT_8032ee28 != uVar11) goto LAB_801002d4;
        if (uVar15 == 0 && DAT_8032ee28 == uVar11) {
          (menuPcs->m_mcCtrl).m_saveIndex = (int)cRam8032ee21;
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)(menuPcs->m_mcCtrl).m_saveIndex;
        }
      }
      iVar12 = 0;
      iVar14 = 0;
      iVar21 = 4;
      do {
        if (*(char *)((int)menuPcs->m_unk0x838 + iVar14 + 0x42) != '\0') {
          (menuPcs->m_mcCtrl).m_saveIndex = iVar12;
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)iVar12;
          break;
        }
        iVar14 = iVar14 + 0x48;
        iVar12 = iVar12 + 1;
        iVar21 = iVar21 + -1;
      } while (iVar21 != 0);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
    }
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      sVar7 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar7 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar7 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 0xd:
  case 0x13:
  case 0x1a:
    if (*(char *)(iVar14 + 9) == '\0') {
      uVar20 = 0;
      if (iVar12 == 0xd) {
        uVar17 = 7;
      }
      else if (iVar12 == 0x1a) {
        uVar17 = 0x1a;
        uVar20 = 1;
      }
      else {
        uVar17 = 8;
      }
      pCVar19 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(FLOAT_803313e8,pCVar19);
      SetShadow__5CFontFi(pCVar19,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar19);
      iVar12 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,uVar20);
      iVar14 = 0;
      piVar4 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,uVar17);
      piVar18 = piVar4;
      for (iVar21 = 0; iVar21 < *piVar4; iVar21 = iVar21 + 1) {
        pcVar10 = *(char **)(iVar12 + *(short *)(piVar18 + 1) * 4);
        if (pcVar10 != (char *)0x0) {
          if (*pcVar10 == '$') {
            pcVar10 = pcVar10 + 1;
          }
          dVar23 = (double)GetWidth__5CFontFPc(pCVar19,pcVar10);
          if (iVar14 < (int)dVar23) {
            iVar14 = (int)dVar23;
          }
        }
        piVar18 = (int *)((int)piVar18 + 2);
      }
      iVar12 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar7 = (short)iVar12 - (short)(iVar12 >> 0x1f);
      if (iVar14 != (iVar12 - (iVar12 >> 0x1f)) * 0x16) {
        sVar7 = sVar7 + 1;
      }
      sVar7 = (sVar7 + 2) * 0x16 + 0x40;
      sVar16 = (short)*piVar4 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar7) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar16) ^ 0x80000000);
      dVar23 = (double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) * DOUBLE_803313f8;
      **(undefined2 **)&menuPcs->field_0x848 =
           (short)(int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)(int)dVar23;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar7;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar16;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
      (menuPcs->m_mcCtrl).m_previousState = 0;
      (menuPcs->m_mcCtrl).m_state = 0;
      (menuPcs->m_mcCtrl).m_lastResult = 0;
      (menuPcs->m_mcCtrl).m_iteration = 0;
      (menuPcs->m_mcCtrl).m_userBuffer = (void *)0x0;
      (menuPcs->m_mcCtrl).m_createFlag = 0;
      if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 8) &&
         (*(void **)&menuPcs->field_0x88c != (void *)0x0)) {
        (menuPcs->m_mcCtrl).m_userBuffer = *(void **)&menuPcs->field_0x88c;
      }
      else {
        (menuPcs->m_mcCtrl).m_userBuffer = (void *)0x0;
      }
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
    }
    else if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) &&
            (*(short *)(iVar14 + 0x1a) == 0)) {
      if (iVar12 == 0xd) {
        uVar8 = Format__6McCtrlFi(&menuPcs->m_mcCtrl,1);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x2e) < 0) {
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
        }
      }
      else if (iVar12 == 0x1a) {
        uVar8 = EraseDat__6McCtrlFv(&menuPcs->m_mcCtrl);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x2e) < 0) {
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
        }
      }
      else {
        uVar8 = SaveDat__6McCtrlFv(&menuPcs->m_mcCtrl);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x2e) < 0) {
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
        }
      }
      iVar14 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar14 + 0x2e) == 0) break;
      if (*(short *)(iVar14 + 0x16) == 0x13) {
        if (*(short *)(iVar14 + 0x1c) != 8) {
          DAT_8032ee28 = (menuPcs->m_mcCtrl).m_serialLo;
          DAT_8032ee2c = (menuPcs->m_mcCtrl).m_serialHi;
          DAT_8032ee20 = (char)(menuPcs->m_mcCtrl).m_cardChannel;
          cRam8032ee21 = (char)(menuPcs->m_mcCtrl).m_saveIndex;
        }
        menuPcs->m_unk0x838[(menuPcs->m_mcCtrl).m_saveIndex * 0x12 + 2] = Game.game.m_gameWork._8_4_
        ;
      }
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
    }
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      sVar7 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar7 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar7 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 0x11:
    uVar8 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar8;
    iVar14 = *(int *)&menuPcs->field_0x82c;
    if ((*(short *)(iVar14 + 0x2e) == 0) && (uVar6 != 0)) {
      if ((uVar6 & 8) == 0) {
        if ((uVar6 & 4) != 0) {
          if (*(short *)(iVar14 + 0x26) < 3) {
            *(short *)(iVar14 + 0x26) = *(short *)(iVar14 + 0x26) + 1;
          }
          else {
            *(undefined2 *)(iVar14 + 0x26) = 0;
          }
          PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
        }
      }
      else {
        if (*(short *)(iVar14 + 0x26) < 1) {
          *(undefined2 *)(iVar14 + 0x26) = 3;
        }
        else {
          *(short *)(iVar14 + 0x26) = *(short *)(iVar14 + 0x26) + -1;
        }
        PlaySe__6CSoundFiiii(&Sound,1,0x40,0x7f,0);
      }
      if ((uVar6 & 0xc) == 0) {
        if ((uVar3 & 0x100) != 0) {
          sVar7 = *(short *)(*(int *)&menuPcs->field_0x82c + 0xe);
          if ((sVar7 != -1) && (sVar7 != 1)) {
            (menuPcs->m_mcCtrl).m_saveIndex = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 1;
            PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
          }
        }
        if ((uVar3 & 0x200) != 0) {
          sVar7 = *(short *)(*(int *)&menuPcs->field_0x82c + 0xe);
          if ((sVar7 != -1) && (sVar7 != 1)) {
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0xffff;
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
        }
      }
    }
  }
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x16) != 0) {
    CalcMcObj__8CMenuPcsFv(menuPcs);
  }
  return;
}

