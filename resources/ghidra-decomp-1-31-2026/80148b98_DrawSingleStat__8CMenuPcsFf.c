// Function: DrawSingleStat__8CMenuPcsFf
// Entry: 80148b98
// Size: 1988 bytes

/* WARNING: Removing unreachable block (ram,0x80149340) */
/* WARNING: Removing unreachable block (ram,0x80149338) */
/* WARNING: Removing unreachable block (ram,0x80149330) */
/* WARNING: Removing unreachable block (ram,0x80149328) */
/* WARNING: Removing unreachable block (ram,0x80149320) */
/* WARNING: Removing unreachable block (ram,0x80149318) */
/* WARNING: Removing unreachable block (ram,0x80149310) */
/* WARNING: Removing unreachable block (ram,0x80148bd8) */
/* WARNING: Removing unreachable block (ram,0x80148bd0) */
/* WARNING: Removing unreachable block (ram,0x80148bc8) */
/* WARNING: Removing unreachable block (ram,0x80148bc0) */
/* WARNING: Removing unreachable block (ram,0x80148bb8) */
/* WARNING: Removing unreachable block (ram,0x80148bb0) */
/* WARNING: Removing unreachable block (ram,0x80148ba8) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawSingleStat__8CMenuPcsFf(double param_1,CMenuPcs *menuPcs)

{
  float fVar1;
  uint8_t uVar2;
  float fVar3;
  undefined4 *puVar4;
  undefined2 uVar5;
  int iVar6;
  undefined *puVar7;
  undefined **ppuVar8;
  undefined **ppuVar9;
  undefined **ppuVar10;
  undefined **ppuVar11;
  undefined **ppuVar12;
  CFont *font;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  undefined auStack_130 [4];
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined auStack_114 [36];
  longlong local_f0;
  undefined4 local_e8;
  uint uStack_e4;
  longlong local_e0;
  undefined4 local_d8;
  uint uStack_d4;
  undefined4 local_d0;
  uint uStack_cc;
  longlong local_c8;
  undefined4 local_c0;
  uint uStack_bc;
  longlong local_b8;
  longlong local_b0;
  longlong local_a8;
  
  uVar2 = Game.game.m_gameWork.m_languageId;
  DrawInit__8CMenuPcsFv(menuPcs);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  dVar18 = (double)(float)((double)FLOAT_80332940 * param_1);
  iVar6 = (int)((double)FLOAT_80332940 * param_1);
  local_f0 = (longlong)iVar6;
  local_118 = CONCAT31(0xffffff,(char)iVar6);
  local_11c = local_118;
  GXSetChanMatColor(4,&local_11c);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x26);
  dVar13 = (double)FLOAT_8033294c;
  dVar15 = (double)FLOAT_803329d4;
  DrawRect__8CMenuPcsFUlfffffffff
            (dVar15,dVar13,(double)FLOAT_803329d8,(double)FLOAT_803329d0,dVar13,dVar13,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)FLOAT_803329d4,(double)FLOAT_803329dc,(double)FLOAT_803329d8,
             (double)FLOAT_803329d0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,4);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x29);
  dVar13 = (double)FLOAT_80332930;
  dVar16 = (double)FLOAT_803329dc;
  dVar17 = (double)FLOAT_8033294c;
  fVar1 = FLOAT_803329d0;
  while (dVar14 = (double)fVar1, dVar14 < dVar16) {
    if ((double)(float)(dVar16 - dVar14) < dVar13) {
      dVar13 = (double)(float)(dVar16 - dVar14);
    }
    DrawRect__8CMenuPcsFUlfffffffff
              ((double)FLOAT_803329d4,dVar14,(double)FLOAT_803329a4,dVar13,dVar17,dVar17,
               (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
    fVar1 = (float)(dVar14 + dVar13);
  }
  iVar6 = (int)(DOUBLE_803329e0 * DOUBLE_80332968 * param_1);
  local_f0 = (longlong)iVar6;
  local_118 = CONCAT31(0xffffff,(char)iVar6);
  local_120 = local_118;
  GXSetChanMatColor(4,&local_120);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x22);
  dVar13 = (double)FLOAT_803329e8;
  local_e8 = 0x43300000;
  uStack_e4 = *(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e0) & 1 ^ 0x80000000;
  uStack_cc = (int)(uint)*(ushort *)(Game.game.m_scriptFoodBase[0] + 0x3e0) >> 1 ^ 0x80000000;
  local_d0 = 0x43300000;
  local_d8 = 0x43300000;
  uStack_d4 = (uint)((double)(float)((double)CONCAT44(0x43300000,uStack_e4) - DOUBLE_80332938) *
                    dVar13);
  local_e0 = (longlong)(int)uStack_d4;
  local_c0 = 0x43300000;
  uStack_bc = (uint)((double)(float)((double)CONCAT44(0x43300000,uStack_cc) - DOUBLE_80332938) *
                    dVar13);
  local_c8 = (longlong)(int)uStack_bc;
  uStack_d4 = uStack_d4 ^ 0x80000000;
  uStack_bc = uStack_bc ^ 0x80000000;
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(float)(dVar15 - (double)FLOAT_8033292c),(double)FLOAT_803329ac,dVar13,dVar13,
             (double)(float)((double)CONCAT44(0x43300000,uStack_d4) - DOUBLE_80332938),
             (double)(float)((double)CONCAT44(0x43300000,uStack_bc) - DOUBLE_80332938),
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  local_b8 = (longlong)(int)dVar18;
  local_118 = CONCAT31(0xffffff,(char)(int)dVar18);
  local_124 = local_118;
  GXSetChanMatColor(4,&local_124);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x2a);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(FLOAT_803329d4 + FLOAT_803329ec),(double)FLOAT_803329f0,(double)FLOAT_803329f4
             ,(double)FLOAT_803329f0,(double)FLOAT_8033294c,(double)FLOAT_8033294c,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  DrawInit__8CMenuPcsFv(menuPcs);
  SetProjection__8CMenuPcsFi(menuPcs,0);
  SetLight__8CMenuPcsFi(menuPcs,1);
  *(float *)(*(int *)(*(int *)&menuPcs->field_0x774 + 0x168) + 0x9c) = (float)param_1;
  Draw__Q29CCharaPcs7CHandleFi(*(undefined4 *)&menuPcs->field_0x774,5);
  RestoreProjection__8CMenuPcsFv(menuPcs);
  DrawInit__8CMenuPcsFv(menuPcs);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
  local_b0 = (longlong)(int)dVar18;
  local_118 = CONCAT31(0xffffff,(char)(int)dVar18);
  local_128 = local_118;
  GXSetChanMatColor(4,&local_128);
  SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x2a);
  DrawRect__8CMenuPcsFUlfffffffff
            ((double)(FLOAT_803329d4 + FLOAT_803329ec),(double)FLOAT_80332994,(double)FLOAT_803329f4
             ,(double)FLOAT_803329f8,(double)FLOAT_8033294c,(double)FLOAT_803329f0,
             (double)FLOAT_80332934,(double)FLOAT_80332934,&MenuPcs,0);
  DrawInit__8CMenuPcsFv(menuPcs);
  font = *(CFont **)&menuPcs->field_0xf8;
  SetMargin__5CFontFf(FLOAT_80332934,font);
  SetShadow__5CFontFi(font,1);
  SetScale__5CFontFf(FLOAT_803329b8,font);
  local_a8 = (longlong)(int)dVar18;
  puVar4 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_130,0xff,0xff,0xff,(int)dVar18);
  local_12c = *puVar4;
  SetColor__5CFontF8_GXColor(font,&local_12c);
  DrawInit__5CFontFv(font);
  iVar6 = Game.game.m_scriptFoodBase[0] + 0x3ca;
  dVar13 = (double)GetWidth__5CFontFPc(font,iVar6);
  SetTlut__5CFontFi(font,0x12);
  dVar13 = (double)(FLOAT_803329d4 +
                   (float)((double)(float)((double)FLOAT_803329d8 - dVar13) * DOUBLE_80332968));
  SetPosX__5CFontFf((float)((double)FLOAT_80332934 + dVar13),font);
  SetPosY__5CFontFf(FLOAT_803329fc,font);
  Draw__5CFontFPc(font,iVar6);
  SetTlut__5CFontFi(font,0x17);
  SetPosX__5CFontFf((float)dVar13,font);
  SetPosY__5CFontFf(FLOAT_80332a00,font);
  Draw__5CFontFPc(font,iVar6);
  SetTlut__5CFontFi(font,0x15);
  dVar13 = (double)FLOAT_80332954;
  ppuVar12 = &PTR_DAT_802142c0;
  dVar16 = (double)FLOAT_80332a18;
  ppuVar11 = &PTR_DAT_802143a0;
  dVar15 = (double)FLOAT_80332a1c;
  ppuVar10 = &PTR_DAT_80214480;
  ppuVar9 = &PTR_DAT_80214560;
  ppuVar8 = &PTR_DAT_802141e0;
  iVar6 = 0;
  fVar1 = FLOAT_80332a04;
  do {
    dVar17 = (double)fVar1;
    SetPosX__5CFontFf(FLOAT_803329d4,font);
    SetPosY__5CFontFf((float)(dVar17 - dVar13),font);
    if (Game.game.m_gameWork.m_languageId == '\x03') {
      puVar7 = ppuVar11[5];
    }
    else if (Game.game.m_gameWork.m_languageId < 3) {
      if ((Game.game.m_gameWork.m_languageId == '\x01') ||
         (Game.game.m_gameWork.m_languageId == '\0')) {
LAB_80149194:
        puVar7 = ppuVar8[5];
      }
      else {
        puVar7 = ppuVar12[5];
      }
    }
    else if (Game.game.m_gameWork.m_languageId == '\x05') {
      puVar7 = ppuVar9[5];
    }
    else {
      if (4 < Game.game.m_gameWork.m_languageId) goto LAB_80149194;
      puVar7 = ppuVar10[5];
    }
    if ((uVar2 == '\x02') && (iVar6 == 3)) {
      SetScaleX__5CFontFf(FLOAT_80332a08,font);
      SetScaleY__5CFontFf(FLOAT_803329b8,font);
    }
    else {
      SetScaleX__5CFontFf(FLOAT_803329b8,font);
    }
    Draw__5CFontFPc(font,puVar7);
    font->renderFlags = font->renderFlags & 0xef | 0x10;
    if (uVar2 == '\x02') {
      SetMargin__5CFontFf(FLOAT_80332a0c,font);
      SetScaleX__5CFontFf(FLOAT_80332a08,font);
      SetScaleY__5CFontFf(FLOAT_803329b8,font);
    }
    else {
      SetMargin__5CFontFf(FLOAT_80332a10,font);
      SetScale__5CFontFf(FLOAT_803329b8,font);
    }
    if (iVar6 == 0) {
      uVar5 = *(undefined2 *)(Game.game.m_scriptFoodBase[0] + 0x1e);
    }
    else if (iVar6 == 1) {
      uVar5 = *(undefined2 *)(Game.game.m_scriptFoodBase[0] + 0x22);
    }
    else if (iVar6 == 2) {
      uVar5 = *(undefined2 *)(Game.game.m_scriptFoodBase[0] + 0x20);
    }
    else {
      uVar5 = *(undefined2 *)(Game.game.m_scriptFoodBase[0] + 0x3de);
    }
    sprintf(auStack_114,&DAT_80332a14,uVar5);
    dVar18 = (double)GetWidth__5CFontFPc(font,auStack_114);
    SetPosX__5CFontFf((float)(dVar16 - dVar18),font);
    Draw__5CFontFPc(font,auStack_114);
    fVar1 = FLOAT_80332934;
    font->renderFlags = font->renderFlags & 0xef;
    SetMargin__5CFontFf(fVar1,font);
    fVar3 = FLOAT_80332934;
    iVar6 = iVar6 + 1;
    fVar1 = (float)(dVar17 + dVar15);
    ppuVar12 = ppuVar12 + 1;
    ppuVar11 = ppuVar11 + 1;
    ppuVar10 = ppuVar10 + 1;
    ppuVar9 = ppuVar9 + 1;
    ppuVar8 = ppuVar8 + 1;
    if (3 < iVar6) {
      font->renderFlags = font->renderFlags & 0xef;
      SetMargin__5CFontFf(fVar3,font);
      DrawInit__8CMenuPcsFv(menuPcs);
      return;
    }
  } while( true );
}

