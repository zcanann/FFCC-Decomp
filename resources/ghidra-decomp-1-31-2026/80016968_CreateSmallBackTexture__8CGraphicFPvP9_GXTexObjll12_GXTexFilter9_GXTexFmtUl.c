// Function: CreateSmallBackTexture__8CGraphicFPvP9_GXTexObjll12_GXTexFilter9_GXTexFmtUl
// Entry: 80016968
// Size: 1608 bytes

void CreateSmallBackTexture__8CGraphicFPvP9_GXTexObjll12_GXTexFilter9_GXTexFmtUl
               (CGraphic *graphic,undefined4 param_2,undefined4 param_3,uint param_4,uint param_5,
               undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 local_1c8;
  undefined4 local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  undefined4 local_1b8;
  undefined4 local_1b4;
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
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  undefined auStack_120 [32];
  Mat4x4 MStack_100;
  Mtx MStack_c0;
  undefined4 local_90;
  uint uStack_8c;
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  SetOrthoEnv__5CUtilFv(&DAT_8032ec70);
  SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
  DisableIndMtx__5CUtilFv(&DAT_8032ec70);
  GXSetNumChans(1);
  GXSetZCompLoc(0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,1,1,7,0);
  GXSetCullMode(0);
  GXSetZMode(0,3,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,4,5,1);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,1,0,7,0);
  GXSetNumTevStages(1);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  GXSetNumTexGens(1);
  GXSetNumTevStages(1);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,3);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,4,5,1);
  GXSetColorUpdate(1);
  GXSetAlphaUpdate(0);
  uVar3 = (int)param_4 / 2;
  uVar2 = (int)param_5 / 2;
  local_1b4 = 0xffffffff;
  GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
            (graphic,graphic->tempBuffer,auStack_120,0,0,0x140,0xe0,0x46000,param_6,6,0);
  uStack_8c = uVar3 ^ 0x80000000;
  uStack_84 = uVar2 ^ 0x80000000;
  local_90 = 0x43300000;
  local_138 = (float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_8032f6e8);
  local_88 = 0x43300000;
  local_12c = FLOAT_8032f6c0;
  local_134 = (float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_8032f6e8);
  local_128 = FLOAT_8032f6c0;
  local_124 = FLOAT_8032f6c0;
  local_130 = FLOAT_8032f6c0;
  GXLoadTexObj(auStack_120,0);
  uVar1 = local_1b4;
  local_1b8 = local_1b4;
  local_150 = local_138;
  local_14c = local_134;
  local_148 = local_130;
  local_144 = local_12c;
  local_140 = local_128;
  local_13c = local_124;
  RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
            (&DAT_8032ec70,&local_144,&local_150,&local_1b8,0,0);
  GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
            (graphic,graphic->tempBuffer,param_3,0x140,0,0x140,0xe0,0,param_6,param_7,0);
  uStack_7c = uVar3 ^ 0x80000000;
  uStack_74 = param_4 ^ 0x80000000;
  uStack_6c = uVar2 ^ 0x80000000;
  local_80 = 0x43300000;
  local_12c = (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_8032f6e8);
  local_78 = 0x43300000;
  local_138 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8032f6e8);
  local_70 = 0x43300000;
  local_134 = (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_8032f6e8);
  local_128 = FLOAT_8032f6c0;
  local_124 = FLOAT_8032f6c0;
  local_130 = FLOAT_8032f6c0;
  GXLoadTexObj(param_3,0);
  local_1bc = uVar1;
  local_168 = local_138;
  local_164 = local_134;
  local_160 = local_130;
  local_15c = local_12c;
  local_158 = local_128;
  local_154 = local_124;
  RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
            (&DAT_8032ec70,&local_15c,&local_168,&local_1bc,0,0);
  GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
            (graphic,graphic->tempBuffer,param_3,0,0xe0,0x140,0xe0,0,param_6,param_7,0);
  uStack_64 = uVar2 ^ 0x80000000;
  uStack_5c = uVar3 ^ 0x80000000;
  uStack_54 = param_5 ^ 0x80000000;
  local_68 = 0x43300000;
  local_128 = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_8032f6e8);
  local_60 = 0x43300000;
  local_138 = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_8032f6e8);
  local_58 = 0x43300000;
  local_12c = FLOAT_8032f6c0;
  local_134 = (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8032f6e8);
  local_124 = FLOAT_8032f6c0;
  local_130 = FLOAT_8032f6c0;
  GXLoadTexObj(param_3,0);
  local_1c0 = uVar1;
  local_180 = local_138;
  local_17c = local_134;
  local_178 = local_130;
  local_174 = local_12c;
  local_170 = local_128;
  local_16c = local_124;
  RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
            (&DAT_8032ec70,&local_174,&local_180,&local_1c0,0,0);
  GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
            (graphic,graphic->tempBuffer,param_3,0x140,0xe0,0x140,0xe0,0,param_6,param_7,0);
  uStack_4c = uVar3 ^ 0x80000000;
  uStack_44 = uVar2 ^ 0x80000000;
  uStack_3c = param_4 ^ 0x80000000;
  uStack_34 = param_5 ^ 0x80000000;
  local_50 = 0x43300000;
  local_12c = (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8032f6e8);
  local_48 = 0x43300000;
  local_128 = (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8032f6e8);
  local_40 = 0x43300000;
  local_138 = (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8032f6e8);
  local_38 = 0x43300000;
  local_134 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8032f6e8);
  local_124 = FLOAT_8032f6c0;
  local_130 = FLOAT_8032f6c0;
  GXLoadTexObj(param_3,0);
  local_1c4 = uVar1;
  local_198 = local_138;
  local_194 = local_134;
  local_190 = local_130;
  local_18c = local_12c;
  local_188 = local_128;
  local_184 = local_124;
  RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
            (&DAT_8032ec70,&local_18c,&local_198,&local_1c4,0,0);
  GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
            (graphic,param_2,param_3,0,0,param_4,param_5,param_8,param_6,param_7,0);
  GXLoadTexObj(auStack_120,0);
  local_12c = FLOAT_8032f6c0;
  local_128 = FLOAT_8032f6c0;
  local_124 = FLOAT_8032f6c0;
  local_138 = FLOAT_8032f6f0;
  local_134 = FLOAT_8032f6f4;
  local_130 = FLOAT_8032f6c0;
  local_1c8 = uVar1;
  local_1b0 = FLOAT_8032f6f0;
  local_1ac = FLOAT_8032f6f4;
  local_1a8 = FLOAT_8032f6c0;
  local_1a4 = FLOAT_8032f6c0;
  local_1a0 = FLOAT_8032f6c0;
  local_19c = FLOAT_8032f6c0;
  RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
            (&DAT_8032ec70,&local_1a4,&local_1b0,&local_1c8,0,0);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_c0);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_100);
  GXLoadPosMtxImm(&MStack_c0,0);
  GXSetProjection(&MStack_100,0);
  return;
}

