// Function: drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
// Entry: 800e46dc
// Size: 2268 bytes

/* WARNING: Removing unreachable block (ram,0x800e4f9c) */
/* WARNING: Removing unreachable block (ram,0x800e4f94) */
/* WARNING: Removing unreachable block (ram,0x800e46f4) */
/* WARNING: Removing unreachable block (ram,0x800e46ec) */

void drawParaboloidMap__FP9_GXTexObjP9_GXTexObjPvUlP9_GXTexObjUc
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
               byte param_6)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  double dVar11;
  double dVar12;
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
  float local_240 [2];
  undefined4 local_238;
  undefined2 local_234;
  Vec local_230;
  undefined4 local_224;
  undefined4 local_220;
  undefined4 local_21c;
  Vec local_218;
  undefined4 local_20c;
  undefined4 local_208;
  undefined2 local_204;
  undefined4 local_200;
  undefined4 local_1fc;
  undefined2 local_1f8;
  undefined4 local_1f4;
  undefined4 local_1f0;
  undefined2 local_1ec;
  float local_1e8 [4];
  undefined4 local_1d8;
  undefined4 local_1d4;
  Mtx MStack_1d0;
  Mtx MStack_1a0;
  Mtx MStack_170;
  Mtx MStack_140;
  Mtx MStack_110;
  undefined auStack_d0 [64];
  undefined4 local_90;
  uint uStack_8c;
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  undefined4 local_78;
  uint uStack_74;
  uint local_70;
  uint local_6c;
  
  local_1f4 = DAT_801db740;
  local_1f0 = DAT_801db744;
  local_1ec = DAT_801db748;
  local_200 = DAT_801db74c;
  local_1fc = DAT_801db750;
  local_1f8 = DAT_801db754;
  local_20c = DAT_801db758;
  local_208 = DAT_801db75c;
  local_204 = DAT_801db760;
  local_1e8[0] = DAT_801db770;
  local_1e8[1] = (float)DAT_801db774;
  local_1e8[2] = (float)DAT_801db778;
  local_1e8[3] = (float)DAT_801db77c;
  local_1d8 = DAT_801db780;
  local_1d4 = DAT_801db784;
  local_238 = DAT_80331170;
  local_234 = DAT_80331174;
  local_240[0] = DAT_80331178;
  local_240[1] = (float)DAT_8033117c;
  uVar3 = GXGetTexObjWidth(param_2);
  uVar4 = GXGetTexObjHeight(param_2);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  uStack_8c = uVar3 & 0xffff;
  uStack_84 = uVar4 & 0xffff;
  iVar7 = (uint)param_6 * 5;
  local_90 = 0x43300000;
  local_88 = 0x43300000;
  local_254 = 0xff;
  local_218.x = DAT_801db788;
  local_218.y = DAT_801db78c;
  local_218.z = DAT_801db790;
  local_224 = DAT_801db794;
  local_220 = DAT_801db798;
  local_21c = DAT_801db79c;
  local_230.x = DAT_801db7a0;
  local_230.y = DAT_801db7a4;
  local_230.z = DAT_801db7a8;
  local_258 = 0xff;
  local_70 = uStack_84;
  local_6c = uStack_8c;
  RenderColorQuad__5CUtilFffff8_GXColor
            ((double)FLOAT_80331180,(double)FLOAT_80331180,
             (double)(float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_803311a8),
             (double)(float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_803311a8),&DAT_8032ec70
             ,&local_258);
  uVar3 = GXGetTexObjWidth(param_2);
  uVar4 = GXGetTexObjHeight(param_2);
  uVar5 = GXGetTexObjFmt(param_2);
  uVar6 = GXGetTexObjData(param_2);
  C_MTXOrtho(FLOAT_80331184,FLOAT_80331188,FLOAT_80331188,FLOAT_80331184,FLOAT_80331184,
             FLOAT_8033118c,&MStack_110);
  GXSetProjection(&MStack_110,1);
  C_MTXLookAt(&MStack_140,&local_218,&local_224,&local_230);
  GXLoadPosMtxImm(&MStack_140,0);
  GXSetCullMode(2);
  uStack_7c = uVar3 & 0xffff;
  uStack_74 = uVar4 & 0xffff;
  dVar11 = (double)FLOAT_80331180;
  local_80 = 0x43300000;
  local_78 = 0x43300000;
  GXSetViewport(dVar11,dVar11,
                (double)(float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_803311a8),
                (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_803311a8),dVar11,
                (double)FLOAT_80331184);
  GXSetScissor(0,0,uVar3 & 0xffff,uVar4 & 0xffff);
  GXSetTexCopySrc(0,0,uVar3,uVar4);
  GXSetTexCopyDst(uVar3,uVar4,uVar5,0);
  GXSetChanCtrl(4,1,0,0,1,0,0);
  local_254 = 0xffffffff;
  local_25c = 0xffffffff;
  GXInitLightColor(auStack_d0,&local_25c);
  local_260 = local_254;
  GXSetChanMatColor(4,&local_260);
  local_254 = 0;
  local_264 = 0;
  GXSetChanAmbColor(4,&local_264);
  GXInitLightAttnA((double)FLOAT_80331180,(double)FLOAT_80331190,(double)FLOAT_80331180,auStack_d0);
  GXInitLightAttnK((double)FLOAT_80331180,(double)FLOAT_80331184,(double)FLOAT_80331180,auStack_d0);
  GXInitLightPos((double)FLOAT_80331180,(double)FLOAT_80331180,(double)FLOAT_80331188,auStack_d0);
  GXInitLightDir((double)FLOAT_80331180,(double)FLOAT_80331180,(double)FLOAT_80331188,auStack_d0);
  GXLoadLightObjImm(auStack_d0,1);
  GXSetTexCoordGen2(0,0,1,0x1e,0,0x7d);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (0,0xf,0xf,0xf,8);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (0,7,4,5,7);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0);
  GXSetNumTevStages(1);
  GXSetNumTexGens(1);
  GXSetNumChans(1);
  C_MTXLightFrustum(FLOAT_80331194,FLOAT_80331198,FLOAT_80331194,FLOAT_80331198,FLOAT_80331184,
                    FLOAT_8033119c,FLOAT_8033119c,FLOAT_8033119c,&MStack_1a0);
  GXSetZMode(0,7,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,0xf);
  if (param_5 != 0) {
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (0,0xf,0xf,0xf,0xf);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (0,7,4,5,7);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (1,0xf,8,1,0xf);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,0,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (1,7,7,4,0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,0,1,0)
    ;
    GXSetTevDirect(0);
    GXSetTevDirect(1);
    GXSetNumTevStages(2);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0,0,1,0x1e,0,0x7d);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,0,1,4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
    local_254 = 0xffffffff;
    local_268 = 0xffffffff;
    GXSetChanMatColor(4,&local_268);
    GXLoadTexObj(param_5,0);
  }
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(10,1);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,10,0,4,0);
  dVar11 = (double)FLOAT_80331180;
  dVar12 = (double)FLOAT_803311a0;
  pbVar8 = (byte *)((int)&local_1f4 + iVar7);
  pbVar9 = (byte *)((int)&local_200 + iVar7);
  pbVar10 = (byte *)((int)&local_20c + iVar7);
  iVar7 = 0;
  do {
    bVar1 = *pbVar9;
    bVar2 = *pbVar10;
    if (param_5 == 0) {
      GXLoadTexObj(param_1 + (uint)*pbVar8 * 0x20,0);
    }
    else {
      GXLoadTexObj(param_1 + (uint)*pbVar8 * 0x20,1);
    }
    PSMTXIdentity(&MStack_170);
    if ((double)local_240[bVar2] != dVar11) {
      PSMTXRotRad((float)((double)FLOAT_803311a0 * (double)local_240[bVar2]),&MStack_1d0,0x79);
      PSMTXConcat(&MStack_170,&MStack_1d0,&MStack_170);
    }
    PSMTXRotRad((float)(dVar12 * (double)local_1e8[bVar1]),&MStack_1d0,
                (uint)*(byte *)((int)&local_238 + (uint)bVar1));
    PSMTXConcat(&MStack_170,&MStack_1d0,&MStack_170);
    PSMTXConcat(&MStack_1a0,&MStack_170,&MStack_170);
    GXLoadTexMtxImm(&MStack_170,0x1e,0);
    GXLoadNrmMtxImm(&MStack_170,0);
    GXCallDisplayList(param_3,param_4);
    iVar7 = iVar7 + 1;
    pbVar9 = pbVar9 + 1;
    pbVar8 = pbVar8 + 1;
    pbVar10 = pbVar10 + 1;
  } while (iVar7 < 5);
  GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
            (&Graphic,uVar6,param_2,0,0,uVar3 & 0xffff,uVar4 & 0xffff,0,1,4,0);
  GXSetScissor(0,0,0x280,0x1c0);
  SetViewport__8CGraphicFv(&Graphic);
  if (param_6 != 0) {
    uStack_74 = uVar3 & 0xffff;
    uStack_7c = uVar4 & 0xffff;
    local_78 = 0x43300000;
    local_80 = 0x43300000;
    local_248 = FLOAT_80331184;
    local_244 = FLOAT_80331180;
    local_250 = FLOAT_80331180;
    local_24c = FLOAT_80331184;
    RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)FLOAT_80331180,(double)FLOAT_80331180,
               (double)(float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_803311a8),
               (double)(float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_803311a8),
               &DAT_8032ec70,param_2,&local_248,&local_250,0,4,5);
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,uVar6,param_2,0,0,local_6c,local_70,0,1,4,0);
  }
  return;
}

