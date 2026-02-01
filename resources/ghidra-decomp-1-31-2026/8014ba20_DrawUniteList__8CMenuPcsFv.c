// Function: DrawUniteList__8CMenuPcsFv
// Entry: 8014ba20
// Size: 3228 bytes

/* WARNING: Removing unreachable block (ram,0x8014c6a0) */
/* WARNING: Removing unreachable block (ram,0x8014c698) */
/* WARNING: Removing unreachable block (ram,0x8014c690) */
/* WARNING: Removing unreachable block (ram,0x8014c688) */
/* WARNING: Removing unreachable block (ram,0x8014c680) */
/* WARNING: Removing unreachable block (ram,0x8014c678) */
/* WARNING: Removing unreachable block (ram,0x8014c670) */
/* WARNING: Removing unreachable block (ram,0x8014c668) */
/* WARNING: Removing unreachable block (ram,0x8014ba68) */
/* WARNING: Removing unreachable block (ram,0x8014ba60) */
/* WARNING: Removing unreachable block (ram,0x8014ba58) */
/* WARNING: Removing unreachable block (ram,0x8014ba50) */
/* WARNING: Removing unreachable block (ram,0x8014ba48) */
/* WARNING: Removing unreachable block (ram,0x8014ba40) */
/* WARNING: Removing unreachable block (ram,0x8014ba38) */
/* WARNING: Removing unreachable block (ram,0x8014ba30) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawUniteList__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  short sVar2;
  bool bVar3;
  uint32_t uVar4;
  int32_t iVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  short *psVar11;
  int iVar12;
  undefined *puVar13;
  uint32_t uVar14;
  int unaff_r20;
  int unaff_r21;
  undefined4 *puVar15;
  int iVar16;
  CFont *pCVar17;
  uint uVar18;
  short *psVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double in_f28;
  double in_f29;
  double dVar26;
  undefined auStack_130 [4];
  undefined4 local_12c;
  undefined auStack_128 [4];
  undefined4 local_124;
  undefined4 local_120;
  undefined auStack_11c [4];
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_108;
  uint uStack_104;
  undefined4 local_100;
  uint uStack_fc;
  undefined4 local_f8;
  uint uStack_f4;
  undefined8 local_f0;
  longlong local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  
  uVar4 = Game.game.m_scriptFoodBase[0];
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  iVar7 = *(int *)&menuPcs->field_0x850;
  iVar16 = 0;
  bVar3 = false;
  iVar12 = 0;
  uVar18 = (uint)*(short *)(iVar7 + 8);
  DAT_8032eec8 = 0;
  psVar19 = (short *)(iVar7 + *(short *)(iVar7 + 2) * 0x40 + 8);
  uVar14 = uVar4;
  do {
    if (iVar12 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26)) {
      bVar3 = true;
    }
    else if (-1 < *(short *)(uVar14 + 0x214)) {
      bVar3 = false;
    }
    if (*(short *)(uVar4 + 0xbaa) <= iVar12) break;
    if (*(short *)(uVar14 + 0x214) != 0) {
      psVar11 = (short *)(*(int *)&menuPcs->field_0x850 + iVar16 + 8);
      local_108 = 0x43300000;
      local_f0 = (double)(longlong)(int)(FLOAT_80332acc * *(float *)(psVar11 + 8));
      uStack_104 = (int)*psVar11 + 4U ^ 0x80000000;
      uStack_fc = (int)psVar11[1] ^ 0x80000000;
      uStack_f4 = (int)psVar11[2] - 8U ^ 0x80000000;
      dVar22 = (double)(float)((double)CONCAT44(0x43300000,uStack_104) - DOUBLE_80332a80);
      dVar24 = (double)*(float *)(psVar11 + 4);
      local_100 = 0x43300000;
      in_f29 = (double)(float)((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80332a80);
      local_f8 = 0x43300000;
      in_f28 = (double)(float)((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80332a80);
      local_110 = CONCAT31(0xffffff,(char)(int)(FLOAT_80332acc * *(float *)(psVar11 + 8)));
      local_114 = local_110;
      GXSetChanMatColor(4,&local_114);
      if (0 < *(short *)(uVar14 + 0x214)) {
        if (iVar12 + 2 < 8) {
          if (*(short *)(uVar14 + 0x218) == -1) {
            unaff_r20 = 3;
          }
          else {
            unaff_r20 = 2;
          }
        }
        else {
          unaff_r20 = 2;
        }
        iVar8 = *(int *)&menuPcs->field_0x82c;
        iVar7 = (int)*(short *)(iVar8 + 0x26);
        unaff_r21 = iVar12;
        if ((iVar12 <= iVar7) && (iVar7 < iVar12 + unaff_r20)) {
          if ((*(short *)(iVar8 + 0x12) == 3) && (iVar12 != iVar7)) {
            *(short *)(iVar8 + 0x26) = (short)iVar12;
          }
          bVar3 = true;
        }
      }
      uVar9 = 0x35;
      if (unaff_r20 == 2) {
        uVar9 = 0x36;
      }
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar9);
      dVar20 = (double)FLOAT_80332ab0;
      if (bVar3) {
        dVar20 = (double)FLOAT_80332ad4;
      }
      DrawRect__8CMenuPcsFUlfffffffff
                (dVar22,(double)(float)(in_f29 - (double)FLOAT_80332ad0),in_f28,
                 (double)FLOAT_80332ad4,dVar24,dVar20,(double)FLOAT_80332a70,(double)FLOAT_80332a70,
                 &MenuPcs,0);
    }
    iVar12 = iVar12 + 1;
    iVar16 = iVar16 + 0x40;
    uVar14 = uVar14 + 2;
  } while (iVar12 < 8);
  pCVar17 = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_80332a70,pCVar17);
  SetShadow__5CFontFi(pCVar17,1);
  SetScale__5CFontFf(FLOAT_80332ad8,pCVar17);
  DrawInit__5CFontFv(pCVar17);
  SetTlut__5CFontFi(pCVar17,7);
  psVar11 = (short *)(*(int *)&menuPcs->field_0x850 + 8);
  uVar14 = uVar4;
  for (iVar7 = 0; iVar7 < *(short *)(uVar4 + 0xbaa); iVar7 = iVar7 + 1) {
    if ((7 < iVar7) || (*(short *)(uVar14 + 0x214) != 0)) {
      fVar1 = FLOAT_80332a70;
      if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) != 3) {
        fVar1 = *(float *)(psVar11 + 8);
      }
      local_f0 = (double)(longlong)(int)(FLOAT_80332acc * fVar1);
      puVar15 = (undefined4 *)
                __ct__6CColorFUcUcUcUc(auStack_11c,0xff,0xff,0xff,(int)(FLOAT_80332acc * fVar1));
      local_118 = *puVar15;
      SetColor__5CFontF8_GXColor(pCVar17,&local_118);
      if (iVar7 < 2) {
        iVar5 = GetMenuStr__8CMenuPcsFi(menuPcs,iVar7 + 9);
      }
      else {
        if (*(short *)(uVar14 + 0x204) < 0) goto LAB_8014bea8;
        iVar5 = Game.game.m_cFlatDataArr[1].m_table[0].index
                [*(short *)(uVar4 + *(short *)(uVar14 + 0x204) * 2 + 0xb6) * 5 + 4];
      }
      dVar22 = (double)GetWidth__5CFontFPc(pCVar17,iVar5);
      uVar10 = (uint)*psVar11;
      uStack_f4 = uVar10 ^ 0x80000000;
      local_f0 = (double)(CONCAT44(0x43300000,(int)psVar11[2]) ^ 0x80000000);
      fVar1 = (float)((double)(float)((double)(float)(local_f0 - DOUBLE_80332a80) - dVar22) *
                      DOUBLE_80332a60 + ((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80332a80));
      if (uVar18 != uVar10) {
        uStack_f4 = uVar18 - uVar10 ^ 0x80000000;
        local_f0 = (double)CONCAT44(0x43300000,uVar10 + psVar11[2] + -0x18 ^ 0x80000000);
        fVar1 = (float)(ABS((double)CONCAT44(0x43300000,uStack_f4) - DOUBLE_80332a80) *
                       DOUBLE_80332ae0) *
                ((float)((double)(float)(local_f0 - DOUBLE_80332a80) - dVar22) - fVar1) + fVar1;
      }
      local_f8 = 0x43300000;
      local_f0 = (double)(CONCAT44(0x43300000,psVar11[1] + 3) ^ 0x80000000);
      in_f29 = (double)(float)(local_f0 - DOUBLE_80332a80);
      SetPosX__5CFontFf(fVar1,pCVar17);
      SetPosY__5CFontFf((float)(in_f29 - (double)FLOAT_80332ae8),pCVar17);
      Draw__5CFontFPc(pCVar17,iVar5);
    }
LAB_8014bea8:
    uVar14 = uVar14 + 2;
    psVar11 = psVar11 + 0x20;
  }
  DrawInit__8CMenuPcsFv(menuPcs);
  iVar12 = 0;
  iVar7 = 0;
  uVar14 = uVar4;
  do {
    iVar16 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
    if (iVar12 == iVar16) {
      bVar3 = true;
    }
    else if (-1 < *(short *)(uVar14 + 0x214)) {
      bVar3 = false;
    }
    if (*(short *)(uVar4 + 0xbaa) <= iVar12) break;
    if (*(short *)(uVar14 + 0x214) != 0) {
      if (0 < *(short *)(uVar14 + 0x214)) {
        if (iVar12 + 2 < 8) {
          if (*(short *)(uVar14 + 0x218) == -1) {
            unaff_r20 = 3;
          }
          else {
            unaff_r20 = 2;
          }
        }
        else {
          unaff_r20 = 2;
        }
        unaff_r21 = iVar12;
        if ((iVar12 <= iVar16) && (iVar16 < iVar12 + unaff_r20)) {
          bVar3 = true;
        }
      }
      if (iVar12 == unaff_r21 + unaff_r20 + -1) {
        iVar8 = *(int *)&menuPcs->field_0x850 + iVar7 + 8;
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x38);
        iVar16 = unaff_r21;
        if (unaff_r21 == *(short *)(*(int *)&menuPcs->field_0x82c + 0x26)) {
          iVar16 = unaff_r21 + 1;
        }
        in_f28 = (double)FLOAT_80332aec;
        local_f0 = (double)(CONCAT44(0x43300000,
                                     uVar18 * 2 -
                                     (int)*(short *)(*(int *)&menuPcs->field_0x850 +
                                                    iVar16 * 0x40 + 8)) ^ 0x80000000);
        dVar22 = (double)(float)(local_f0 - DOUBLE_80332a80);
        fVar1 = FLOAT_80332ab0;
        if (bVar3) {
          fVar1 = FLOAT_80332ac8;
        }
        dVar24 = (double)fVar1;
        iVar16 = *(int *)&menuPcs->field_0x850 + unaff_r21 * 0x40 + 8;
        uVar10 = (uint)*(short *)(iVar16 + 2);
        local_f8 = 0x43300000;
        uStack_fc = uVar10 ^ 0x80000000;
        uStack_f4 = ((int)*(short *)(iVar8 + 2) + (int)*(short *)(iVar8 + 6)) - uVar10 ^ 0x80000000;
        local_100 = 0x43300000;
        in_f29 = (double)(float)((double)((float)((double)CONCAT44(0x43300000,uStack_f4) -
                                                 DOUBLE_80332a80) - FLOAT_80332ac8) *
                                 DOUBLE_80332a60 +
                                ((double)CONCAT44(0x43300000,uStack_fc) - DOUBLE_80332a80));
        if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) == 3) {
          fVar1 = *(float *)(iVar16 + 0x10);
        }
        else {
          uStack_104 = uVar18 ^ 0x80000000;
          local_108 = 0x43300000;
          fVar1 = (float)(ABS((double)(float)(dVar22 - (double)(float)((double)CONCAT44(0x43300000,
                                                                                        uStack_104)
                                                                      - DOUBLE_80332a80))) *
                         DOUBLE_80332ae0);
        }
        dVar23 = (double)fVar1;
        local_e8 = (longlong)(int)((double)FLOAT_80332acc * dVar23);
        local_110 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80332acc * dVar23));
        local_120 = local_110;
        GXSetChanMatColor(4,&local_120);
        local_e0 = (double)(longlong)(int)dVar22;
        local_d8 = (double)(longlong)(int)in_f29;
        iVar16 = (int)FLOAT_80332aec;
        local_d0 = (double)(longlong)iVar16;
        iVar8 = (int)FLOAT_80332ac8;
        local_c8 = (double)(longlong)iVar8;
        psVar19[DAT_8032eec8 * 0x20] = (short)(int)dVar22;
        dVar20 = (double)FLOAT_80332af0;
        psVar19[DAT_8032eec8 * 0x20 + 1] = (short)(int)in_f29;
        fVar1 = FLOAT_80332ab0;
        psVar19[DAT_8032eec8 * 0x20 + 2] = (short)iVar16;
        psVar19[DAT_8032eec8 * 0x20 + 3] = (short)iVar8;
        *(float *)(psVar19 + DAT_8032eec8 * 0x20 + 4) = fVar1;
        *(float *)(psVar19 + DAT_8032eec8 * 0x20 + 6) = (float)dVar24;
        *(float *)(psVar19 + DAT_8032eec8 * 0x20 + 8) = (float)dVar23;
        s_UniteTop[DAT_8032eec8] = unaff_r21;
        DAT_8032eec8 = DAT_8032eec8 + 1;
        DrawRect__8CMenuPcsFUlfffffffff(dVar22,(double)(float)(in_f29 - dVar20),&MenuPcs,0);
      }
    }
    iVar12 = iVar12 + 1;
    iVar7 = iVar7 + 0x40;
    uVar14 = uVar14 + 2;
  } while (iVar12 < 8);
  pCVar17 = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_80332a70,pCVar17);
  SetShadow__5CFontFi(pCVar17,1);
  SetScale__5CFontFf(FLOAT_80332a70,pCVar17);
  DrawInit__5CFontFv(pCVar17);
  SetTlut__5CFontFi(pCVar17,6);
  puVar15 = s_UniteTop;
  dVar26 = (double)FLOAT_80332acc;
  dVar25 = (double)FLOAT_80332ae8;
  iVar7 = 0;
  dVar22 = DOUBLE_80332af8;
  dVar24 = DOUBLE_80332a60;
  dVar20 = DOUBLE_80332b00;
  dVar23 = DOUBLE_80332a80;
  do {
    if (DAT_8032eec8 <= iVar7) {
      DrawInit__8CMenuPcsFv(menuPcs);
      if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) == 0) &&
         (sVar2 = *(short *)(uVar4 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 2 + 0x214),
         iVar7 = (int)sVar2, sVar2 != 0)) {
        uVar18 = (uint)(FLOAT_80332acc * *(float *)(*(int *)&menuPcs->field_0x850 + 0x18));
        local_c8 = (double)(longlong)(int)uVar18;
        if ((iVar7 == 0x207) || ((iVar7 == 0x20b || (iVar7 == 0x20f)))) {
          iVar7 = iVar7 + 2;
        }
        puVar15 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_130,0xff,0xff,0xff,uVar18 & 0xff);
        local_d0 = (double)(longlong)(int)in_f29;
        local_12c = *puVar15;
        local_c8 = (double)(longlong)
                           (int)-(float)(in_f28 * (double)FLOAT_80332a88 - (double)FLOAT_80332b08);
        DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(menuPcs,iVar7);
      }
      return;
    }
    fVar1 = FLOAT_80332a70;
    if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) != 3) {
      fVar1 = *(float *)(psVar19 + 8);
    }
    local_c8 = (double)(longlong)(int)(dVar26 * (double)fVar1);
    puVar6 = (undefined4 *)
             __ct__6CColorFUcUcUcUc(auStack_128,0xff,0xff,0xff,(int)(dVar26 * (double)fVar1));
    local_124 = *puVar6;
    SetColor__5CFontF8_GXColor(pCVar17,&local_124);
    iVar12 = (int)*(short *)(uVar4 + *puVar15 * 2 + 0x214);
    if (iVar12 == 0x207) {
      puVar13 = PTR_s_Colpo_Fire_80214d50;
      if (Game.game.m_gameWork.m_languageId != '\x03') {
        if (Game.game.m_gameWork.m_languageId < 3) {
          if ((Game.game.m_gameWork.m_languageId == '\x01') ||
             (puVar13 = PTR_s_Feuer_Hieb_80214d3c, Game.game.m_gameWork.m_languageId == '\0')) {
LAB_8014c338:
            puVar13 = PTR_s_Flamestrike_80214d28;
          }
        }
        else {
          puVar13 = PTR_s_Efecto_Fuego_80214d78;
          if ((Game.game.m_gameWork.m_languageId != '\x05') &&
             (puVar13 = PTR_s_Pyro_Frappe_80214d64, 4 < Game.game.m_gameWork.m_languageId))
          goto LAB_8014c338;
        }
      }
    }
    else if (iVar12 == 0x20b) {
      puVar13 = PTR_s_Colpo_Blizzard_80214d54;
      if (Game.game.m_gameWork.m_languageId != '\x03') {
        if (Game.game.m_gameWork.m_languageId < 3) {
          if ((Game.game.m_gameWork.m_languageId == '\x01') ||
             (puVar13 = PTR_s_Eis_Hieb_80214d40, Game.game.m_gameWork.m_languageId == '\0')) {
LAB_8014c39c:
            puVar13 = PTR_s_Icestrike_80214d2c;
          }
        }
        else {
          puVar13 = PTR_s_Efecto_Hielo_80214d7c;
          if ((Game.game.m_gameWork.m_languageId != '\x05') &&
             (puVar13 = PTR_s_Cryo_Frappe_80214d68, 4 < Game.game.m_gameWork.m_languageId))
          goto LAB_8014c39c;
        }
      }
    }
    else if (iVar12 == 0x20f) {
      puVar13 = PTR_s_Colpo_Thunder_80214d58;
      if (Game.game.m_gameWork.m_languageId != '\x03') {
        if (Game.game.m_gameWork.m_languageId < 3) {
          if ((Game.game.m_gameWork.m_languageId == '\x01') ||
             (puVar13 = PTR_s_Blitz_Hieb_80214d44, Game.game.m_gameWork.m_languageId == '\0')) {
LAB_8014c3fc:
            puVar13 = PTR_s_Thunderstrike_80214d30;
          }
        }
        else {
          puVar13 = PTR_s_Efecto_Electro_80214d80;
          if ((Game.game.m_gameWork.m_languageId != '\x05') &&
             (puVar13 = PTR_DAT_80214d6c, 4 < Game.game.m_gameWork.m_languageId)) goto LAB_8014c3fc;
        }
      }
    }
    else if (iVar12 == 0x222) {
      puVar13 = PTR_DAT_80214d5c;
      if (Game.game.m_gameWork.m_languageId != '\x03') {
        if (Game.game.m_gameWork.m_languageId < 3) {
          if ((Game.game.m_gameWork.m_languageId == '\x01') ||
             (puVar13 = PTR_DAT_80214d48, Game.game.m_gameWork.m_languageId == '\0')) {
LAB_8014c45c:
            puVar13 = PTR_DAT_80214d34;
          }
        }
        else {
          puVar13 = PTR_DAT_80214d84;
          if ((Game.game.m_gameWork.m_languageId != '\x05') &&
             (puVar13 = PTR_DAT_80214d70, 4 < Game.game.m_gameWork.m_languageId)) goto LAB_8014c45c;
        }
      }
    }
    else if (iVar12 == 0x227) {
      puVar13 = PTR_DAT_80214d60;
      if (Game.game.m_gameWork.m_languageId != '\x03') {
        if (Game.game.m_gameWork.m_languageId < 3) {
          if ((Game.game.m_gameWork.m_languageId == '\x01') ||
             (puVar13 = PTR_DAT_80214d4c, Game.game.m_gameWork.m_languageId == '\0')) {
LAB_8014c4bc:
            puVar13 = PTR_DAT_80214d38;
          }
        }
        else {
          puVar13 = PTR_DAT_80214d88;
          if ((Game.game.m_gameWork.m_languageId != '\x05') &&
             (puVar13 = PTR_DAT_80214d74, 4 < Game.game.m_gameWork.m_languageId)) goto LAB_8014c4bc;
        }
      }
    }
    else {
      puVar13 = (undefined *)Game.game.m_cFlatDataArr[1].m_table[0].index[iVar12 * 5 + 4];
    }
    dVar21 = (double)GetWidth__5CFontFPc(pCVar17,puVar13);
    local_c8 = (double)CONCAT44(0x43300000,(int)psVar19[3] ^ 0x80000000);
    local_d0 = (double)CONCAT44(0x43300000,(int)psVar19[1] ^ 0x80000000);
    local_d8 = (double)CONCAT44(0x43300000,(int)psVar19[2] ^ 0x80000000);
    local_e0 = (double)CONCAT44(0x43300000,(int)*psVar19 ^ 0x80000000);
    in_f29 = (double)(float)((((local_c8 - dVar23) - dVar22) * dVar24 + (local_d0 - dVar23)) -
                            dVar20);
    SetPosX__5CFontFf((float)((double)(float)((double)(float)(local_d8 - dVar23) - dVar21) * dVar24
                             + (local_e0 - dVar23)),pCVar17);
    SetPosY__5CFontFf((float)(in_f29 - dVar25),pCVar17);
    Draw__5CFontFPc(pCVar17,puVar13);
    puVar15 = puVar15 + 1;
    iVar7 = iVar7 + 1;
    psVar19 = psVar19 + 0x20;
  } while( true );
}

