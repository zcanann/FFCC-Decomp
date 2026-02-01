// Function: DrawMake__9CShopMenuFv
// Entry: 80153a64
// Size: 5172 bytes

/* WARNING: Removing unreachable block (ram,0x80154e7c) */
/* WARNING: Removing unreachable block (ram,0x80154e74) */
/* WARNING: Removing unreachable block (ram,0x80154e6c) */
/* WARNING: Removing unreachable block (ram,0x80154e64) */
/* WARNING: Removing unreachable block (ram,0x80153a8c) */
/* WARNING: Removing unreachable block (ram,0x80153a84) */
/* WARNING: Removing unreachable block (ram,0x80153a7c) */
/* WARNING: Removing unreachable block (ram,0x80153a74) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawMake__9CShopMenuFv(CShopMenu *shopMenu)

{
  uint uVar1;
  short sVar2;
  float fVar3;
  int iVar4;
  undefined4 *puVar5;
  char cVar8;
  int iVar6;
  undefined4 *puVar7;
  CFont *font;
  int32_t iVar9;
  undefined *puVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  uint uVar15;
  short *psVar16;
  int iVar17;
  int iVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  undefined4 local_2d8;
  undefined auStack_2d4 [4];
  undefined4 local_2d0;
  undefined auStack_2cc [4];
  undefined4 local_2c8;
  undefined auStack_2c4 [4];
  undefined4 local_2c0;
  undefined auStack_2bc [4];
  undefined auStack_2b8 [4];
  undefined4 local_2b4;
  undefined auStack_2b0 [4];
  undefined4 local_2ac;
  undefined auStack_2a8 [4];
  undefined4 local_2a4;
  undefined auStack_2a0 [4];
  undefined4 local_29c;
  short local_298 [6];
  undefined auStack_28c [64];
  undefined auStack_24c [64];
  undefined auStack_20c [64];
  undefined auStack_1cc [64];
  undefined auStack_18c [132];
  undefined8 local_108;
  longlong local_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  double local_c8;
  undefined8 local_c0;
  double local_b8;
  double local_b0;
  undefined4 local_a8;
  undefined *puStack_a4;
  int local_a0;
  CMenuPcs *local_9c;
  CMenuPcs *local_98;
  CMenuPcs *local_94;
  CMenuPcs *local_90;
  
  DrawMakeBase__9CShopMenuFv();
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0xf,0,0xa8,0x4a,0xff,0,0,0);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawSingleIcon__8CMenuPcsFiiifif
            ((double)FLOAT_80332d28,(double)FLOAT_80332d28,&MenuPcs,
             *(undefined4 *)&shopMenu->field_0x150,0x40,0x32,0);
  uVar12 = MenuPcs._248_4_;
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._248_4_);
  SetShadow__5CFontFi((CFont *)uVar12,1);
  SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2a0,0xff,0xff,0xff,0xff);
  local_29c = *puVar5;
  SetColor__5CFontF8_GXColor((CFont *)uVar12,&local_29c);
  DrawInit__5CFontFv((CFont *)uVar12);
  if (*(int *)&shopMenu->field_0x150 < 1) {
    iVar9 = 0;
  }
  else {
    iVar9 = Game.game.m_cFlatDataArr[1].m_table[0].index[*(int *)&shopMenu->field_0x150 * 5 + 4];
  }
  DrawInit__5CFontFv((CFont *)uVar12);
  DrawShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)FLOAT_80332d54,(double)FLOAT_80332e0c,&MenuPcs,uVar12,iVar9,0x18,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  local_a0 = (Game.game.m_gameWork.m_languageId - 1) * 0x54;
  puVar10 = (&PTR_DAT_80214da4)[(Game.game.m_gameWork.m_languageId - 1) * 0x15];
  DrawInit__5CFontFv((CFont *)uVar12);
  local_108 = 4503601774854324.0;
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(4503601774854324.0 - DOUBLE_80332d20),(double)FLOAT_80332d58,&MenuPcs,
             uVar12,puVar10,0x18,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  dVar19 = (double)GetWidth__5CFontFPc((CFont *)uVar12,puVar10);
  local_100 = 0x43300000800000b4;
  uVar15 = (uint)((float)(4503601774854324.0 - DOUBLE_80332d20) +
                 (float)((double)FLOAT_80332d5c + dVar19));
  local_f8 = (double)(longlong)(int)uVar15;
  GetRaceStr__8CMenuPcsFiPc(&MenuPcs,*(undefined4 *)&shopMenu->field_0x150,auStack_18c);
  cVar8 = ChkEquipPossible__8CMenuPcsFi(&MenuPcs,*(undefined4 *)&shopMenu->field_0x150);
  uVar11 = 2;
  if (cVar8 != '\0') {
    uVar11 = 0x18;
  }
  DrawInit__5CFontFv((CFont *)uVar12);
  local_f0 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_f0 - DOUBLE_80332d20),(double)FLOAT_80332d58,&MenuPcs,uVar12,
             auStack_18c,uVar11,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  iVar6 = *(int *)&shopMenu->field_0x14;
  iVar4 = *(int *)&shopMenu->field_0x28;
  if (iVar6 == 0) {
    iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar4 * 2 + 0xbe6);
  }
  else if (iVar6 == 1) {
    iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar4 * 2 + 0xb6);
  }
  else if (iVar6 == 2) {
    if (*(int *)(&shopMenu->field_0x50 + iVar4 * 4) == -1) {
      iVar4 = -1;
    }
    else {
      iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                              *(int *)(&shopMenu->field_0x50 + iVar4 * 4) * 2 + 0xb6);
    }
  }
  else {
    iVar4 = -1;
  }
  if (iVar4 < 1) {
    iVar4 = 0;
  }
  else {
    iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
            (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar4 * 0x48 + 0x24);
    iVar4 = iVar4 / 100 + (iVar4 >> 0x1f);
    iVar4 = iVar4 - (iVar4 >> 0x1f);
  }
  DrawInit__5CFontFv((CFont *)uVar12);
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)uVar12);
  SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  puVar5 = (undefined4 *)((int)&PTR_DAT_80214da8 + local_a0);
  dVar19 = (double)GetWidth__5CFontFPc((CFont *)uVar12,*puVar5);
  uVar11 = MenuPcs._248_4_;
  dVar22 = (double)FLOAT_80332e10;
  uVar15 = (uint)(((float)((double)FLOAT_80332e14 - dVar19) - FLOAT_80332d5c) - FLOAT_80332d5c);
  local_f0 = (double)(longlong)(int)uVar15;
  SetShadow__5CFontFi((CFont *)MenuPcs._248_4_,1);
  SetScaleX__5CFontFf(FLOAT_80332d28,(CFont *)uVar11);
  SetScaleY__5CFontFf(FLOAT_80332d8c,(CFont *)uVar11);
  puVar7 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2bc,0xff,0xff,0xff,0xff);
  local_2c0 = *puVar7;
  SetColor__5CFontF8_GXColor((CFont *)uVar11,&local_2c0);
  DrawInit__5CFontFv((CFont *)uVar11);
  fVar3 = FLOAT_80332d64;
  *(byte *)(uVar11 + 0x24) = *(byte *)(uVar11 + 0x24) & 0xef | 0x10;
  SetMargin__5CFontFf(fVar3,(CFont *)uVar11);
  sprintf(auStack_1cc,&DAT_80332d14,iVar4);
  dVar20 = (double)GetWidth__5CFontFPc((CFont *)uVar11,auStack_1cc);
  local_f8 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
  iVar4 = (int)((double)(float)(local_f8 - DOUBLE_80332d20) - dVar20);
  local_100 = (longlong)iVar4;
  local_108 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_108 - DOUBLE_80332d20),(double)FLOAT_80332e18,&MenuPcs,uVar11,
             auStack_1cc,0x13,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  uVar11 = MenuPcs._248_4_;
  iVar6 = *(int *)&shopMenu->field_0x14;
  iVar4 = *(int *)&shopMenu->field_0x28;
  uVar15 = (uint)((float)((double)FLOAT_80332e1c - dVar19) - FLOAT_80332d5c);
  local_e8 = (double)(longlong)(int)uVar15;
  if (iVar6 == 0) {
    iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar4 * 2 + 0xbe6);
  }
  else if (iVar6 == 1) {
    iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar4 * 2 + 0xb6);
  }
  else if (iVar6 == 2) {
    if (*(int *)(&shopMenu->field_0x50 + iVar4 * 4) == -1) {
      iVar4 = -1;
    }
    else {
      iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                              *(int *)(&shopMenu->field_0x50 + iVar4 * 4) * 2 + 0xb6);
    }
  }
  else {
    iVar4 = -1;
  }
  if (iVar4 < 1) {
    iVar4 = 0;
  }
  else {
    iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
            (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar4 * 0x48 + 0x24);
    iVar4 = iVar4 / 100 + (iVar4 >> 0x1f);
    iVar4 = iVar4 - (iVar4 >> 0x1f);
  }
  uVar13 = 2;
  if (iVar4 <= *(int *)(*(int *)&shopMenu->field_0x20 + 0x200)) {
    uVar13 = 0x14;
  }
  uVar14 = *(undefined4 *)(*(int *)&shopMenu->field_0x20 + 0x200);
  SetShadow__5CFontFi((CFont *)MenuPcs._248_4_,1);
  SetScaleX__5CFontFf(FLOAT_80332d28,(CFont *)uVar11);
  SetScaleY__5CFontFf(FLOAT_80332d8c,(CFont *)uVar11);
  puVar7 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2c4,0xff,0xff,0xff,0xff);
  local_2c8 = *puVar7;
  SetColor__5CFontF8_GXColor((CFont *)uVar11,&local_2c8);
  DrawInit__5CFontFv((CFont *)uVar11);
  fVar3 = FLOAT_80332d64;
  *(byte *)(uVar11 + 0x24) = *(byte *)(uVar11 + 0x24) & 0xef | 0x10;
  SetMargin__5CFontFf(fVar3,(CFont *)uVar11);
  sprintf(auStack_20c,&DAT_80332d14,uVar14);
  dVar19 = (double)GetWidth__5CFontFPc((CFont *)uVar11,auStack_20c);
  local_e8 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
  iVar4 = (int)((double)(float)(local_e8 - DOUBLE_80332d20) - dVar19);
  local_f0 = (double)(longlong)iVar4;
  local_f8 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_f8 - DOUBLE_80332d20),(double)FLOAT_80332e18,&MenuPcs,uVar11,
             auStack_20c,uVar13,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  DrawInit__5CFontFv((CFont *)uVar12);
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  uVar11 = *puVar5;
  SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)uVar12);
  SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  dVar20 = (double)GetWidth__5CFontFPc((CFont *)uVar12,uVar11);
  DrawInit__5CFontFv((CFont *)uVar12);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)FLOAT_80332e14,(double)FLOAT_80332e20,&MenuPcs,uVar12,&DAT_80332d84,0x1b,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  local_100 = 0x4330000080000138;
  uVar15 = (uint)((float)(4503601774854456.0 - DOUBLE_80332d20) -
                 (float)((double)FLOAT_80332d5c + dVar20));
  local_108 = (double)(longlong)(int)uVar15;
  DrawInit__5CFontFv((CFont *)uVar12);
  local_e0 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_e0 - DOUBLE_80332d20),(double)FLOAT_80332e20,&MenuPcs,uVar12,
             uVar11,0x19,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  dVar19 = (double)FLOAT_80332e1c;
  local_d8 = (double)(longlong)(int)(dVar19 - dVar20);
  DrawInit__5CFontFv((CFont *)uVar12);
  local_d0 = (double)CONCAT44(0x43300000,(int)(dVar19 - dVar20) ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_d0 - DOUBLE_80332d20),(double)FLOAT_80332e20,&MenuPcs,uVar12,
             uVar11,0x19,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  uVar12 = MenuPcs._264_4_;
  local_9c = &MenuPcs;
  DrawInit__5CFontFv((CFont *)MenuPcs._264_4_);
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  SetShadow__5CFontFi((CFont *)uVar12,0);
  SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2a8,0xff,0xff,0xff,0xff);
  local_2a4 = *puVar5;
  SetColor__5CFontF8_GXColor((CFont *)uVar12,&local_2a4);
  SetPosY__5CFontFf(FLOAT_80332e24,(CFont *)uVar12);
  uVar11 = *(undefined4 *)((int)&PTR_DAT_80214dac + local_a0);
  dVar19 = (double)GetWidth__5CFontFPc((CFont *)uVar12,uVar11);
  iVar4 = (int)((float)((double)FLOAT_80332e28 - dVar19) * FLOAT_80332d78 + FLOAT_80332d6c);
  local_c8 = (double)(longlong)iVar4;
  local_c0 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
  SetPosX__5CFontFf((float)(local_c0 - DOUBLE_80332d20),(CFont *)uVar12);
  Draw__5CFontFPc((CFont *)uVar12,uVar11);
  uVar11 = *(undefined4 *)((int)&PTR_s_Money_80214db0 + local_a0);
  dVar19 = (double)GetWidth__5CFontFPc((CFont *)uVar12,uVar11);
  iVar4 = (int)((float)((double)FLOAT_80332d68 - dVar19) * FLOAT_80332d78 + FLOAT_80332e2c);
  local_b8 = (double)(longlong)iVar4;
  local_b0 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
  SetPosX__5CFontFf((float)(local_b0 - DOUBLE_80332d20),(CFont *)uVar12);
  Draw__5CFontFPc((CFont *)uVar12,uVar11);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,5,0,0x32,0x104,0xff,0,0,0);
  iVar4 = 0x32;
  do {
    iVar6 = iVar4;
    iVar4 = iVar6 + 0x20;
    drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,6,0,iVar4,0x104,0xff,0,0,0);
  } while (iVar4 < 0x20e);
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,5,0,iVar6 + 0x60,0x104,0xff,1,0,0);
  uVar12 = MenuPcs._248_4_;
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._248_4_);
  SetShadow__5CFontFi((CFont *)uVar12,1);
  SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
  puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2b0,0xff,0xff,0xff,0xff);
  local_2ac = *puVar5;
  SetColor__5CFontF8_GXColor((CFont *)uVar12,&local_2ac);
  DrawInit__5CFontFv((CFont *)uVar12);
  uVar11 = *(undefined4 *)((int)&PTR_s_Materials_80214db4 + local_a0);
  dVar19 = (double)GetWidth__5CFontFPc((CFont *)uVar12,uVar11);
  local_b0 = 4503601774854272.0;
  uVar15 = (uint)((float)((double)FLOAT_80332e30 - dVar19) * FLOAT_80332d78 +
                 (float)(4503601774854272.0 - DOUBLE_80332d20));
  local_b8 = (double)(longlong)(int)uVar15;
  DrawInit__5CFontFv((CFont *)uVar12);
  local_c0 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_c0 - DOUBLE_80332d20),(double)FLOAT_80332e34,&MenuPcs,uVar12,
             uVar11,4,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  uVar11 = *(undefined4 *)((int)&PTR_s_Stock_80214db8 + local_a0);
  dVar19 = (double)GetWidth__5CFontFPc((CFont *)uVar12,uVar11);
  local_c8 = 4503601774854564.0;
  uVar15 = (uint)((float)((double)FLOAT_80332e38 - dVar19) * FLOAT_80332d78 +
                 (float)(4503601774854564.0 - DOUBLE_80332d20));
  local_d0 = (double)(longlong)(int)uVar15;
  DrawInit__5CFontFv((CFont *)uVar12);
  local_d8 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)(local_d8 - DOUBLE_80332d20),(double)FLOAT_80332e34,&MenuPcs,uVar12,
             uVar11,9,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  iVar6 = *(int *)&shopMenu->field_0x14;
  uVar15 = 300;
  iVar4 = *(int *)&shopMenu->field_0x28;
  if (iVar6 == 0) {
    iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar4 * 2 + 0xbe6);
  }
  else if (iVar6 == 1) {
    iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar4 * 2 + 0xb6);
  }
  else if (iVar6 == 2) {
    if (*(int *)(&shopMenu->field_0x50 + iVar4 * 4) == -1) {
      iVar4 = -1;
    }
    else {
      iVar4 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                              *(int *)(&shopMenu->field_0x50 + iVar4 * 4) * 2 + 0xb6);
    }
  }
  else {
    iVar4 = -1;
  }
  GetRecipeMaterial__8CMenuPcsFiPQ28CMenuPcs12MaterialInfo(&MenuPcs,iVar4,local_298);
  dVar20 = (double)FLOAT_80332d28;
  dVar23 = (double)FLOAT_80332d10;
  local_98 = &MenuPcs;
  local_94 = &MenuPcs;
  psVar16 = local_298;
  iVar4 = 0;
  local_90 = &MenuPcs;
  dVar19 = DOUBLE_80332d20;
  do {
    if (*psVar16 < 1) break;
    DrawInit__5CFontFv((CFont *)uVar12);
    SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
    SetShadow__5CFontFi((CFont *)uVar12,1);
    SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
    DrawInit__5CFontFv((CFont *)uVar12);
    local_b0 = (double)(CONCAT44(0x43300000,uVar15) ^ 0x80000000);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
              ((double)FLOAT_80332e3c,(double)(float)(local_b0 - dVar19),&MenuPcs,uVar12,
               &DAT_80332d84,0x1b,0x12);
    DrawInit__8CMenuPcsFv(&MenuPcs);
    uVar11 = MenuPcs._248_4_;
    sVar2 = psVar16[3];
    SetShadow__5CFontFi((CFont *)MenuPcs._248_4_,1);
    SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar11);
    puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2cc,0xff,0xff,0xff,0xff);
    local_2d0 = *puVar5;
    SetColor__5CFontF8_GXColor((CFont *)uVar11,&local_2d0);
    DrawInit__5CFontFv((CFont *)uVar11);
    *(byte *)(uVar11 + 0x24) = *(byte *)(uVar11 + 0x24) & 0xef | 0x10;
    SetMargin__5CFontFf((float)(dVar22 * dVar20 + dVar23),(CFont *)uVar11);
    sprintf(auStack_24c,&DAT_80332d14,(int)sVar2);
    dVar22 = (double)GetWidth__5CFontFPc((CFont *)uVar11,auStack_24c);
    local_b8 = 4503601774854516.0;
    local_d0 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
    iVar6 = (int)((double)(float)(4503601774854516.0 - dVar19) - dVar22);
    local_c0 = (double)(longlong)iVar6;
    local_c8 = (double)(CONCAT44(0x43300000,iVar6) ^ 0x80000000);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
              ((double)(float)(local_c8 - dVar19),(double)(float)(local_d0 - dVar19),&MenuPcs,uVar11
               ,auStack_24c,0x1b,0x12);
    DrawInit__8CMenuPcsFv(&MenuPcs);
    DrawInit__5CFontFv((CFont *)uVar12);
    SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
    SetShadow__5CFontFi((CFont *)uVar12,1);
    SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar12);
    dVar22 = (double)GetWidth__5CFontFPc((CFont *)uVar12,&DAT_80332e40);
    local_d8 = (double)(CONCAT44(0x43300000,iVar6 + -8) ^ 0x80000000);
    uVar1 = (uint)((double)(float)(local_d8 - dVar19) - dVar22);
    local_e0 = (double)(longlong)(int)uVar1;
    DrawInit__5CFontFv((CFont *)uVar12);
    local_e8 = (double)CONCAT44(0x43300000,uVar1 ^ 0x80000000);
    local_f0 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
              ((double)(float)(local_e8 - dVar19),(double)(float)(local_f0 - dVar19),&MenuPcs,uVar12
               ,&DAT_80332e40,0x1b,0x12);
    DrawInit__8CMenuPcsFv(&MenuPcs);
    if (*psVar16 < 1) {
      iVar9 = 0;
    }
    else {
      iVar9 = Game.game.m_cFlatDataArr[1].m_table[0].index[*psVar16 * 5 + 4];
    }
    dVar22 = (double)GetWidth__5CFontFPc((CFont *)uVar12,iVar9);
    local_f8 = (double)(CONCAT44(0x43300000,uVar1 - 8) ^ 0x80000000);
    uVar1 = (uint)((double)(float)(local_f8 - dVar19) - dVar22);
    local_100 = (longlong)(int)uVar1;
    DrawInit__5CFontFv((CFont *)uVar12);
    puStack_a4 = (undefined *)(uVar15 ^ 0x80000000);
    local_108 = (double)CONCAT44(0x43300000,uVar1 ^ 0x80000000);
    local_a8 = 0x43300000;
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
              ((double)(float)(local_108 - dVar19),
               (double)(float)((double)CONCAT44(0x43300000,puStack_a4) - dVar19),&MenuPcs,uVar12,
               iVar9,0x1b,0x12);
    DrawInit__8CMenuPcsFv(local_98);
    uVar11 = MenuPcs._248_4_;
    iVar6 = 0;
    sVar2 = *psVar16;
    iVar17 = 0;
    iVar18 = 8;
    do {
      if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar6 + 0xb6) == sVar2) {
        iVar17 = iVar17 + 1;
      }
      if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar6 + 0xb8) == sVar2) {
        iVar17 = iVar17 + 1;
      }
      if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar6 + 0xba) == sVar2) {
        iVar17 = iVar17 + 1;
      }
      if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar6 + 0xbc) == sVar2) {
        iVar17 = iVar17 + 1;
      }
      if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar6 + 0xbe) == sVar2) {
        iVar17 = iVar17 + 1;
      }
      if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar6 + 0xc0) == sVar2) {
        iVar17 = iVar17 + 1;
      }
      if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar6 + 0xc2) == sVar2) {
        iVar17 = iVar17 + 1;
      }
      if (*(short *)(*(int *)&shopMenu->field_0x20 + iVar6 + 0xc4) == sVar2) {
        iVar17 = iVar17 + 1;
      }
      iVar6 = iVar6 + 0x10;
      iVar18 = iVar18 + -1;
    } while (iVar18 != 0);
    uVar13 = 2;
    dVar22 = (double)FLOAT_80332e10;
    if (psVar16[3] <= iVar17) {
      uVar13 = 0x1b;
    }
    SetShadow__5CFontFi((CFont *)MenuPcs._248_4_,1);
    SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar11);
    puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2d4,0xff,0xff,0xff,0xff);
    local_2d8 = *puVar5;
    SetColor__5CFontF8_GXColor((CFont *)uVar11,&local_2d8);
    DrawInit__5CFontFv((CFont *)uVar11);
    fVar3 = FLOAT_80332d64;
    *(byte *)(uVar11 + 0x24) = *(byte *)(uVar11 + 0x24) & 0xef | 0x10;
    SetMargin__5CFontFf(fVar3,(CFont *)uVar11);
    sprintf(auStack_28c,&DAT_80332d18,iVar17);
    dVar21 = (double)GetWidth__5CFontFPc((CFont *)uVar11,auStack_28c);
    puStack_a4 = &DAT_800001c4;
    local_a8 = 0x43300000;
    local_c0 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
    iVar6 = (int)((double)(float)(4503601774854596.0 - dVar19) - dVar21);
    local_b0 = (double)(longlong)iVar6;
    local_b8 = (double)(CONCAT44(0x43300000,iVar6) ^ 0x80000000);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
              ((double)(float)(local_b8 - dVar19),(double)(float)(local_c0 - dVar19),local_94,uVar11
               ,auStack_28c,uVar13,0x12);
    DrawInit__8CMenuPcsFv(local_90);
    iVar4 = iVar4 + 1;
    psVar16 = psVar16 + 1;
    uVar15 = uVar15 + 0x1e;
  } while (iVar4 < 3);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  iVar4 = 0x1f6;
  do {
    drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0xc,0,iVar4,0x18c,0xff,0,0,0);
    iVar4 = iVar4 + -0x10;
  } while (0x32 < iVar4);
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0xb,0,0x226,0x168,0xff,0,0,0);
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,1,1,iVar4,0x18c,0xff,0,0,0);
  font = *(CFont **)&local_9c->field_0x108;
  SetMargin__5CFontFf(FLOAT_80332d28,font);
  SetShadow__5CFontFi(font,0);
  puVar5 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2b8,0xff,0xff,0xff,0xff);
  local_2b4 = *puVar5;
  SetColor__5CFontF8_GXColor(font,&local_2b4);
  SetScaleX__5CFontFf(FLOAT_80332d2c,font);
  SetScaleY__5CFontFf(FLOAT_80332d28,font);
  DrawInit__5CFontFv(font);
  uVar12 = *(undefined4 *)((int)&PTR_s_Craft_80214dbc + local_a0);
  dVar19 = (double)GetWidth__5CFontFPc(font,uVar12);
  puStack_a4 = &DAT_800001f8;
  local_a8 = 0x43300000;
  iVar4 = (int)((float)((double)FLOAT_80332dd4 - dVar19) * FLOAT_80332d78 +
               (float)(4503601774854648.0 - DOUBLE_80332d20));
  local_b0 = (double)(longlong)iVar4;
  local_b8 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
  SetPosX__5CFontFf((float)(local_b8 - DOUBLE_80332d20),font);
  SetPosY__5CFontFf(FLOAT_80332ddc,font);
  Draw__5CFontFPc(font,uVar12);
  uVar12 = *(undefined4 *)((int)&PTR_s_Cancel_80214d98 + local_a0);
  dVar19 = (double)GetWidth__5CFontFPc(font,uVar12);
  local_c0 = 4503601774854648.0;
  iVar4 = (int)((float)((double)FLOAT_80332dd4 - dVar19) * FLOAT_80332d78 +
               (float)(4503601774854648.0 - DOUBLE_80332d20));
  local_c8 = (double)(longlong)iVar4;
  local_d0 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
  SetPosX__5CFontFf((float)(local_d0 - DOUBLE_80332d20),font);
  SetPosY__5CFontFf(FLOAT_80332e44,font);
  Draw__5CFontFPc(font,uVar12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawCursor__8CMenuPcsFiif
            ((double)FLOAT_80332d28,&MenuPcs,iVar4 + -0x24,
             *(int *)&shopMenu->field_0x3c * 0x18 + 0x14c);
  return;
}

