// Function: CmakeVillageDraw__8CMenuPcsFv
// Entry: 8016d25c
// Size: 1764 bytes

/* WARNING: Removing unreachable block (ram,0x8016d924) */
/* WARNING: Removing unreachable block (ram,0x8016d91c) */
/* WARNING: Removing unreachable block (ram,0x8016d274) */
/* WARNING: Removing unreachable block (ram,0x8016d26c) */

void CmakeVillageDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  float fVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined *puVar9;
  CFont *font;
  int iVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  undefined4 local_b0;
  undefined auStack_ac [4];
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined8 local_88;
  longlong local_80;
  double local_78;
  undefined4 local_70;
  uint uStack_6c;
  longlong local_68;
  longlong local_60;
  double local_58;
  
  iVar10 = *(int *)&menuPcs->field_0x830;
  uVar5 = (int)*(short *)(iVar10 + 0x22) - 1;
  if ((int)uVar5 < 0) {
    uVar5 = 0;
  }
  if (*(short *)(iVar10 + 0x10) == 0) {
    local_88 = (double)CONCAT44(0x43300000,uVar5 ^ 0x80000000);
    dVar12 = (double)(float)(DOUBLE_80333268 * (local_88 - DOUBLE_803332d0));
  }
  else if (*(short *)(iVar10 + 0x10) == 1) {
    dVar12 = (double)FLOAT_80333258;
  }
  else {
    local_88 = (double)CONCAT44(0x43300000,uVar5 ^ 0x80000000);
    dVar12 = (double)(float)-(DOUBLE_80333268 * (local_88 - DOUBLE_803332d0) - DOUBLE_80333270);
  }
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  dVar13 = (double)(float)((double)FLOAT_80333240 * dVar12);
  iVar7 = (int)((double)FLOAT_80333240 * dVar12);
  local_88 = (double)(longlong)iVar7;
  local_90 = CONCAT31(0xffffff,(char)iVar7);
  local_8c = local_90;
  GXSetChanMatColor(4,&local_8c);
  uVar6 = 0x3a;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar6 = 0x61;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar6);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80333278,(double)FLOAT_8033327c,(double)FLOAT_80333280,
             (double)FLOAT_80333284,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  DrawCmakeTitle__8CMenuPcsFiff((double)FLOAT_80333258,dVar12,menuPcs,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_80 = (longlong)(int)dVar13;
  local_98 = CONCAT31(0xffffff,(char)(int)dVar13);
  local_94 = local_98;
  GXSetChanMatColor(4,&local_94);
  uVar6 = 0x3a;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar6 = 0x61;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar6);
  local_70 = 0x43300000;
  uStack_6c = (uint)-((double)FLOAT_80333290 * DOUBLE_80333298 - DOUBLE_80333288);
  local_78 = (double)(longlong)(int)uStack_6c;
  uStack_6c = uStack_6c ^ 0x80000000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_803332d0),
             (double)FLOAT_803332a0,(double)FLOAT_80333290,(double)FLOAT_8033327c,
             (double)FLOAT_80333254,(double)FLOAT_803332a4,(double)FLOAT_80333258,
             (double)FLOAT_80333258,&MenuPcs,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_68 = (longlong)(int)dVar13;
  local_a0 = CONCAT31(0xffffff,(char)(int)dVar13);
  local_9c = local_a0;
  GXSetChanMatColor(4,&local_9c);
  uVar6 = 0x41;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar6 = 0x68;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar6);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803332a8,(double)FLOAT_803332ac,(double)FLOAT_803332b0,
             (double)FLOAT_803332b0,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  dVar11 = (double)FLOAT_803332b0;
  local_60 = (longlong)(int)DOUBLE_803332b8;
  local_58 = (double)(CONCAT44(0x43300000,(int)DOUBLE_803332b8) ^ 0x80000000);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)(local_58 - DOUBLE_803332d0),(double)FLOAT_803332ac,dVar11,dVar11,dVar11
             ,(double)FLOAT_80333254,(double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  if ((*(short *)(iVar10 + 0x10) == 1) && (sVar1 = *(short *)(iVar10 + 0x28), sVar1 < 5)) {
    local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar10 + 0x26)) ^ 0x80000000);
    local_60 = 0x43300000800000e5;
    uVar5 = (uint)(FLOAT_803332c0 * (float)(local_58 - DOUBLE_803332d0) +
                  (float)(4503601774854373.0 - DOUBLE_803332d0));
    local_68 = (longlong)(int)uVar5;
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_a8 = 0xffffffff;
    local_a4 = 0xffffffff;
    GXSetChanMatColor(4,&local_a4);
    uVar6 = 0x3d;
    if (*(short *)&menuPcs->field_0x86c != 0) {
      uVar6 = 100;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar6);
    uStack_6c = uVar5 ^ 0x80000000;
    local_70 = 0x43300000;
    local_78 = (double)(CONCAT44(0x43300000,sVar1 * 0x20 + 99) ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_803332d0),
               (double)(float)(local_78 - DOUBLE_803332d0),(double)FLOAT_803332b0,
               (double)FLOAT_803332b0,(double)FLOAT_8033324c,(double)FLOAT_80333254,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  sVar1 = *(short *)(iVar10 + 0x2a);
  if (*(short *)&menuPcs->field_0x86c == 0) {
    font = *(CFont **)&menuPcs->field_0xfc;
  }
  else {
    font = *(CFont **)&menuPcs->field_0x108;
  }
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_80333258,font);
  DrawInit__5CFontFv(font);
  fVar2 = FLOAT_803332c4;
  font->renderFlags = font->renderFlags & 0xef | 0x10;
  SetMargin__5CFontFf(fVar2,font);
  local_58 = (double)(longlong)(int)dVar13;
  puVar3 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_ac,0xff,0xff,0xff,(int)dVar13);
  local_b0 = *puVar3;
  SetColor__5CFontF8_GXColor(font,&local_b0);
  iVar8 = 0;
  iVar7 = 0x6c;
  dVar13 = DOUBLE_803332d0;
  do {
    puVar9 = (&PTR_s_ABCDEFGHIJKL_80215968)[sVar1 * 5 + iVar8];
    SetPosX__5CFontFf(FLOAT_803332c8,font);
    local_58 = (double)(CONCAT44(0x43300000,iVar7) ^ 0x80000000);
    SetPosY__5CFontFf((float)(local_58 - dVar13),font);
    Draw__5CFontFPc(font,puVar9);
    iVar8 = iVar8 + 1;
    iVar7 = iVar7 + 0x20;
  } while (iVar8 < 5);
  font->renderFlags = font->renderFlags & 0xef;
  DrawInit__8CMenuPcsFv(menuPcs);
  if ((*(short *)(iVar10 + 0x10) == 1) && (*(short *)(iVar10 + 0x28) < 5)) {
    local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar10 + 0x26)) ^ 0x80000000);
    local_60 = 0x43300000800000c8;
    iVar8 = (int)System.m_frameCounter >> 0x1f;
    iVar7 = (int)(FLOAT_803332c0 * (float)(local_58 - DOUBLE_803332d0) +
                 (float)(4503601774854344.0 - DOUBLE_803332d0));
    local_68 = (longlong)iVar7;
    DrawCursor__8CMenuPcsFiif
              ((double)FLOAT_80333258,menuPcs,
               iVar7 + ((iVar8 * 8 | System.m_frameCounter * 0x20000000 + iVar8 >> 0x1d) - iVar8),
               *(short *)(iVar10 + 0x28) * 0x20 + 0x70);
  }
  uVar5 = countLeadingZeros(1 - *(short *)(iVar10 + 0x10));
  uVar5 = uVar5 >> 5;
  if (4 < *(short *)(iVar10 + 0x28)) {
    uVar5 = 0;
  }
  uVar4 = strlen(&s_CmakeInfo);
  if (6 < (int)(uVar4 & (int)(-uVar4 | uVar4) >> 0x1f)) {
    uVar5 = 0;
  }
  DrawCmakeName__8CMenuPcsFiiPcf(dVar12,menuPcs,1,uVar5,&s_CmakeInfo);
  DrawCmakeDecision__8CMenuPcsFif
            (dVar12,menuPcs,
             ((int)*(short *)(iVar10 + 0x28) >> 0x1f) +
             (uint)(4 < (uint)(int)*(short *)(iVar10 + 0x28)));
  return;
}

