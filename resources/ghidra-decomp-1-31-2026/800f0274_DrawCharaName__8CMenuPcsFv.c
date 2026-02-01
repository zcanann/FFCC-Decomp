// Function: DrawCharaName__8CMenuPcsFv
// Entry: 800f0274
// Size: 2044 bytes

/* WARNING: Removing unreachable block (ram,0x800f0a54) */
/* WARNING: Removing unreachable block (ram,0x800f0a4c) */
/* WARNING: Removing unreachable block (ram,0x800f0a44) */
/* WARNING: Removing unreachable block (ram,0x800f0a3c) */
/* WARNING: Removing unreachable block (ram,0x800f0a34) */
/* WARNING: Removing unreachable block (ram,0x800f0a2c) */
/* WARNING: Removing unreachable block (ram,0x800f0a24) */
/* WARNING: Removing unreachable block (ram,0x800f0a1c) */
/* WARNING: Removing unreachable block (ram,0x800f0a14) */
/* WARNING: Removing unreachable block (ram,0x800f0a0c) */
/* WARNING: Removing unreachable block (ram,0x800f02cc) */
/* WARNING: Removing unreachable block (ram,0x800f02c4) */
/* WARNING: Removing unreachable block (ram,0x800f02bc) */
/* WARNING: Removing unreachable block (ram,0x800f02b4) */
/* WARNING: Removing unreachable block (ram,0x800f02ac) */
/* WARNING: Removing unreachable block (ram,0x800f02a4) */
/* WARNING: Removing unreachable block (ram,0x800f029c) */
/* WARNING: Removing unreachable block (ram,0x800f0294) */
/* WARNING: Removing unreachable block (ram,0x800f028c) */
/* WARNING: Removing unreachable block (ram,0x800f0284) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawCharaName__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  short sVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint8_t *puVar11;
  int iVar12;
  uint uVar13;
  CFont *font;
  int iVar14;
  int iVar15;
  int iVar16;
  undefined **ppuVar17;
  uint uVar18;
  uint uVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  double dVar30;
  undefined auStack_130 [4];
  undefined4 local_12c;
  undefined auStack_128 [4];
  undefined4 local_124;
  undefined auStack_120 [4];
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  uint8_t auStack_110 [32];
  undefined8 local_f0;
  
  font = *(CFont **)&menuPcs->field_0xf8;
  iVar8 = *(int *)&menuPcs->field_0x828;
  if (Game.game.m_gameWork.m_languageId == '\x03') {
    ppuVar17 = &PTR_s_Vuoto_8032e900;
    goto LAB_800f033c;
  }
  if (Game.game.m_gameWork.m_languageId < 3) {
    if ((Game.game.m_gameWork.m_languageId != '\x01') && (Game.game.m_gameWork.m_languageId != '\0')
       ) {
      ppuVar17 = &PTR_DAT_8032e8f8;
      goto LAB_800f033c;
    }
  }
  else {
    if (Game.game.m_gameWork.m_languageId == '\x05') {
      ppuVar17 = &PTR_DAT_8032e910;
      goto LAB_800f033c;
    }
    if (Game.game.m_gameWork.m_languageId < 5) {
      ppuVar17 = &PTR_DAT_8032e908;
      goto LAB_800f033c;
    }
  }
  ppuVar17 = &PTR_s_Empty_8032e8f0;
LAB_800f033c:
  iVar5 = *(int *)&menuPcs->field_0x82c;
  if (*(short *)(iVar5 + 0x10) == 1) {
    local_f0 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar5 + 0x22)) ^ 0x80000000);
    dVar24 = (double)(float)(DOUBLE_803314e8 * (local_f0 - DOUBLE_80331408));
  }
  else if (*(short *)(iVar5 + 0x10) == 2) {
    dVar24 = (double)FLOAT_803313e8;
  }
  else {
    local_f0 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar5 + 0x22)) ^ 0x80000000);
    dVar24 = (double)(float)-(DOUBLE_803314e8 * (local_f0 - DOUBLE_80331408) - DOUBLE_80331420);
  }
  uVar13 = 0;
  uVar18 = 0;
  uVar19 = 0;
  iVar5 = 2;
  do {
    if (*(char *)(iVar8 + 0xd) != '\0') {
      uVar6 = 1 << (int)*(short *)(iVar8 + 4);
      uVar18 = uVar18 | uVar6;
      if (*(char *)(iVar8 + 10) != '\0') {
        uVar13 = uVar13 | uVar6;
      }
      if ((*(char *)(iVar8 + 0xb) != '\0') || (*(char *)(iVar8 + 0xc) != '\0')) {
        uVar19 = uVar19 | uVar6;
      }
    }
    if (*(char *)(iVar8 + 0x1d) != '\0') {
      uVar6 = 1 << (int)*(short *)(iVar8 + 0x14);
      uVar18 = uVar18 | uVar6;
      if (*(char *)(iVar8 + 0x1a) != '\0') {
        uVar13 = uVar13 | uVar6;
      }
      if ((*(char *)(iVar8 + 0x1b) != '\0') || (*(char *)(iVar8 + 0x1c) != '\0')) {
        uVar19 = uVar19 | uVar6;
      }
    }
    iVar8 = iVar8 + 0x20;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  SetMargin__5CFontFf(FLOAT_803313e8,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_8033158c,font);
  DrawInit__5CFontFv(font);
  DrawInit__8CMenuPcsFv(menuPcs);
  dVar30 = (double)(float)((double)FLOAT_80331458 * dVar24);
  iVar8 = (int)((double)FLOAT_80331458 * dVar24);
  local_f0 = (double)(longlong)iVar8;
  local_114 = CONCAT31(0xffffff,(char)iVar8);
  local_118 = local_114;
  GXSetChanMatColor(4,&local_118);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x28);
  iVar8 = 0;
  iVar15 = 0;
  iVar5 = 0;
  dVar28 = (double)FLOAT_80331478;
  dVar29 = -(DOUBLE_80331418 * (double)FLOAT_80331680 - DOUBLE_80331678);
  dVar27 = (double)FLOAT_80331684;
  dVar23 = DOUBLE_80331408;
  do {
    local_f0 = (double)(CONCAT44(0x43300000,iVar15) ^ 0x80000000);
    dVar26 = (double)(float)((double)(float)(dVar28 + (double)(float)(local_f0 - dVar23)) + dVar27);
    if (iVar8 != 0) {
      dVar26 = (double)(float)(dVar26 + (double)FLOAT_80331548);
    }
    iVar10 = iVar5 * 0xc30;
    iVar12 = 0;
    uVar6 = 0;
    iVar14 = iVar5;
    do {
      if ((uVar13 & 1 << iVar14) != 0) {
        local_f0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
        dVar25 = (double)(FLOAT_80331410 + (float)(local_f0 - DOUBLE_80331408));
        dVar20 = (double)GetWidth__5CFontFPc(font,iVar10 + -0x7fddf986);
        fVar3 = FLOAT_803313e8;
        dVar22 = dVar29;
        if ((double)FLOAT_80331680 < dVar20 * DOUBLE_803313f8) {
          fVar3 = (float)(((double)(float)(dVar20 + DOUBLE_80331510) * DOUBLE_803313f8) /
                         (double)FLOAT_80331680);
          dVar22 = (double)(float)((double)FLOAT_8033155c -
                                  (double)(float)(dVar20 + DOUBLE_80331510));
        }
        dVar20 = (double)(float)(dVar22 * DOUBLE_803313f8 + dVar25);
        dVar22 = (double)fVar3;
        DrawRect__8CMenuPcsFUlfffffffff
                  (dVar20,dVar26,(double)FLOAT_80331680,(double)FLOAT_80331410,
                   (double)FLOAT_803313dc,(double)FLOAT_803313dc,dVar22,(double)FLOAT_803313e8,
                   &MenuPcs,0);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)(float)((double)FLOAT_80331680 * dVar22 + dVar20),dVar26,
                   (double)FLOAT_80331680,(double)FLOAT_80331410,(double)FLOAT_803313dc,
                   (double)FLOAT_803313dc,dVar22,(double)FLOAT_803313e8,&MenuPcs,8);
      }
      iVar12 = iVar12 + 1;
      iVar10 = iVar10 + 0xc30;
      uVar6 = uVar6 + 0x90;
      iVar14 = iVar14 + 1;
    } while (iVar12 < 4);
    iVar8 = iVar8 + 1;
    iVar5 = iVar5 + 4;
    iVar15 = iVar15 + 0xb8;
  } while (iVar8 < 2);
  DrawInit__8CMenuPcsFv(menuPcs);
  SetMargin__5CFontFf(FLOAT_803313e8,font);
  SetShadow__5CFontFi(font,1);
  SetScale__5CFontFf(FLOAT_8033158c,font);
  DrawInit__5CFontFv(font);
  local_f0 = (double)(longlong)(int)dVar30;
  puVar7 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_120,0xff,0xff,0xff,(int)dVar30);
  local_11c = *puVar7;
  SetColor__5CFontF8_GXColor(font,&local_11c);
  iVar8 = 0;
  dVar22 = (double)FLOAT_80331410;
  iVar15 = 0;
  iVar5 = 0;
  dVar28 = (double)FLOAT_8033155c;
  dVar29 = (double)FLOAT_80331478;
  dVar30 = (double)FLOAT_80331688;
  dVar26 = (double)FLOAT_80331550;
  dVar23 = DOUBLE_803313f8;
  dVar27 = DOUBLE_80331408;
  do {
    local_f0 = (double)(CONCAT44(0x43300000,iVar15) ^ 0x80000000);
    dVar20 = (double)(float)((double)(float)(dVar29 + (double)(float)(local_f0 - dVar27)) + dVar30);
    if (iVar8 != 0) {
      dVar20 = (double)(float)(dVar20 + (double)FLOAT_80331548);
    }
    dVar20 = (double)(float)(dVar20 - dVar26);
    iVar12 = iVar5 * 0x9c0;
    iVar10 = 0;
    iVar16 = iVar5 * 0xc30;
    uVar13 = 0;
    iVar14 = iVar5;
    do {
      bVar1 = false;
      sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x1c);
      local_f0 = (double)CONCAT44(0x43300000,uVar13 ^ 0x80000000);
      dVar25 = (double)(float)(dVar22 + (double)(float)(local_f0 - dVar27));
      if ((sVar2 == 8) && (*(int *)&menuPcs->field_0x88c != 0)) {
        uVar6 = *(uint *)(*(int *)&menuPcs->field_0x88c + iVar12 + 0x1a84);
        uVar6 = -uVar6 | uVar6;
      }
      else {
        uVar6 = *(uint *)(Game.game.m_caravanWorkArr[0].m_backupCmdlistExtra + iVar16 + 0x14);
        uVar6 = -uVar6 | uVar6;
      }
      if ((int)uVar6 < 0) {
        if (((sVar2 == 8) && (menuPcs->field_0x888 == '\x01')) &&
           (*(int *)&menuPcs->field_0x88c != 0)) {
          memset(auStack_110,0,0x20);
          memcpy(auStack_110,*(int *)&menuPcs->field_0x88c + iVar12 + 0x15c0,0x10);
          puVar11 = auStack_110;
        }
        else {
          puVar11 = Game.game.m_caravanWorkArr[0].unk_0x3ca_0x3dd + iVar16;
        }
        if ((uVar18 & 1 << iVar14) == 0) {
          SetTlut__5CFontFi(font,8);
        }
        else {
          SetTlut__5CFontFi(font,6);
        }
      }
      else if ((uVar19 & 1 << iVar14) == 0) {
        if ((uVar18 & 1 << iVar14) == 0) {
          SetTlut__5CFontFi(font,8);
        }
        else {
          SetTlut__5CFontFi(font,7);
        }
        puVar11 = *ppuVar17;
      }
      else {
        SetTlut__5CFontFi(font,0x10);
        puVar11 = ppuVar17[1];
        bVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2;
        iVar4 = (int)System.m_frameCounter / 0x14 + ((int)System.m_frameCounter >> 0x1f);
        uVar6 = (System.m_frameCounter + (iVar4 - (iVar4 >> 0x1f)) * -0x14) - 10;
        if (bVar1) {
          uVar9 = (int)uVar6 >> 0x1f;
          local_f0 = (double)(CONCAT44(0x43300000,(uVar9 ^ uVar6) - uVar9) ^ 0x80000000);
          dVar24 = (double)(float)-(DOUBLE_80331460 * (local_f0 - DOUBLE_80331408) - DOUBLE_80331420
                                   );
        }
        local_f0 = (double)(longlong)(int)((double)FLOAT_80331458 * dVar24);
        puVar7 = (undefined4 *)
                 __ct__6CColorFUcUcUcUc
                           (auStack_128,0xff,0xff,0xff,(int)((double)FLOAT_80331458 * dVar24));
        local_124 = *puVar7;
        SetColor__5CFontF8_GXColor(font,&local_124);
      }
      dVar21 = (double)GetWidth__5CFontFPc(font,puVar11);
      SetPosX__5CFontFf((float)((double)(float)(dVar28 - dVar21) * dVar23 + dVar25),font);
      SetPosY__5CFontFf((float)dVar20,font);
      Draw__5CFontFPc(font,puVar11);
      if (bVar1) {
        puVar7 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_130,0xff,0xff,0xff,0xff);
        local_12c = *puVar7;
        SetColor__5CFontF8_GXColor(font,&local_12c);
      }
      iVar10 = iVar10 + 1;
      iVar16 = iVar16 + 0xc30;
      iVar12 = iVar12 + 0x9c0;
      uVar13 = uVar13 + 0x90;
      iVar14 = iVar14 + 1;
    } while (iVar10 < 4);
    iVar8 = iVar8 + 1;
    iVar5 = iVar5 + 4;
    iVar15 = iVar15 + 0xb8;
  } while (iVar8 < 2);
  DrawInit__8CMenuPcsFv(menuPcs);
  return;
}

