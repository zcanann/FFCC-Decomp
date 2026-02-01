// Function: CmakeNameDraw__8CMenuPcsFv
// Entry: 80171340
// Size: 3168 bytes

/* WARNING: Removing unreachable block (ram,0x80171f84) */
/* WARNING: Removing unreachable block (ram,0x80171f7c) */
/* WARNING: Removing unreachable block (ram,0x80171f74) */
/* WARNING: Removing unreachable block (ram,0x80171360) */
/* WARNING: Removing unreachable block (ram,0x80171358) */
/* WARNING: Removing unreachable block (ram,0x80171350) */

void CmakeNameDraw__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  float fVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  CFont *font;
  undefined *puVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  undefined4 local_d0;
  undefined auStack_cc [4];
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined8 local_88;
  undefined8 local_80;
  undefined4 local_78;
  uint uStack_74;
  longlong local_70;
  longlong local_68;
  double local_60;
  
  uVar10 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22) - 1;
  if ((int)uVar10 < 0) {
    uVar10 = 0;
  }
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if (sVar2 == 0) {
    local_88 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
    dVar14 = (double)(float)(DOUBLE_80333268 * (local_88 - DOUBLE_803332d0));
  }
  else if (sVar2 == 1) {
    dVar14 = (double)FLOAT_80333258;
  }
  else {
    local_88 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
    dVar14 = (double)(float)-(DOUBLE_80333268 * (local_88 - DOUBLE_803332d0) - DOUBLE_80333270);
  }
  DrawWMFrame0__8CMenuPcsFif((double)FLOAT_80333258,menuPcs,1);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_90 = 0xffffffff;
  local_8c = 0xffffffff;
  GXSetChanMatColor(4,&local_8c);
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
  dVar13 = (double)FLOAT_80333254;
  dVar12 = DOUBLE_803332d0;
  for (uVar10 = 0x20; (int)uVar10 < 0x260; uVar10 = uVar10 + uVar7) {
    uVar7 = 0x20;
    if ((int)(0x260 - uVar10) < 0x20) {
      uVar7 = 0x260 - uVar10;
    }
    local_88 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
    local_80 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)(local_88 - dVar12),(double)FLOAT_803332d8,
               (double)(float)(local_80 - dVar12),(double)FLOAT_803332e0,dVar13,dVar13,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  dVar12 = (double)(float)((double)FLOAT_80333240 * dVar14);
  iVar5 = (int)((double)FLOAT_80333240 * dVar14);
  local_80 = (double)(longlong)iVar5;
  local_98 = CONCAT31(0xffffff,(char)iVar5);
  local_94 = local_98;
  GXSetChanMatColor(4,&local_94);
  uVar8 = 0x3a;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar8 = 0x61;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar8);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_80333278,(double)FLOAT_8033327c,(double)FLOAT_80333280,
             (double)FLOAT_80333284,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  if ((DAT_8032ef10 == 2) && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 0)) {
    iVar5 = (int)*(short *)&menuPcs->field_0x86a;
    iVar9 = *(int *)&menuPcs->field_0x814;
    if (*(int *)(iVar9 + (iVar5 + 0x20) * 0x50) != 0) {
      *(undefined2 *)(iVar9 + 0x6e8) = 0xff24;
      *(undefined2 *)(iVar9 + 0x6ea) = 4;
      DrawInit__8CMenuPcsFv(menuPcs);
      if (**(int **)(&menuPcs->field_0x7f4 + iVar5 * 4) == 3) {
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x32);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
        local_a0 = 0xffffffff;
        local_9c = 0xffffffff;
        GXSetChanMatColor(4,&local_9c);
        DrawRect__8CMenuPcsFUlfffffffff
                  ((double)FLOAT_80333244,(double)FLOAT_80333248,(double)FLOAT_8033324c,
                   (double)FLOAT_80333250,(double)FLOAT_80333254,(double)FLOAT_80333254,
                   (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
      }
      else {
        SetProjection__8CMenuPcsFi(menuPcs,0x16);
        SetLight__8CMenuPcsFi(menuPcs,2);
        *(float *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar5 * 4) + 0x168) + 0x9c) =
             FLOAT_80333258;
        Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)(&menuPcs->field_0x7f4 + iVar5 * 4),5);
        RestoreProjection__8CMenuPcsFv(menuPcs);
      }
      DrawInit__8CMenuPcsFv(menuPcs);
    }
    DrawCmakeTitle__8CMenuPcsFiff(dVar14,(double)FLOAT_80333258,menuPcs,1);
  }
  else {
    bVar1 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10) != 2;
    if ((bVar1) || ((!bVar1 && (*(short *)(*(int *)&menuPcs->field_0x82c + 0x1e) == -1)))) {
      iVar5 = (int)*(short *)&menuPcs->field_0x86a;
      iVar9 = *(int *)&menuPcs->field_0x814;
      if (*(int *)(iVar9 + (iVar5 + 0x20) * 0x50) != 0) {
        *(undefined2 *)(iVar9 + 0x6e8) = 0xff24;
        *(undefined2 *)(iVar9 + 0x6ea) = 4;
        DrawInit__8CMenuPcsFv(menuPcs);
        if (**(int **)(&menuPcs->field_0x7f4 + iVar5 * 4) == 3) {
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x32);
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
          local_80 = (double)(longlong)(int)dVar12;
          local_a8 = CONCAT31(0xffffff,(char)(int)dVar12);
          local_a4 = local_a8;
          GXSetChanMatColor(4,&local_a4);
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)FLOAT_80333244,(double)FLOAT_80333248,(double)FLOAT_8033324c,
                     (double)FLOAT_80333250,(double)FLOAT_80333254,(double)FLOAT_80333254,
                     (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
        }
        else {
          SetProjection__8CMenuPcsFi(menuPcs,0x16);
          SetLight__8CMenuPcsFi(menuPcs,2);
          *(float *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar5 * 4) + 0x168) + 0x9c) =
               (float)dVar14;
          Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)(&menuPcs->field_0x7f4 + iVar5 * 4),5);
          RestoreProjection__8CMenuPcsFv(menuPcs);
        }
        DrawInit__8CMenuPcsFv(menuPcs);
      }
      DrawCmakeTitle__8CMenuPcsFiff((double)FLOAT_80333258,dVar14,menuPcs,1);
    }
    else {
      iVar5 = (int)*(short *)&menuPcs->field_0x86a;
      iVar9 = *(int *)&menuPcs->field_0x814;
      if (*(int *)(iVar9 + (iVar5 + 0x20) * 0x50) != 0) {
        *(undefined2 *)(iVar9 + 0x6e8) = 0xff24;
        *(undefined2 *)(iVar9 + 0x6ea) = 4;
        DrawInit__8CMenuPcsFv(menuPcs);
        if (**(int **)(&menuPcs->field_0x7f4 + iVar5 * 4) == 3) {
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x32);
          SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
          local_b0 = 0xffffffff;
          local_ac = 0xffffffff;
          GXSetChanMatColor(4,&local_ac);
          DrawRect__8CMenuPcsFUlfffffffff
                    ((double)FLOAT_80333244,(double)FLOAT_80333248,(double)FLOAT_8033324c,
                     (double)FLOAT_80333250,(double)FLOAT_80333254,(double)FLOAT_80333254,
                     (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
        }
        else {
          SetProjection__8CMenuPcsFi(menuPcs,0x16);
          SetLight__8CMenuPcsFi(menuPcs,2);
          *(float *)(*(int *)(*(int *)(&menuPcs->field_0x7f4 + iVar5 * 4) + 0x168) + 0x9c) =
               FLOAT_80333258;
          Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)(&menuPcs->field_0x7f4 + iVar5 * 4),5);
          RestoreProjection__8CMenuPcsFv(menuPcs);
        }
        DrawInit__8CMenuPcsFv(menuPcs);
      }
      DrawCmakeTitle__8CMenuPcsFiff(dVar14,(double)FLOAT_80333258,menuPcs,1);
    }
  }
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_80 = (double)(longlong)(int)dVar12;
  local_b8 = CONCAT31(0xffffff,(char)(int)dVar12);
  local_b4 = local_b8;
  GXSetChanMatColor(4,&local_b4);
  uVar8 = 0x3a;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar8 = 0x61;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar8);
  local_78 = 0x43300000;
  uStack_74 = (uint)-((double)FLOAT_80333338 * DOUBLE_80333298 - DOUBLE_80333288);
  local_88 = (double)(longlong)(int)uStack_74;
  uStack_74 = uStack_74 ^ 0x80000000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_803332d0),
             (double)FLOAT_8033333c,(double)FLOAT_80333338,(double)FLOAT_80333340,
             (double)FLOAT_80333254,(double)FLOAT_80333344,(double)FLOAT_80333258,
             (double)FLOAT_80333258,&MenuPcs,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_70 = (longlong)(int)dVar12;
  local_c0 = CONCAT31(0xffffff,(char)(int)dVar12);
  local_bc = local_c0;
  GXSetChanMatColor(4,&local_bc);
  uVar8 = 0x41;
  if (*(short *)&menuPcs->field_0x86c != 0) {
    uVar8 = 0x68;
  }
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar8);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803332a8,(double)FLOAT_803332ac,(double)FLOAT_803332b0,
             (double)FLOAT_803332b0,(double)FLOAT_80333254,(double)FLOAT_80333254,
             (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  dVar13 = (double)FLOAT_803332b0;
  local_68 = (longlong)(int)DOUBLE_803332b8;
  local_60 = (double)(CONCAT44(0x43300000,(int)DOUBLE_803332b8) ^ 0x80000000);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)(local_60 - DOUBLE_803332d0),(double)FLOAT_803332ac,dVar13,dVar13,dVar13
             ,(double)FLOAT_80333254,(double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  iVar5 = *(int *)&menuPcs->field_0x82c;
  if ((*(short *)(iVar5 + 0x10) == 1) && (sVar2 = *(short *)(iVar5 + 0x28), sVar2 < 5)) {
    local_60 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar5 + 0x26)) ^ 0x80000000);
    local_68 = 0x43300000800000e5;
    uVar10 = (uint)(FLOAT_803332c0 * (float)(local_60 - DOUBLE_803332d0) +
                   (float)(4503601774854373.0 - DOUBLE_803332d0));
    local_70 = (longlong)(int)uVar10;
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
    local_c8 = 0xffffffff;
    local_c4 = 0xffffffff;
    GXSetChanMatColor(4,&local_c4);
    uVar8 = 0x3d;
    if (*(short *)&menuPcs->field_0x86c != 0) {
      uVar8 = 100;
    }
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,uVar8);
    uStack_74 = uVar10 ^ 0x80000000;
    local_78 = 0x43300000;
    local_80 = (double)(CONCAT44(0x43300000,sVar2 * 0x20 + 99) ^ 0x80000000);
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_803332d0),
               (double)(float)(local_80 - DOUBLE_803332d0),(double)FLOAT_803332b0,
               (double)FLOAT_803332b0,(double)FLOAT_8033324c,(double)FLOAT_80333254,
               (double)FLOAT_80333258,(double)FLOAT_80333258,&MenuPcs,0);
  }
  sVar2 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x2a);
  if (*(short *)&menuPcs->field_0x86c == 0) {
    font = *(CFont **)&menuPcs->field_0xfc;
  }
  else {
    font = *(CFont **)&menuPcs->field_0x108;
  }
  SetShadow__5CFontFi(font,0);
  SetScale__5CFontFf(FLOAT_80333258,font);
  DrawInit__5CFontFv(font);
  fVar4 = FLOAT_803332c4;
  font->renderFlags = font->renderFlags & 0xef | 0x10;
  SetMargin__5CFontFf(fVar4,font);
  local_60 = (double)(longlong)(int)dVar12;
  puVar6 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_cc,0xff,0xff,0xff,(int)dVar12);
  local_d0 = *puVar6;
  SetColor__5CFontF8_GXColor(font,&local_d0);
  iVar9 = 0;
  iVar5 = 0x6c;
  dVar12 = DOUBLE_803332d0;
  do {
    puVar11 = (&PTR_s_ABCDEFGHIJKL_80215968)[sVar2 * 5 + iVar9];
    SetPosX__5CFontFf(FLOAT_803332c8,font);
    local_60 = (double)(CONCAT44(0x43300000,iVar5) ^ 0x80000000);
    SetPosY__5CFontFf((float)(local_60 - dVar12),font);
    Draw__5CFontFPc(font,puVar11);
    iVar9 = iVar9 + 1;
    iVar5 = iVar5 + 0x20;
  } while (iVar9 < 5);
  font->renderFlags = font->renderFlags & 0xef;
  DrawInit__8CMenuPcsFv(menuPcs);
  iVar5 = *(int *)&menuPcs->field_0x82c;
  if ((*(short *)(iVar5 + 0x10) == 1) && (*(short *)(iVar5 + 0x28) < 5)) {
    local_60 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar5 + 0x26)) ^ 0x80000000);
    local_68 = 0x43300000800000c8;
    iVar3 = (int)System.m_frameCounter >> 0x1f;
    iVar9 = (int)(FLOAT_803332c0 * (float)(local_60 - DOUBLE_803332d0) +
                 (float)(4503601774854344.0 - DOUBLE_803332d0));
    local_70 = (longlong)iVar9;
    DrawCursor__8CMenuPcsFiif
              ((double)FLOAT_80333258,menuPcs,
               iVar9 + ((iVar3 * 8 | System.m_frameCounter * 0x20000000 + iVar3 >> 0x1d) - iVar3),
               *(short *)(iVar5 + 0x28) * 0x20 + 0x70);
  }
  uVar10 = countLeadingZeros(1 - *(short *)(*(int *)&menuPcs->field_0x82c + 0x10));
  uVar10 = uVar10 >> 5;
  if (4 < *(short *)(*(int *)&menuPcs->field_0x82c + 0x28)) {
    uVar10 = 0;
  }
  uVar7 = strlen(&s_CmakeInfo);
  if (6 < (int)(uVar7 & (int)(-uVar7 | uVar7) >> 0x1f)) {
    uVar10 = 0;
  }
  DrawCmakeName__8CMenuPcsFiiPcf(dVar14,menuPcs,0,uVar10,&s_CmakeInfo);
  uVar10 = (uint)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28);
  DrawCmakeDecision__8CMenuPcsFif(dVar14,menuPcs,((int)uVar10 >> 0x1f) + (uint)(4 < uVar10));
  if ((*(short *)(*(int *)&menuPcs->field_0x848 + 10) != 3) &&
     (DrawMcWin__8CMenuPcsFss(menuPcs,0xffff,0), *(short *)(*(int *)&menuPcs->field_0x848 + 10) == 1
     )) {
    DrawMcWinMess__8CMenuPcsFii(menuPcs,0x14,0);
  }
  return;
}

