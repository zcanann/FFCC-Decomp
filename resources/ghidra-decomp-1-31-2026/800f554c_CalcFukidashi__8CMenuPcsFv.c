// Function: CalcFukidashi__8CMenuPcsFv
// Entry: 800f554c
// Size: 4080 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcFukidashi__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  float fVar2;
  ushort uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  double dVar8;
  int iVar9;
  undefined *puVar10;
  int iVar11;
  float *pfVar12;
  int iVar13;
  float *pfVar14;
  short sVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  undefined4 *puVar20;
  uint uVar21;
  CFont *font;
  short sVar22;
  CFont *font_00;
  double dVar23;
  Mtx MStack_1e8;
  Mtx MStack_1b8;
  Mtx MStack_188;
  Mtx MStack_158;
  undefined local_128 [64];
  undefined auStack_e8 [64];
  char local_a8 [64];
  Mtx MStack_68;
  undefined4 local_38;
  uint uStack_34;
  undefined8 local_30;
  
  fVar1 = FLOAT_803313dc;
  if (menuPcs->field_0x9 == '\x01') {
    **(undefined2 **)&menuPcs->field_0x818 = *(undefined2 *)&menuPcs->field_0x1c;
    *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 2) = *(undefined2 *)&menuPcs->field_0x1e;
    *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 4) = 0xf0;
    *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 6) = 0xc4;
    *(float *)(*(int *)&menuPcs->field_0x818 + 0xc) = fVar1;
    if ((menuPcs->field_0x8 == '\x02') || (menuPcs->field_0x8 == '\x03')) {
      *(float *)(*(int *)&menuPcs->field_0x818 + 8) = FLOAT_803313dc;
    }
    else {
      *(float *)(*(int *)&menuPcs->field_0x818 + 8) = FLOAT_80331704;
    }
    fVar1 = FLOAT_80331708;
    if ((*(ushort *)&menuPcs->field_0x1a & 0x3f0) != 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x20) = 0x50;
      fVar2 = FLOAT_803313dc;
      *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x22) = 0x48;
      *(float *)(*(int *)&menuPcs->field_0x818 + 0x24) = fVar1;
      *(float *)(*(int *)&menuPcs->field_0x818 + 0x28) = fVar2;
      *(short *)(*(int *)&menuPcs->field_0x818 + 0x1e) =
           *(short *)(*(int *)&menuPcs->field_0x818 + 2) + 0x1c;
      if ((menuPcs->field_0x8 == '\x02') || (menuPcs->field_0x8 == '\x03')) {
        *(short *)(*(int *)&menuPcs->field_0x818 + 0x1e) =
             *(short *)(*(int *)&menuPcs->field_0x818 + 0x1e) + 0x10;
      }
      (*(undefined2 **)&menuPcs->field_0x818)[0xe] = **(undefined2 **)&menuPcs->field_0x818;
      if ((*(ushort *)&menuPcs->field_0x1a & 0xf) == 0) {
        if ((*(ushort *)&menuPcs->field_0x1a & 0x200) == 0) {
          *(short *)(*(int *)&menuPcs->field_0x818 + 0x1c) =
               *(short *)(*(int *)&menuPcs->field_0x818 + 0x1c) + 0x38;
        }
        else {
          *(short *)(*(int *)&menuPcs->field_0x818 + 0x1c) =
               *(short *)(*(int *)&menuPcs->field_0x818 + 0x1c) + 0x50;
        }
      }
      else {
        *(short *)(*(int *)&menuPcs->field_0x818 + 0x1c) =
             *(short *)(*(int *)&menuPcs->field_0x818 + 0x1c) + 0x20;
      }
    }
    fVar1 = FLOAT_803313dc;
    if ((*(ushort *)&menuPcs->field_0x1a & 0x1ff) != 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x3c) = 0x20;
      *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x3e) = 0x20;
      *(float *)(*(int *)&menuPcs->field_0x818 + 0x40) = fVar1;
      *(float *)(*(int *)&menuPcs->field_0x818 + 0x44) = fVar1;
      iVar9 = *(int *)&menuPcs->field_0x818;
      *(undefined2 *)(iVar9 + 0x54) = *(undefined2 *)(iVar9 + 0x38);
      *(undefined2 *)(iVar9 + 0x56) = *(undefined2 *)(iVar9 + 0x3a);
      *(undefined2 *)(iVar9 + 0x58) = *(undefined2 *)(iVar9 + 0x3c);
      *(undefined2 *)(iVar9 + 0x5a) = *(undefined2 *)(iVar9 + 0x3e);
      *(undefined4 *)(iVar9 + 0x5c) = *(undefined4 *)(iVar9 + 0x40);
      *(undefined4 *)(iVar9 + 0x60) = *(undefined4 *)(iVar9 + 0x44);
      *(undefined4 *)(iVar9 + 100) = *(undefined4 *)(iVar9 + 0x48);
      *(undefined4 *)(iVar9 + 0x68) = *(undefined4 *)(iVar9 + 0x4c);
      *(undefined4 *)(iVar9 + 0x6c) = *(undefined4 *)(iVar9 + 0x50);
      iVar9 = *(int *)&menuPcs->field_0x818;
      sVar15 = *(short *)(iVar9 + 0x1c) + *(short *)(iVar9 + 0x20);
      if ((*(ushort *)&menuPcs->field_0x1a & 0xf) == 0) {
        *(short *)(iVar9 + 0x54) = sVar15 + 8;
        *(short *)(*(int *)&menuPcs->field_0x818 + 0x38) = sVar15 + 8;
        *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x3a) =
             *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x1e);
        *(short *)(*(int *)&menuPcs->field_0x818 + 0x3a) =
             *(short *)(*(int *)&menuPcs->field_0x818 + 0x3a) + 0x14;
      }
      else {
        *(short *)(iVar9 + 0x54) = sVar15;
        iVar13 = 0;
        iVar9 = 4;
        iVar11 = 0;
        *(short *)(*(int *)&menuPcs->field_0x818 + 0x38) = sVar15;
        do {
          if (((int)*(short *)&menuPcs->field_0x1a & 1 << iVar13) != 0) {
            iVar11 = iVar11 + 1;
          }
          iVar13 = iVar13 + 1;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
        if (iVar11 == 1) {
          *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x3a) =
               *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x1e);
          *(short *)(*(int *)&menuPcs->field_0x818 + 0x3a) =
               *(short *)(*(int *)&menuPcs->field_0x818 + 0x3a) + 0x14;
        }
        else {
          *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x3a) =
               *(undefined2 *)(*(int *)&menuPcs->field_0x818 + 0x1e);
          iVar9 = *(int *)&menuPcs->field_0x818;
          *(short *)(iVar9 + 0x56) = *(short *)(iVar9 + 0x1e) + *(short *)(iVar9 + 0x22) + -0x20;
        }
      }
    }
    font_00 = *(CFont **)&menuPcs->field_0xfc;
    SetMargin__5CFontFf(FLOAT_803313e8,font_00);
    SetShadow__5CFontFi(font_00,0);
    SetScale__5CFontFf(FLOAT_803313e8,font_00);
    iVar9 = (int)(char)menuPcs->field_0x7;
    if (iVar9 == 0xf) {
      strcpy(local_a8,0x8021ff68);
    }
    else if (iVar9 == 0x16) {
      if (Game.game.m_gameWork.m_languageId == 2) {
        strcpy(local_a8,0x8021ff68);
        strcat(local_a8,PTR_s__Hafen_80210d14);
      }
      else {
        strcpy(local_a8,(&PTR_s_cc_logo03_80210d0c)[Game.game.m_gameWork.m_languageId]);
        strcat(local_a8,Game.game.m_gameWork.m_townName);
      }
    }
    else {
      strcpy(local_a8,Game.game.m_cFlatDataArr[1].m_table[3].index[iVar9]);
    }
    if (local_a8[0] != '\0') {
      local_a8[0] = _toupperLatin1();
    }
    uVar21 = 0xd8;
    font = *(CFont **)&menuPcs->field_0xfc;
    if (*(short *)&menuPcs->field_0x1a != 0) {
      uVar21 = 0xa2;
    }
    SetMargin__5CFontFf(FLOAT_803313e8,font);
    SetShadow__5CFontFi(font,0);
    SetScale__5CFontFf(FLOAT_803313e8,font);
    dVar23 = (double)GetWidth__5CFontFPc(font,local_a8);
    uStack_34 = uVar21 ^ 0x80000000;
    local_38 = 0x43300000;
    if ((double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331408) < dVar23) {
      strcpy(auStack_e8,local_a8);
      puVar10 = (undefined *)strrchr(auStack_e8,0x20);
      if (puVar10 == (undefined *)0x0) {
        local_128[0] = 0;
      }
      else {
        *puVar10 = 0;
        strcpy(local_128,puVar10 + 1);
      }
      strcpy(local_a8,auStack_e8);
    }
    dVar23 = (double)GetWidth__5CFontFPc(font_00,local_a8);
    sVar15 = 0x4c;
    local_38 = 0x43300000;
    uStack_34 = (int)**(short **)&menuPcs->field_0x818 ^ 0x80000000;
    (*(short **)&menuPcs->field_0x818)[0x38] =
         (short)(int)((float)((double)FLOAT_80331704 - dVar23) * FLOAT_80331434 +
                     (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80331408));
    fVar2 = FLOAT_803314a4;
    fVar1 = FLOAT_803313dc;
    if ((*(ushort *)&menuPcs->field_0x1a & 0x3f0) != 0) {
      sVar15 = 0x6c;
    }
    if ((menuPcs->field_0x8 == '\x02') || (menuPcs->field_0x8 == '\x03')) {
      sVar15 = sVar15 + 0x10;
    }
    iVar11 = 6;
    iVar9 = 0x1e0;
    *(short *)(*(int *)&menuPcs->field_0x818 + 0x72) =
         *(short *)(*(int *)&menuPcs->field_0x818 + 2) + sVar15;
    *(short *)(*(int *)&menuPcs->field_0x818 + 0x72) =
         *(short *)(*(int *)&menuPcs->field_0x818 + 0x72) + -4;
    sVar15 = **(short **)&menuPcs->field_0x818 + -0x28;
    sVar22 = (*(short **)&menuPcs->field_0x818)[1] + -0xe;
    iVar13 = 2;
    do {
      puVar20 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar9);
      iVar19 = iVar9 + 0x50;
      *puVar20 = 0;
      iVar18 = iVar9 + 0xa0;
      iVar17 = iVar9 + 0xf0;
      iVar16 = iVar9 + 0x140;
      *(short *)(puVar20 + 2) = sVar15;
      iVar9 = iVar9 + 400;
      iVar11 = iVar11 + 5;
      *(short *)((int)puVar20 + 10) = sVar22;
      *(undefined2 *)(puVar20 + 3) = 0x140;
      *(undefined2 *)((int)puVar20 + 0xe) = 0xe0;
      puVar20[4] = fVar1;
      puVar20[5] = fVar1;
      puVar20[6] = fVar2;
      puVar20 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar19);
      *puVar20 = 0;
      *(short *)(puVar20 + 2) = sVar15;
      *(short *)((int)puVar20 + 10) = sVar22;
      *(undefined2 *)(puVar20 + 3) = 0x140;
      *(undefined2 *)((int)puVar20 + 0xe) = 0xe0;
      puVar20[4] = fVar1;
      puVar20[5] = fVar1;
      puVar20[6] = fVar2;
      puVar20 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar18);
      *puVar20 = 0;
      *(short *)(puVar20 + 2) = sVar15;
      *(short *)((int)puVar20 + 10) = sVar22;
      *(undefined2 *)(puVar20 + 3) = 0x140;
      *(undefined2 *)((int)puVar20 + 0xe) = 0xe0;
      puVar20[4] = fVar1;
      puVar20[5] = fVar1;
      puVar20[6] = fVar2;
      puVar20 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar17);
      *puVar20 = 0;
      *(short *)(puVar20 + 2) = sVar15;
      *(short *)((int)puVar20 + 10) = sVar22;
      *(undefined2 *)(puVar20 + 3) = 0x140;
      *(undefined2 *)((int)puVar20 + 0xe) = 0xe0;
      puVar20[4] = fVar1;
      puVar20[5] = fVar1;
      puVar20[6] = fVar2;
      puVar20 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar16);
      *puVar20 = 0;
      *(short *)(puVar20 + 2) = sVar15;
      *(short *)((int)puVar20 + 10) = sVar22;
      *(undefined2 *)(puVar20 + 3) = 0x140;
      *(undefined2 *)((int)puVar20 + 0xe) = 0xe0;
      puVar20[4] = fVar1;
      puVar20[5] = fVar1;
      puVar20[6] = fVar2;
      fVar4 = FLOAT_803314a4;
      fVar7 = FLOAT_803313dc;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    iVar9 = 0x11 - iVar11;
    iVar13 = iVar11 * 0x50;
    if (iVar11 < 0x11) {
      do {
        puVar20 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar13);
        iVar13 = iVar13 + 0x50;
        *puVar20 = 0;
        *(short *)(puVar20 + 2) = sVar15;
        *(short *)((int)puVar20 + 10) = sVar22;
        *(undefined2 *)(puVar20 + 3) = 0x140;
        *(undefined2 *)((int)puVar20 + 0xe) = 0xe0;
        puVar20[4] = fVar7;
        puVar20[5] = fVar7;
        puVar20[6] = fVar4;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
    }
    fVar2 = FLOAT_8033170c;
    fVar1 = FLOAT_803313dc;
    uVar3 = *(ushort *)&menuPcs->field_0x1a;
    if ((uVar3 & 0x3f0) != 0) {
      if ((uVar3 & 0x200) == 0) {
        iVar9 = 0;
        if (((((uVar3 & 0x10) == 0) && (iVar9 = 1, (uVar3 & 0x20) == 0)) &&
            (iVar9 = 2, (uVar3 & 0x40) == 0)) &&
           ((iVar9 = 3, (uVar3 & 0x80) == 0 && (iVar9 = 4, (uVar3 & 0x100) == 0)))) {
          iVar9 = 5;
        }
        iVar9 = iVar9 + 0xc;
      }
      else if (menuPcs->field_0x6 == '\x01') {
        iVar9 = 7;
      }
      else {
        iVar9 = 6;
      }
      puVar20 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar9 * 0x50);
      *puVar20 = 1;
      puVar20[7] = fVar1;
      puVar20[8] = fVar1;
      puVar20[9] = fVar1;
      puVar20[0xd] = fVar2;
      puVar20[0xe] = fVar2;
      puVar20[0xf] = fVar2;
      if ((menuPcs->field_0x8 == '\x02') || (menuPcs->field_0x8 == '\x03')) {
        puVar20[8] = FLOAT_80331710;
      }
      dVar8 = DOUBLE_80331720;
      dVar23 = DOUBLE_80331420;
      if ((*(ushort *)&menuPcs->field_0x1a & 0xf) == 0) {
        if ((*(ushort *)&menuPcs->field_0x1a & 0x200) == 0) {
          puVar20[7] = FLOAT_80331718;
          puVar20[8] = (float)((double)(float)puVar20[8] + dVar8);
        }
        else {
          puVar20[7] = FLOAT_803313dc;
          puVar20[8] = (float)((double)(float)puVar20[8] + dVar23);
        }
      }
      else {
        puVar20[7] = FLOAT_80331714;
        puVar20[8] = (float)((double)(float)puVar20[8] + dVar23);
      }
      fVar7 = FLOAT_803314c0;
      dVar23 = DOUBLE_80331408;
      fVar1 = FLOAT_803313dc;
      local_30 = (double)CONCAT44(0x43300000,puVar20[1] ^ 0x80000000);
      fVar2 = (float)(local_30 - DOUBLE_80331408) / FLOAT_803314c0;
      if (fVar2 < DAT_8032e8b4[DAT_8032e8b0 * 4 + -4]) {
        iVar13 = 0;
        pfVar14 = DAT_8032e8b4;
        iVar11 = DAT_8032e8b0;
        fVar4 = FLOAT_803313dc;
        if (0 < DAT_8032e8b0) {
          do {
            if (fVar2 <= *pfVar14) {
              if (iVar13 == 0) {
                fVar4 = DAT_8032e8b4[1];
              }
              else {
                pfVar12 = DAT_8032e8b4 + iVar13 * 4;
                pfVar14 = DAT_8032e8b4 + (iVar13 + -1) * 4;
                fVar4 = *pfVar12 - *pfVar14;
                fVar6 = (fVar2 - *pfVar14) / fVar4;
                fVar5 = fVar6 * fVar6;
                fVar2 = fVar5 * fVar6;
                fVar4 = fVar4 * (pfVar14[3] * (fVar6 + -(FLOAT_803314c8 * fVar5 - fVar2)) +
                                pfVar12[2] * (fVar2 - fVar5)) +
                        pfVar14[1] *
                        (FLOAT_803313e8 + (FLOAT_803314c8 * fVar2 - FLOAT_803314c4 * fVar5)) +
                        pfVar12[1] * (FLOAT_803314cc * fVar2 + FLOAT_803314c4 * fVar5);
              }
              break;
            }
            pfVar14 = pfVar14 + 4;
            iVar13 = iVar13 + 1;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
        }
      }
      else {
        fVar4 = DAT_8032e8b4[DAT_8032e8b0 * 4 + -3];
      }
      puVar20[8] = (float)puVar20[8] + fVar4;
      fVar2 = FLOAT_803315d0;
      local_30 = (double)(CONCAT44(0x43300000,puVar20[1]) ^ 0x80000000);
      fVar7 = (float)(local_30 - dVar23) / fVar7;
      if (fVar7 < DAT_8032e8bc[DAT_8032e8b8 * 4 + -4]) {
        iVar13 = 0;
        pfVar14 = DAT_8032e8bc;
        iVar11 = DAT_8032e8b8;
        if (0 < DAT_8032e8b8) {
          do {
            if (fVar7 <= *pfVar14) {
              if (iVar13 == 0) {
                fVar1 = DAT_8032e8bc[1];
              }
              else {
                pfVar12 = DAT_8032e8bc + iVar13 * 4;
                pfVar14 = DAT_8032e8bc + (iVar13 + -1) * 4;
                fVar1 = *pfVar12 - *pfVar14;
                fVar5 = (fVar7 - *pfVar14) / fVar1;
                fVar4 = fVar5 * fVar5;
                fVar7 = fVar4 * fVar5;
                fVar1 = fVar1 * (pfVar14[3] * (fVar5 + -(FLOAT_803314c8 * fVar4 - fVar7)) +
                                pfVar12[2] * (fVar7 - fVar4)) +
                        pfVar14[1] *
                        (FLOAT_803313e8 + (FLOAT_803314c8 * fVar7 - FLOAT_803314c4 * fVar4)) +
                        pfVar12[1] * (FLOAT_803314cc * fVar7 + FLOAT_803314c4 * fVar4);
              }
              break;
            }
            pfVar14 = pfVar14 + 4;
            iVar13 = iVar13 + 1;
            iVar11 = iVar11 + -1;
          } while (iVar11 != 0);
        }
      }
      else {
        fVar1 = DAT_8032e8bc[DAT_8032e8b8 * 4 + -3];
      }
      puVar20[0xb] = FLOAT_803314bc * fVar1;
      puVar20[10] = fVar2;
      PSMTXScale((float)puVar20[0xd],(float)puVar20[0xe],(float)puVar20[0xf],&MStack_68);
      PSMTXRotRad((float)puVar20[10],&MStack_158,0x78);
      PSMTXRotRad((float)puVar20[0xb],&MStack_1b8,0x79);
      PSMTXConcat(&MStack_158,&MStack_1b8,&MStack_158);
      MStack_158.value[0][3] = (float)puVar20[7];
      MStack_158.value[1][3] = (float)puVar20[8];
      MStack_158.value[2][3] = (float)puVar20[9];
      PSMTXConcat(&MStack_158,&MStack_68,&MStack_68);
      SetMatrix__Q26CChara6CModelFPA4_f
                (*(CModel **)(*(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar9 * 4) + 0x168),
                 &MStack_68);
      CalcMatrix__Q26CChara6CModelFv
                (*(undefined4 *)(*(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar9 * 4) + 0x168))
      ;
      CalcSkin__Q26CChara6CModelFv
                (*(undefined4 *)(*(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar9 * 4) + 0x168))
      ;
      dVar23 = DOUBLE_803314a8;
      puVar20[1] = puVar20[1] + 1;
      local_30 = (double)(CONCAT44(0x43300000,puVar20[1]) ^ 0x80000000);
      if (dVar23 * (double)DAT_8032e8b4[DAT_8032e8b0 * 4 + -4] <=
          (double)(float)(local_30 - DOUBLE_80331408)) {
        puVar20[1] = 0;
      }
    }
    uVar21 = (uint)*(short *)&menuPcs->field_0x1a;
    if (((uVar21 & 0x200) != 0) && ((uVar21 & 0xf) != 0)) {
      iVar11 = 0;
      iVar13 = 0;
      iVar9 = 4;
      do {
        if ((uVar21 & 1 << iVar11) != 0) {
          iVar13 = iVar13 + 1;
        }
        iVar11 = iVar11 + 1;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
      iVar11 = 0;
      iVar9 = 0;
      do {
        fVar1 = FLOAT_80331728;
        if (((int)*(short *)&menuPcs->field_0x1a & 1 << iVar9) != 0) {
          puVar20 = (undefined4 *)(*(int *)&menuPcs->field_0x814 + (iVar9 + 8) * 0x50);
          *puVar20 = 1;
          puVar20[7] = fVar1;
          if (iVar11 == 0) {
            if (iVar13 == 2) {
              puVar20[8] = FLOAT_8033172c;
            }
            else {
              puVar20[8] = FLOAT_80331668;
            }
          }
          else {
            puVar20[8] = FLOAT_80331710;
          }
          if ((menuPcs->field_0x8 == '\x02') || (menuPcs->field_0x8 == '\x03')) {
            if ((iVar9 == 0) && (iVar13 == 1)) {
              puVar20[8] = (float)((double)(float)puVar20[8] - DOUBLE_80331730);
            }
            else {
              puVar20[8] = (float)((double)(float)puVar20[8] - DOUBLE_80331738);
            }
          }
          fVar2 = FLOAT_80331740;
          fVar1 = FLOAT_803313dc;
          puVar20[9] = FLOAT_803313dc;
          dVar23 = DOUBLE_80331408;
          puVar20[0xd] = fVar2;
          fVar7 = FLOAT_803314c0;
          puVar20[0xe] = fVar2;
          puVar20[0xf] = fVar2;
          fVar4 = FLOAT_803314c0;
          dVar8 = DOUBLE_80331408;
          fVar2 = FLOAT_803313dc;
          local_30 = (double)CONCAT44(0x43300000,puVar20[1] ^ 0x80000000);
          fVar7 = (float)(local_30 - dVar23) / fVar7;
          if (fVar7 < DAT_8032e8b4[DAT_8032e8b0 * 4 + -4]) {
            iVar17 = 0;
            pfVar14 = DAT_8032e8b4;
            iVar16 = DAT_8032e8b0;
            if (0 < DAT_8032e8b0) {
              do {
                if (fVar7 <= *pfVar14) {
                  if (iVar17 == 0) {
                    fVar1 = DAT_8032e8b4[1];
                  }
                  else {
                    pfVar12 = DAT_8032e8b4 + iVar17 * 4;
                    pfVar14 = DAT_8032e8b4 + (iVar17 + -1) * 4;
                    fVar1 = *pfVar12 - *pfVar14;
                    fVar6 = (fVar7 - *pfVar14) / fVar1;
                    fVar5 = fVar6 * fVar6;
                    fVar7 = fVar5 * fVar6;
                    fVar1 = fVar1 * (pfVar14[3] * (fVar6 + -(FLOAT_803314c8 * fVar5 - fVar7)) +
                                    pfVar12[2] * (fVar7 - fVar5)) +
                            pfVar14[1] *
                            (FLOAT_803313e8 + (FLOAT_803314c8 * fVar7 - FLOAT_803314c4 * fVar5)) +
                            pfVar12[1] * (FLOAT_803314cc * fVar7 + FLOAT_803314c4 * fVar5);
                  }
                  break;
                }
                pfVar14 = pfVar14 + 4;
                iVar17 = iVar17 + 1;
                iVar16 = iVar16 + -1;
              } while (iVar16 != 0);
            }
          }
          else {
            fVar1 = DAT_8032e8b4[DAT_8032e8b0 * 4 + -3];
          }
          puVar20[8] = (float)puVar20[8] + fVar1;
          local_30 = (double)(CONCAT44(0x43300000,puVar20[1]) ^ 0x80000000);
          fVar4 = (float)(local_30 - dVar8) / fVar4;
          if (fVar4 < DAT_8032e8bc[DAT_8032e8b8 * 4 + -4]) {
            iVar17 = 0;
            pfVar14 = DAT_8032e8bc;
            iVar16 = DAT_8032e8b8;
            if (0 < DAT_8032e8b8) {
              do {
                if (fVar4 <= *pfVar14) {
                  if (iVar17 == 0) {
                    fVar2 = DAT_8032e8bc[1];
                  }
                  else {
                    pfVar12 = DAT_8032e8bc + iVar17 * 4;
                    pfVar14 = DAT_8032e8bc + (iVar17 + -1) * 4;
                    fVar1 = *pfVar12 - *pfVar14;
                    fVar4 = (fVar4 - *pfVar14) / fVar1;
                    fVar7 = fVar4 * fVar4;
                    fVar2 = fVar7 * fVar4;
                    fVar2 = fVar1 * (pfVar14[3] * (fVar4 + -(FLOAT_803314c8 * fVar7 - fVar2)) +
                                    pfVar12[2] * (fVar2 - fVar7)) +
                            pfVar14[1] *
                            (FLOAT_803313e8 + (FLOAT_803314c8 * fVar2 - FLOAT_803314c4 * fVar7)) +
                            pfVar12[1] * (FLOAT_803314cc * fVar2 + FLOAT_803314c4 * fVar7);
                  }
                  break;
                }
                pfVar14 = pfVar14 + 4;
                iVar17 = iVar17 + 1;
                iVar16 = iVar16 + -1;
              } while (iVar16 != 0);
            }
          }
          else {
            fVar2 = DAT_8032e8bc[DAT_8032e8b8 * 4 + -3];
          }
          puVar20[0xb] = FLOAT_803314bc * fVar2;
          if (iVar13 == 1) {
            puVar20[10] = FLOAT_80331744;
          }
          else {
            puVar20[10] = FLOAT_803315d0;
          }
          PSMTXScale((float)puVar20[0xd],(float)puVar20[0xe],(float)puVar20[0xf],&MStack_68);
          PSMTXRotRad((float)puVar20[10],&MStack_188,0x78);
          PSMTXRotRad((float)puVar20[0xb],&MStack_1e8,0x79);
          PSMTXConcat(&MStack_188,&MStack_1e8,&MStack_188);
          MStack_188.value[0][3] = (float)puVar20[7];
          MStack_188.value[1][3] = (float)puVar20[8];
          MStack_188.value[2][3] = (float)puVar20[9];
          PSMTXConcat(&MStack_188,&MStack_68,&MStack_68);
          iVar16 = iVar9 * 4;
          SetMatrix__Q26CChara6CModelFPA4_f
                    (*(CModel **)
                      (*(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar16 + 0x20) + 0x168),
                     &MStack_68);
          CalcMatrix__Q26CChara6CModelFv
                    (*(undefined4 *)
                      (*(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar16 + 0x20) + 0x168));
          CalcSkin__Q26CChara6CModelFv
                    (*(undefined4 *)
                      (*(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar16 + 0x20) + 0x168));
          dVar23 = DOUBLE_803314a8;
          puVar20[1] = puVar20[1] + 1;
          local_30 = (double)(CONCAT44(0x43300000,puVar20[1]) ^ 0x80000000);
          if (dVar23 * (double)DAT_8032e8b4[DAT_8032e8b0 * 4 + -4] <=
              (double)(float)(local_30 - DOUBLE_80331408)) {
            puVar20[1] = 0;
          }
          iVar11 = iVar11 + 1;
        }
        iVar9 = iVar9 + 1;
      } while (iVar9 < 4);
    }
  }
  return;
}

