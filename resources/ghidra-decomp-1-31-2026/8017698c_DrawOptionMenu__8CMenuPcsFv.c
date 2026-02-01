// Function: DrawOptionMenu__8CMenuPcsFv
// Entry: 8017698c
// Size: 10652 bytes

/* WARNING: Removing unreachable block (ram,0x8017930c) */
/* WARNING: Removing unreachable block (ram,0x80179304) */
/* WARNING: Removing unreachable block (ram,0x801792fc) */
/* WARNING: Removing unreachable block (ram,0x801792f4) */
/* WARNING: Removing unreachable block (ram,0x801792ec) */
/* WARNING: Removing unreachable block (ram,0x801792e4) */
/* WARNING: Removing unreachable block (ram,0x801792dc) */
/* WARNING: Removing unreachable block (ram,0x801769cc) */
/* WARNING: Removing unreachable block (ram,0x801769c4) */
/* WARNING: Removing unreachable block (ram,0x801769bc) */
/* WARNING: Removing unreachable block (ram,0x801769b4) */
/* WARNING: Removing unreachable block (ram,0x801769ac) */
/* WARNING: Removing unreachable block (ram,0x801769a4) */
/* WARNING: Removing unreachable block (ram,0x8017699c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawOptionMenu__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  char cVar4;
  float fVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  CFont *pCVar13;
  int iVar14;
  undefined *puVar15;
  CFont *font;
  undefined **ppuVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  undefined4 local_298;
  undefined4 local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  float local_250;
  float local_24c;
  float local_248;
  float local_244;
  undefined *local_240 [4];
  undefined *local_230;
  undefined *local_22c [4];
  undefined *local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  float local_208;
  float local_204;
  float local_200;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  float local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  float local_1d0;
  float local_1cc;
  float local_1c8;
  float local_1c4;
  float local_1c0;
  float local_1bc;
  float local_1b8;
  float local_1b4;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  undefined4 local_168;
  float local_164;
  undefined4 local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  undefined4 local_140;
  float local_13c;
  undefined4 local_138;
  float local_134;
  undefined8 local_130;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 local_118;
  undefined8 local_110;
  undefined4 local_108;
  uint uStack_104;
  undefined8 local_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined **local_c8;
  
  pCVar13 = *(CFont **)&menuPcs->field_0xf8;
  uVar11 = (uint)Game.game.m_gameWork.m_languageId;
  iVar14 = uVar11 - 1;
  SetScale__5CFontFf(FLOAT_80333548,pCVar13);
  SetMargin__5CFontFf(FLOAT_8033354c,pCVar13);
  iVar12 = (int)(FLOAT_80333550 * *(float *)&menuPcs->field_0x98);
  local_130 = (double)(longlong)iVar12;
  local_254 = CONCAT31(0xffffff,(char)iVar12);
  local_120 = (double)CONCAT44(0x43300000,*(undefined4 *)(*(int *)&menuPcs->field_0xd4 + 0x68));
  dVar23 = (double)(float)(local_120 - DOUBLE_80333638);
  local_22c[0] = (&PTR_s_Position_Markers_80215a50)[iVar14 * 0x14];
  local_128 = (double)CONCAT44(0x43300000,*(undefined4 *)(*(int *)&menuPcs->field_0xd4 + 100));
  local_22c[1] = (&PTR_s_Sound_Mode_80215a54)[iVar14 * 0x14];
  local_22c[2] = (&PTR_s_Music_80215a58)[iVar14 * 0x14];
  dVar22 = (double)(float)(local_128 - DOUBLE_80333638);
  local_22c[3] = (&PTR_s_Sound_Effects_80215a5c)[iVar14 * 0x14];
  local_21c = (&PTR_s_GBA_Colour_Balance_80215a60)[iVar14 * 0x14];
  local_240[0] = (&PTR_s_Show_or_hide_position_marker_und_80215a64)[iVar14 * 0x14];
  local_240[1] = (&PTR_s_Select_stereo_or_monaural_sound__80215a68)[iVar14 * 0x14];
  local_240[2] = (&PTR_s_Adjust_volume_of_background_musi_80215a6c)[iVar14 * 0x14];
  local_240[3] = (&PTR_s_Adjust_volume_of_sound_effects__80215a70)[iVar14 * 0x14];
  local_230 = (&PTR_s_Adjust_colour_balance_of_Game_Bo_80215a74)[iVar14 * 0x14];
  uVar6 = __cvt_fp2unsigned(dVar23);
  uVar7 = __cvt_fp2unsigned(dVar22);
  CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,0,uVar7,uVar6);
  CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x280,uVar6,uVar7,uVar6);
  RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
            ((double)FLOAT_8033354c,
             (double)(-(float)(dVar23 * (double)FLOAT_80333558 - (double)FLOAT_80333554) -
                     FLOAT_8033355c),(double)FLOAT_80333560,dVar23,&DAT_8032ec70,
             *(undefined4 *)&menuPcs->field_0xd4,&local_248,&local_250,&local_254,4,5);
  iVar12 = *(int *)&menuPcs->field_0xe8;
  local_118 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 100));
  dVar27 = (double)(float)(local_118 - DOUBLE_80333638);
  local_110 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 0x68));
  dVar22 = (double)(float)(local_110 - DOUBLE_80333638);
  RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
            ((double)FLOAT_80333564,(double)FLOAT_80333568,dVar27,dVar22,&DAT_8032ec70,iVar12,0,0,
             &local_254,4,5);
  dVar23 = (double)(float)((double)FLOAT_80333568 + dVar22);
  local_248 = FLOAT_8033354c;
  local_244 = FLOAT_8033356c;
  local_250 = FLOAT_8033356c;
  local_24c = FLOAT_8033354c;
  RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
            ((double)FLOAT_80333564,dVar23,dVar27,dVar22,&DAT_8032ec70,
             *(undefined4 *)&menuPcs->field_0xe8,&local_248,&local_250,&local_254,4,5);
  dVar26 = (double)(float)((double)FLOAT_80333564 + dVar27);
  local_248 = FLOAT_8033356c;
  local_244 = FLOAT_8033354c;
  local_250 = FLOAT_8033354c;
  local_24c = FLOAT_8033356c;
  RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
            (dVar26,(double)FLOAT_80333568,dVar27,dVar22,&DAT_8032ec70,
             *(undefined4 *)&menuPcs->field_0xe8,&local_248,&local_250,&local_254,4,5);
  local_248 = FLOAT_8033356c;
  local_244 = FLOAT_8033356c;
  local_250 = FLOAT_8033354c;
  local_24c = FLOAT_8033354c;
  RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
            (dVar26,dVar23,dVar27,dVar22,&DAT_8032ec70,*(undefined4 *)&menuPcs->field_0xe8,
             &local_248,&local_250,&local_254,4,5);
  uStack_104 = *(uint *)(*(int *)&menuPcs->field_0x18c + 100);
  local_100 = (double)CONCAT44(0x43300000,*(undefined4 *)(*(int *)&menuPcs->field_0x18c + 0x68));
  local_108 = 0x43300000;
  dVar22 = (double)(float)((double)CONCAT44(0x43300000,uStack_104) - DOUBLE_80333638);
  uVar6 = __cvt_fp2unsigned((double)(float)(local_100 - DOUBLE_80333638));
  uVar7 = __cvt_fp2unsigned(dVar22);
  CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,0,uVar7,uVar6);
  CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x20,0x20,uVar7,uVar6);
  iVar12 = (int)System.m_frameCounter >> 0x1f;
  local_f8 = (double)(CONCAT44(0x43300000,
                               ((iVar12 * 8 | System.m_frameCounter * 0x20000000 + iVar12 >> 0x1d) -
                               iVar12) + 0x1c) ^ 0x80000000);
  local_f0 = (double)(CONCAT44(0x43300000,(char)menuPcs->field_0x8e * 0x28 + 0x70) ^ 0x80000000);
  RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
            ((double)(float)(local_f8 - DOUBLE_80333640),(double)(float)(local_f0 - DOUBLE_80333640)
             ,(double)FLOAT_80333570,(double)FLOAT_80333570,&DAT_8032ec70,
             *(undefined4 *)&menuPcs->field_0x18c,&local_248,&local_250,&local_254,4,5);
  iVar12 = *(int *)&menuPcs->field_0xc8;
  local_e8 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 100));
  local_e0 = (double)CONCAT44(0x43300000,(char)menuPcs->field_0x8e * 0x28 + 0x70U ^ 0x80000000);
  local_d8 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 0x68));
  RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
            ((double)FLOAT_80333574,(double)(float)(local_e0 - DOUBLE_80333640),
             (double)(float)(local_e8 - DOUBLE_80333638),(double)(float)(local_d8 - DOUBLE_80333638)
             ,&DAT_8032ec70,iVar12,0,0,&local_254,4,5);
  SetScaleX__5CFontFf(FLOAT_80333578,pCVar13);
  ppuVar16 = local_22c;
  dVar28 = (double)FLOAT_8033354c;
  iVar19 = 0;
  dVar27 = (double)FLOAT_8033356c;
  iVar12 = 0x70;
  uVar17 = 0x73;
  dVar26 = (double)FLOAT_80333558;
  uVar18 = 0x75;
  dVar22 = DOUBLE_80333638;
  dVar23 = DOUBLE_80333640;
  do {
    local_d8 = (double)CONCAT44(0x43300000,*(undefined4 *)(*(int *)&menuPcs->field_0xc0 + 100));
    dVar24 = (double)(float)(local_d8 - dVar22);
    local_e0 = (double)CONCAT44(0x43300000,*(undefined4 *)(*(int *)&menuPcs->field_0xc0 + 0x68));
    local_248 = FLOAT_80333558;
    if (iVar19 == (char)menuPcs->field_0x8e) {
      local_248 = FLOAT_8033354c;
    }
    local_244 = (float)dVar28;
    local_250 = FLOAT_8033356c;
    if (iVar19 == (char)menuPcs->field_0x8e) {
      local_250 = FLOAT_80333558;
    }
    local_e8 = (double)(CONCAT44(0x43300000,iVar12) ^ 0x80000000);
    local_24c = (float)dVar27;
    RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)FLOAT_8033357c,(double)(float)(local_e8 - dVar23),
               (double)(float)(dVar24 * dVar26),(double)(float)(local_e0 - dVar22),&DAT_8032ec70,
               *(undefined4 *)&menuPcs->field_0xc0,&local_248,&local_250,&local_254,4,5);
    if (iVar19 == (char)menuPcs->field_0x8e) {
      local_d8 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
      local_258 = local_254;
      iVar20 = (int)(FLOAT_80333580 + (float)(local_d8 - DOUBLE_80333640));
      local_e0 = (double)(longlong)iVar20;
      DrawFont__8CMenuPcsFii8_GXColoriPcff
                ((double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,0x5e,iVar20,&local_258,0x16,
                 *ppuVar16);
    }
    else {
      local_d8 = (double)CONCAT44(0x43300000,uVar18 ^ 0x80000000);
      local_25c = local_254;
      iVar20 = (int)(FLOAT_80333580 + (float)(local_d8 - DOUBLE_80333640));
      local_e0 = (double)(longlong)iVar20;
      DrawFont__8CMenuPcsFii8_GXColoriPcff
                ((double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,0x60,iVar20,&local_25c,6,
                 *ppuVar16);
    }
    iVar19 = iVar19 + 1;
    ppuVar16 = ppuVar16 + 1;
    uVar17 = uVar17 + 0x28;
    uVar18 = uVar18 + 0x28;
    iVar12 = iVar12 + 0x28;
  } while (iVar19 < 5);
  SetScaleX__5CFontFf(FLOAT_8033356c,pCVar13);
  RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
            ((double)FLOAT_8033354c,(double)FLOAT_80333584,(double)FLOAT_80333560,
             (double)FLOAT_80333588,&DAT_8032ec70,*(undefined4 *)&menuPcs->field_0x208,0,0,
             &local_254,4,5);
  local_260 = local_254;
  font = *(CFont **)&menuPcs->field_0xf8;
  puVar15 = local_240[(char)menuPcs->field_0x8e];
  SetShadow__5CFontFi(font,1);
  SetMargin__5CFontFf(FLOAT_8033356c,font);
  SetScaleX__5CFontFf(FLOAT_80333578,font);
  SetScaleY__5CFontFf(FLOAT_8033356c,font);
  dVar22 = (double)GetWidth__5CFontFPc(font,puVar15);
  iVar12 = (int)-(float)(dVar22 * (double)FLOAT_80333558 - (double)FLOAT_8033358c);
  local_e0 = (double)(longlong)(int)FLOAT_80333590;
  local_d8 = (double)(longlong)iVar12;
  DrawFont2__8CMenuPcsFii8_GXColoriPcfff
            ((double)FLOAT_80333578,(double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,iVar12,
             (int)FLOAT_80333590,&local_260,7,local_240[(char)menuPcs->field_0x8e]);
  bVar1 = menuPcs->field_0x93 == '\0';
  bVar2 = menuPcs->field_0x94 == '\0';
  iVar12 = (int)(*(float *)&menuPcs->field_0xa0 / FLOAT_80333598);
  local_f0 = (double)(longlong)iVar12;
  iVar19 = (int)(FLOAT_80333550 * *(float *)&menuPcs->field_0xa0);
  local_e8 = (double)(longlong)iVar19;
  local_f8 = (double)(CONCAT44(0x43300000,iVar12) ^ 0x80000000);
  local_254 = CONCAT31(local_254._0_3_,(char)iVar19);
  fVar5 = (float)(local_f8 - DOUBLE_80333640) * FLOAT_8033359c;
  dVar23 = (double)(FLOAT_80333594 * fVar5);
  dVar22 = (double)sin((double)(FLOAT_80333594 * FLOAT_803335a0 * fVar5));
  dVar26 = (double)(float)dVar22;
  dVar22 = (double)cos(dVar23);
  cVar4 = menuPcs->field_0x8e;
  dVar22 = (double)(float)dVar22;
  if (cVar4 == '\x02') {
    local_188 = (float)DAT_801e3794;
    local_1b8 = FLOAT_803335f8;
    local_1b4 = FLOAT_803335fc;
    local_1b0 = FLOAT_80333600;
    local_1ac = FLOAT_80333604;
    local_1a8 = FLOAT_80333564;
    local_1a4 = FLOAT_80333608;
    local_1a0 = FLOAT_8033360c;
    local_19c = FLOAT_80333608;
    local_198 = FLOAT_80333610;
    local_194 = FLOAT_80333614;
    local_190 = FLOAT_80333610;
    local_18c = FLOAT_80333618;
    local_184 = FLOAT_80333618;
    iVar19 = __vc__21CPtrArray<P8CTexture>FUl(*(int *)&menuPcs->field_0xbc + 8,3);
    fVar5 = FLOAT_803335a8 - local_1b8;
    local_e0 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar19 + 0x68));
    local_d0 = (double)(longlong)(int)fVar5;
    uVar11 = (uint)((FLOAT_8033361c + local_1b0) - FLOAT_803335a8);
    local_d8 = (double)(longlong)(int)uVar11;
    uVar6 = __cvt_fp2unsigned((double)(float)(local_e0 - DOUBLE_80333638));
    local_e8 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar19 + 100));
    uVar7 = __cvt_fp2unsigned((double)(float)(local_e8 - DOUBLE_80333638));
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,0x28,uVar7,uVar6);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x18,0x40,uVar7,uVar6);
    local_f0 = (double)CONCAT44(0x43300000,(int)fVar5 ^ 0x80000000);
    dVar23 = (double)(float)((double)FLOAT_80333620 * dVar26);
    iVar12 = (int)((double)(float)(local_f0 - DOUBLE_80333640) * dVar22 + (double)local_1b8);
    local_f8 = (double)(longlong)iVar12;
    local_100 = (double)(CONCAT44(0x43300000,iVar12) ^ 0x80000000);
    RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)(float)(local_100 - DOUBLE_80333640),
               (double)(float)((double)local_1b4 - dVar23),(double)FLOAT_8033361c,
               (double)FLOAT_8033361c,&DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,0,uVar7,uVar6);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x28,0x28,uVar7,uVar6);
    uStack_104 = uVar11 ^ 0x80000000;
    local_108 = 0x43300000;
    iVar12 = (int)-(float)((double)(float)((double)CONCAT44(0x43300000,uStack_104) - DOUBLE_80333640
                                          ) * dVar22 - (double)local_1b0);
    local_110 = (double)(longlong)iVar12;
    local_118 = (double)(CONCAT44(0x43300000,iVar12) ^ 0x80000000);
    RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)(float)(local_118 - DOUBLE_80333640),
               (double)(float)((double)local_1ac + dVar23),(double)FLOAT_80333588,
               (double)FLOAT_80333588,&DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
    iVar12 = (int)(FLOAT_80333550 * *(float *)&menuPcs->field_0xa8);
    local_120 = (double)(longlong)iVar12;
    local_254 = CONCAT31(local_254._0_3_,(char)iVar12);
    if (bVar1) {
      CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,0x58,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x10,0x70,uVar7,uVar6);
    }
    else {
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x18,0x58,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x28,0x70,uVar7,uVar6);
    }
    RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)local_1a8,(double)local_1a4,(double)FLOAT_80333624,(double)FLOAT_8033361c,
               &DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
    if (bVar2) {
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x48,0x5c,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x30,0x7c,uVar7,uVar6);
    }
    else {
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x60,0x5c,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x48,0x7c,uVar7,uVar6);
    }
    RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)local_1a0,(double)local_19c,(double)FLOAT_8033361c,(double)FLOAT_80333570,
               &DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x40,0x28,uVar7,uVar6);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x50,0x38,uVar7,uVar6);
    dVar23 = (double)local_198;
    iVar12 = 0;
    uVar11 = 0;
    dVar22 = DOUBLE_80333640;
    do {
      local_d0 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
      RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)(float)(dVar23 + (double)(float)(local_d0 - dVar22)),(double)local_194,
                 (double)FLOAT_80333624,(double)FLOAT_80333624,&DAT_8032ec70,iVar19,&local_248,
                 &local_250,&local_254,4,5);
      if ((menuPcs->field_0x9c != '\x02') && (iVar12 + 1 <= (int)(char)menuPcs->field_0x91)) {
        local_d0 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
        RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                  ((double)(local_198 + (float)(local_d0 - DOUBLE_80333640)),(double)local_194,
                   (double)FLOAT_80333624,(double)FLOAT_80333624,&DAT_8032ec70,iVar19,&local_248,
                   &local_250,&local_254,1,1);
      }
      iVar12 = iVar12 + 1;
      uVar11 = uVar11 + 0x10;
    } while (iVar12 < 0xc);
    local_d0 = (double)(longlong)(int)local_190;
    local_d8 = (double)(longlong)(int)local_18c;
    local_284 = local_254;
    DrawFont__8CMenuPcsFii8_GXColoriPcff
              ((double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,(int)local_190,(int)local_18c,
               &local_284,7,(&PTR_DAT_80215a88)[iVar14 * 0x14]);
    dVar22 = (double)GetWidth__5CFontFPc(pCVar13,(&PTR_DAT_80215a8c)[iVar14 * 0x14]);
    local_188 = (float)((double)FLOAT_80333628 - dVar22);
    local_e8 = (double)(longlong)(int)local_184;
    iVar12 = (int)((double)FLOAT_80333628 - dVar22);
    local_e0 = (double)(longlong)iVar12;
    local_288 = local_254;
    DrawFont__8CMenuPcsFii8_GXColoriPcff
              ((double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,iVar12,(int)local_184,
               &local_288,7,(&PTR_DAT_80215a8c)[iVar14 * 0x14]);
  }
  else if (cVar4 < '\x02') {
    if (cVar4 == '\0') {
      local_150 = DAT_801e371c;
      local_158 = DAT_801e3714;
      fVar5 = FLOAT_803335a8 - DAT_801e3714;
      local_d8 = (double)(longlong)(int)fVar5;
      uVar17 = (uint)((float)(dVar24 * (double)FLOAT_80333558 + (double)DAT_801e371c) -
                     FLOAT_803335a8);
      local_e0 = (double)(longlong)(int)uVar17;
      local_154 = DAT_801e3718;
      local_14c = DAT_801e3720;
      local_148 = DAT_801e3724;
      local_144 = DAT_801e3728;
      local_140 = DAT_801e372c;
      local_138 = DAT_801e3734;
      local_13c = FLOAT_803335a4;
      local_134 = FLOAT_803335a4;
      iVar19 = __vc__21CPtrArray<P8CTexture>FUl(*(int *)&menuPcs->field_0xbc + 8,1);
      local_f8 = (double)CONCAT44(0x43300000,(int)fVar5 ^ 0x80000000);
      local_e8 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar19 + 100));
      uStack_104 = (uint)((double)(float)(local_f8 - DOUBLE_80333640) * dVar22 + (double)local_158);
      local_100 = (double)(longlong)(int)uStack_104;
      local_f0 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar19 + 0x68));
      uStack_104 = uStack_104 ^ 0x80000000;
      dVar26 = (double)((float)(local_e8 - DOUBLE_80333638) * FLOAT_80333558);
      local_108 = 0x43300000;
      dVar23 = (double)(float)(local_f0 - DOUBLE_80333638);
      local_248 = FLOAT_8033354c;
      local_244 = FLOAT_8033354c;
      local_250 = FLOAT_80333558;
      local_24c = FLOAT_8033356c;
      RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)(float)((double)CONCAT44(0x43300000,uStack_104) - DOUBLE_80333640),
                 (double)local_154,dVar26,dVar23,&DAT_8032ec70,iVar19,&local_248,&local_250,
                 &local_254,4,5);
      local_110 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
      local_248 = FLOAT_80333558;
      local_244 = FLOAT_8033354c;
      iVar12 = (int)-(float)((double)(float)(local_110 - DOUBLE_80333640) * dVar22 -
                            (double)local_150);
      local_118 = (double)(longlong)iVar12;
      local_250 = FLOAT_8033356c;
      local_24c = FLOAT_8033356c;
      local_120 = (double)(CONCAT44(0x43300000,iVar12) ^ 0x80000000);
      RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)(float)(local_120 - DOUBLE_80333640),(double)local_14c,dVar26,dVar23,
                 &DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
      iVar12 = (int)(FLOAT_80333550 * *(float *)&menuPcs->field_0xa8);
      local_128 = (double)(longlong)iVar12;
      local_254 = CONCAT31(local_254._0_3_,(char)iVar12);
      iVar12 = __vc__21CPtrArray<P8CTexture>FUl(*(int *)&menuPcs->field_0xbc + 8,4);
      local_130 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 0x68));
      uVar6 = __cvt_fp2unsigned((double)(float)(local_130 - DOUBLE_80333638));
      local_d0 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 100));
      uVar7 = __cvt_fp2unsigned((double)(float)(local_d0 - DOUBLE_80333638));
      CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,0,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x78,0x30,uVar7,uVar6);
      fVar5 = local_148;
      if (menuPcs->field_0x8f != '\0') {
        fVar5 = FLOAT_803335ac + local_148;
      }
      RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)fVar5,(double)local_144,(double)FLOAT_803335b0,(double)FLOAT_803335b4,
                 &DAT_8032ec70,iVar12,&local_248,&local_250,&local_254,4,5);
      bVar1 = false;
      if ((uVar11 == 4) || (uVar11 == 5)) {
        bVar1 = true;
      }
      dVar22 = DOUBLE_803335c0;
      if (bVar1) {
        dVar22 = DOUBLE_803335b8;
      }
      dVar22 = (double)(float)dVar22;
      if (menuPcs->field_0x8f == '\0') {
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        puVar15 = (&PTR_DAT_80215a78)[iVar14 * 0x14];
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        dVar26 = (double)(float)((double)FLOAT_8033356c * dVar22);
        SetScale__5CFontFf((float)((double)FLOAT_8033356c * dVar22),pCVar13);
        dVar23 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_264 = local_254;
        iVar12 = (int)((double)(float)((double)FLOAT_803335b0 - dVar23) * DOUBLE_803335d0 +
                      DOUBLE_803335c8);
        local_d0 = (double)(longlong)iVar12;
        local_d8 = (double)(longlong)(int)(local_13c - FLOAT_803335a0);
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  (dVar26,(double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,iVar12,
                   (int)(local_13c - FLOAT_803335a0),&local_264,0x17,puVar15);
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        puVar15 = (&PTR_DAT_80215a7c)[iVar14 * 0x14];
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        SetScale__5CFontFf((float)dVar22,pCVar13);
        dVar23 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_e8 = (double)(longlong)(int)local_134;
        local_268 = local_254;
        iVar12 = (int)((double)(float)((double)FLOAT_803335b0 - dVar23) * DOUBLE_803335d0 +
                      DOUBLE_803335d8);
        local_e0 = (double)(longlong)iVar12;
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  (dVar22,(double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,iVar12,
                   (int)local_134,&local_268,6,puVar15);
      }
      else {
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        puVar15 = (&PTR_DAT_80215a78)[iVar14 * 0x14];
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        SetScale__5CFontFf((float)dVar22,pCVar13);
        dVar23 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_d8 = (double)(longlong)(int)local_13c;
        local_26c = local_254;
        iVar12 = (int)((double)(float)((double)FLOAT_803335b0 - dVar23) * DOUBLE_803335d0 +
                      DOUBLE_803335c8);
        local_d0 = (double)(longlong)iVar12;
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  (dVar22,(double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,iVar12,
                   (int)local_13c,&local_26c,6,puVar15);
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        puVar15 = (&PTR_DAT_80215a7c)[iVar14 * 0x14];
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        dVar23 = (double)(float)((double)FLOAT_8033356c * dVar22);
        SetScale__5CFontFf((float)((double)FLOAT_8033356c * dVar22),pCVar13);
        dVar22 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_270 = local_254;
        iVar12 = (int)((double)(float)((double)FLOAT_803335b0 - dVar22) * DOUBLE_803335d0 +
                      DOUBLE_803335d8);
        local_e0 = (double)(longlong)iVar12;
        local_e8 = (double)(longlong)(int)(local_134 - FLOAT_803335a0);
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  (dVar23,(double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,iVar12,
                   (int)(local_134 - FLOAT_803335a0),&local_270,0x17,puVar15);
      }
    }
    else if (-1 < cVar4) {
      local_178 = DAT_801e3744;
      local_180 = DAT_801e373c;
      fVar5 = FLOAT_803335a8 - DAT_801e373c;
      local_d0 = (double)(longlong)(int)fVar5;
      uVar11 = (uint)((float)(dVar24 * (double)FLOAT_80333558 + (double)DAT_801e3744) -
                     FLOAT_803335a8);
      local_d8 = (double)(longlong)(int)uVar11;
      local_17c = DAT_801e3740;
      local_174 = DAT_801e3748;
      local_170 = DAT_801e374c;
      local_16c = DAT_801e3750;
      local_168 = DAT_801e3754;
      local_160 = DAT_801e375c;
      local_164 = FLOAT_803335a4;
      local_15c = FLOAT_803335a4;
      iVar19 = __vc__21CPtrArray<P8CTexture>FUl(*(int *)&menuPcs->field_0xbc + 8,1);
      local_f0 = (double)CONCAT44(0x43300000,(int)fVar5 ^ 0x80000000);
      local_e0 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar19 + 100));
      uVar17 = (uint)((double)(float)(local_f0 - DOUBLE_80333640) * dVar22 + (double)local_180);
      local_f8 = (double)(longlong)(int)uVar17;
      local_e8 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar19 + 0x68));
      dVar26 = (double)((float)(local_e0 - DOUBLE_80333638) * FLOAT_80333558);
      local_100 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
      dVar23 = (double)(float)(local_e8 - DOUBLE_80333638);
      local_248 = FLOAT_8033354c;
      local_244 = FLOAT_8033354c;
      local_250 = FLOAT_80333558;
      local_24c = FLOAT_8033356c;
      RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)(float)(local_100 - DOUBLE_80333640),(double)local_17c,dVar26,dVar23,
                 &DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
      uStack_104 = uVar11 ^ 0x80000000;
      local_108 = 0x43300000;
      local_248 = FLOAT_80333558;
      local_244 = FLOAT_8033354c;
      iVar12 = (int)-(float)((double)(float)((double)CONCAT44(0x43300000,uStack_104) -
                                            DOUBLE_80333640) * dVar22 - (double)local_178);
      local_110 = (double)(longlong)iVar12;
      local_250 = FLOAT_8033356c;
      local_24c = FLOAT_8033356c;
      local_118 = (double)(CONCAT44(0x43300000,iVar12) ^ 0x80000000);
      RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)(float)(local_118 - DOUBLE_80333640),(double)local_174,dVar26,dVar23,
                 &DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
      iVar12 = (int)(FLOAT_80333550 * *(float *)&menuPcs->field_0xa8);
      local_120 = (double)(longlong)iVar12;
      local_254 = CONCAT31(local_254._0_3_,(char)iVar12);
      iVar12 = __vc__21CPtrArray<P8CTexture>FUl(*(int *)&menuPcs->field_0xbc + 8,4);
      local_128 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 0x68));
      uVar6 = __cvt_fp2unsigned((double)(float)(local_128 - DOUBLE_80333638));
      local_130 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar12 + 100));
      uVar7 = __cvt_fp2unsigned((double)(float)(local_130 - DOUBLE_80333638));
      CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,0,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x78,0x30,uVar7,uVar6);
      fVar5 = local_170;
      if (menuPcs->field_0x90 != '\0') {
        fVar5 = FLOAT_803335e0 + local_170;
      }
      RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)fVar5,(double)local_16c,(double)FLOAT_803335b0,(double)FLOAT_803335b4,
                 &DAT_8032ec70,iVar12,&local_248,&local_250,&local_254,4,5);
      if (menuPcs->field_0x90 == '\0') {
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        puVar15 = (&PTR_s_Stereo_80215a80)[iVar14 * 0x14];
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        dVar23 = DOUBLE_803335b8 * (double)FLOAT_8033356c;
        SetScale__5CFontFf((float)dVar23,pCVar13);
        dVar22 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_274 = local_254;
        iVar12 = (int)((double)(float)((double)FLOAT_803335b0 - dVar22) * DOUBLE_803335d0 +
                      DOUBLE_803335e8);
        local_d0 = (double)(longlong)iVar12;
        local_d8 = (double)(longlong)(int)(local_164 - FLOAT_803335a0);
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  ((double)(float)dVar23,(double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,
                   iVar12,(int)(local_164 - FLOAT_803335a0),&local_274,0x17,puVar15);
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        puVar15 = (&PTR_s_Monaural_80215a84)[iVar14 * 0x14];
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        SetScale__5CFontFf(FLOAT_80333578,pCVar13);
        dVar22 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_e8 = (double)(longlong)(int)local_15c;
        local_278 = local_254;
        iVar12 = (int)((double)(float)((double)FLOAT_803335b0 - dVar22) * DOUBLE_803335d0 +
                      DOUBLE_803335f0);
        local_e0 = (double)(longlong)iVar12;
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  ((double)FLOAT_80333578,(double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,
                   iVar12,(int)local_15c,&local_278,6,puVar15);
      }
      else {
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        puVar15 = (&PTR_s_Stereo_80215a80)[iVar14 * 0x14];
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        SetScale__5CFontFf(FLOAT_80333578,pCVar13);
        dVar22 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_d8 = (double)(longlong)(int)local_164;
        local_27c = local_254;
        iVar12 = (int)((double)(float)((double)FLOAT_803335b0 - dVar22) * DOUBLE_803335d0 +
                      DOUBLE_803335e8);
        local_d0 = (double)(longlong)iVar12;
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  ((double)FLOAT_80333578,(double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,
                   iVar12,(int)local_164,&local_27c,6,puVar15);
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        puVar15 = (&PTR_s_Monaural_80215a84)[iVar14 * 0x14];
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        dVar23 = DOUBLE_803335b8 * (double)FLOAT_8033356c;
        SetScale__5CFontFf((float)dVar23,pCVar13);
        dVar22 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_280 = local_254;
        iVar12 = (int)((double)(float)((double)FLOAT_803335b0 - dVar22) * DOUBLE_803335d0 +
                      DOUBLE_803335f0);
        local_e0 = (double)(longlong)iVar12;
        local_e8 = (double)(longlong)(int)(local_15c - FLOAT_803335a0);
        DrawFont2__8CMenuPcsFii8_GXColoriPcfff
                  ((double)(float)dVar23,(double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,
                   iVar12,(int)(local_15c - FLOAT_803335a0),&local_280,0x17,puVar15);
      }
    }
  }
  else if (cVar4 == '\x04') {
    local_218 = DAT_801e37d4;
    local_214 = DAT_801e37d8;
    local_210 = DAT_801e37dc;
    local_20c = DAT_801e37e0;
    local_208 = DAT_801e37e4;
    local_204 = DAT_801e37e8;
    local_200 = DAT_801e37ec;
    local_1fc = DAT_801e37f0;
    local_1f8 = DAT_801e37f4;
    local_1f4 = DAT_801e37f8;
    if (DOUBLE_803335c0 <= (double)*(float *)&menuPcs->field_0xa0) {
      uVar11 = 0xd;
    }
    else {
      uVar11 = (uint)((double)*(float *)&menuPcs->field_0xa0 / (double)FLOAT_8033362c);
      local_d0 = (double)(longlong)(int)uVar11;
    }
    local_d8 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
    dVar22 = (double)cos((double)(FLOAT_80333594 *
                                 (float)(local_d8 - DOUBLE_80333640) * FLOAT_80333630));
    local_c8 = &PTR_s_Enhanced_80215a90 + iVar14 * 0x14;
    dVar26 = (double)(float)dVar22;
    dVar27 = (double)FLOAT_803335b4;
    uVar17 = 0;
    dVar28 = (double)FLOAT_8033361c;
    iVar20 = 0;
    iVar12 = 0;
    iVar19 = 0x18;
    uVar11 = 0x280;
    dVar22 = DOUBLE_80333638;
    dVar23 = DOUBLE_80333640;
    do {
      iVar8 = __vc__21CPtrArray<P8CTexture>FUl(*(int *)&menuPcs->field_0xbc + 8,4);
      local_d0 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar8 + 100));
      dVar25 = (double)(float)(local_d0 - dVar22);
      local_d8 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar8 + 0x68));
      dVar24 = (double)(float)(local_d8 - dVar22);
      if ((*(int *)&menuPcs->field_0xb0 != 0) && ((char)menuPcs->field_0xb4 == iVar12)) {
        uVar6 = __cvt_fp2unsigned(dVar24);
        uVar7 = __cvt_fp2unsigned(dVar25);
        uVar9 = __cvt_fp2unsigned((double)(float)(dVar25 - (double)FLOAT_803335b4));
        CalcUV__5CUtilFRfRfUlUlUlUl
                  ((CUtil *)&DAT_8032ec70,&local_248,&local_244,uVar9,0,uVar7,uVar6);
        CalcUV__5CUtilFRfRfUlUlUlUl
                  ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,uVar7,0x28,uVar7,uVar6);
        local_d0 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
        RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                  ((double)local_218,(double)(local_214 + (float)(local_d0 - DOUBLE_80333640)),
                   (double)FLOAT_803335b4,(double)FLOAT_80333588,&DAT_8032ec70,iVar8,&local_248,
                   &local_250,&local_254,4,5);
      }
      if ((*(int *)&menuPcs->field_0xb0 != 0) && ((char)menuPcs->field_0xb4 == iVar12)) {
        uVar6 = __cvt_fp2unsigned(dVar24);
        uVar7 = __cvt_fp2unsigned(dVar25);
        CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,0x30,uVar7,uVar6)
        ;
        CalcUV__5CUtilFRfRfUlUlUlUl
                  ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,uVar7,uVar6,uVar7,uVar6);
        local_d0 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
        RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                  ((double)local_210,(double)(local_20c + (float)(local_d0 - DOUBLE_80333640)),
                   dVar25,(double)FLOAT_80333624,&DAT_8032ec70,iVar8,&local_248,&local_250,
                   &local_254,4,5);
        CalcUV__5CUtilFRfRfUlUlUlUl
                  ((CUtil *)&DAT_8032ec70,&local_248,&local_244,uVar7,0x30,uVar7,uVar6);
        CalcUV__5CUtilFRfRfUlUlUlUl
                  ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0,uVar6,uVar7,uVar6);
        local_d8 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
        RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                  ((double)(float)(dVar25 + (double)local_210),
                   (double)(local_20c + (float)(local_d8 - DOUBLE_80333640)),dVar25,
                   (double)FLOAT_80333624,&DAT_8032ec70,iVar8,&local_248,&local_250,&local_254,4,5);
      }
      iVar10 = __vc__21CPtrArray<P8CTexture>FUl(*(int *)&menuPcs->field_0xbc + 8,7);
      local_d0 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar10 + 100));
      dVar24 = (double)(float)(local_d0 - dVar22);
      local_d8 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar10 + 0x68));
      uVar6 = __cvt_fp2unsigned((double)(float)(local_d8 - dVar22));
      uVar7 = __cvt_fp2unsigned(dVar24);
      uVar9 = __cvt_fp2unsigned((double)(float)(dVar24 - dVar27));
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_248,&local_244,uVar9,iVar20,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,uVar7,iVar19,uVar7,uVar6);
      uStack_104 = uVar17 ^ 0x80000000;
      local_e0 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
      local_108 = 0x43300000;
      iVar8 = (int)((double)(float)(local_e0 - dVar23) - (double)local_208);
      local_e8 = (double)(longlong)iVar8;
      local_f0 = (double)(CONCAT44(0x43300000,iVar8) ^ 0x80000000);
      iVar8 = (int)((double)(float)(local_f0 - dVar23) * dVar26 + (double)local_208);
      local_f8 = (double)(longlong)iVar8;
      local_100 = (double)(CONCAT44(0x43300000,iVar8) ^ 0x80000000);
      RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)(float)(local_100 - dVar23),
                 (double)(local_204 + (float)((double)CONCAT44(0x43300000,uStack_104) - dVar23)),
                 (double)FLOAT_80333588,(double)FLOAT_8033361c,&DAT_8032ec70,iVar10,&local_248,
                 &local_250,&local_254,4,5);
      local_110 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
      iVar8 = (int)(dVar28 + (double)(float)((double)(float)(local_110 - dVar23) - (double)local_200
                                            ));
      local_118 = (double)(longlong)iVar8;
      local_120 = (double)(CONCAT44(0x43300000,iVar8) ^ 0x80000000);
      dVar24 = (double)(float)((double)(float)(local_120 - dVar23) * dVar26);
      uVar18 = (uint)((double)local_200 + dVar24);
      local_128 = (double)(longlong)(int)uVar18;
      if ((&menuPcs->field_0xb5)[iVar12] == '\0') {
        CalcUV__5CUtilFRfRfUlUlUlUl
                  ((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,iVar20,uVar7,uVar6);
        CalcUV__5CUtilFRfRfUlUlUlUl
                  ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x78,(iVar12 + 1) * 0x20,uVar7,uVar6
                  );
        local_d8 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
        local_d0 = (double)CONCAT44(0x43300000,uVar18 ^ 0x80000000);
        RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                  ((double)(float)(local_d0 - DOUBLE_80333640),
                   (double)(local_1fc + (float)(local_d8 - DOUBLE_80333640)),(double)FLOAT_803335b0,
                   (double)FLOAT_80333570,&DAT_8032ec70,iVar10,&local_248,&local_250,&local_254,4,5)
        ;
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        dVar25 = (double)local_1f8;
        puVar15 = *local_c8;
        local_e0 = (double)(longlong)(int)(dVar25 + dVar24);
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        SetScale__5CFontFf(FLOAT_8033356c,pCVar13);
        dVar21 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_f8 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
        local_e8 = (double)CONCAT44(0x43300000,(int)(dVar25 + dVar24) ^ 0x80000000);
        local_294 = local_254;
        iVar8 = (int)(FLOAT_80333580 +
                     FLOAT_80333634 + local_1f4 + (float)(local_f8 - DOUBLE_80333640));
        local_100 = (double)(longlong)iVar8;
        iVar10 = (int)((double)(float)((double)FLOAT_803335b0 - dVar21) * DOUBLE_803335d0 +
                      (local_e8 - DOUBLE_80333640));
        local_f0 = (double)(longlong)iVar10;
        DrawFont__8CMenuPcsFii8_GXColoriPcff
                  ((double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,iVar10,iVar8,&local_294,7,
                   puVar15);
      }
      else {
        pCVar13 = *(CFont **)&menuPcs->field_0xf8;
        puVar15 = (&PTR_s_Standard_80215a94)[iVar14 * 0x14];
        SetMargin__5CFontFf(FLOAT_8033356c,pCVar13);
        SetShadow__5CFontFi(pCVar13,1);
        SetScale__5CFontFf(FLOAT_8033356c,pCVar13);
        dVar25 = (double)GetWidth__5CFontFPc(pCVar13,puVar15);
        local_e0 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
        local_d0 = (double)CONCAT44(0x43300000,uVar18 ^ 0x80000000);
        local_298 = local_254;
        iVar8 = (int)(FLOAT_80333580 +
                     FLOAT_80333634 + local_1fc + (float)(local_e0 - DOUBLE_80333640));
        local_e8 = (double)(longlong)iVar8;
        iVar3 = (int)((double)(float)((double)FLOAT_803335b0 - dVar25) * DOUBLE_803335d0 +
                     (local_d0 - DOUBLE_80333640));
        local_d8 = (double)(longlong)iVar3;
        DrawFont__8CMenuPcsFii8_GXColoriPcff
                  ((double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,iVar3,iVar8,&local_298,7,
                   puVar15);
        dVar25 = (double)local_1f8;
        local_f0 = (double)(longlong)(int)(dVar25 + dVar24);
        CalcUV__5CUtilFRfRfUlUlUlUl
                  ((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x78,iVar20,uVar7,uVar6);
        CalcUV__5CUtilFRfRfUlUlUlUl
                  ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0xe0,(iVar12 + 1) * 0x20,uVar7,uVar6
                  );
        local_100 = (double)CONCAT44(0x43300000,uVar17 ^ 0x80000000);
        local_f8 = (double)CONCAT44(0x43300000,(int)(dVar25 + dVar24) ^ 0x80000000);
        RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                  ((double)(float)(local_f8 - DOUBLE_80333640),
                   (double)(local_1f4 + (float)(local_100 - DOUBLE_80333640)),(double)FLOAT_803335e0
                   ,(double)FLOAT_80333570,&DAT_8032ec70,iVar10,&local_248,&local_250,&local_254,4,5
                  );
      }
      iVar12 = iVar12 + 1;
      uVar17 = uVar17 + 0x28;
      iVar20 = iVar20 + 0x20;
      iVar19 = iVar19 + 0x20;
      uVar11 = uVar11 + 0x40;
    } while (iVar12 < 4);
  }
  else if (cVar4 < '\x04') {
    local_1c0 = (float)DAT_801e37cc;
    local_1f0 = FLOAT_803335f8;
    local_1ec = FLOAT_803335fc;
    local_1e8 = FLOAT_80333600;
    local_1e4 = FLOAT_80333604;
    local_1e0 = FLOAT_80333564;
    local_1dc = FLOAT_80333608;
    local_1d8 = FLOAT_8033360c;
    local_1d4 = FLOAT_80333608;
    local_1d0 = FLOAT_80333610;
    local_1cc = FLOAT_80333614;
    local_1c8 = FLOAT_80333610;
    local_1c4 = FLOAT_80333618;
    local_1bc = FLOAT_80333618;
    iVar19 = __vc__21CPtrArray<P8CTexture>FUl(*(int *)&menuPcs->field_0xbc + 8,3);
    fVar5 = FLOAT_803335a8 - local_1f0;
    local_e0 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar19 + 0x68));
    local_d0 = (double)(longlong)(int)fVar5;
    uVar11 = (uint)((FLOAT_8033361c + local_1e8) - FLOAT_803335a8);
    local_d8 = (double)(longlong)(int)uVar11;
    uVar6 = __cvt_fp2unsigned((double)(float)(local_e0 - DOUBLE_80333638));
    local_e8 = (double)CONCAT44(0x43300000,*(undefined4 *)(iVar19 + 100));
    uVar7 = __cvt_fp2unsigned((double)(float)(local_e8 - DOUBLE_80333638));
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x18,0x28,uVar7,uVar6);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x30,0x40,uVar7,uVar6);
    local_f0 = (double)CONCAT44(0x43300000,(int)fVar5 ^ 0x80000000);
    dVar23 = (double)(float)((double)FLOAT_80333620 * dVar26);
    iVar12 = (int)((double)(float)(local_f0 - DOUBLE_80333640) * dVar22 + (double)local_1f0);
    local_f8 = (double)(longlong)iVar12;
    local_100 = (double)(CONCAT44(0x43300000,iVar12) ^ 0x80000000);
    RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)(float)(local_100 - DOUBLE_80333640),
               (double)(float)((double)local_1ec + dVar23),(double)FLOAT_8033361c,
               (double)FLOAT_8033361c,&DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x28,0,uVar7,uVar6);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x50,0x28,uVar7,uVar6);
    uStack_104 = uVar11 ^ 0x80000000;
    local_108 = 0x43300000;
    iVar12 = (int)-(float)((double)(float)((double)CONCAT44(0x43300000,uStack_104) - DOUBLE_80333640
                                          ) * dVar22 - (double)local_1e8);
    local_110 = (double)(longlong)iVar12;
    local_118 = (double)(CONCAT44(0x43300000,iVar12) ^ 0x80000000);
    RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)(float)(local_118 - DOUBLE_80333640),
               (double)(float)((double)local_1e4 - dVar23),(double)FLOAT_80333588,
               (double)FLOAT_80333588,&DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
    iVar12 = (int)(FLOAT_80333550 * *(float *)&menuPcs->field_0xa8);
    local_120 = (double)(longlong)iVar12;
    local_254 = CONCAT31(local_254._0_3_,(char)iVar12);
    if (bVar1) {
      CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0,0x40,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x10,0x58,uVar7,uVar6);
    }
    else {
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x18,0x40,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x28,0x58,uVar7,uVar6);
    }
    RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)local_1e0,(double)local_1dc,(double)FLOAT_80333624,(double)FLOAT_8033361c,
               &DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
    if (bVar2) {
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x48,0x3c,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x30,0x5c,uVar7,uVar6);
    }
    else {
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x60,0x3c,uVar7,uVar6);
      CalcUV__5CUtilFRfRfUlUlUlUl
                ((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x48,0x5c,uVar7,uVar6);
    }
    RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)local_1d8,(double)local_1d4,(double)FLOAT_8033361c,(double)FLOAT_80333570,
               &DAT_8032ec70,iVar19,&local_248,&local_250,&local_254,4,5);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_248,&local_244,0x30,0x28,uVar7,uVar6);
    CalcUV__5CUtilFRfRfUlUlUlUl((CUtil *)&DAT_8032ec70,&local_250,&local_24c,0x40,0x38,uVar7,uVar6);
    dVar23 = (double)local_1d0;
    iVar12 = 0;
    uVar11 = 0;
    dVar22 = DOUBLE_80333640;
    do {
      local_d0 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
      RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                ((double)(float)(dVar23 + (double)(float)(local_d0 - dVar22)),(double)local_1cc,
                 (double)FLOAT_80333624,(double)FLOAT_80333624,&DAT_8032ec70,iVar19,&local_248,
                 &local_250,&local_254,4,5);
      if ((menuPcs->field_0x9c != '\x02') && (iVar12 + 1 <= (int)(char)menuPcs->field_0x92)) {
        local_d0 = (double)CONCAT44(0x43300000,uVar11 ^ 0x80000000);
        RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
                  ((double)(local_1d0 + (float)(local_d0 - DOUBLE_80333640)),(double)local_1cc,
                   (double)FLOAT_80333624,(double)FLOAT_80333624,&DAT_8032ec70,iVar19,&local_248,
                   &local_250,&local_254,1,1);
      }
      iVar12 = iVar12 + 1;
      uVar11 = uVar11 + 0x10;
    } while (iVar12 < 0xc);
    local_d0 = (double)(longlong)(int)local_1c8;
    local_d8 = (double)(longlong)(int)local_1c4;
    local_28c = local_254;
    DrawFont__8CMenuPcsFii8_GXColoriPcff
              ((double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,(int)local_1c8,(int)local_1c4,
               &local_28c,7,(&PTR_DAT_80215a88)[iVar14 * 0x14]);
    dVar22 = (double)GetWidth__5CFontFPc(pCVar13,(&PTR_DAT_80215a8c)[iVar14 * 0x14]);
    local_1c0 = (float)((double)FLOAT_80333628 - dVar22);
    local_e8 = (double)(longlong)(int)local_1bc;
    iVar12 = (int)((double)FLOAT_80333628 - dVar22);
    local_e0 = (double)(longlong)iVar12;
    local_290 = local_254;
    DrawFont__8CMenuPcsFii8_GXColoriPcff
              ((double)FLOAT_8033356c,(double)FLOAT_8033356c,menuPcs,iVar12,(int)local_1bc,
               &local_290,7,(&PTR_DAT_80215a8c)[iVar14 * 0x14]);
  }
  return;
}

