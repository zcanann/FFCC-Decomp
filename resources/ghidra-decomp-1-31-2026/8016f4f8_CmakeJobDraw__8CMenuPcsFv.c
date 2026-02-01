// Function: CmakeJobDraw__8CMenuPcsFv
// Entry: 8016f4f8
// Size: 1600 bytes

/* WARNING: Removing unreachable block (ram,0x8016fb1c) */
/* WARNING: Removing unreachable block (ram,0x8016fb14) */
/* WARNING: Removing unreachable block (ram,0x8016fb0c) */
/* WARNING: Removing unreachable block (ram,0x8016f518) */
/* WARNING: Removing unreachable block (ram,0x8016f510) */
/* WARNING: Removing unreachable block (ram,0x8016f508) */

void CmakeJobDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  CFont *font;
  uint uVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined auStack_78 [4];
  undefined4 local_74;
  undefined8 local_70;
  undefined8 local_68;
  longlong local_60;
  undefined4 local_58;
  uint uStack_54;
  longlong local_50;
  
  uVar8 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) - 1;
  if ((int)uVar8 < 0) {
    uVar8 = 0;
  }
  sVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if (sVar1 == 0) {
    local_70 = (double)CONCAT44(0x43300000,uVar8 ^ 0x80000000);
    dVar12 = (double)(float)(DOUBLE_80333268 * (local_70 - DOUBLE_803332d0));
  }
  else if (sVar1 == 1) {
    dVar12 = (double)FLOAT_80333258;
  }
  else {
    local_70 = (double)CONCAT44(0x43300000,uVar8 ^ 0x80000000);
    dVar12 = (double)(float)-(DOUBLE_80333268 * (local_70 - DOUBLE_803332d0) - DOUBLE_80333270);
  }
  DrawWMFrame0__8CMenuPcsFif((double)FLOAT_80333258,menuPcs,1);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_80 = 0xffffffff;
  local_7c = 0xffffffff;
  GXSetChanMatColor(4,&local_7c);
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
  for (uVar8 = 0x20; (int)uVar8 < 0x260; uVar8 = uVar8 + uVar9) {
    uVar9 = 0x20;
    if ((int)(0x260 - uVar8) < 0x20) {
      uVar9 = 0x260 - uVar8;
    }
    local_70 = (double)CONCAT44(0x43300000,uVar8 ^ 0x80000000);
    local_68 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(local_70 - dVar10),(double)FLOAT_803332d8,
               (double)(float)(local_68 - dVar10),(double)FLOAT_803332e0,dVar11,dVar11,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  iVar3 = (int)*(short *)&menuPcs->field_0x86a;
  iVar6 = *(int *)&menuPcs->field_0x814;
  if (*(int *)(iVar6 + (iVar3 + 0x20) * 0x50) != 0) {
    *(undefined2 *)(iVar6 + 0x6e8) = 0xff24;
    *(undefined2 *)(iVar6 + 0x6ea) = 4;
    DrawInit__8CMenuPcsFv(menuPcs);
    if (**(int **)(&menuPcs->field_0x7f4 + iVar3 * 4) == 3) {
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x32);
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      local_88 = 0xffffffff;
      local_84 = 0xffffffff;
      GXSetChanMatColor(4,&local_84);
      DrawRect__8CMenuPcsFUlfffffffff
                ((double)FLOAT_80333244,(double)FLOAT_80333248,(double)FLOAT_8033324c,
                 (double)FLOAT_80333250,(double)FLOAT_80333254,(double)FLOAT_80333254,
                 (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
    }
    else {
      SetProjection__8CMenuPcsFi(menuPcs,0x16);
      SetLight__8CMenuPcsFi(menuPcs,2);
      *(float *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar3 * 4) + 0x168) + 0x9c) =
           FLOAT_80333258;
      Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)(&menuPcs->field_0x7f4 + iVar3 * 4),5);
      RestoreProjection__8CMenuPcsFv(menuPcs);
    }
    DrawInit__8CMenuPcsFv(menuPcs);
  }
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  dVar10 = (double)(float)((double)FLOAT_80333240 * dVar12);
  iVar3 = (int)((double)FLOAT_80333240 * dVar12);
  local_68 = (double)(longlong)iVar3;
  local_90 = CONCAT31(0xffffff,(char)iVar3);
  local_8c = local_90;
  GXSetChanMatColor(4,&local_8c);
  uVar7 = 0x3a;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar7 = 0x61;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar7);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80333278,(double)FLOAT_8033327c,(double)FLOAT_80333280,
             (double)FLOAT_80333284,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  DrawCmakeTitle__8CMenuPcsFiff(dVar12,(double)FLOAT_80333258,menuPcs,5);
  font = *(CFont **)&menuPcs->field_0xfc;
  SetMargin__5CFontFf(FLOAT_80333258,font);
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_80333258,font);
  DrawInit__5CFontFv(font);
  local_70 = (double)(longlong)(int)dVar10;
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_78,0xff,0xff,0xff,(int)dVar10);
  local_74 = *puVar4;
  SetColor__5CFontF8_GXColor(font,&local_74);
  iVar3 = 0;
  dVar11 = (double)FLOAT_803332f4;
  dVar10 = DOUBLE_803332d0;
  do {
    uVar5 = GetJobStr__8CMenuPcsFi(menuPcs,iVar3);
    uVar7 = 0x1a8;
    if (iVar3 < 4) {
      uVar7 = 0x110;
    }
    local_68 = (double)(CONCAT44(0x43300000,uVar7) ^ 0x80000000);
    SetPosX__5CFontFf((float)(local_68 - dVar10),font);
    iVar6 = iVar3 >> 0x1f;
    local_70 = (double)(CONCAT44(0x43300000,
                                 ((iVar6 * 4 | (uint)(iVar3 * 0x40000000 + iVar6) >> 0x1e) - iVar6)
                                 * 0x28 + 0x70) ^ 0x80000000);
    SetPosY__5CFontFf((float)((double)(float)(local_70 - dVar10) - dVar11),font);
    Draw__5CFontFPc(font,uVar5);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 8);
  if (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 1) {
    iVar3 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
    uVar8 = 0x1a8;
    if (iVar3 < 4) {
      uVar8 = 0x110;
    }
    iVar6 = iVar3 >> 0x1f;
    iVar2 = (int)System.m_frameCounter >> 0x1f;
    local_68 = (double)CONCAT44(0x43300000,uVar8 ^ 0x80000000);
    local_70 = (double)(CONCAT44(0x43300000,
                                 (iVar2 * 8 | System.m_frameCounter * 0x20000000 + iVar2 >> 0x1d) -
                                 iVar2) ^ 0x80000000);
    uStack_54 = ((iVar6 * 4 | (uint)(iVar3 * 0x40000000 + iVar6) >> 0x1e) - iVar6) * 0x28 + 0x70 ^
                0x80000000;
    local_58 = 0x43300000;
    iVar3 = (int)(((float)(local_68 - DOUBLE_803332d0) - FLOAT_80333308) +
                 (float)(local_70 - DOUBLE_803332d0));
    local_60 = (longlong)iVar3;
    iVar6 = (int)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_803332d0);
    local_50 = (longlong)iVar6;
    DrawCursor__8CMenuPcsFiif(dVar12,menuPcs,iVar3,iVar6);
  }
  if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) != 3) &&
     (DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0), *(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1
     )) {
    DrawMcWinMess__8CMenuPcsFii(menuPcs,0x16,0);
  }
  return;
}

