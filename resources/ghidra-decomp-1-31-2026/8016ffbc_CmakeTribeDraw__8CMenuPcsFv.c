// Function: CmakeTribeDraw__8CMenuPcsFv
// Entry: 8016ffbc
// Size: 2292 bytes

/* WARNING: Removing unreachable block (ram,0x80170894) */
/* WARNING: Removing unreachable block (ram,0x8017088c) */
/* WARNING: Removing unreachable block (ram,0x80170884) */
/* WARNING: Removing unreachable block (ram,0x8017087c) */
/* WARNING: Removing unreachable block (ram,0x8016ffe4) */
/* WARNING: Removing unreachable block (ram,0x8016ffdc) */
/* WARNING: Removing unreachable block (ram,0x8016ffd4) */
/* WARNING: Removing unreachable block (ram,0x8016ffcc) */

void CmakeTribeDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  CFont *pCVar7;
  uint uVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined auStack_c0 [4];
  undefined4 local_bc;
  undefined auStack_b8 [4];
  undefined4 local_b4;
  undefined8 local_b0;
  undefined8 local_a8;
  undefined4 local_a0;
  uint uStack_9c;
  longlong local_98;
  undefined4 local_90;
  uint uStack_8c;
  longlong local_88;
  double local_80;
  double local_78;
  double local_70;
  
  uVar6 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) - 1;
  if ((int)uVar6 < 0) {
    uVar6 = 0;
  }
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if (sVar1 == 0) {
    local_b0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    dVar13 = (double)(float)(DOUBLE_80333268 * (local_b0 - DOUBLE_803332d0));
  }
  else if (sVar1 == 1) {
    dVar13 = (double)FLOAT_80333258;
  }
  else {
    local_b0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    dVar13 = (double)(float)-(DOUBLE_80333268 * (local_b0 - DOUBLE_803332d0) - DOUBLE_80333270);
  }
  DrawWMFrame0__8CMenuPcsFif((double)FLOAT_80333258,menuPcs,1);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_c8 = 0xffffffff;
  local_c4 = 0xffffffff;
  GXSetChanMatColor(4,&local_c4);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x3f);
  dVar10 = (double)FLOAT_80333254;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar10,(double)FLOAT_803332d8,(double)FLOAT_803332dc,(double)FLOAT_803332e0,dVar10,
             dVar10,(double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803332e4,(double)FLOAT_803332d8,(double)FLOAT_803332dc,
             (double)FLOAT_803332e0,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,8);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x40);
  dVar11 = (double)FLOAT_80333254;
  dVar10 = DOUBLE_803332d0;
  for (uVar6 = 0x20; (int)uVar6 < 0x260; uVar6 = uVar6 + uVar8) {
    uVar8 = 0x20;
    if ((int)(0x260 - uVar6) < 0x20) {
      uVar8 = 0x260 - uVar6;
    }
    local_b0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    local_a8 = (double)CONCAT44(0x43300000,uVar8 ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(local_b0 - dVar10),(double)FLOAT_803332d8,
               (double)(float)(local_a8 - dVar10),(double)FLOAT_803332e0,dVar11,dVar11,
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
      local_d0 = 0xffffffff;
      local_cc = 0xffffffff;
      GXSetChanMatColor(4,&local_cc);
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
  dVar10 = (double)(float)((double)FLOAT_80333240 * dVar13);
  iVar2 = (int)((double)FLOAT_80333240 * dVar13);
  local_a8 = (double)(longlong)iVar2;
  local_d8 = CONCAT31(0xffffff,(char)iVar2);
  local_d4 = local_d8;
  GXSetChanMatColor(4,&local_d4);
  uVar5 = 0x3a;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar5 = 0x61;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar5);
  local_a0 = 0x43300000;
  uStack_9c = (uint)-((double)FLOAT_80333280 * DOUBLE_80333298 - DOUBLE_80333288);
  local_b0 = (double)(longlong)(int)uStack_9c;
  local_90 = 0x43300000;
  uStack_8c = (uint)-((double)FLOAT_803332c8 * DOUBLE_80333298 - DOUBLE_80333310);
  local_98 = (longlong)(int)uStack_8c;
  uStack_9c = uStack_9c ^ 0x80000000;
  uStack_8c = uStack_8c ^ 0x80000000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_9c) - DOUBLE_803332d0),
             (double)(float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_803332d0),
             (double)FLOAT_80333280,(double)FLOAT_80333284,(double)FLOAT_80333254,
             (double)FLOAT_80333254,(double)FLOAT_80333258,(double)FLOAT_80333318,&MenuPcs,0);
  DrawCmakeTitle__8CMenuPcsFiff(dVar13,(double)FLOAT_80333258,menuPcs,3);
  uVar6 = (uint)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_88 = (longlong)(int)dVar10;
  local_e0 = CONCAT31(0xffffff,(char)(int)dVar10);
  local_dc = local_e0;
  GXSetChanMatColor(4,&local_dc);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x31);
  local_80 = (double)(CONCAT44(0x43300000,(uVar6 & 1) * 0xb8) ^ 0x80000000);
  local_78 = (double)(CONCAT44(0x43300000,((int)uVar6 / 2) * 0xb8) ^ 0x80000000);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803332e8,(double)FLOAT_803332ec,(double)FLOAT_803332a8,
             (double)FLOAT_803332a8,(double)(float)(local_80 - DOUBLE_803332d0),
             (double)(float)(local_78 - DOUBLE_803332d0),(double)FLOAT_80333258,
             (double)FLOAT_80333258,&MenuPcs,0);
  pCVar7 = *(CFont **)&menuPcs->field_0xfc;
  SetMargin__5CFontFf(FLOAT_80333258,pCVar7);
  SetShadow__5CFontFi(pCVar7,0);
  SetScale__5CFontFf(FLOAT_80333258,pCVar7);
  DrawInit__5CFontFv(pCVar7);
  local_70 = (double)(longlong)(int)dVar10;
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_b8,0xff,0xff,0xff,(int)dVar10);
  local_b4 = *puVar3;
  SetColor__5CFontF8_GXColor(pCVar7,&local_b4);
  iVar2 = 0;
  dVar12 = (double)FLOAT_803332f4;
  iVar4 = 0x88;
  dVar11 = DOUBLE_803332d0;
  do {
    uVar5 = GetTribeStr__8CMenuPcsFi(menuPcs,iVar2);
    SetPosX__5CFontFf(FLOAT_80333284,pCVar7);
    local_70 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
    SetPosY__5CFontFf((float)((double)(float)(local_70 - dVar11) - dVar12),pCVar7);
    Draw__5CFontFPc(pCVar7,uVar5);
    iVar2 = iVar2 + 1;
    iVar4 = iVar4 + 0x1c;
  } while (iVar2 < 4);
  pCVar7 = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_80333258,pCVar7);
  SetShadow__5CFontFi(pCVar7,1);
  SetScale__5CFontFf(FLOAT_80333258,pCVar7);
  DrawInit__5CFontFv(pCVar7);
  local_70 = (double)(longlong)(int)dVar10;
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_c0,0xff,0xff,0xff,(int)dVar10);
  local_bc = *puVar3;
  SetColor__5CFontF8_GXColor(pCVar7,&local_bc);
  SetTlut__5CFontFi(pCVar7,6);
  iVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 8;
  if (s_CmakeInfo._18_1_ != '\0') {
    iVar2 = iVar2 + 4;
  }
  iVar9 = 0;
  dVar11 = (double)FLOAT_803332f4;
  iVar4 = 0x88;
  dVar10 = DOUBLE_803332d0;
  do {
    uVar5 = GetHairStr__8CMenuPcsFi(menuPcs,iVar2 + iVar9);
    SetPosX__5CFontFf(FLOAT_8033331c,pCVar7);
    local_70 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
    SetPosY__5CFontFf((float)((double)(float)(local_70 - dVar10) - dVar11),pCVar7);
    Draw__5CFontFPc(pCVar7,uVar5);
    iVar9 = iVar9 + 1;
    iVar4 = iVar4 + 0x1c;
  } while (iVar9 < 4);
  DrawInit__8CMenuPcsFv(menuPcs);
  iVar2 = *(int *)&menuPcs->field_0x82c;
  if (*(short *)(iVar2 + 0x10) == 1) {
    local_70 = (double)(CONCAT44(0x43300000,*(short *)(iVar2 + 0x26) * 0x1c + 0x88) ^ 0x80000000);
    dVar10 = local_70 - DOUBLE_803332d0;
    if (*(short *)(iVar2 + 0x30) == 0) {
      iVar2 = (int)dVar10;
      local_80 = (double)(longlong)iVar2;
      iVar4 = (int)System.m_frameCounter >> 0x1f;
      local_70 = (double)(CONCAT44(0x43300000,
                                   (iVar4 * 8 | System.m_frameCounter * 0x20000000 + iVar4 >> 0x1d)
                                   - iVar4) ^ 0x80000000);
      iVar4 = (int)(FLOAT_80333320 + (float)(local_70 - DOUBLE_803332d0));
      local_78 = (double)(longlong)iVar4;
      DrawCursor__8CMenuPcsFiif(dVar13,menuPcs,iVar4,iVar2);
    }
    else {
      if ((System.m_frameCounter & 1) != 0) {
        local_70 = (double)(longlong)(int)FLOAT_80333320;
        iVar2 = (int)dVar10;
        local_78 = (double)(longlong)iVar2;
        DrawCursor__8CMenuPcsFiif(dVar13,menuPcs,(int)FLOAT_80333320,iVar2);
      }
      iVar2 = (int)System.m_frameCounter >> 0x1f;
      local_70 = (double)(CONCAT44(0x43300000,
                                   (iVar2 * 8 | System.m_frameCounter * 0x20000000 + iVar2 >> 0x1d)
                                   - iVar2) ^ 0x80000000);
      local_80 = (double)(CONCAT44(0x43300000,
                                   *(short *)(*(int *)&menuPcs->field_0x82c + 0x28) * 0x1c + 0x88) ^
                         0x80000000);
      iVar2 = (int)(FLOAT_80333324 + (float)(local_70 - DOUBLE_803332d0));
      local_78 = (double)(longlong)iVar2;
      local_88 = (longlong)(int)(local_80 - DOUBLE_803332d0);
      DrawCursor__8CMenuPcsFiif(dVar13,menuPcs,iVar2,(int)(local_80 - DOUBLE_803332d0));
    }
  }
  if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) != 3) &&
     (DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0), *(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1
     )) {
    DrawMcWinMess__8CMenuPcsFii(menuPcs,0x15,0);
  }
  return;
}

