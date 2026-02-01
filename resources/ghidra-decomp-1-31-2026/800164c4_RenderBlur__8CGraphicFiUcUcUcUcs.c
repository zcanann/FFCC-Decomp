// Function: RenderBlur__8CGraphicFiUcUcUcUcs
// Entry: 800164c4
// Size: 1164 bytes

void RenderBlur__8CGraphicFiUcUcUcUcs
               (CGraphic *graphic,undefined4 param_2,char param_3,undefined4 param_4,byte param_5,
               undefined param_6,short param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  undefined auStack_9c [32];
  Mtx MStack_7c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  
  DisableIndMtx__5CUtilFv(&DAT_8032ec70);
  SetOrthoEnv__5CUtilFv(&DAT_8032ec70);
  SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
  GXSetZCompLoc(0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,1,1,7,0);
  GXSetCullMode(0);
  GXSetColorUpdate(1);
  GXSetAlphaUpdate(0);
  GXSetZMode(0,3,0);
  local_e8 = CONCAT22(0x8080,CONCAT11(0x80,param_6));
  local_ec = local_e8;
  GXSetChanAmbColor(4,&local_ec);
  local_f0 = local_e8;
  GXSetChanMatColor(4,&local_f0);
  SetOrthoEnv__5CUtilFv(&DAT_8032ec70);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  GXSetTevDirect(0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (0,0xf,0xf,0xf,8);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (0,7,7,7,5);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0);
  GXSetNumTevStages(1);
  GXSetNumTexGens(1);
  iVar1 = (int)param_7;
  iVar3 = 0;
  for (iVar2 = 0; iVar2 < (int)(uint)(byte)graphic->field_0x735e; iVar2 = iVar2 + 1) {
    GXInitTexObj(auStack_9c,*(int *)&graphic->field_0x71ec + iVar3,0x140,0xe0,6,0,0,0);
    dVar4 = (double)FLOAT_8032f6c0;
    GXInitTexObjLOD(dVar4,dVar4,dVar4,auStack_9c,1,1,0,0,0);
    GXLoadTexObj(auStack_9c,0);
    if (param_3 == '\x01') {
      local_a8 = FLOAT_8032f6c0;
      local_a4 = FLOAT_8032f6c0;
      local_a0 = FLOAT_8032f6c0;
      local_b4 = FLOAT_8032f6c8;
      local_b0 = FLOAT_8032f6cc;
      local_ac = FLOAT_8032f6c0;
      local_f4 = local_e8;
      local_cc = FLOAT_8032f6c8;
      local_c8 = FLOAT_8032f6cc;
      local_c4 = FLOAT_8032f6c0;
      local_c0 = FLOAT_8032f6c0;
      local_bc = FLOAT_8032f6c0;
      local_b8 = FLOAT_8032f6c0;
      RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                (&DAT_8032ec70,&local_c0,&local_cc,&local_f4,0,0);
    }
    else if (param_3 == '\0') {
      uStack_44 = -iVar1 ^ 0x80000000;
      uStack_34 = iVar1 + 0x280U ^ 0x80000000;
      uStack_2c = iVar1 + 0x1c0U ^ 0x80000000;
      local_48 = 0x43300000;
      local_d8 = (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8032f6e8);
      local_40 = 0x43300000;
      local_d4 = (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8032f6e8);
      local_a0 = FLOAT_8032f6c0;
      local_ac = FLOAT_8032f6c0;
      local_38 = 0x43300000;
      local_e4 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8032f6e8);
      local_30 = 0x43300000;
      local_e0 = (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8032f6e8);
      local_f8 = local_e8;
      local_dc = FLOAT_8032f6c0;
      local_d0 = FLOAT_8032f6c0;
      local_b4 = local_e4;
      local_b0 = local_e0;
      local_a8 = local_d8;
      local_a4 = local_d4;
      uStack_3c = uStack_44;
      RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                (&DAT_8032ec70,&local_d8,&local_e4,&local_f8,0,0);
    }
    iVar3 = iVar3 + 0x46000;
  }
  GXSetZMode(1,3,0);
  PSMTXIdentity(&MStack_7c);
  GXLoadPosMtxImm(0x802687ac,0);
  GXSetCurrentMtx(0);
  GXSetProjection(0x8026883c,0);
  GXSetAlphaUpdate(1);
  if ((byte)graphic->field_0x735c < param_5) {
    graphic->field_0x735c = graphic->field_0x735c + 1;
  }
  else if (System.m_scenegraphStepMode != 2) {
    CreateSmallBackTexture__8CGraphicFPvP9_GXTexObjll12_GXTexFilter9_GXTexFmtUl
              (graphic,*(undefined4 *)&graphic->field_0x71ec,auStack_9c,0x140,0xe0,1,6,
               (uint)(byte)graphic->field_0x735d * 0x46000);
    graphic->field_0x735c = 0;
    graphic->field_0x735e = graphic->field_0x735e + '\x01';
    if (2 < (byte)graphic->field_0x735e) {
      graphic->field_0x735e = 2;
    }
    graphic->field_0x735d = graphic->field_0x735d + '\x01';
    if (1 < (byte)graphic->field_0x735d) {
      graphic->field_0x735d = 0;
    }
  }
  return;
}

