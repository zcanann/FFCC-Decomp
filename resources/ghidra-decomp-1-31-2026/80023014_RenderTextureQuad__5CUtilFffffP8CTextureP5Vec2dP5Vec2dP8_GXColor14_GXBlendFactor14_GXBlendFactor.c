// Function: RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
// Entry: 80023014
// Size: 1452 bytes

/* WARNING: Removing unreachable block (ram,0x800235a4) */
/* WARNING: Removing unreachable block (ram,0x8002359c) */
/* WARNING: Removing unreachable block (ram,0x80023594) */
/* WARNING: Removing unreachable block (ram,0x8002358c) */
/* WARNING: Removing unreachable block (ram,0x8002303c) */
/* WARNING: Removing unreachable block (ram,0x80023034) */
/* WARNING: Removing unreachable block (ram,0x8002302c) */
/* WARNING: Removing unreachable block (ram,0x80023024) */

void RenderTextureQuad__5CUtilFffffP8CTextureP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
               (double param_1,double param_2,double param_3,double param_4,CUtil *param_5,
               CTexture *param_6,float *param_7,float *param_8,undefined4 *param_9,
               undefined4 param_10,undefined4 param_11)

{
  int iVar1;
  undefined4 uVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  undefined4 local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
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
  undefined auStack_15c [24];
  Mtx MStack_144;
  Mtx MStack_114;
  Mtx MStack_d4;
  Mat4x4 MStack_a4;
  
  PSMTXIdentity(&MStack_144);
  GXLoadPosMtxImm(&MStack_144,0);
  GXSetCurrentMtx(0);
  C_MTXOrtho(FLOAT_8032f888,FLOAT_8032f8a0,FLOAT_8032f888,FLOAT_8032f8a4,FLOAT_8032f888,
             FLOAT_8032f88c,&MStack_114);
  GXSetProjection(&MStack_114,1);
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
  memset(auStack_15c,0,0x18);
  GXSetIndTexMtx(1,auStack_15c,1);
  GXSetIndTexMtx(2,auStack_15c,1);
  GXSetIndTexMtx(3,auStack_15c,1);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  GXSetVtxAttrFmt(7,0xd,1,4,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  GXLoadTexObj(&param_6->field_0x28,0);
  local_1a8 = 0xffffffff;
  local_1ac = 0xffffffff;
  GXSetChanAmbColor(4,&local_1ac);
  local_1b0 = local_1a8;
  GXSetChanMatColor(4,&local_1b0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp
            (1,param_10,param_11,5);
  iVar1 = param_6->field93_0x60;
  if (iVar1 == 1) {
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (1,0,0,0,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,1);
  }
  else if ((iVar1 == 9) || (iVar1 == 8)) {
    SetPaletteEnv__5CUtilFP8CTexture(param_5,param_6);
  }
  uVar2 = local_1a8;
  local_174 = (float)(param_1 + param_3);
  local_170 = (float)(param_2 + param_4);
  local_168 = (float)param_1;
  local_164 = (float)param_2;
  local_160 = FLOAT_8032f888;
  local_16c = FLOAT_8032f888;
  if (param_9 == (undefined4 *)0x0) {
    local_19c = FLOAT_8032f888;
    local_190 = FLOAT_8032f888;
    if ((param_7 == (float *)0x0) || (param_8 == (float *)0x0)) {
      dVar3 = (double)FLOAT_8032f888;
      dVar5 = (double)FLOAT_8032f88c;
      dVar4 = dVar3;
      dVar6 = dVar5;
    }
    else {
      dVar3 = (double)*param_7;
      dVar4 = (double)param_7[1];
      dVar5 = (double)*param_8;
      dVar6 = (double)param_8[1];
    }
    local_1a4 = local_174;
    local_1a0 = local_170;
    local_198 = local_168;
    local_194 = local_164;
    GXBegin(0x80,7,4);
    DAT_cc008000 = local_198;
    DAT_cc008000 = local_194;
    DAT_cc008000 = local_190;
    DAT_cc008000 = uVar2;
    DAT_cc008000 = (float)dVar3;
    DAT_cc008000 = (float)dVar4;
    DAT_cc008000 = local_1a4;
    DAT_cc008000 = local_194;
    DAT_cc008000 = local_190;
    DAT_cc008000 = uVar2;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = (float)dVar4;
    DAT_cc008000 = local_1a4;
    DAT_cc008000 = local_1a0;
    DAT_cc008000 = local_190;
    DAT_cc008000 = uVar2;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = (float)dVar6;
    DAT_cc008000 = local_198;
    DAT_cc008000 = local_1a0;
    DAT_cc008000 = local_190;
    DAT_cc008000 = uVar2;
    DAT_cc008000 = (float)dVar3;
    DAT_cc008000 = (float)dVar6;
  }
  else {
    uVar2 = *param_9;
    local_184 = FLOAT_8032f888;
    local_178 = FLOAT_8032f888;
    if ((param_7 == (float *)0x0) || (param_8 == (float *)0x0)) {
      dVar5 = (double)FLOAT_8032f888;
      dVar3 = (double)FLOAT_8032f88c;
      dVar4 = dVar3;
      dVar6 = dVar5;
    }
    else {
      dVar6 = (double)*param_7;
      dVar5 = (double)param_7[1];
      dVar4 = (double)*param_8;
      dVar3 = (double)param_8[1];
    }
    local_18c = local_174;
    local_188 = local_170;
    local_180 = local_168;
    local_17c = local_164;
    GXBegin(0x80,7,4);
    DAT_cc008000 = local_180;
    DAT_cc008000 = local_17c;
    DAT_cc008000 = local_178;
    DAT_cc008000 = uVar2;
    DAT_cc008000 = (float)dVar6;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_18c;
    DAT_cc008000 = local_17c;
    DAT_cc008000 = local_178;
    DAT_cc008000 = uVar2;
    DAT_cc008000 = (float)dVar4;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_18c;
    DAT_cc008000 = local_188;
    DAT_cc008000 = local_178;
    DAT_cc008000 = uVar2;
    DAT_cc008000 = (float)dVar4;
    DAT_cc008000 = (float)dVar3;
    DAT_cc008000 = local_180;
    DAT_cc008000 = local_188;
    DAT_cc008000 = local_178;
    DAT_cc008000 = uVar2;
    DAT_cc008000 = (float)dVar6;
    DAT_cc008000 = (float)dVar3;
  }
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_d4);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_a4);
  GXLoadPosMtxImm(&MStack_d4,0);
  GXSetProjection(&MStack_a4,0);
  iVar1 = GXGetTexObjFmt(&param_6->field_0x28);
  if (iVar1 == 1) {
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  }
  return;
}

