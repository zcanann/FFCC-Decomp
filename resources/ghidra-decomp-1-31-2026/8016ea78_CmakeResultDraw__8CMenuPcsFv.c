// Function: CmakeResultDraw__8CMenuPcsFv
// Entry: 8016ea78
// Size: 2688 bytes

/* WARNING: Removing unreachable block (ram,0x8016f4dc) */
/* WARNING: Removing unreachable block (ram,0x8016f4d4) */
/* WARNING: Removing unreachable block (ram,0x8016f4cc) */
/* WARNING: Removing unreachable block (ram,0x8016f4c4) */
/* WARNING: Removing unreachable block (ram,0x8016f4bc) */
/* WARNING: Removing unreachable block (ram,0x8016f4b4) */
/* WARNING: Removing unreachable block (ram,0x8016eab0) */
/* WARNING: Removing unreachable block (ram,0x8016eaa8) */
/* WARNING: Removing unreachable block (ram,0x8016eaa0) */
/* WARNING: Removing unreachable block (ram,0x8016ea98) */
/* WARNING: Removing unreachable block (ram,0x8016ea90) */
/* WARNING: Removing unreachable block (ram,0x8016ea88) */

void CmakeResultDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  CmakeInfo *pCVar7;
  float *pfVar8;
  uint uVar9;
  CFont *pCVar10;
  float *pfVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined auStack_d0 [4];
  undefined4 local_cc;
  undefined auStack_c8 [4];
  undefined4 local_c4;
  float local_c0 [4];
  undefined auStack_b0 [24];
  undefined8 local_98;
  undefined8 local_90;
  
  uVar6 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) - 1;
  if ((int)uVar6 < 0) {
    uVar6 = 0;
  }
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if (sVar1 == 0) {
    auStack_b0._20_4_ = uVar6 ^ 0x80000000;
    auStack_b0._16_4_ = 0x43300000;
    dVar16 = (double)(float)(DOUBLE_80333268 *
                            ((double)CONCAT44(0x43300000,auStack_b0._20_4_) - DOUBLE_803332d0));
  }
  else if (sVar1 == 1) {
    dVar16 = (double)FLOAT_80333258;
  }
  else {
    auStack_b0._20_4_ = uVar6 ^ 0x80000000;
    auStack_b0._16_4_ = 0x43300000;
    dVar16 = (double)(float)-(DOUBLE_80333268 *
                              ((double)CONCAT44(0x43300000,auStack_b0._20_4_) - DOUBLE_803332d0) -
                             DOUBLE_80333270);
  }
  DrawWMFrame0__8CMenuPcsFif((double)FLOAT_80333258,menuPcs,1);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_d8 = 0xffffffff;
  local_d4 = 0xffffffff;
  GXSetChanMatColor(4,&local_d4);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x3f);
  dVar12 = (double)FLOAT_80333254;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar12,(double)FLOAT_803332d8,(double)FLOAT_803332dc,(double)FLOAT_803332e0,dVar12,
             dVar12,(double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803332e4,(double)FLOAT_803332d8,(double)FLOAT_803332dc,
             (double)FLOAT_803332e0,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,8);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x40);
  dVar15 = (double)FLOAT_80333254;
  dVar12 = DOUBLE_803332d0;
  for (uVar6 = 0x20; (int)uVar6 < 0x260; uVar6 = uVar6 + uVar9) {
    uVar9 = 0x20;
    if ((int)(0x260 - uVar6) < 0x20) {
      uVar9 = 0x260 - uVar6;
    }
    auStack_b0._20_4_ = uVar6 ^ 0x80000000;
    auStack_b0._16_4_ = 0x43300000;
    local_98 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,auStack_b0._20_4_) - dVar12),
               (double)FLOAT_803332d8,(double)(float)(local_98 - dVar12),(double)FLOAT_803332e0,
               dVar15,dVar15,(double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
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
      local_e0 = 0xffffffff;
      local_dc = 0xffffffff;
      GXSetChanMatColor(4,&local_dc);
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
  if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2) &&
     (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) < 0)) {
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_e8 = 0xffffffff;
    local_e4 = 0xffffffff;
    GXSetChanMatColor(4,&local_e4);
    uVar5 = 0x3a;
    if (*(short *)&menuPcs->field_0x86c != 0) {
      uVar5 = 0x61;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar5);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_80333278,(double)FLOAT_8033327c,(double)FLOAT_80333280,
               (double)FLOAT_80333284,(double)FLOAT_80333254,(double)FLOAT_80333254,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  else {
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_98 = (double)(longlong)(int)((double)FLOAT_80333240 * dVar16);
    local_f0 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80333240 * dVar16));
    local_ec = local_f0;
    GXSetChanMatColor(4,&local_ec);
    uVar5 = 0x3a;
    if (*(short *)&menuPcs->field_0x86c != 0) {
      uVar5 = 0x61;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar5);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_80333278,(double)FLOAT_8033327c,(double)FLOAT_80333280,
               (double)FLOAT_80333284,(double)FLOAT_80333254,(double)FLOAT_80333254,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2) &&
     (0 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x1e))) {
    DrawCmakeTitle__8CMenuPcsFiff((double)FLOAT_80333258,dVar16,menuPcs,6);
  }
  else {
    DrawCmakeTitle__8CMenuPcsFiff(dVar16,(double)FLOAT_80333258,menuPcs,6);
  }
  if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2) &&
     (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) < 0)) {
    uVar6 = (uint)(char)s_CmakeInfo._19_1_;
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_f8 = 0xffffffff;
    local_f4 = 0xffffffff;
    GXSetChanMatColor(4,&local_f4);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x31);
    local_98 = (double)(CONCAT44(0x43300000,(uVar6 & 1) * 0xb8) ^ 0x80000000);
    auStack_b0._20_4_ = ((int)uVar6 / 2) * 0xb8 ^ 0x80000000;
    auStack_b0._16_4_ = 0x43300000;
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_803332e8,(double)FLOAT_803332ec,(double)FLOAT_803332a8,
               (double)FLOAT_803332a8,(double)(float)(local_98 - DOUBLE_803332d0),
               (double)(float)((double)CONCAT44(0x43300000,auStack_b0._20_4_) - DOUBLE_803332d0),
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  else {
    uVar6 = (uint)(char)s_CmakeInfo._19_1_;
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_98 = (double)(longlong)(int)((double)FLOAT_80333240 * dVar16);
    local_100 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80333240 * dVar16));
    local_fc = local_100;
    GXSetChanMatColor(4,&local_fc);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x31);
    auStack_b0._20_4_ = (uVar6 & 1) * 0xb8 ^ 0x80000000;
    auStack_b0._16_4_ = 0x43300000;
    local_90 = (double)(CONCAT44(0x43300000,((int)uVar6 / 2) * 0xb8) ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_803332e8,(double)FLOAT_803332ec,(double)FLOAT_803332a8,
               (double)FLOAT_803332a8,
               (double)(float)((double)CONCAT44(0x43300000,auStack_b0._20_4_) - DOUBLE_803332d0),
               (double)(float)(local_90 - DOUBLE_803332d0),(double)FLOAT_80333258,
               (double)FLOAT_80333258,&MenuPcs,0);
  }
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 1) {
    iVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) + 1;
  }
  else {
    iVar2 = 0;
  }
  DrawCmakeYesNo__8CMenuPcsFif(dVar16,menuPcs,iVar2);
  if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2) &&
     (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) < 0)) {
    dVar16 = (double)FLOAT_80333258;
  }
  pCVar10 = *(CFont **)&menuPcs->field_0xfc;
  SetMargin__5CFontFf(FLOAT_80333258,pCVar10);
  SetShadow__5CFontFi(pCVar10,0);
  SetScale__5CFontFf(FLOAT_80333258,pCVar10);
  DrawInit__5CFontFv(pCVar10);
  dVar17 = (double)(float)((double)FLOAT_80333240 * dVar16);
  iVar2 = (int)((double)FLOAT_80333240 * dVar16);
  local_90 = (double)(longlong)iVar2;
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_c8,0xff,0xff,0xff,iVar2);
  local_c4 = *puVar3;
  SetColor__5CFontF8_GXColor(pCVar10,&local_c4);
  pfVar8 = local_c0;
  dVar15 = (double)FLOAT_803332f0;
  dVar12 = (double)FLOAT_803332f4;
  iVar2 = 0;
  iVar4 = 0x70;
  pfVar11 = pfVar8;
  dVar16 = DOUBLE_803332d0;
  do {
    uVar5 = GetMenuStr__8CMenuPcsFi(menuPcs,iVar2 + 0x2a);
    dVar13 = (double)GetWidth__5CFontFPc(pCVar10,uVar5);
    *pfVar11 = (float)(dVar15 + dVar13);
    SetPosX__5CFontFf((float)dVar15,pCVar10);
    local_90 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
    SetPosY__5CFontFf((float)((double)(float)(local_90 - dVar16) - dVar12),pCVar10);
    Draw__5CFontFPc(pCVar10,uVar5);
    iVar2 = iVar2 + 1;
    pfVar11 = pfVar11 + 1;
    iVar4 = iVar4 + 0x28;
  } while (iVar2 < 4);
  pCVar10 = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_80333258,pCVar10);
  SetShadow__5CFontFi(pCVar10,1);
  SetScale__5CFontFf(FLOAT_80333258,pCVar10);
  DrawInit__5CFontFv(pCVar10);
  local_90 = (double)(longlong)(int)dVar17;
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_d0,0xff,0xff,0xff,(int)dVar17);
  local_cc = *puVar3;
  SetColor__5CFontF8_GXColor(pCVar10,&local_cc);
  SetTlut__5CFontFi(pCVar10,6);
  dVar12 = (double)FLOAT_803332fc;
  dVar15 = (double)FLOAT_803332f4;
  iVar2 = 0;
  uVar6 = 0x70;
  dVar16 = DOUBLE_803332d0;
  do {
    if (iVar2 == 0) {
      pCVar7 = &s_CmakeInfo;
    }
    else if (iVar2 == 1) {
      pCVar7 = (CmakeInfo *)GetMenuStr__8CMenuPcsFi(menuPcs,(char)s_CmakeInfo._18_1_ + 0x11);
    }
    else if (iVar2 == 2) {
      uVar5 = GetTribeStr__8CMenuPcsFi(menuPcs,(int)(char)s_CmakeInfo._19_1_);
      strcpy(auStack_b0,uVar5);
      strcat(auStack_b0,&DAT_803332f8);
      pCVar7 = (CmakeInfo *)auStack_b0;
    }
    else {
      pCVar7 = (CmakeInfo *)GetJobStr__8CMenuPcsFi(menuPcs,(int)(char)s_CmakeInfo._21_1_);
    }
    dVar14 = (double)(float)(dVar12 + (double)*pfVar8);
    local_90 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    dVar13 = (double)(float)(local_90 - dVar16);
    dVar17 = (double)GetWidth__5CFontFPc(pCVar10,pCVar7);
    SetPosX__5CFontFf((float)dVar14,pCVar10);
    SetPosY__5CFontFf((float)(dVar13 - dVar15),pCVar10);
    Draw__5CFontFPc(pCVar10,pCVar7);
    if (iVar2 == 2) {
      iVar4 = (char)s_CmakeInfo._19_1_ * 8;
      if (s_CmakeInfo._18_1_ != '\0') {
        iVar4 = iVar4 + 4;
      }
      uVar5 = GetHairStr__8CMenuPcsFi(menuPcs,iVar4 + (char)s_CmakeInfo._20_1_);
      SetPosX__5CFontFf(FLOAT_80333300 + (float)(dVar14 + dVar17),pCVar10);
      SetPosY__5CFontFf((float)(dVar13 - (double)FLOAT_803332f4),pCVar10);
      Draw__5CFontFPc(pCVar10,uVar5);
    }
    iVar2 = iVar2 + 1;
    uVar6 = uVar6 + 0x28;
    pfVar8 = pfVar8 + 1;
  } while (iVar2 < 4);
  DrawInit__8CMenuPcsFv(menuPcs);
  return;
}

