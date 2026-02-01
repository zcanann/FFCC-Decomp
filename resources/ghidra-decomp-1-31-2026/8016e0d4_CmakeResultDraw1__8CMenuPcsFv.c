// Function: CmakeResultDraw1__8CMenuPcsFv
// Entry: 8016e0d4
// Size: 2468 bytes

/* WARNING: Removing unreachable block (ram,0x8016ea5c) */
/* WARNING: Removing unreachable block (ram,0x8016ea54) */
/* WARNING: Removing unreachable block (ram,0x8016ea4c) */
/* WARNING: Removing unreachable block (ram,0x8016ea44) */
/* WARNING: Removing unreachable block (ram,0x8016ea3c) */
/* WARNING: Removing unreachable block (ram,0x8016ea34) */
/* WARNING: Removing unreachable block (ram,0x8016ea2c) */
/* WARNING: Removing unreachable block (ram,0x8016e114) */
/* WARNING: Removing unreachable block (ram,0x8016e10c) */
/* WARNING: Removing unreachable block (ram,0x8016e104) */
/* WARNING: Removing unreachable block (ram,0x8016e0fc) */
/* WARNING: Removing unreachable block (ram,0x8016e0f4) */
/* WARNING: Removing unreachable block (ram,0x8016e0ec) */
/* WARNING: Removing unreachable block (ram,0x8016e0e4) */

