// Function: CmakeSexDraw__8CMenuPcsFv
// Entry: 80170ce8
// Size: 1624 bytes

/* WARNING: Removing unreachable block (ram,0x80171324) */
/* WARNING: Removing unreachable block (ram,0x8017131c) */
/* WARNING: Removing unreachable block (ram,0x80171314) */
/* WARNING: Removing unreachable block (ram,0x8017130c) */
/* WARNING: Removing unreachable block (ram,0x80171304) */
/* WARNING: Removing unreachable block (ram,0x80170d18) */
/* WARNING: Removing unreachable block (ram,0x80170d10) */
/* WARNING: Removing unreachable block (ram,0x80170d08) */
/* WARNING: Removing unreachable block (ram,0x80170d00) */
/* WARNING: Removing unreachable block (ram,0x80170cf8) */

void CmakeSexDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  CFont *font;
  uint uVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined auStack_a8 [4];
  undefined4 local_a4;
  undefined8 local_a0;
  undefined8 local_98;
  double local_90;
  longlong local_88;
  undefined4 local_80;
  uint uStack_7c;
  undefined8 local_78;
  
  uVar6 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) - 1;
  if ((int)uVar6 < 0) {
    uVar6 = 0;
  }
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if (sVar1 == 0) {
    local_a0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    dVar12 = (double)(float)(DOUBLE_80333268 * (local_a0 - DOUBLE_803332d0));
  }
  else if (sVar1 == 1) {
    dVar12 = (double)FLOAT_80333258;
  }
  else {
    local_a0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    dVar12 = (double)(float)-(DOUBLE_80333268 * (local_a0 - DOUBLE_803332d0) - DOUBLE_80333270);
  }
  DrawWMFrame0__8CMenuPcsFif((double)FLOAT_80333258,menuPcs,1);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_b0 = 0xffffffff;
  local_ac = 0xffffffff;
  GXSetChanMatColor(4,&local_ac);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x3f);
  dVar8 = (double)FLOAT_80333254;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar8,(double)FLOAT_803332d8,(double)FLOAT_803332dc,(double)FLOAT_803332e0,dVar8,dVar8,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803332e4,(double)FLOAT_803332d8,(double)FLOAT_803332dc,
             (double)FLOAT_803332e0,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,8);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x40);
  dVar10 = (double)FLOAT_80333254;
  dVar8 = DOUBLE_803332d0;
  for (uVar6 = 0x20; (int)uVar6 < 0x260; uVar6 = uVar6 + uVar7) {
    uVar7 = 0x20;
    if ((int)(0x260 - uVar6) < 0x20) {
      uVar7 = 0x260 - uVar6;
    }
    local_a0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    local_98 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(local_a0 - dVar8),(double)FLOAT_803332d8,
               (double)(float)(local_98 - dVar8),(double)FLOAT_803332e0,dVar10,dVar10,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  iVar2 = (int)*(short *)&menuPcs->field_0x86a;
  iVar4 = *(int *)&menuPcs->field_0x814;
  if (*(int *)(iVar4 + (iVar2 + 0x20) * 0x50) != 0) {
    *(undefined2 *)(iVar4 + 0x6e8) = 0xff24;
    *(undefined2 *)(iVar4 + 0x6ea) = 4;
    DrawInit__8CMenuPcsFv(menuPcs);
    if (**(int **)(&menuPcs->field_0x7f4 + iVar2 * 4) == 3) {
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x32);
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      local_b8 = 0xffffffff;
      local_b4 = 0xffffffff;
      GXSetChanMatColor(4,&local_b4);
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)FLOAT_80333244,(double)FLOAT_80333248,(double)FLOAT_8033324c,
                 (double)FLOAT_80333250,(double)FLOAT_80333254,(double)FLOAT_80333254,
                 (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
    }
    else {
      SetProjection__8CMenuPcsFi(menuPcs,0x16);
      SetLight__8CMenuPcsFi(menuPcs,2);
      *(float *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar2 * 4) + 0x168) + 0x9c) =
           FLOAT_80333258;
      Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)(&menuPcs->field_0x7f4 + iVar2 * 4),5);
      RestoreProjection__8CMenuPcsFv(menuPcs);
    }
    DrawInit__8CMenuPcsFv(menuPcs);
  }
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  dVar8 = (double)(float)((double)FLOAT_80333240 * dVar12);
  iVar2 = (int)((double)FLOAT_80333240 * dVar12);
  local_98 = (double)(longlong)iVar2;
  local_c0 = CONCAT31(0xffffff,(char)iVar2);
  local_bc = local_c0;
  GXSetChanMatColor(4,&local_bc);
  uVar5 = 0x3a;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar5 = 0x61;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar5);
  iVar2 = (int)-((double)FLOAT_80333328 * DOUBLE_80333298 - DOUBLE_80333288);
  local_a0 = (double)(longlong)iVar2;
  local_80 = 0x43300000;
  uStack_7c = (uint)-((double)FLOAT_8033332c * DOUBLE_80333298 - DOUBLE_80333310);
  local_88 = (longlong)(int)uStack_7c;
  local_90 = (double)(CONCAT44(0x43300000,iVar2) ^ 0x80000000);
  uStack_7c = uStack_7c ^ 0x80000000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)(local_90 - DOUBLE_803332d0),
             (double)(float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_803332d0),
             (double)FLOAT_80333280,(double)FLOAT_80333284,(double)FLOAT_80333254,
             (double)FLOAT_80333254,(double)FLOAT_80333330,(double)FLOAT_80333330,&MenuPcs,0);
  DrawCmakeTitle__8CMenuPcsFiff(dVar12,(double)FLOAT_80333258,menuPcs,2);
  font = *(CFont **)&menuPcs->field_0xfc;
  SetMargin__5CFontFf(FLOAT_80333258,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_80333258,font);
  DrawInit__5CFontFv(font);
  local_78 = (double)(longlong)(int)dVar8;
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_a8,0xff,0xff,0xff,(int)dVar8);
  local_a4 = *puVar3;
  SetColor__5CFontF8_GXColor(font,&local_a4);
  dVar12 = (double)FLOAT_80333254;
  iVar4 = 0;
  iVar2 = 0x9c;
  dVar13 = (double)FLOAT_803332f4;
  dVar8 = DOUBLE_80333298;
  dVar10 = DOUBLE_80333288;
  dVar11 = DOUBLE_803332d0;
  do {
    uVar5 = GetMenuStr__8CMenuPcsFi(menuPcs,iVar4 + 0x11);
    dVar9 = (double)GetWidth__5CFontFPc(font,uVar5);
    if (dVar12 < dVar9) {
      dVar12 = dVar9;
    }
    SetPosX__5CFontFf((float)-(dVar9 * dVar8 - dVar10),font);
    local_78 = (double)(CONCAT44(0x43300000,iVar2) ^ 0x80000000);
    SetPosY__5CFontFf((float)((double)(float)(local_78 - dVar11) - dVar13),font);
    Draw__5CFontFPc(font,uVar5);
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + 0x28;
  } while (iVar4 < 2);
  DrawInit__8CMenuPcsFv(menuPcs);
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 1) {
    iVar2 = (int)System.m_frameCounter >> 0x1f;
    local_80 = 0x43300000;
    uStack_7c = (iVar2 * 8 | System.m_frameCounter * 0x20000000 + iVar2 >> 0x1d) - iVar2 ^
                0x80000000;
    local_78 = (double)CONCAT44(0x43300000,
                                *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x28 ^ 0x80000000
                               );
    iVar2 = (int)((double)((float)(DOUBLE_80333288 - dVar12 * DOUBLE_80333298) +
                          (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_803332d0)) -
                 dVar12 * DOUBLE_80333298);
    local_88 = (longlong)iVar2;
    iVar4 = (int)(FLOAT_80333334 + (float)(local_78 - DOUBLE_803332d0));
    local_90 = (double)(longlong)iVar4;
    DrawCursor__8CMenuPcsFiif((double)FLOAT_80333258,menuPcs,iVar2,iVar4);
  }
  return;
}

