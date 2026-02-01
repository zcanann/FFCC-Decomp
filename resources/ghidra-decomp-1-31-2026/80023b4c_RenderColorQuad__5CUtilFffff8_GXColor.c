// Function: RenderColorQuad__5CUtilFffff8_GXColor
// Entry: 80023b4c
// Size: 900 bytes

/* WARNING: Removing unreachable block (ram,0x80023eb4) */
/* WARNING: Removing unreachable block (ram,0x80023eac) */
/* WARNING: Removing unreachable block (ram,0x80023ea4) */
/* WARNING: Removing unreachable block (ram,0x80023e9c) */
/* WARNING: Removing unreachable block (ram,0x80023b74) */
/* WARNING: Removing unreachable block (ram,0x80023b6c) */
/* WARNING: Removing unreachable block (ram,0x80023b64) */
/* WARNING: Removing unreachable block (ram,0x80023b5c) */

void RenderColorQuad__5CUtilFffff8_GXColor
               (double param_1,double param_2,double param_3,double param_4,undefined4 param_5,
               undefined4 *param_6)

{
  undefined4 uVar1;
  undefined4 local_184;
  undefined4 local_180;
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
  undefined auStack_14c [24];
  Mtx MStack_134;
  Mtx MStack_104;
  Mtx MStack_c4;
  Mat4x4 MStack_94;
  
  PSMTXIdentity(&MStack_134);
  GXLoadPosMtxImm(&MStack_134,0);
  GXSetCurrentMtx(0);
  C_MTXOrtho(FLOAT_8032f888,FLOAT_8032f8a0,FLOAT_8032f888,FLOAT_8032f8a4,FLOAT_8032f888,
             FLOAT_8032f88c,&MStack_104);
  GXSetProjection(&MStack_104,1);
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
  memset(auStack_14c,0,0x18);
  GXSetIndTexMtx(1,auStack_14c,1);
  GXSetIndTexMtx(2,auStack_14c,1);
  GXSetIndTexMtx(3,auStack_14c,1);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  GXSetNumTexGens(0);
  local_180 = 0xffffffff;
  local_184 = 0xffffffff;
  GXSetChanAmbColor(4,&local_184);
  GXSetChanCtrl(4,1,0,1,0,0,2);
  GXSetNumChans(1);
  local_17c = (float)(param_1 + param_3);
  local_178 = (float)(param_2 + param_4);
  local_170 = (float)param_1;
  uVar1 = *param_6;
  local_16c = (float)param_2;
  local_150 = FLOAT_8032f888;
  local_15c = FLOAT_8032f888;
  local_174 = FLOAT_8032f888;
  local_168 = FLOAT_8032f888;
  local_164 = local_17c;
  local_160 = local_178;
  local_158 = local_170;
  local_154 = local_16c;
  GXBegin(0x80,7,4);
  DAT_cc008000 = local_170;
  DAT_cc008000 = local_16c;
  DAT_cc008000 = local_168;
  DAT_cc008000 = uVar1;
  DAT_cc008000 = local_17c;
  DAT_cc008000 = local_16c;
  DAT_cc008000 = local_168;
  DAT_cc008000 = uVar1;
  DAT_cc008000 = local_17c;
  DAT_cc008000 = local_178;
  DAT_cc008000 = local_168;
  DAT_cc008000 = uVar1;
  DAT_cc008000 = local_170;
  DAT_cc008000 = local_178;
  DAT_cc008000 = local_168;
  DAT_cc008000 = uVar1;
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_c4);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_94);
  GXLoadPosMtxImm(&MStack_c4,0);
  GXSetProjection(&MStack_94,0);
  return;
}

