// Function: CalcLoadMenu__8CMenuPcsFv
// Entry: 800fcfb4
// Size: 7148 bytes

/* WARNING: Removing unreachable block (ram,0x800feb84) */
/* WARNING: Removing unreachable block (ram,0x800fcfc4) */
/* WARNING: Removing unreachable block (ram,0x800fe778) */
/* WARNING: Removing unreachable block (ram,0x800fe46c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcLoadMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  ushort uVar4;
  ushort uVar7;
  int *piVar5;
  short sVar8;
  undefined2 uVar9;
  int iVar6;
  int iVar10;
  uint uVar11;
  char *pcVar12;
  undefined4 *puVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  short sVar18;
  undefined4 uVar19;
  int *piVar20;
  CFont *pCVar21;
  undefined4 uVar22;
  int iVar23;
  CMenuPcs *pCVar24;
  int iVar25;
  double dVar26;
  double dVar27;
  int local_f8 [40];
  undefined8 local_58;
  double local_50;
  double local_48;
  double local_40;
  
  bVar1 = false;
  menuPcs->field_0x86e = 0;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar1 = true;
  }
  if (bVar1) {
    uVar4 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    uVar4 = Pad._8_2_;
  }
  uVar7 = GetButtonRepeat__8CMenuPcsFi(menuPcs,0);
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 8) == '\0') {
    *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
    fVar3 = FLOAT_803313e8;
    fVar2 = FLOAT_803313dc;
    *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 6) = 0x10;
    *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 8) = 0xe8;
    *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 10) = 0x168;
    *(float *)(*(int *)&menuPcs->field_0x820 + 0xc) = fVar2;
    *(float *)(*(int *)&menuPcs->field_0x820 + 0x10) = fVar2;
    *(float *)(*(int *)&menuPcs->field_0x820 + 0x14) = fVar3;
    *(float *)(*(int *)&menuPcs->field_0x820 + 0x18) = fVar3;
    *(undefined4 *)(*(int *)&menuPcs->field_0x820 + 0x1c) = 0;
    iVar14 = *(int *)&menuPcs->field_0x820;
    *(undefined2 *)(iVar14 + 0x20) = *(undefined2 *)(iVar14 + 4);
    *(undefined2 *)(iVar14 + 0x22) = *(undefined2 *)(iVar14 + 6);
    *(undefined2 *)(iVar14 + 0x24) = *(undefined2 *)(iVar14 + 8);
    *(undefined2 *)(iVar14 + 0x26) = *(undefined2 *)(iVar14 + 10);
    *(undefined4 *)(iVar14 + 0x28) = *(undefined4 *)(iVar14 + 0xc);
    *(undefined4 *)(iVar14 + 0x2c) = *(undefined4 *)(iVar14 + 0x10);
    *(undefined4 *)(iVar14 + 0x30) = *(undefined4 *)(iVar14 + 0x14);
    *(undefined4 *)(iVar14 + 0x34) = *(undefined4 *)(iVar14 + 0x18);
    *(undefined4 *)(iVar14 + 0x38) = *(undefined4 *)(iVar14 + 0x1c);
    iVar14 = *(int *)&menuPcs->field_0x820;
    *(short *)(iVar14 + 0x20) = 0x280 - (*(short *)(iVar14 + 8) + *(short *)(iVar14 + 4));
    *(undefined4 *)(*(int *)&menuPcs->field_0x820 + 0x38) = 8;
    (menuPcs->m_mcCtrl).m_previousState = 0;
    (menuPcs->m_mcCtrl).m_state = 0;
    (menuPcs->m_mcCtrl).m_lastResult = 0;
    (menuPcs->m_mcCtrl).m_iteration = 0;
    (menuPcs->m_mcCtrl).m_userBuffer = (void *)0x0;
    (menuPcs->m_mcCtrl).m_createFlag = 0;
    (menuPcs->m_mcCtrl).m_cardChannel = 0;
    (menuPcs->m_mcCtrl).m_saveIndex = 0;
    memset(menuPcs->m_unk0x838,0,0x120);
    iVar14 = *(int *)&menuPcs->field_0x82c;
    Game.game.m_gameWork.m_wmBackupParams[0] = (int32_t)*(short *)(iVar14 + 0x36);
    Game.game.m_gameWork.m_wmBackupParams[1] = (int32_t)*(short *)(iVar14 + 0x38);
    Game.game.m_gameWork.m_wmBackupParams[2] = (int32_t)*(short *)(iVar14 + 0x3a);
    Game.game.m_gameWork.m_wmBackupParams[3] = (int32_t)*(short *)(iVar14 + 0x3c);
    if ((*(short *)(iVar14 + 0x1c) == 8) && ((byte)menuPcs->field_0x889 != 0)) {
      (menuPcs->m_mcCtrl).m_cardChannel = (byte)menuPcs->field_0x889 - 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x16) = 3;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
    }
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 10) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
  }
  dVar27 = DOUBLE_80331408;
  iVar14 = *(int *)&menuPcs->field_0x82c;
  sVar8 = *(short *)(iVar14 + 0x10);
  if (sVar8 == 0) {
    uVar15 = (int)*(short *)(iVar14 + 0x22) - 10;
  }
  else if ((sVar8 < 1) || (3 < sVar8)) {
    uVar15 = -(int)*(short *)(iVar14 + 0x22);
  }
  else {
    uVar15 = 0;
  }
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
  iVar10 = *(int *)&menuPcs->field_0x820;
  local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar10 + 8) + (int)*(short *)(iVar10 + 4))
                     ^ 0x80000000);
  iVar14 = (int)(FLOAT_803313e0 - (float)(local_58 - dVar27));
  local_50 = (double)(longlong)iVar14;
  *(short *)(iVar10 + 0x20) = (short)iVar14;
  if ((int)uVar15 < 0) {
    local_50 = (double)(CONCAT44(0x43300000,
                                 (int)*(short *)(*(int *)&menuPcs->field_0x820 + 8) +
                                 (int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^ 0x80000000);
    dVar26 = (double)(float)(local_50 - dVar27);
    if (-0xb < (int)uVar15) {
      uVar11 = (int)uVar15 >> 0x1f;
      local_50 = (double)(CONCAT44(0x43300000,(uVar11 ^ uVar15) - uVar11) ^ 0x80000000);
      uVar11 = (uVar11 ^ uVar15) - uVar11;
      dVar27 = (double)(float)(dVar26 * DOUBLE_803314e8 * (local_50 - dVar27));
      if ((int)uVar11 < 0) {
        uVar11 = 0;
      }
      if (10 < (int)uVar11) {
        uVar11 = 10;
      }
      local_58 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
      dVar26 = (double)sin((double)(FLOAT_803314bc *
                                   (float)(local_58 - DOUBLE_80331408) * FLOAT_803316d4));
      dVar26 = (double)(float)(dVar27 * (double)(float)dVar26);
    }
    dVar27 = DOUBLE_80331408;
    local_50 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x820 + 4)) ^
                       0x80000000);
    iVar14 = (int)((double)(float)(local_50 - DOUBLE_80331408) - dVar26);
    local_58 = (double)(longlong)iVar14;
    *(short *)(*(int *)&menuPcs->field_0x820 + 4) = (short)iVar14;
    local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x820 + 0x20)) ^
                       0x80000000);
    iVar14 = (int)((double)(float)(local_48 - dVar27) + dVar26);
    local_40 = (double)(longlong)iVar14;
    *(short *)(*(int *)&menuPcs->field_0x820 + 0x20) = (short)iVar14;
  }
  fVar2 = FLOAT_803313e8;
  iVar14 = *(int *)&menuPcs->field_0x82c;
  if (*(short *)(iVar14 + 0x10) != 2) {
    return;
  }
  iVar10 = (int)*(short *)(iVar14 + 0x16);
  switch(iVar10) {
  case 0:
  case 2:
    if (*(char *)(iVar14 + 9) == '\0') {
      *(short *)(iVar14 + 0x26) = (short)(menuPcs->m_mcCtrl).m_cardChannel;
      pCVar21 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(fVar2,pCVar21);
      SetShadow__5CFontFi(pCVar21,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar21);
      iVar10 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,0);
      iVar14 = 0;
      piVar5 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,0);
      piVar20 = piVar5;
      for (iVar23 = 0; iVar23 < *piVar5; iVar23 = iVar23 + 1) {
        pcVar12 = *(char **)(iVar10 + *(short *)(piVar20 + 1) * 4);
        if (pcVar12 != (char *)0x0) {
          if (*pcVar12 == '$') {
            pcVar12 = pcVar12 + 1;
          }
          dVar27 = (double)GetWidth__5CFontFPc(pCVar21,pcVar12);
          iVar25 = (int)dVar27;
          local_40 = (double)(longlong)iVar25;
          if (iVar14 < iVar25) {
            iVar14 = iVar25;
          }
        }
        piVar20 = (int *)((int)piVar20 + 2);
      }
      iVar10 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar8 = (short)iVar10 - (short)(iVar10 >> 0x1f);
      if (iVar14 != (iVar10 - (iVar10 >> 0x1f)) * 0x16) {
        sVar8 = sVar8 + 1;
      }
      sVar8 = (sVar8 + 2) * 0x16 + 0x40;
      sVar18 = (short)*piVar5 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar8) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar18) ^ 0x80000000);
      iVar14 = (int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      local_48 = (double)(longlong)iVar14;
      iVar10 = (int)((double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) *
                    DOUBLE_803313f8);
      local_58 = (double)(longlong)iVar10;
      **(undefined2 **)&menuPcs->field_0x848 = (short)iVar14;
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)iVar10;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar8;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar18;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
      memset(menuPcs->m_unk0x838,0,0x120);
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 10) = 0;
    }
    if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) &&
       (iVar14 = *(int *)&menuPcs->field_0x82c, *(short *)(iVar14 + 0x1a) == 0)) {
      if ((uVar7 & 3) == 0) {
        if ((uVar4 & 0x100) == 0) {
          if ((uVar4 & 0x200) != 0) {
            *(undefined2 *)(iVar14 + 0xe) = 0xffff;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 1;
            PlaySe__6CSoundFiiii(&Sound,3,0x40,0x7f,0);
          }
        }
        else {
          *(undefined2 *)(iVar14 + 0xe) = 1;
          (menuPcs->m_mcCtrl).m_cardChannel = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
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
      sVar8 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar8 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar8 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 3:
    uVar9 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
    break;
  case 4:
    if (*(char *)(iVar14 + 9) == '\0') {
      pCVar21 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(FLOAT_803313e8,pCVar21);
      SetShadow__5CFontFi(pCVar21,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar21);
      iVar10 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,0);
      iVar14 = 0;
      piVar5 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,6);
      piVar20 = piVar5;
      for (iVar23 = 0; iVar23 < *piVar5; iVar23 = iVar23 + 1) {
        pcVar12 = *(char **)(iVar10 + *(short *)(piVar20 + 1) * 4);
        if (pcVar12 != (char *)0x0) {
          if (*pcVar12 == '$') {
            pcVar12 = pcVar12 + 1;
          }
          dVar27 = (double)GetWidth__5CFontFPc(pCVar21,pcVar12);
          iVar25 = (int)dVar27;
          local_40 = (double)(longlong)iVar25;
          if (iVar14 < iVar25) {
            iVar14 = iVar25;
          }
        }
        piVar20 = (int *)((int)piVar20 + 2);
      }
      iVar10 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar8 = (short)iVar10 - (short)(iVar10 >> 0x1f);
      if (iVar14 != (iVar10 - (iVar10 >> 0x1f)) * 0x16) {
        sVar8 = sVar8 + 1;
      }
      sVar8 = (sVar8 + 2) * 0x16 + 0x40;
      sVar18 = (short)*piVar5 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar8) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar18) ^ 0x80000000);
      iVar14 = (int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      local_48 = (double)(longlong)iVar14;
      iVar10 = (int)((double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) *
                    DOUBLE_803313f8);
      local_58 = (double)(longlong)iVar10;
      **(undefined2 **)&menuPcs->field_0x848 = (short)iVar14;
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)iVar10;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar8;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar18;
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
      uVar9 = ChkEmpty__6McCtrlFi(&menuPcs->m_mcCtrl,1);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
      if (-1 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x2e)) break;
      MemoryCardMan.m_opDoneFlag = '\x01';
      MemoryCardMan.m_currentSlot = 0xff;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 0xffff;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
    }
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      sVar8 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar8 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar8 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 5:
  case 6:
  case 7:
  case 10:
  case 0xe:
  case 0xf:
  case 0x10:
  case 0x17:
  case 0x18:
  case 0x1b:
  case 0x1c:
    if (*(char *)(iVar14 + 9) == '\0') {
      bVar1 = true;
      uVar22 = 0;
      if (iVar10 == 5) {
        uVar19 = 1;
      }
      else if (iVar10 == 6) {
        uVar19 = 2;
      }
      else if (iVar10 == 7) {
        uVar19 = 3;
      }
      else if (iVar10 == 10) {
        uVar19 = 0xb;
      }
      else if (iVar10 == 0xe) {
        uVar19 = 0xc;
      }
      else if (iVar10 == 0xf) {
        uVar19 = 0xd;
      }
      else if (iVar10 == 0x1c) {
        uVar19 = 0x1b;
        uVar22 = 1;
      }
      else if (iVar10 == 0x1b) {
        uVar19 = 0x1c;
        uVar22 = 1;
      }
      else if (iVar10 == 0x18) {
        bVar1 = false;
        uVar19 = 0x10;
      }
      else if (iVar10 == 0x17) {
        uVar19 = 0x11;
      }
      else {
        uVar19 = 0x13;
      }
      if (bVar1) {
        PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
      }
      pCVar21 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(FLOAT_803313e8,pCVar21);
      SetShadow__5CFontFi(pCVar21,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar21);
      iVar10 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,uVar22);
      iVar14 = 0;
      piVar5 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,uVar19);
      piVar20 = piVar5;
      for (iVar23 = 0; iVar23 < *piVar5; iVar23 = iVar23 + 1) {
        pcVar12 = *(char **)(iVar10 + *(short *)(piVar20 + 1) * 4);
        if (pcVar12 != (char *)0x0) {
          if (*pcVar12 == '$') {
            pcVar12 = pcVar12 + 1;
          }
          dVar27 = (double)GetWidth__5CFontFPc(pCVar21,pcVar12);
          iVar25 = (int)dVar27;
          local_40 = (double)(longlong)iVar25;
          if (iVar14 < iVar25) {
            iVar14 = iVar25;
          }
        }
        piVar20 = (int *)((int)piVar20 + 2);
      }
      iVar10 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar8 = (short)iVar10 - (short)(iVar10 >> 0x1f);
      if (iVar14 != (iVar10 - (iVar10 >> 0x1f)) * 0x16) {
        sVar8 = sVar8 + 1;
      }
      sVar8 = (sVar8 + 2) * 0x16 + 0x40;
      sVar18 = (short)*piVar5 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar8) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar18) ^ 0x80000000);
      iVar14 = (int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      local_48 = (double)(longlong)iVar14;
      iVar10 = (int)((double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) *
                    DOUBLE_803313f8);
      local_58 = (double)(longlong)iVar10;
      **(undefined2 **)&menuPcs->field_0x848 = (short)iVar14;
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)iVar10;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar8;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar18;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 8) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 3;
      *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 0;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 9) = 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 0;
    }
    if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) &&
       (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
      sVar8 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x16);
      if (sVar8 == 0xe) {
        uVar9 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x2e) < 0) {
LAB_800fd9f4:
          iVar14 = *(int *)&menuPcs->field_0x82c;
          sVar8 = *(short *)(iVar14 + 0x16);
          if (sVar8 == 5) {
            sVar18 = -1;
          }
          else if (sVar8 == 6) {
            sVar18 = -3;
          }
          else if (sVar8 == 7) {
            sVar18 = -4;
          }
          else {
            sVar18 = 0;
          }
          if (sVar8 == 7) {
            sVar8 = *(short *)(iVar14 + 0x2e);
            if (((sVar8 != 0) && (sVar8 != sVar18)) && (sVar8 != 1)) {
              *(undefined2 *)(iVar14 + 0xe) = 0xffff;
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 1;
              break;
            }
          }
          else if ((*(short *)(iVar14 + 0x2e) != sVar18) && (*(short *)(iVar14 + 0x2e) != 1)) {
            *(undefined2 *)(iVar14 + 0xe) = 0xffff;
            *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 1;
            break;
          }
        }
      }
      else if (sVar8 == 5) {
        uVar9 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
        goto LAB_800fd9f4;
      }
      if ((uVar4 & 0x300) != 0) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 1;
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
        PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
      }
    }
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      sVar8 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar8 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar8 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 8:
  case 0xb:
  case 0x19:
    if (*(char *)(iVar14 + 9) == '\0') {
      uVar22 = 0;
      if (iVar10 == 8) {
        *(undefined2 *)(iVar14 + 0x26) = 0;
        uVar19 = 4;
      }
      else if (iVar10 == 0x19) {
        uVar22 = 1;
        uVar19 = 0x19;
        *(undefined2 *)(iVar14 + 0x26) = 1;
      }
      else {
        uVar19 = 5;
        *(undefined2 *)(iVar14 + 0x26) = 1;
      }
      pCVar21 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(FLOAT_803313e8,pCVar21);
      SetShadow__5CFontFi(pCVar21,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar21);
      iVar10 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,uVar22);
      iVar14 = 0;
      piVar5 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,uVar19);
      piVar20 = piVar5;
      for (iVar23 = 0; iVar23 < *piVar5; iVar23 = iVar23 + 1) {
        pcVar12 = *(char **)(iVar10 + *(short *)(piVar20 + 1) * 4);
        if (pcVar12 != (char *)0x0) {
          if (*pcVar12 == '$') {
            pcVar12 = pcVar12 + 1;
          }
          dVar27 = (double)GetWidth__5CFontFPc(pCVar21,pcVar12);
          iVar25 = (int)dVar27;
          local_40 = (double)(longlong)iVar25;
          if (iVar14 < iVar25) {
            iVar14 = iVar25;
          }
        }
        piVar20 = (int *)((int)piVar20 + 2);
      }
      iVar10 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar8 = (short)iVar10 - (short)(iVar10 >> 0x1f);
      if (iVar14 != (iVar10 - (iVar10 >> 0x1f)) * 0x16) {
        sVar8 = sVar8 + 1;
      }
      sVar8 = (sVar8 + 2) * 0x16 + 0x40;
      sVar18 = (short)*piVar5 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar8) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar18) ^ 0x80000000);
      iVar14 = (int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      local_48 = (double)(longlong)iVar14;
      iVar10 = (int)((double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) *
                    DOUBLE_803313f8);
      local_58 = (double)(longlong)iVar10;
      **(undefined2 **)&menuPcs->field_0x848 = (short)iVar14;
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)iVar10;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar8;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar18;
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
      uVar9 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
      iVar14 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar14 + 0x2e) == 0) {
        if ((uVar7 & 3) == 0) {
          if ((uVar4 & 0x100) == 0) {
            if ((uVar4 & 0x200) != 0) {
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
        uVar9 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
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
      uVar9 = LoadMcList__6McCtrlFv(&menuPcs->m_mcCtrl);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
      iVar14 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar14 + 0x2e) == 0) break;
      if (*(short *)(iVar14 + 0x1c) == 8) {
        iVar23 = 0;
        iVar10 = 4;
        iVar25 = 0;
        do {
          if ((*(char *)((int)menuPcs->m_unk0x838 + iVar25 + 0x42) == '\0') &&
             (0 < *(int *)((int)menuPcs->m_unk0x838 + iVar25 + 8))) {
            iVar23 = iVar23 + 1;
          }
          iVar25 = iVar25 + 0x48;
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
        if (iVar23 == 0) {
          *(undefined2 *)(iVar14 + 0x2e) = 0xfc19;
        }
      }
      piVar5 = local_f8;
      iVar10 = 0;
      iVar14 = 0;
      piVar20 = piVar5;
      do {
        puVar13 = (undefined4 *)((int)menuPcs->m_unk0x838 + iVar14);
        OSTicksToCalendarTime(*puVar13,puVar13[1],piVar20);
        iVar10 = iVar10 + 1;
        piVar20 = piVar20 + 10;
        iVar14 = iVar14 + 0x48;
      } while (iVar10 < 4);
      iVar23 = 0;
      iVar10 = 0;
      iVar25 = 4;
      iVar14 = -1;
      do {
        iVar17 = iVar14;
        if (((*(char *)((int)menuPcs->m_unk0x838 + iVar10 + 0x42) == '\0') &&
            (0 < *(int *)((int)menuPcs->m_unk0x838 + iVar10 + 8))) && (iVar17 = iVar23, -1 < iVar14)
           ) {
          iVar17 = iVar14;
          if ((local_f8[iVar14 * 10 + 5] <= piVar5[5]) &&
             ((local_f8[iVar14 * 10 + 5] < piVar5[5] ||
              ((local_f8[iVar14 * 10 + 7] <= piVar5[7] &&
               ((local_f8[iVar14 * 10 + 7] < piVar5[7] ||
                ((local_f8[iVar14 * 10 + 2] <= piVar5[2] &&
                 ((local_f8[iVar14 * 10 + 2] < piVar5[2] ||
                  ((local_f8[iVar14 * 10 + 1] <= piVar5[1] &&
                   ((local_f8[iVar14 * 10 + 1] < piVar5[1] ||
                    ((local_f8[iVar14 * 10] <= *piVar5 &&
                     ((local_f8[iVar14 * 10] < *piVar5 ||
                      ((local_f8[iVar14 * 10 + 8] <= piVar5[8] &&
                       ((local_f8[iVar14 * 10 + 8] < piVar5[8] ||
                        (local_f8[iVar14 * 10 + 9] < piVar5[9])))))))))))))))))))))))) {
            iVar17 = iVar23;
          }
        }
        iVar10 = iVar10 + 0x48;
        piVar5 = piVar5 + 10;
        iVar23 = iVar23 + 1;
        iVar25 = iVar25 + -1;
        iVar14 = iVar17;
      } while (iVar25 != 0);
      if (iVar17 < 0) {
        iVar17 = 0;
      }
      iVar10 = 0;
      iVar14 = 0;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)iVar17;
      iVar23 = 4;
      do {
        if (*(char *)((int)menuPcs->m_unk0x838 + iVar14 + 0x42) != '\0') {
          (menuPcs->m_mcCtrl).m_saveIndex = iVar10;
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = (short)iVar10;
          break;
        }
        iVar14 = iVar14 + 0x48;
        iVar10 = iVar10 + 1;
        iVar23 = iVar23 + -1;
      } while (iVar23 != 0);
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
    }
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      sVar8 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar8 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar8 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 0xd:
  case 0x16:
  case 0x1a:
    if (*(char *)(iVar14 + 9) == '\0') {
      uVar22 = 0;
      if (iVar10 == 0xd) {
        uVar19 = 7;
      }
      else if (iVar10 == 0x1a) {
        uVar19 = 0x1a;
        uVar22 = 1;
      }
      else {
        uVar19 = 9;
      }
      pCVar21 = *(CFont **)&menuPcs->field_0xf8;
      SetMargin__5CFontFf(FLOAT_803313e8,pCVar21);
      SetShadow__5CFontFi(pCVar21,0);
      SetScale__5CFontFf(FLOAT_803313e8,pCVar21);
      iVar10 = GetMcWinMessBuff__8CMenuPcsFi(menuPcs,uVar22);
      iVar14 = 0;
      piVar5 = (int *)GetWinMess__8CMenuPcsFi(menuPcs,uVar19);
      piVar20 = piVar5;
      for (iVar23 = 0; iVar23 < *piVar5; iVar23 = iVar23 + 1) {
        pcVar12 = *(char **)(iVar10 + *(short *)(piVar20 + 1) * 4);
        if (pcVar12 != (char *)0x0) {
          if (*pcVar12 == '$') {
            pcVar12 = pcVar12 + 1;
          }
          dVar27 = (double)GetWidth__5CFontFPc(pCVar21,pcVar12);
          iVar25 = (int)dVar27;
          local_40 = (double)(longlong)iVar25;
          if (iVar14 < iVar25) {
            iVar14 = iVar25;
          }
        }
        piVar20 = (int *)((int)piVar20 + 2);
      }
      iVar10 = iVar14 / 0x16 + (iVar14 >> 0x1f);
      sVar8 = (short)iVar10 - (short)(iVar10 >> 0x1f);
      if (iVar14 != (iVar10 - (iVar10 >> 0x1f)) * 0x16) {
        sVar8 = sVar8 + 1;
      }
      sVar8 = (sVar8 + 2) * 0x16 + 0x40;
      sVar18 = (short)*piVar5 * 0x1e + 0x40;
      local_40 = (double)(CONCAT44(0x43300000,0x280 - sVar8) ^ 0x80000000);
      local_50 = (double)(CONCAT44(0x43300000,(int)sVar18) ^ 0x80000000);
      iVar14 = (int)((double)(float)(local_40 - DOUBLE_80331408) * DOUBLE_803313f8);
      local_48 = (double)(longlong)iVar14;
      iVar10 = (int)((double)(FLOAT_80331430 - (float)(local_50 - DOUBLE_80331408)) *
                    DOUBLE_803313f8);
      local_58 = (double)(longlong)iVar10;
      **(undefined2 **)&menuPcs->field_0x848 = (short)iVar14;
      *(short *)(*(int *)&menuPcs->field_0x848 + 2) = (short)iVar10;
      *(short *)(*(int *)&menuPcs->field_0x848 + 4) = sVar8;
      *(short *)(*(int *)&menuPcs->field_0x848 + 6) = sVar18;
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
      if (iVar10 == 0xd) {
        uVar9 = Format__6McCtrlFi(&menuPcs->m_mcCtrl,1);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x2e) < 0) {
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
        }
      }
      else if (iVar10 == 0x1a) {
        uVar9 = EraseDat__6McCtrlFv(&menuPcs->m_mcCtrl);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x2e) < 0) {
          MemoryCardMan.m_opDoneFlag = '\x01';
          MemoryCardMan.m_currentSlot = 0xff;
        }
      }
      else {
        uVar9 = LoadDat__6McCtrlFv(&menuPcs->m_mcCtrl);
        *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
      }
      iVar14 = *(int *)&menuPcs->field_0x82c;
      if (*(short *)(iVar14 + 0x2e) == 0) break;
      if (*(short *)(iVar14 + 0x16) == 0x16) {
        if ((*(short *)(iVar14 + 0x1c) == 8) || (*(short *)(iVar14 + 0x2e) != 1)) {
          DAT_8032ee24 = (undefined)(menuPcs->m_mcCtrl).m_cardChannel;
          uRam8032ee25 = (undefined)(menuPcs->m_mcCtrl).m_saveIndex;
        }
        else {
          DAT_8032ee28 = (menuPcs->m_mcCtrl).m_serialLo;
          DAT_8032ee2c = (menuPcs->m_mcCtrl).m_serialHi;
          DAT_8032ee20 = (undefined)(menuPcs->m_mcCtrl).m_cardChannel;
          uRam8032ee21 = (undefined)(menuPcs->m_mcCtrl).m_saveIndex;
        }
        iVar10 = 0;
        iVar25 = -0x7fde1140;
        iVar23 = 0;
        iVar14 = 0;
        pCVar24 = menuPcs;
        do {
          iVar17 = *(int *)&menuPcs->field_0x824 + iVar10;
          if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) == 8) &&
             (*(int *)&menuPcs->field_0x88c != 0)) {
            iVar6 = *(int *)&menuPcs->field_0x88c + iVar23 + 0x14d0;
            if (*(int *)(iVar6 + 0x5b4) == 0) {
              uVar15 = 0xffffffff;
              *(undefined4 *)(iVar17 + 8) = 0xffffffff;
              uVar16 = 0xffffffff;
              uVar11 = 0xffffffff;
            }
            else {
              uVar15 = (uint)*(ushort *)(iVar6 + 0x2e);
              uVar16 = (uint)*(ushort *)(iVar6 + 0x32);
              uVar11 = (uint)*(ushort *)(iVar6 + 0x30);
            }
          }
          else if (*(int *)(iVar25 + 0x1794) == 0) {
            uVar15 = 0xffffffff;
            *(undefined4 *)(iVar17 + 8) = 0xffffffff;
            uVar16 = 0xffffffff;
            uVar11 = 0xffffffff;
          }
          else {
            uVar15 = (uint)*(ushort *)(iVar25 + 0x17d0);
            uVar11 = (uint)*(ushort *)(iVar25 + 0x17d2);
            uVar16 = (uint)*(ushort *)(iVar25 + 0x17d4);
            iVar6 = uVar15 * 200 + 100;
            if (uVar11 != 0) {
              iVar6 = uVar15 * 200 + 200;
            }
            *(uint *)(iVar17 + 8) = iVar6 + uVar16;
          }
          iVar17 = *(int *)&menuPcs->field_0x824 + iVar10;
          if ((int)uVar15 < 0) {
            uVar22 = 3;
            *(undefined *)(iVar17 + 0xc) = 0;
            iVar6 = 0x43;
          }
          else {
            uVar22 = 0;
            iVar6 = uVar15 * 200 + 100;
            if (uVar11 != 0) {
              iVar6 = uVar15 * 200 + 200;
            }
            iVar6 = iVar6 + uVar16;
            *(undefined *)(iVar17 + 0xc) = 1;
          }
          LoadModelASync__Q29CCharaPcs7CHandleFiUlUl
                    (*(CCharaPcsCHandle **)&pCVar24->field_0x7f4,uVar22,iVar6,0);
          iVar14 = iVar14 + 1;
          iVar23 = iVar23 + 0x9c0;
          iVar25 = iVar25 + 0xc30;
          pCVar24 = (CMenuPcs *)&pCVar24->field_0x4;
          iVar10 = iVar10 + 0x34;
        } while (iVar14 < 8);
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1c) != 8) {
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x36) =
               (short)Game.game.m_gameWork.m_wmBackupParams[0];
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x3e) =
               (short)Game.game.m_gameWork.m_wmBackupParams[0];
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x38) =
               (short)Game.game.m_gameWork.m_wmBackupParams[1];
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x40) =
               (short)Game.game.m_gameWork.m_wmBackupParams[1];
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x3a) =
               (short)Game.game.m_gameWork.m_wmBackupParams[2];
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x42) =
               (short)Game.game.m_gameWork.m_wmBackupParams[2];
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x3c) =
               (short)Game.game.m_gameWork.m_wmBackupParams[3];
          *(short *)(*(int *)&menuPcs->field_0x82c + 0x44) =
               (short)Game.game.m_gameWork.m_wmBackupParams[3];
        }
      }
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x1a) = 10;
    }
    if (*(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1) {
      sVar8 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a);
      if ((sVar8 != 0) &&
         (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) = sVar8 + -1,
         *(short *)(*(int *)&menuPcs->field_0x82c + 0x1a) == 0)) {
        *(undefined2 *)(*(int *)&menuPcs->field_0x848 + 10) = 2;
      }
    }
    break;
  case 0x11:
    uVar9 = McChkConnect__14CMemoryCardManFi(&MemoryCardMan,(menuPcs->m_mcCtrl).m_cardChannel);
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x2e) = uVar9;
    iVar14 = *(int *)&menuPcs->field_0x82c;
    if ((*(short *)(iVar14 + 0x2e) == 0) && (uVar7 != 0)) {
      if ((uVar7 & 8) == 0) {
        if ((uVar7 & 4) != 0) {
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
      if ((uVar7 & 0xc) == 0) {
        if ((uVar4 & 0x100) != 0) {
          sVar8 = *(short *)(*(int *)&menuPcs->field_0x82c + 0xe);
          if ((sVar8 != -1) && (sVar8 != 1)) {
            iVar14 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
            if ((*(char *)((int)menuPcs->m_unk0x838 + iVar14 * 0x48 + 0x41) == '\0') ||
               (*(char *)((int)menuPcs->m_unk0x838 + iVar14 * 0x48 + 0x42) != '\0')) {
              PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
            }
            else {
              (menuPcs->m_mcCtrl).m_saveIndex = iVar14;
              *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0xe) = 1;
              PlaySe__6CSoundFiiii(&Sound,2,0x40,0x7f,0);
            }
          }
        }
        if ((uVar4 & 0x200) != 0) {
          sVar8 = *(short *)(*(int *)&menuPcs->field_0x82c + 0xe);
          if ((sVar8 != -1) && (sVar8 != 1)) {
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

