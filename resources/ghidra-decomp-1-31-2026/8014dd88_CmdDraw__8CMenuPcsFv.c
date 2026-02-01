// Function: CmdDraw__8CMenuPcsFv
// Entry: 8014dd88
// Size: 5472 bytes

/* WARNING: Removing unreachable block (ram,0x8014f2cc) */
/* WARNING: Removing unreachable block (ram,0x8014f2c4) */
/* WARNING: Removing unreachable block (ram,0x8014f2bc) */
/* WARNING: Removing unreachable block (ram,0x8014f2b4) */
/* WARNING: Removing unreachable block (ram,0x8014f2ac) */
/* WARNING: Removing unreachable block (ram,0x8014f2a4) */
/* WARNING: Removing unreachable block (ram,0x8014f29c) */
/* WARNING: Removing unreachable block (ram,0x8014f294) */
/* WARNING: Removing unreachable block (ram,0x8014ddd0) */
/* WARNING: Removing unreachable block (ram,0x8014ddc8) */
/* WARNING: Removing unreachable block (ram,0x8014ddc0) */
/* WARNING: Removing unreachable block (ram,0x8014ddb8) */
/* WARNING: Removing unreachable block (ram,0x8014ddb0) */
/* WARNING: Removing unreachable block (ram,0x8014dda8) */
/* WARNING: Removing unreachable block (ram,0x8014dda0) */
/* WARNING: Removing unreachable block (ram,0x8014dd98) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CmdDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  short sVar2;
  bool bVar3;
  bool bVar4;
  uint32_t uVar5;
  short *psVar6;
  int iVar7;
  char cVar11;
  undefined4 *puVar8;
  int32_t iVar9;
  undefined4 uVar10;
  uint uVar12;
  short *psVar13;
  int iVar14;
  short *psVar15;
  CFont *pCVar16;
  uint32_t uVar17;
  int iVar18;
  int unaff_r21;
  int iVar19;
  uint uVar20;
  int iVar21;
  uint uVar22;
  int iVar23;
  int iVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double in_f26;
  double in_f27;
  double in_f28;
  double dVar28;
  double dVar29;
  double dVar30;
  undefined auStack_160 [4];
  undefined4 local_15c;
  undefined auStack_158 [4];
  undefined4 local_154;
  undefined4 local_150;
  undefined auStack_14c [4];
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined auStack_13c [4];
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined local_12c;
  undefined local_12b;
  undefined local_12a;
  undefined local_129;
  undefined local_128;
  undefined local_127;
  undefined local_126;
  undefined local_125;
  undefined local_124;
  undefined local_123;
  undefined local_122;
  undefined local_121;
  undefined auStack_120 [40];
  undefined8 local_f8;
  undefined8 local_f0;
  undefined4 local_e8;
  uint uStack_e4;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  
  bVar4 = false;
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  uVar5 = Game.game.m_scriptFoodBase[0];
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  psVar15 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  iVar21 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x30);
  uVar17 = Game.game.m_scriptFoodBase[0];
  for (iVar18 = 0; iVar18 < **(short **)&menuPcs->field_0x850; iVar18 = iVar18 + 1) {
    if (-1 < *(int *)(psVar15 + 0xe)) {
      uStack_e4 = (int)psVar15[2] ^ 0x80000000;
      local_f8 = (double)CONCAT44(0x43300000,(int)*psVar15 ^ 0x80000000);
      dVar29 = (double)*(float *)(psVar15 + 4);
      in_f28 = (double)(float)(local_f8 - DOUBLE_80332a80);
      local_f0 = (double)CONCAT44(0x43300000,(int)psVar15[1] ^ 0x80000000);
      in_f27 = (double)(float)(local_f0 - DOUBLE_80332a80);
      local_e8 = 0x43300000;
      in_f26 = (double)(float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80332a80);
      local_e0 = (double)CONCAT44(0x43300000,(int)psVar15[3] ^ 0x80000000);
      dVar27 = (double)(float)(local_e0 - DOUBLE_80332a80);
      if ((7 < iVar18) || (*(short *)(uVar17 + 0x214) == 0)) {
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(int *)(psVar15 + 0xe));
        fVar1 = FLOAT_80332ad0;
        if ((1 < *(short *)(uVar17 + 0x204)) && (*(short *)(uVar17 + 0x204) == -1)) {
          fVar1 = (float)((double)FLOAT_80332ad0 + dVar27);
        }
        dVar30 = (double)fVar1;
        if (((sVar2 == 1) && (iVar18 < *(short *)(uVar5 + 0xbaa))) &&
           (iVar18 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) {
          dVar30 = (double)FLOAT_80332b10;
          in_f27 = (double)(float)(in_f27 - (double)FLOAT_80332ad0);
          dVar27 = (double)(float)(dVar27 + (double)FLOAT_80332ad0);
        }
        local_e0 = (double)(longlong)(int)(FLOAT_80332acc * *(float *)(psVar15 + 8));
        local_130 = CONCAT31(0xffffff,(char)(int)(FLOAT_80332acc * *(float *)(psVar15 + 8)));
        local_134 = local_130;
        GXSetChanMatColor(4,&local_134);
        DrawRect__8CMenuPcsFUlfffffffff
                  (in_f28,in_f27,in_f26,dVar27,dVar29,dVar30,(double)*(float *)(psVar15 + 10),
                   (double)*(float *)(psVar15 + 10),&MenuPcs,0);
      }
    }
    uVar17 = uVar17 + 2;
    psVar15 = psVar15 + 0x20;
  }
  pCVar16 = *(CFont **)&menuPcs->field_0x108;
  SetMargin__5CFontFf(FLOAT_80332a70,pCVar16);
  SetShadow__5CFontFi(pCVar16,0);
  SetScale__5CFontFf(FLOAT_80332ad8,pCVar16);
  DrawInit__5CFontFv(pCVar16);
  psVar15 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  uVar17 = uVar5;
  for (iVar18 = 0; iVar18 < *(short *)(uVar5 + 0xbaa); iVar18 = iVar18 + 1) {
    if ((7 < iVar18) || (*(short *)(uVar17 + 0x214) == 0)) {
      dVar27 = DOUBLE_80332a58;
      if (iVar21 != 3) {
        dVar27 = (double)*(float *)(psVar15 + 8);
      }
      local_e0 = (double)(longlong)(int)(FLOAT_80332acc * (float)dVar27);
      puVar8 = (undefined4 *)
               __ct__6CColorFUcUcUcUc
                         (auStack_13c,0xff,0xff,0xff,(int)(FLOAT_80332acc * (float)dVar27));
      local_138 = *puVar8;
      SetColor__5CFontF8_GXColor(pCVar16,&local_138);
      if (iVar18 < 2) {
        iVar9 = GetMenuStr__8CMenuPcsFi(menuPcs,iVar18 + 9);
      }
      else {
        if (*(short *)(uVar17 + 0x204) < 0) goto LAB_8014e170;
        iVar23 = (int)*(short *)(uVar5 + *(short *)(uVar17 + 0x204) * 2 + 0xb6);
        iVar9 = Game.game.m_cFlatDataArr[1].m_table[0].index[iVar23 * 5 + 4];
        if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) == 0) &&
           (iVar18 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26))) {
          bVar4 = true;
          unaff_r21 = iVar23;
        }
      }
      dVar27 = (double)GetWidth__5CFontFPc(pCVar16,iVar9);
      uStack_e4 = (int)*psVar15 ^ 0x80000000;
      local_e0 = (double)CONCAT44(0x43300000,(int)psVar15[2] ^ 0x80000000);
      local_e8 = 0x43300000;
      local_f0 = (double)CONCAT44(0x43300000,(int)psVar15[1] + 3U ^ 0x80000000);
      in_f27 = (double)(float)(local_f0 - DOUBLE_80332a80);
      fVar1 = (float)((double)(float)((double)(float)(local_e0 - DOUBLE_80332a80) - dVar27) *
                      DOUBLE_80332a60 + ((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80332a80));
      in_f28 = (double)fVar1;
      SetPosX__5CFontFf(fVar1,pCVar16);
      SetPosY__5CFontFf((float)(in_f27 - (double)FLOAT_80332ae8),pCVar16);
      Draw__5CFontFPc(pCVar16,iVar9);
    }
LAB_8014e170:
    uVar17 = uVar17 + 2;
    psVar15 = psVar15 + 0x20;
  }
  DrawInit__8CMenuPcsFv(menuPcs);
  DrawUniteList__8CMenuPcsFv(menuPcs);
  psVar15 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  uVar17 = uVar5;
  for (iVar18 = 0; iVar18 < *(short *)(uVar5 + 0xbaa); iVar18 = iVar18 + 1) {
    if ((1 < iVar18) && (-1 < *(short *)(uVar17 + 0x204))) {
      uStack_e4 = (int)psVar15[1] - 2U ^ 0x80000000;
      uVar20 = (int)*psVar15 + psVar15[2] + -0x10 ^ 0x80000000;
      local_e8 = 0x43300000;
      in_f27 = (double)(float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80332a80);
      local_f0 = (double)CONCAT44(0x43300000,uVar20);
      local_e0 = (double)CONCAT44(0x43300000,uVar20);
      local_d8 = (double)(longlong)(int)(in_f27 - (double)FLOAT_80332a70);
      local_f8 = (double)(longlong)(int)(local_f0 - DOUBLE_80332a80);
      in_f28 = (double)(float)(local_e0 - DOUBLE_80332a80);
      DrawSingleIcon__8CMenuPcsFiiifif
                ((double)*(float *)(psVar15 + 8),menuPcs,
                 (int)*(short *)(uVar5 + *(short *)(uVar17 + 0x204) * 2 + 0xb6),
                 (int)(local_f0 - DOUBLE_80332a80),(int)(in_f27 - (double)FLOAT_80332a70),0);
    }
    uVar17 = uVar17 + 2;
    psVar15 = psVar15 + 0x20;
  }
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x32) != 0) {
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    iVar23 = 0;
    psVar15 = *(short **)&menuPcs->field_0x850 + **(short **)&menuPcs->field_0x850 * 0x20 + 4;
    psVar6 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    iVar18 = (int)*psVar6;
    for (iVar24 = (int)**(short **)&menuPcs->field_0x850; uVar17 = Game.game.m_scriptFoodBase[0],
        iVar24 < (*(short **)&menuPcs->field_0x850)[1]; iVar24 = iVar24 + 1) {
      iVar19 = *(int *)(psVar15 + 0xe);
      if (-1 < iVar19) {
        uStack_e4 = (int)psVar15[2] ^ 0x80000000;
        local_d8 = (double)CONCAT44(0x43300000,(int)*psVar15 ^ 0x80000000);
        in_f28 = (double)(float)(local_d8 - DOUBLE_80332a80);
        dVar29 = (double)*(float *)(psVar15 + 4);
        local_e0 = (double)CONCAT44(0x43300000,(int)psVar15[1] ^ 0x80000000);
        dVar27 = (double)*(float *)(psVar15 + 6);
        in_f27 = (double)(float)(local_e0 - DOUBLE_80332a80);
        local_e8 = 0x43300000;
        in_f26 = (double)(float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80332a80);
        local_f0 = (double)CONCAT44(0x43300000,(int)psVar15[3] ^ 0x80000000);
        dVar30 = (double)(float)(local_f0 - DOUBLE_80332a80);
        if (iVar24 == **(short **)&menuPcs->field_0x850) {
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,1);
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar15 + 0xe));
          local_130 = 0xffffffff;
          local_12c = 0xff;
          local_12b = 0xff;
          local_12a = 0xff;
          local_129 = 0xff;
          local_128 = 0xff;
          local_127 = 0xff;
          local_126 = 0xff;
          local_125 = 0xff;
          local_124 = 0xff;
          local_123 = 0xff;
          local_122 = 0xff;
          local_121 = 0xff;
          local_140 = 0xffffffff;
          GXSetChanMatColor(4,&local_140);
          in_f26 = (double)(float)((double)*(float *)(psVar15 + 8) * in_f26);
          if ((double)FLOAT_80332ab0 < in_f26) {
            DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                      (in_f28,in_f27,in_f26,dVar30,dVar29,dVar27,(double)FLOAT_80332a70,
                       (double)FLOAT_80332a70,&MenuPcs,0,&local_130);
            in_f28 = (double)(float)(in_f28 + in_f26);
            dVar29 = (double)(float)(dVar29 + in_f26);
          }
          if ((double)FLOAT_80332ab0 < in_f26) {
            local_d8 = (double)(CONCAT44(0x43300000,(int)psVar15[2]) ^ 0x80000000);
            if (in_f26 < (double)(float)(local_d8 - DOUBLE_80332a80)) {
              local_12c = 0xff;
              local_12b = 0xff;
              local_12a = 0xff;
              local_129 = 0;
              local_124 = 0xff;
              local_123 = 0xff;
              local_122 = 0xff;
              local_121 = 0;
              local_d8 = (double)(CONCAT44(0x43300000,*(undefined4 *)(psVar15 + 0x14)) ^ 0x80000000)
              ;
              local_e0 = (double)CONCAT44(0x43300000,(int)psVar15[2] ^ 0x80000000);
              in_f26 = (double)((float)(DOUBLE_80332a58 / (local_d8 - DOUBLE_80332a80)) *
                               (float)(local_e0 - DOUBLE_80332a80));
              DrawRect__8CMenuPcsFUlffffffP8_GXColorfff
                        (in_f28,in_f27,in_f26,dVar30,dVar29,dVar27,(double)FLOAT_80332a70,
                         (double)FLOAT_80332a70,&MenuPcs,0,&local_130);
            }
          }
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
        }
        else {
          dVar26 = (double)*(float *)(psVar15 + 8);
          if (iVar19 == 0x37) {
            iVar7 = iVar23 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
            iVar14 = iVar7;
            if ((7 < iVar18) && (iVar18 <= iVar7)) {
              iVar14 = iVar7 - iVar18;
            }
            if (iVar14 < 2) {
              psVar13 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
              if ((iVar14 < 0) || (*psVar13 <= iVar14)) {
                uVar20 = 0;
              }
              else if (iVar14 == 0) {
                uVar20 = (uint)(int)*(short *)(uVar17 + *(short *)(*(int *)&menuPcs->field_0x82c +
                                                                  0x26) * 2 + 0x204) >> 0x1f ^ 1;
              }
              else if (iVar14 == 1) {
                uVar20 = ChkUnite__8CMenuPcsFiPA2_i
                                   (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26),
                                    auStack_120);
                uVar20 = (-uVar20 | uVar20) >> 0x1f;
              }
              else {
                uVar20 = EquipChk__8CMenuPcsFi(menuPcs,(int)psVar13[iVar14 + -1]);
                uVar20 = countLeadingZeros(uVar20 & 0xff);
                uVar20 = uVar20 >> 5;
              }
              if ((uVar20 & 0xff) == 0) {
                iVar19 = 0x34;
                dVar26 = (double)(float)(DOUBLE_80332a60 * (double)*(float *)(psVar15 + 8));
              }
            }
            else {
              iVar7 = iVar7 + -2;
              if ((7 < iVar18) && (iVar18 <= iVar7)) {
                iVar7 = iVar7 - iVar18;
              }
              if ((iVar18 <= iVar7 + 2) ||
                 (cVar11 = EquipChk__8CMenuPcsFi(menuPcs,(int)psVar6[iVar7 + 1]), cVar11 != '\0')) {
                if (iVar7 + 2 < iVar18) {
                  local_d8 = (double)(longlong)(int)(in_f28 - (double)FLOAT_80332b14);
                  iVar19 = (int)((double)(float)(dVar30 - (double)FLOAT_80332b18) * DOUBLE_80332a60
                                + in_f27);
                  local_e0 = (double)(longlong)iVar19;
                  DrawEquipMark__8CMenuPcsFiif
                            ((double)*(float *)(psVar15 + 8),menuPcs,
                             (int)(in_f28 - (double)FLOAT_80332b14),iVar19);
                }
                iVar19 = 0x34;
                dVar26 = (double)(float)(DOUBLE_80332a60 * (double)*(float *)(psVar15 + 8));
              }
            }
            if ((iVar19 == 0x37) && (iVar23 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x28))) {
              dVar27 = (double)(float)(dVar27 + dVar30);
            }
            iVar23 = iVar23 + 1;
          }
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,iVar19);
          local_d8 = (double)(longlong)(int)((double)FLOAT_80332acc * dVar26);
          local_130 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332acc * dVar26));
          local_144 = local_130;
          GXSetChanMatColor(4,&local_144);
          DrawRect__8CMenuPcsFUlfffffffff
                    (in_f28,in_f27,in_f26,dVar30,dVar29,dVar27,(double)*(float *)(psVar15 + 10),
                     (double)*(float *)(psVar15 + 10),&MenuPcs,0);
        }
      }
      psVar15 = psVar15 + 0x20;
    }
  }
  if (iVar21 == 1) {
    pCVar16 = *(CFont **)&menuPcs->field_0x108;
    SetMargin__5CFontFf(FLOAT_80332a70,pCVar16);
    SetShadow__5CFontFi(pCVar16,0);
    SetScale__5CFontFf(FLOAT_80332ad8,pCVar16);
    DrawInit__5CFontFv(pCVar16);
    psVar6 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    psVar13 = *(short **)&menuPcs->field_0x850;
    iVar19 = (int)*psVar6;
    iVar24 = (int)*psVar13;
    iVar18 = iVar24 << 6;
    iVar23 = psVar13[1] - iVar24;
    if (iVar24 < psVar13[1]) {
      do {
        psVar15 = (short *)((int)psVar13 + iVar18 + 8);
        if (*(int *)(psVar15 + 0xe) == 0x37) break;
        iVar18 = iVar18 + 0x40;
        iVar23 = iVar23 + -1;
      } while (iVar23 != 0);
    }
    dVar27 = (double)FLOAT_80332acc;
    iVar18 = 0;
    psVar13 = psVar15;
    do {
      if ((iVar19 < 9) && (iVar19 <= iVar18 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34)))
      break;
      iVar23 = iVar18 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
      if (iVar19 <= iVar23) {
        iVar23 = iVar23 - iVar19;
      }
      local_d8 = (double)(longlong)(int)(dVar27 * (double)*(float *)(psVar15 + 8));
      puVar8 = (undefined4 *)
               __ct__6CColorFUcUcUcUc
                         (auStack_14c,0xff,0xff,0xff,(int)(dVar27 * (double)*(float *)(psVar15 + 8))
                         );
      local_148 = *puVar8;
      SetColor__5CFontF8_GXColor(pCVar16,&local_148);
      if (iVar23 < 2) {
        iVar9 = GetMenuStr__8CMenuPcsFi(menuPcs,iVar23 + 0xb);
LAB_8014e8d8:
        GetWidth__5CFontFPc(pCVar16,iVar9);
        uStack_e4 = (int)*psVar13 + 0x1cU ^ 0x80000000;
        local_d8 = (double)(CONCAT44(0x43300000,(int)*psVar13 + 0x1cU) ^ 0x80000000);
        in_f28 = (double)(float)(local_d8 - DOUBLE_80332a80);
        local_e0 = (double)CONCAT44(0x43300000,(int)psVar13[1] + 0xbU ^ 0x80000000);
        in_f27 = (double)(float)(local_e0 - DOUBLE_80332a80);
        local_e8 = 0x43300000;
        SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80332a80),pCVar16)
        ;
        SetPosY__5CFontFf((float)(in_f27 - (double)FLOAT_80332ae8),pCVar16);
        Draw__5CFontFPc(pCVar16,iVar9);
      }
      else if (iVar23 < iVar19) {
        iVar24 = (int)*(short *)(uVar5 + psVar6[iVar23 + -1] * 2 + 0xb6);
        iVar14 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28) +
                 (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
        iVar9 = Game.game.m_cFlatDataArr[1].m_table[0].index[iVar24 * 5 + 4];
        if (iVar19 <= iVar14) {
          iVar14 = iVar14 - iVar19;
        }
        if (iVar23 == iVar14) {
          bVar4 = true;
          unaff_r21 = iVar24;
        }
        goto LAB_8014e8d8;
      }
      iVar18 = iVar18 + 1;
      psVar13 = psVar13 + 0x20;
    } while (iVar18 < 8);
    DrawInit__8CMenuPcsFv(menuPcs);
    iVar18 = 0;
    psVar13 = psVar15;
    do {
      if ((iVar19 < 9) && (iVar19 <= iVar18 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34)))
      break;
      iVar23 = iVar18 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x34);
      if (iVar19 <= iVar23) {
        iVar23 = iVar23 - iVar19;
      }
      if (1 < iVar23) {
        uStack_e4 = (int)*psVar13 + psVar13[2] + -0x10 ^ 0x80000000;
        local_e0 = (double)CONCAT44(0x43300000,(int)psVar13[1] + 6U ^ 0x80000000);
        in_f27 = (double)(float)(local_e0 - DOUBLE_80332a80);
        local_e8 = 0x43300000;
        local_d8 = (double)CONCAT44(0x43300000,uStack_e4);
        local_f8 = (double)(longlong)(int)(in_f27 - (double)FLOAT_80332a70);
        iVar24 = (int)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80332a80);
        local_f0 = (double)(longlong)iVar24;
        in_f28 = (double)(float)(local_d8 - DOUBLE_80332a80);
        DrawSingleIcon__8CMenuPcsFiiifif
                  ((double)*(float *)(psVar15 + 8),menuPcs,
                   (int)*(short *)(uVar5 + psVar6[iVar23 + -1] * 2 + 0xb6),iVar24,
                   (int)(in_f27 - (double)FLOAT_80332a70),0);
      }
      iVar18 = iVar18 + 1;
      psVar13 = psVar13 + 0x20;
    } while (iVar18 < 8);
  }
  if ((iVar21 == 1) && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 1)) {
    psVar15 = *(short **)&menuPcs->field_0x850 + **(short **)&menuPcs->field_0x850 * 0x20 + 4;
    psVar6 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    dVar27 = (double)CalcListPos__8CMenuPcsFiii
                               (menuPcs,(int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x34),
                                (int)*psVar6,1);
    if ((double)FLOAT_80332ab0 < dVar27) {
      local_d8 = (double)(CONCAT44(0x43300000,(int)*psVar15) ^ 0x80000000);
      local_e0 = (double)CONCAT44(0x43300000,(int)psVar15[1] ^ 0x80000000);
      DrawListPosMark__8CMenuPcsFfff
                ((double)(float)(local_d8 - DOUBLE_80332a80),
                 (double)(float)(local_e0 - DOUBLE_80332a80),dVar27,menuPcs);
    }
  }
  if (iVar21 == 2) {
    psVar15 = (short *)(*(int *)&menuPcs->field_0x850 +
                       (*(short *)(*(int *)&menuPcs->field_0x850 + 2) + 3) * 0x40 + 8);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,*(undefined4 *)(psVar15 + 0xe));
    local_d8 = (double)(longlong)(int)(FLOAT_80332acc * *(float *)(psVar15 + 8));
    local_130 = CONCAT31(0xffffff,(char)(int)(FLOAT_80332acc * *(float *)(psVar15 + 8)));
    local_150 = local_130;
    GXSetChanMatColor(4,&local_150);
    local_e0 = (double)(CONCAT44(0x43300000,(int)*psVar15) ^ 0x80000000);
    uStack_e4 = (int)psVar15[1] ^ 0x80000000;
    local_e8 = 0x43300000;
    local_f0 = (double)CONCAT44(0x43300000,(int)psVar15[2] ^ 0x80000000);
    local_f8 = (double)CONCAT44(0x43300000,(int)psVar15[3] ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(local_e0 - DOUBLE_80332a80),
               (double)(float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80332a80),
               (double)(float)(local_f0 - DOUBLE_80332a80),
               (double)(float)(local_f8 - DOUBLE_80332a80),(double)*(float *)(psVar15 + 4),
               (double)*(float *)(psVar15 + 6),(double)FLOAT_80332a70,
               (double)*(float *)(psVar15 + 10),&MenuPcs,0);
    pCVar16 = *(CFont **)&menuPcs->field_0xf8;
    SetMargin__5CFontFf(FLOAT_80332a70,pCVar16);
    SetShadow__5CFontFi(pCVar16,1);
    SetScale__5CFontFf(FLOAT_80332ad8,pCVar16);
    DrawInit__5CFontFv(pCVar16);
    SetTlut__5CFontFi(pCVar16,7);
    local_d0 = (double)(longlong)(int)(FLOAT_80332acc * *(float *)(psVar15 + 8));
    puVar8 = (undefined4 *)
             __ct__6CColorFUcUcUcUc
                       (auStack_158,0xff,0xff,0xff,(int)(FLOAT_80332acc * *(float *)(psVar15 + 8)));
    local_154 = *puVar8;
    SetColor__5CFontF8_GXColor(pCVar16,&local_154);
    if (DOUBLE_80332a58 == (double)*(float *)(psVar15 + 10)) {
      uVar20 = 2;
    }
    else {
      uVar20 = 3;
    }
    dVar28 = (double)FLOAT_80332ae8;
    dVar27 = DOUBLE_80332b20;
    dVar29 = DOUBLE_80332af8;
    dVar30 = DOUBLE_80332a60;
    dVar26 = DOUBLE_80332a80;
    for (uVar22 = 0; (int)uVar22 < (int)uVar20; uVar22 = uVar22 + 1) {
      if (uVar22 == 0) {
        uVar10 = GetMenuStr__8CMenuPcsFi(menuPcs,0xd);
      }
      else if ((uVar22 == 1) && (uVar20 == 3)) {
        uVar10 = GetMenuStr__8CMenuPcsFi(menuPcs,0xc);
      }
      else {
        uVar10 = GetMenuStr__8CMenuPcsFi(menuPcs,0x37);
      }
      GetWidth__5CFontFPc(pCVar16,uVar10);
      uStack_e4 = uVar22 ^ 0x80000000;
      local_d8 = (double)CONCAT44(0x43300000,(int)psVar15[3] ^ 0x80000000);
      uVar12 = (int)*psVar15 + 0x18U ^ 0x80000000;
      local_e0 = (double)CONCAT44(0x43300000,uVar20 ^ 0x80000000);
      local_e8 = 0x43300000;
      local_f0 = (double)CONCAT44(0x43300000,(int)psVar15[1] + 8U ^ 0x80000000);
      local_d0 = (double)CONCAT44(0x43300000,uVar12);
      dVar25 = (double)(float)(((double)((float)(local_d8 - dVar26) * *(float *)(psVar15 + 10)) -
                               dVar27) / (local_e0 - dVar26));
      local_f8 = (double)CONCAT44(0x43300000,uVar12);
      in_f28 = (double)(float)(local_d0 - dVar26);
      in_f27 = (double)(float)((dVar25 - dVar29) * dVar30 +
                              (double)(float)(dVar25 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                        uStack_e4) -
                                                                      dVar26) +
                                             (double)(float)(local_f0 - dVar26)));
      SetPosX__5CFontFf((float)(local_f8 - dVar26),pCVar16);
      SetPosY__5CFontFf((float)(in_f27 - dVar28),pCVar16);
      Draw__5CFontFPc(pCVar16,uVar10);
    }
    DrawInit__8CMenuPcsFv(menuPcs);
  }
  bVar3 = false;
  if (((iVar21 == 0) && (sVar2 == 1)) ||
     ((iVar21 != 0 && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 1)))) {
    if ((iVar21 == 0) || (iVar21 == 3)) {
      iVar18 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + iVar21 * 2 + 0x26);
      if (*(short *)(uVar5 + iVar18 * 2 + 0x214) == 0) {
        psVar15 = (short *)(*(int *)&menuPcs->field_0x850 + iVar18 * 0x40 + 8);
      }
      else {
        puVar8 = s_UniteTop;
        iVar24 = 0;
        iVar23 = DAT_8032eec8;
        if (0 < DAT_8032eec8) {
          do {
            if (iVar18 == *puVar8) break;
            puVar8 = puVar8 + 1;
            iVar24 = iVar24 + 1;
            iVar23 = iVar23 + -1;
          } while (iVar23 != 0);
        }
        bVar3 = true;
        psVar15 = (short *)(*(int *)&menuPcs->field_0x850 +
                           (*(short *)(*(int *)&menuPcs->field_0x850 + 2) + iVar24) * 0x40 + 8);
      }
    }
    else if (iVar21 == 1) {
      psVar6 = *(short **)&menuPcs->field_0x850;
      iVar24 = (int)*psVar6;
      iVar18 = iVar24 << 6;
      iVar23 = psVar6[1] - iVar24;
      if (iVar24 < psVar6[1]) {
        do {
          psVar15 = (short *)((int)psVar6 + iVar18 + 8);
          if (*(int *)((int)psVar6 + iVar18 + 0x24) == 0x37) break;
          iVar18 = iVar18 + 0x40;
          iVar23 = iVar23 + -1;
        } while (iVar23 != 0);
      }
      psVar15 = psVar15 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) * 0x20;
    }
    else {
      psVar15 = (short *)(*(int *)&menuPcs->field_0x850 +
                         (*(short *)(*(int *)&menuPcs->field_0x850 + 2) + 3) * 0x40 + 8);
      if (DOUBLE_80332a58 == (double)*(float *)(psVar15 + 10)) {
        uVar20 = 2;
      }
      else {
        uVar20 = 3;
      }
      local_d0 = (double)CONCAT44(0x43300000,(int)psVar15[3] ^ 0x80000000);
      uStack_e4 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x2a) ^ 0x80000000;
      local_d8 = (double)CONCAT44(0x43300000,uVar20 ^ 0x80000000);
      local_e8 = 0x43300000;
      local_f0 = (double)CONCAT44(0x43300000,(int)psVar15[1] + 8U ^ 0x80000000);
      dVar27 = (double)(float)(((double)(float)((double)(float)(local_d0 - DOUBLE_80332a80) *
                                               (double)*(float *)(psVar15 + 10)) - DOUBLE_80332b20)
                              / (local_d8 - DOUBLE_80332a80));
      local_e0 = (double)CONCAT44(0x43300000,(int)*psVar15 - 0x14U ^ 0x80000000);
      in_f28 = (double)(float)(local_e0 - DOUBLE_80332a80);
      in_f27 = (double)(float)((dVar27 - DOUBLE_80332af8) * DOUBLE_80332a60 +
                              (double)(float)(dVar27 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                        uStack_e4) -
                                                                      DOUBLE_80332a80) +
                                             (double)(float)(local_f0 - DOUBLE_80332a80)));
    }
    if (iVar21 != 2) {
      if (bVar3) {
        local_d8 = (double)CONCAT44(0x43300000,(int)psVar15[3] - 0x20U ^ 0x80000000);
        local_e0 = (double)CONCAT44(0x43300000,(int)psVar15[1] ^ 0x80000000);
        local_d0 = (double)CONCAT44(0x43300000,(int)*psVar15 - 0x14U ^ 0x80000000);
        in_f28 = (double)(float)(local_d0 - DOUBLE_80332a80);
        in_f27 = (double)(float)((local_d8 - DOUBLE_80332a80) * DOUBLE_80332a60 +
                                (local_e0 - DOUBLE_80332a80));
      }
      else {
        local_d0 = (double)CONCAT44(0x43300000,(int)*psVar15 - 0x14U ^ 0x80000000);
        in_f28 = (double)(float)(local_d0 - DOUBLE_80332a80);
        local_d8 = (double)CONCAT44(0x43300000,(int)psVar15[1] ^ 0x80000000);
        in_f27 = (double)(float)(local_d8 - DOUBLE_80332a80);
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) != 0) {
          in_f27 = (double)(float)(in_f27 + (double)FLOAT_80332ad0);
        }
      }
    }
    local_e0 = (double)(longlong)(int)in_f27;
    iVar18 = (int)System.m_frameCounter >> 0x1f;
    local_d0 = (double)(CONCAT44(0x43300000,
                                 (iVar18 * 8 | System.m_frameCounter * 0x20000000 + iVar18 >> 0x1d)
                                 - iVar18) ^ 0x80000000);
    iVar18 = (int)(in_f28 + (double)(float)(local_d0 - DOUBLE_80332a80));
    local_d8 = (double)(longlong)iVar18;
    DrawCursor__8CMenuPcsFiif((double)FLOAT_80332a70,menuPcs,iVar18,(int)in_f27);
  }
  psVar15 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
  iVar18 = *(int *)&menuPcs->field_0x82c;
  iVar21 = (int)*(short *)(iVar18 + 0x28) + (int)*(short *)(iVar18 + 0x34);
  if (*psVar15 <= iVar21) {
    iVar21 = iVar21 - *psVar15;
  }
  psVar15 = *(short **)&menuPcs->field_0x850;
  fVar1 = *(float *)(psVar15 + *psVar15 * 0x20 + 0xc);
  if (!bVar4) {
    unaff_r21 = -1;
  }
  sVar2 = *(short *)(iVar18 + 0x30);
  if (((sVar2 == 0) && (unaff_r21 == -1)) &&
     (*(short *)(uVar5 + *(short *)(iVar18 + 0x26) * 2 + 0x214) == 0)) {
    unaff_r21 = 0x266;
  }
  if ((sVar2 == 1) && (iVar21 < 2)) {
    unaff_r21 = iVar21 + 0x259;
  }
  if (sVar2 == 2) {
    if (*(short *)(iVar18 + 0x2a) == 0) {
      unaff_r21 = 0x25b;
    }
    else {
      unaff_r21 = -1;
    }
  }
  if ((sVar2 == 0) || (sVar2 == 2)) {
    fVar1 = *(float *)(psVar15 + 0xc);
  }
  local_d0 = (double)(longlong)(int)(FLOAT_80332acc * fVar1);
  puVar8 = (undefined4 *)
           __ct__6CColorFUcUcUcUc(auStack_160,0xff,0xff,0xff,(int)(FLOAT_80332acc * fVar1) & 0xff);
  local_15c = *puVar8;
  local_d8 = (double)(longlong)(int)FLOAT_80332b28;
  local_d0 = (double)(longlong)
                     (int)-(float)(in_f26 * (double)FLOAT_80332a88 - (double)FLOAT_80332b08);
  DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(menuPcs,unaff_r21);
  return;
}

