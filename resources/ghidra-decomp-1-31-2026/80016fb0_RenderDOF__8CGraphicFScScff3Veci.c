// Function: RenderDOF__8CGraphicFScScff3Veci
// Entry: 80016fb0
// Size: 2112 bytes

/* WARNING: Removing unreachable block (ram,0x800177d4) */
/* WARNING: Removing unreachable block (ram,0x800177cc) */
/* WARNING: Removing unreachable block (ram,0x800177c4) */
/* WARNING: Removing unreachable block (ram,0x800177bc) */
/* WARNING: Removing unreachable block (ram,0x800177b4) */
/* WARNING: Removing unreachable block (ram,0x800177ac) */
/* WARNING: Removing unreachable block (ram,0x800177a4) */
/* WARNING: Removing unreachable block (ram,0x8001779c) */
/* WARNING: Removing unreachable block (ram,0x80016ff8) */
/* WARNING: Removing unreachable block (ram,0x80016ff0) */
/* WARNING: Removing unreachable block (ram,0x80016fe8) */
/* WARNING: Removing unreachable block (ram,0x80016fe0) */
/* WARNING: Removing unreachable block (ram,0x80016fd8) */
/* WARNING: Removing unreachable block (ram,0x80016fd0) */
/* WARNING: Removing unreachable block (ram,0x80016fc8) */
/* WARNING: Removing unreachable block (ram,0x80016fc0) */

CGraphic *
RenderDOF__8CGraphicFScScff3Veci
          (double param_1,double param_2,CGraphic *graphic,char param_4,char param_5,Vec *param_6)

