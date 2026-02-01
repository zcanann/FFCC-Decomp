// Function: ClearZBufferRect__5CUtilFffff
// Entry: 80023ed0
// Size: 956 bytes

/* WARNING: Removing unreachable block (ram,0x80024274) */
/* WARNING: Removing unreachable block (ram,0x8002426c) */
/* WARNING: Removing unreachable block (ram,0x80024264) */
/* WARNING: Removing unreachable block (ram,0x8002425c) */
/* WARNING: Removing unreachable block (ram,0x80023ef8) */
/* WARNING: Removing unreachable block (ram,0x80023ef0) */
/* WARNING: Removing unreachable block (ram,0x80023ee8) */
/* WARNING: Removing unreachable block (ram,0x80023ee0) */

void ClearZBufferRect__5CUtilFffff(double param_1,double param_2,double param_3,double param_4)

{
  undefined4 uVar1;
  double in_f28;
  double in_f29;
  double in_f30;
  double in_f31;
  double in_ps28_1;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
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
  undefined auStack_138 [24];
  Mtx MStack_120;
  Mtx MStack_f0;
  Mtx MStack_b0;
  Mat4x4 MStack_80;
  float local_38;
  float fStack_34;
  float local_28;
  float fStack_24;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  local_28 = (float)in_f29;
  fStack_24 = (float)in_ps29_1;
  local_38 = (float)in_f28;
  fStack_34 = (float)in_ps28_1;
  PSMTXIdentity(&MStack_120);
  GXLoadPosMtxImm(&MStack_120,0);
  GXSetCurrentMtx(0);
  C_MTXOrtho(FLOAT_8032f888,FLOAT_8032f8a0,FLOAT_8032f888,FLOAT_8032f8a4,FLOAT_8032f888,
             FLOAT_8032f88c,&MStack_f0);
  GXSetProjection(&MStack_f0,1);
  GXSetCullMode(0);
  GXSetNumTexGens(1);
  GXSetNumChans(1);
  GXSetNumTevStages(1);
  GXSetZMode(0,3,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,5);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (0,0,1,2,3);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  GXSetChanCtrl(4,1,0,1,0,0,2);
  GXSetTevDirect(0);
  GXSetNumIndStages(0);
  memset(auStack_138,0,0x18);
  GXSetIndTexMtx(1,auStack_138,1);
  GXSetIndTexMtx(2,auStack_138,1);
  GXSetIndTexMtx(3,auStack_138,1);
  GXSetZMode(1,7,1);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  GXSetNumTexGens(0);
  local_16c = 0xffffffff;
  local_170 = 0xffffffff;
  GXSetChanAmbColor(4,&local_170);
  local_174 = local_16c;
  GXSetChanMatColor(4,&local_174);
  GXSetChanCtrl(4,1,0,1,0,0,2);
  local_150 = (float)(param_1 + param_3);
  local_14c = (float)(param_2 + param_4);
  local_144 = (float)param_1;
  local_140 = (float)param_2;
  local_13c = FLOAT_8032f8a8;
  local_148 = FLOAT_8032f8a8;
  GXSetColorUpdate(0);
  GXSetAlphaUpdate(0);
  uVar1 = local_16c;
  local_168 = local_150;
  local_164 = local_14c;
  local_160 = local_148;
  local_15c = local_144;
  local_158 = local_140;
  local_154 = local_13c;
  GXBegin(0x80,7,4);
  DAT_cc008000 = local_15c;
  DAT_cc008000 = local_158;
  DAT_cc008000 = local_154;
  DAT_cc008000 = uVar1;
  DAT_cc008000 = local_168;
  DAT_cc008000 = local_158;
  DAT_cc008000 = local_154;
  DAT_cc008000 = uVar1;
  DAT_cc008000 = local_168;
  DAT_cc008000 = local_164;
  DAT_cc008000 = local_154;
  DAT_cc008000 = uVar1;
  DAT_cc008000 = local_15c;
  DAT_cc008000 = local_164;
  DAT_cc008000 = local_154;
  DAT_cc008000 = uVar1;
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_b0);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_80);
  GXLoadPosMtxImm(&MStack_b0,0);
  GXSetProjection(&MStack_80,0);
  GXSetColorUpdate(1);
  GXSetZMode(0,3,0);
  return;
}

