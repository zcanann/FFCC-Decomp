// Function: pppRenderBlurChara
// Entry: 800ddaf8
// Size: 1460 bytes

/* WARNING: Removing unreachable block (ram,0x800de090) */
/* WARNING: Removing unreachable block (ram,0x800ddb08) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderBlurChara(pppBlurChara *pppBlurChara,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  undefined4 local_200;
  undefined4 local_1fc;
  undefined auStack_1f8 [4];
  undefined auStack_1f4 [4];
  undefined auStack_1f0 [4];
  undefined4 local_1ec;
  undefined4 local_1e8;
  float local_1e4;
  float local_1e0;
  float local_1dc;
  float local_1d8;
  float local_1d4;
  float local_1d0;
  Vec4d local_1cc;
  Vec4d VStack_1bc;
  Vec local_1ac;
  Vec local_1a0;
  Vec VStack_194;
  Vec local_188;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  undefined auStack_164 [24];
  undefined auStack_14c [28];
  undefined auStack_130 [32];
  Mat4x4 MStack_110;
  Mat4x4 local_d0;
  Mtx MStack_90;
  Mtx MStack_60;
  
  iVar5 = 0;
  iVar2 = param_3->m_serializedDataOffsets[2];
  iVar1 = param_3->m_serializedDataOffsets[1];
  if (*(char *)((int)&param_2->m_dataValIndex + 1) == '\x01') {
    local_1ec = 0;
    if (param_2->m_initWOrk == 0xffff) {
      return;
    }
    iVar5 = GetTexture__8CMapMeshFP12CMaterialSetRi
                      (pppEnvStPtr->m_mapMeshPtr[param_2->m_initWOrk],pppEnvStPtr->m_materialSetPtr,
                       &local_1ec);
  }
  else {
    uVar3 = (uint)*(byte *)((int)&param_2->m_dataValIndex + 2);
    CreateSmallBackTexture__8CGraphicFPvP9_GXTexObjll12_GXTexFilter9_GXTexFmtUl
              (&Graphic,DAT_80238030,auStack_130,0x140 / uVar3,0xe0 / uVar3,1,6,0);
  }
  pppInitBlendMode__Fv();
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
            (FLOAT_80331030,(pppCVector *)(&pppBlurChara->field_0x88 + iVar1),(pppFMATRIX *)0x0,
             param_2->m_payload[5],0,0,0,1,1,0);
  iVar4 = *(int *)(&pppBlurChara->field_0x84 + iVar2);
  PSMTXIdentity(&MStack_60);
  local_188.x = (float)CameraPcs._224_4_;
  local_188.z = (float)CameraPcs._232_4_;
  local_1ac.x = (float)CameraPcs._212_4_;
  local_1ac.z = (float)CameraPcs._220_4_;
  local_188.y = FLOAT_80331030;
  local_1ac.y = FLOAT_80331030;
  PSVECSubtract(&local_1ac,&local_188,&VStack_194);
  VStack_194.y = FLOAT_80331030;
  GXGetProjectionv(auStack_14c);
  GXGetViewportv(auStack_164);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_90);
  PSMTXIdentity(&MStack_60);
  local_1a0.x = *(float *)(iVar4 + 0x15c);
  local_1a0.y = *(float *)(iVar4 + 0x160);
  local_1a0.z = *(float *)(iVar4 + 0x164);
  GXProject((double)(local_188.x + local_1a0.x),(double)FLOAT_80331030,
            (double)(local_188.z + local_1a0.z),&MStack_90,auStack_14c,auStack_164,auStack_1f0,
            auStack_1f4,auStack_1f8);
  BeginQuadEnv__5CUtilFv(&DAT_8032ec70);
  GXSetNumTevStages(2);
  GXSetNumTexGens(2);
  SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  GXSetTexCoordGen2(1,1,4,0x3c,0,0x7d);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (1,0,0,0,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,1,5,7);
  local_1fc = local_1e8;
  GXSetChanMatColor(4,&local_1fc);
  GXSetChanCtrl(4,0,0,1,0,0,2);
  local_1e8 = *(undefined4 *)(&pppBlurChara->field_0x88 + iVar1);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,1);
  GXLoadTexObj(*(undefined4 *)(&pppBlurChara->field_0x88 + iVar2),0);
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (0,0xf,10,8,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (0,7,5,4,7);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,1,1,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
  if (*(char *)((int)&param_2->m_dataValIndex + 1) == '\x01') {
    GXLoadTexObj(iVar5 + 0x28,1);
  }
  else {
    GXLoadTexObj(auStack_130,1);
  }
  _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
            (1,0xf,8,1,0xf);
  _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,0,1,0);
  _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
            (1,7,5,0,7);
  _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1,0,0,0,1,0);
  PSMTXIdentity(&MStack_60);
  GXLoadPosMtxImm(&MStack_60,0);
  GXSetCurrentMtx(0);
  PSMTX44Identity(&local_d0);
  local_d0.value[0][0] = FLOAT_80331034;
  local_d0.value[1][1] = FLOAT_80331038;
  local_d0.value[2][2] = FLOAT_8033103c;
  local_d0.value[0][3] = FLOAT_80331040;
  local_d0.value[1][3] = FLOAT_8033103c;
  local_d0.value[2][3] = FLOAT_80331030;
  GXSetProjection(&local_d0,1);
  GXSetZMode(1,3,0);
  dVar6 = (double)PSVECDistance(&local_188,&local_1a0);
  dVar6 = (double)(float)(dVar6 - (double)param_2->m_stepValue);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_110);
  local_1cc.x = FLOAT_80331030;
  local_1cc.y = FLOAT_80331030;
  local_1cc.z = (float)-dVar6;
  local_1cc.w = FLOAT_8033103c;
  MTX44MultVec4__5CMathFPA4_fP5Vec4dP5Vec4d(&Math,&MStack_110,&local_1cc,&VStack_1bc);
  if (VStack_1bc.w != FLOAT_80331030) {
    VStack_1bc.z = VStack_1bc.z / VStack_1bc.w;
  }
  local_1e0 = (float)param_2->m_arg3;
  local_1d4 = -local_1e0;
  local_1d8 = -(FLOAT_80331044 * local_1e0);
  local_1e4 = FLOAT_80331048 + FLOAT_80331044 * local_1e0;
  local_168 = VStack_1bc.z;
  local_1e0 = FLOAT_8033104c + local_1e0;
  local_174 = VStack_1bc.z;
  local_200 = local_1e8;
  local_1dc = VStack_1bc.z;
  local_1d0 = VStack_1bc.z;
  local_17c = local_1e4;
  local_178 = local_1e0;
  local_170 = local_1d8;
  local_16c = local_1d4;
  RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
            (&DAT_8032ec70,&local_1d8,&local_1e4,&local_200,0,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
  pppInitBlendMode__Fv();
  return;
}