{
  bool bVar1;
  bool bVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined uVar8;
  undefined uVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
  undefined4 local_21c;
  undefined4 local_218;
  undefined4 local_214;
  float local_210;
  undefined auStack_20c [4];
  undefined auStack_208 [4];
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
  Vec local_174;
  Vec VStack_168;
  Vec local_15c;
  undefined auStack_150 [32];
  undefined auStack_130 [32];
  undefined auStack_110 [24];
  undefined auStack_f8 [28];
  Mtx MStack_dc;
  undefined4 local_a8;
  CGraphic *pCStack_a4;
  
  if (param_4 < '\x04') {
    if (param_1 < (double)FLOAT_8032f6c0) {
      param_1 = (double)FLOAT_8032f6c0;
    }
    if ((double)FLOAT_8032f6c4 < param_1) {
      param_1 = (double)FLOAT_8032f6c4;
    }
    if (param_2 < param_1) {
      param_2 = param_1;
    }
    if (param_5 < '\x01') {
      param_5 = '\x01';
    }
    uVar9 = 0;
    uVar8 = 0;
    uVar3 = GXGetTexBufferSize(0x140,0xe0,6,0,0);
    bVar1 = false;
    local_15c.x = (float)CameraPcs._224_4_;
    bVar2 = false;
    local_15c.z = (float)CameraPcs._232_4_;
    local_15c.y = FLOAT_8032f6c0;
    param_6->y = FLOAT_8032f6c0;
    PSVECSubtract(param_6,&local_15c,&VStack_168);
    GXGetProjectionv(auStack_f8);
    GXGetViewportv(auStack_110);
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_dc);
    if (param_4 != '\x02') {
      PSVECScale((float)param_1,&VStack_168,&local_174);
      GXProject((double)(local_15c.x + local_174.x),(double)param_6->y,
                (double)(local_15c.z + local_174.z),&MStack_dc,auStack_f8,auStack_110,auStack_208,
                auStack_20c,&local_210);
      uVar4 = __cvt_fp2unsigned((double)(FLOAT_8032f6f8 * local_210));
      uVar4 = uVar4 >> 0x10;
      if (0xfe < uVar4) {
        uVar4 = 0xff;
      }
      uVar9 = (undefined)uVar4;
      bVar1 = true;
    }
    if (param_4 != '\x01') {
      dVar10 = (double)PSVECMag(&VStack_168);
      PSVECScale((float)(param_2 / dVar10),&VStack_168,&local_174);
      GXProject((double)(param_6->x + local_174.x),(double)param_6->y,
                (double)(param_6->z + local_174.z),&MStack_dc,auStack_f8,auStack_110,auStack_208,
                auStack_20c,&local_210);
      uVar4 = __cvt_fp2unsigned((double)(FLOAT_8032f6f8 * local_210));
      uVar4 = uVar4 >> 0x10;
      if (uVar4 == 0) {
        uVar4 = 0xff;
      }
      if (0xfe < uVar4) {
        uVar4 = 0xff;
      }
      uVar8 = (undefined)uVar4;
      bVar2 = true;
    }
    if (!bVar1) {
      uVar9 = 0;
    }
    if (!bVar2) {
      uVar8 = 0xff;
    }
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
    CreateSmallBackTexture__8CGraphicFPvP9_GXTexObjll12_GXTexFilter9_GXTexFmtUl
              (&Graphic,DAT_80238030,auStack_130,0x140,0xe0,1,6,0);
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,DAT_80238030,auStack_150,0,0,0x280,0x1c0,uVar3,1,0x11,0);
    SetVtxFmt_POS_CLR_TEX0_TEX1__5CUtilFv(&DAT_8032ec70);
    SetOrthoEnv__5CUtilFv(&DAT_8032ec70);
    graphic = (CGraphic *)((int)param_5 ^ 0x80000000);
    local_a8 = 0x43300000;
    iVar7 = 0;
    dVar11 = (double)(float)((double)CONCAT44(0x43300000,graphic) - DOUBLE_8032f6e8);
    dVar10 = (double)(float)((double)FLOAT_8032f6fc * dVar11);
    dVar17 = -dVar11;
    dVar16 = (double)(float)((double)FLOAT_8032f6c8 - dVar11);
    dVar15 = (double)(float)((double)FLOAT_8032f6c8 + dVar11);
    dVar14 = -dVar10;
    dVar13 = (double)(float)((double)FLOAT_8032f6cc - dVar10);
    dVar12 = (double)(float)((double)FLOAT_8032f6cc + dVar10);
    pCStack_a4 = graphic;
    do {
      if ((iVar7 != 0) || ((((param_4 != '\x02' && (bVar1)) && (param_4 != '\x01')) && (bVar2)))) {
        uVar3 = 0xc;
        uVar6 = 0x1c;
        uVar5 = uVar9;
        if (iVar7 != 0) {
          uVar3 = 0xd;
          uVar6 = 0x1d;
          uVar5 = uVar8;
        }
        local_218 = CONCAT31(CONCAT21(CONCAT11(uVar5,uVar5),uVar5),uVar5);
        local_214 = CONCAT31(CONCAT21(CONCAT11(uVar5,uVar5),uVar5),0x80);
        local_21c = local_218;
        GXSetTevKColor(iVar7 != 0,&local_21c);
        local_220 = local_214;
        GXSetChanAmbColor(4,&local_220);
        local_224 = local_214;
        GXSetChanMatColor(4,&local_224);
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,5);
        GXSetTevDirect(0);
        GXLoadTexObj(auStack_150,0);
        GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
        GXSetTevKColorSel(0,uVar3);
        GXSetTevKAlphaSel(0,uVar6);
        if (iVar7 == 0) {
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (0,0xe,8,0xc,0xf);
        }
        else {
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (0,8,0xe,0xc,0xf);
        }
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,8,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (0,4,6,6,7);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,8,0,0,1,0);
        GXSetTevDirect(1);
        GXLoadTexObj(auStack_130,1);
        GXSetTexCoordGen2(1,1,5,0x3c,0,0x7d);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,1,1,4);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (1,0xf,0xf,0xf,8);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (1,0,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (1,7,5,0,7);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (1,0,0,0,1,0);
        GXSetNumTevStages(2);
        GXSetNumTexGens(2);
        uVar3 = local_214;
        local_180 = FLOAT_8032f6c0;
        local_17c = FLOAT_8032f6c0;
        local_178 = FLOAT_8032f6c0;
        local_18c = FLOAT_8032f6c8;
        local_188 = FLOAT_8032f6cc;
        local_184 = FLOAT_8032f6c0;
        local_228 = local_214;
        local_1a4 = FLOAT_8032f6c8;
        local_1a0 = FLOAT_8032f6cc;
        local_19c = FLOAT_8032f6c0;
        local_198 = FLOAT_8032f6c0;
        local_194 = FLOAT_8032f6c0;
        local_190 = FLOAT_8032f6c0;
        RenderQuadTex2__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                  (&DAT_8032ec70,&local_198,&local_1a4,&local_228,0,0);
        local_1b0 = (float)dVar17;
        local_17c = FLOAT_8032f6c0;
        local_178 = FLOAT_8032f6c0;
        local_1bc = (float)dVar16;
        local_188 = FLOAT_8032f6cc;
        local_184 = FLOAT_8032f6c0;
        local_22c = uVar3;
        local_1b8 = FLOAT_8032f6cc;
        local_1b4 = FLOAT_8032f6c0;
        local_1ac = FLOAT_8032f6c0;
        local_1a8 = FLOAT_8032f6c0;
        local_18c = local_1bc;
        local_180 = local_1b0;
        RenderQuadTex2__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                  (&DAT_8032ec70,&local_1b0,&local_1bc,&local_22c,0,0);
        local_1c8 = (float)dVar11;
        local_17c = FLOAT_8032f6c0;
        local_178 = FLOAT_8032f6c0;
        local_1d4 = (float)dVar15;
        local_188 = FLOAT_8032f6cc;
        local_184 = FLOAT_8032f6c0;
        local_230 = uVar3;
        local_1d0 = FLOAT_8032f6cc;
        local_1cc = FLOAT_8032f6c0;
        local_1c4 = FLOAT_8032f6c0;
        local_1c0 = FLOAT_8032f6c0;
        local_18c = local_1d4;
        local_180 = local_1c8;
        RenderQuadTex2__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                  (&DAT_8032ec70,&local_1c8,&local_1d4,&local_230,0,0);
        local_180 = FLOAT_8032f6c0;
        local_1dc = (float)dVar14;
        local_178 = FLOAT_8032f6c0;
        local_18c = FLOAT_8032f6c8;
        local_1e8 = (float)dVar13;
        local_184 = FLOAT_8032f6c0;
        local_234 = uVar3;
        local_1ec = FLOAT_8032f6c8;
        local_1e4 = FLOAT_8032f6c0;
        local_1e0 = FLOAT_8032f6c0;
        local_1d8 = FLOAT_8032f6c0;
        local_188 = local_1e8;
        local_17c = local_1dc;
        RenderQuadTex2__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                  (&DAT_8032ec70,&local_1e0,&local_1ec,&local_234,0,0);
        local_180 = FLOAT_8032f6c0;
        local_1f4 = (float)dVar10;
        local_178 = FLOAT_8032f6c0;
        local_18c = FLOAT_8032f6c8;
        local_200 = (float)dVar12;
        local_184 = FLOAT_8032f6c0;
        local_238 = uVar3;
        local_204 = FLOAT_8032f6c8;
        local_1fc = FLOAT_8032f6c0;
        local_1f8 = FLOAT_8032f6c0;
        local_1f0 = FLOAT_8032f6c0;
        local_188 = local_200;
        local_17c = local_1f4;
        graphic = (CGraphic *)
                  RenderQuadTex2__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                            (&DAT_8032ec70,&local_1f8,&local_204,&local_238,0,0);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < 2);
  }
  return graphic;
}