void CmakeResultDraw1__8CMenuPcsFv(CMenuPcs *menuPcs)

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
  double dVar18;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined auStack_e8 [4];
  undefined4 local_e4;
  undefined auStack_e0 [4];
  undefined4 local_dc;
  float local_d8 [4];
  undefined auStack_c8 [20];
  uint uStack_b4;
  undefined8 local_b0;
  double local_a8;
  undefined8 local_a0;
  
  uVar6 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) - 1;
  if ((int)uVar6 < 0) {
    uVar6 = 0;
  }
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if (sVar1 == 0) {
    stack0xffffff48 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    dVar18 = (double)(float)(DOUBLE_80333268 * (stack0xffffff48 - DOUBLE_803332d0));
  }
  else if (sVar1 == 1) {
    dVar18 = (double)FLOAT_80333258;
  }
  else {
    stack0xffffff48 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    dVar18 = (double)(float)-(DOUBLE_80333268 * (stack0xffffff48 - DOUBLE_803332d0) -
                             DOUBLE_80333270);
  }
  DrawWMFrame0__8CMenuPcsFif((double)FLOAT_80333258,menuPcs,1);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_f0 = 0xffffffff;
  local_ec = 0xffffffff;
  GXSetChanMatColor(4,&local_ec);
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
    stack0xffffff48 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    local_b0 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(stack0xffffff48 - dVar12),(double)FLOAT_803332d8,
               (double)(float)(local_b0 - dVar12),(double)FLOAT_803332e0,dVar15,dVar15,
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
      local_f8 = 0xffffffff;
      local_f4 = 0xffffffff;
      GXSetChanMatColor(4,&local_f4);
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
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 0) {
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_100 = 0xffffffff;
    local_fc = 0xffffffff;
    GXSetChanMatColor(4,&local_fc);
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
    local_b0 = (double)(longlong)(int)((double)FLOAT_80333240 * dVar18);
    local_108 = CONCAT31(0xffffff,(char)(int)((double)FLOAT_80333240 * dVar18));
    local_104 = local_108;
    GXSetChanMatColor(4,&local_104);
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
  DrawCmakeTitle__8CMenuPcsFiff(dVar18,(double)FLOAT_80333258,menuPcs,7);
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 0) {
    dVar18 = (double)FLOAT_80333258;
  }
  uVar6 = (uint)(char)s_CmakeInfo._19_1_;
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  dVar17 = (double)(float)((double)FLOAT_80333240 * dVar18);
  iVar2 = (int)((double)FLOAT_80333240 * dVar18);
  local_b0 = (double)(longlong)iVar2;
  local_110 = CONCAT31(0xffffff,(char)iVar2);
  local_10c = local_110;
  GXSetChanMatColor(4,&local_10c);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x31);
  stack0xffffff48 = (double)(CONCAT44(0x43300000,(uVar6 & 1) * 0xb8) ^ 0x80000000);
  local_a8 = (double)(CONCAT44(0x43300000,((int)uVar6 / 2) * 0xb8) ^ 0x80000000);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803332e8,(double)FLOAT_803332ec,(double)FLOAT_803332a8,
             (double)FLOAT_803332a8,(double)(float)(stack0xffffff48 - DOUBLE_803332d0),
             (double)(float)(local_a8 - DOUBLE_803332d0),(double)FLOAT_80333258,
             (double)FLOAT_80333258,&MenuPcs,0);
  pCVar10 = *(CFont **)&menuPcs->field_0xfc;
  SetMargin__5CFontFf(FLOAT_80333258,pCVar10);
  SetShadow__5CFontFi(pCVar10,0);
  SetScale__5CFontFf(FLOAT_80333258,pCVar10);
  DrawInit__5CFontFv(pCVar10);
  local_a0 = (double)(longlong)(int)dVar17;
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_e0,0xff,0xff,0xff,(int)dVar17);
  local_dc = *puVar3;
  SetColor__5CFontF8_GXColor(pCVar10,&local_dc);
  pfVar8 = local_d8;
  dVar16 = (double)FLOAT_803332f0;
  dVar15 = (double)FLOAT_803332f4;
  iVar2 = 0;
  iVar4 = 0x70;
  pfVar11 = pfVar8;
  dVar12 = DOUBLE_803332d0;
  do {
    uVar5 = GetMenuStr__8CMenuPcsFi(menuPcs,iVar2 + 0x2a);
    dVar13 = (double)GetWidth__5CFontFPc(pCVar10,uVar5);
    *pfVar11 = (float)(dVar16 + dVar13);
    SetPosX__5CFontFf((float)dVar16,pCVar10);
    local_a0 = (double)(CONCAT44(0x43300000,iVar4) ^ 0x80000000);
    SetPosY__5CFontFf((float)((double)(float)(local_a0 - dVar12) - dVar15),pCVar10);
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
  local_a0 = (double)(longlong)(int)dVar17;
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_e8,0xff,0xff,0xff,(int)dVar17);
  local_e4 = *puVar3;
  SetColor__5CFontF8_GXColor(pCVar10,&local_e4);
  SetTlut__5CFontFi(pCVar10,6);
  dVar15 = (double)FLOAT_803332fc;
  dVar16 = (double)FLOAT_803332f4;
  iVar2 = 0;
  uVar6 = 0x70;
  dVar12 = DOUBLE_803332d0;
  do {
    if (iVar2 == 0) {
      pCVar7 = &s_CmakeInfo;
    }
    else if (iVar2 == 1) {
      pCVar7 = (CmakeInfo *)GetMenuStr__8CMenuPcsFi(menuPcs,(char)s_CmakeInfo._18_1_ + 0x11);
    }
    else if (iVar2 == 2) {
      uVar5 = GetTribeStr__8CMenuPcsFi(menuPcs,(int)(char)s_CmakeInfo._19_1_);
      strcpy(auStack_c8,uVar5);
      strcat(auStack_c8,&DAT_803332f8);
      pCVar7 = (CmakeInfo *)auStack_c8;
    }
    else {
      pCVar7 = (CmakeInfo *)GetJobStr__8CMenuPcsFi(menuPcs,(int)(char)s_CmakeInfo._21_1_);
    }
    dVar14 = (double)(float)(dVar15 + (double)*pfVar8);
    local_a0 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
    dVar13 = (double)(float)(local_a0 - dVar12);
    dVar17 = (double)GetWidth__5CFontFPc(pCVar10,pCVar7);
    SetPosX__5CFontFf((float)dVar14,pCVar10);
    SetPosY__5CFontFf((float)(dVar13 - dVar16),pCVar10);
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
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 1) {
    iVar2 = (int)System.m_frameCounter >> 0x1f;
    local_a0 = (double)(CONCAT44(0x43300000,
                                 (iVar2 * 8 | System.m_frameCounter * 0x20000000 + iVar2 >> 0x1d) -
                                 iVar2) ^ 0x80000000);
    local_b0 = (double)(CONCAT44(0x43300000,
                                 *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x28 + 0x70) ^
                       0x80000000);
    iVar2 = (int)(FLOAT_80333304 + (float)(local_a0 - DOUBLE_803332d0));
    local_a8 = (double)(longlong)iVar2;
    register0x00004000 = (double)(longlong)(int)(local_b0 - DOUBLE_803332d0);
    DrawCursor__8CMenuPcsFiif(dVar18,menuPcs,iVar2,(int)(local_b0 - DOUBLE_803332d0));
  }
  return;
}

