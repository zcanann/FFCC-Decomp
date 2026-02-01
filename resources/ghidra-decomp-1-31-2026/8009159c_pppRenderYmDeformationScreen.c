// Function: pppRenderYmDeformationScreen
// Entry: 8009159c
// Size: 1604 bytes

/* WARNING: Removing unreachable block (ram,0x80091bbc) */
/* WARNING: Removing unreachable block (ram,0x80091bb4) */
/* WARNING: Removing unreachable block (ram,0x80091bac) */
/* WARNING: Removing unreachable block (ram,0x800915bc) */
/* WARNING: Removing unreachable block (ram,0x800915b4) */
/* WARNING: Removing unreachable block (ram,0x800915ac) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderYmDeformationScreen
               (pppYmDeformationScreen *pppYmDeformationScreen,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  float *pfVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  pppCVector local_178;
  undefined4 local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  undefined auStack_158 [32];
  float local_138;
  float local_134;
  float local_128;
  float local_124;
  Mat4x4 local_108;
  undefined auStack_c8 [64];
  Mtx MStack_88;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  
  local_174 = 0;
  pfVar2 = (float *)((int)(&pppYmDeformationScreen->field0_0x0 + 2) +
                    param_3->m_serializedDataOffsets[2]);
  if (param_2->m_dataValIndex != 0xffff) {
    iVar1 = GetTexture__8CMapMeshFP12CMaterialSetRi
                      (pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex],
                       pppEnvStPtr->m_materialSetPtr,&local_174);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,1,5,1);
    GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    GXSetTexCoordGen2(1,1,5,0x3c,0,0x7d);
    builtin_memcpy(local_178.m_rgba,"@@@@",4);
    pppSetBlendMode__FUc(0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (FLOAT_80330670,&local_178,(pppFMATRIX *)0x0,0,0,0,0,1,1,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    GXSetNumTexGens(2);
    GXSetNumChans(1);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
              (1,0,1,2,0);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,1);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (0,0xf,8,9,0xf);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (0,7,7,7,4);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,0,1,0xff);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(1,0);
    BeginQuadEnv__5CUtilFv(&DAT_8032ec70);
    SetVtxFmt_POS_CLR_TEX0_TEX1__5CUtilFv(&DAT_8032ec70);
    GXSetNumTevStages(1);
    GXSetNumTexGens(2);
    GXSetNumChans(1);
    PSMTXIdentity(&MStack_88);
    GXLoadPosMtxImm(&MStack_88,0);
    GXSetCurrentMtx(0);
    PSMTX44Identity(&local_108);
    local_108.value[0][0] = FLOAT_80330674;
    local_108.value[1][1] = FLOAT_80330678;
    local_108.value[2][2] = FLOAT_8033067c;
    local_108.value[0][3] = FLOAT_80330680;
    local_108.value[1][3] = FLOAT_8033067c;
    local_108.value[2][3] = FLOAT_80330670;
    GXSetProjection(&local_108,1);
    GXSetZMode(1,3,0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,3);
    GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    dVar5 = (double)*pfVar2;
    GXSetNumIndStages(1);
    GXSetIndTexOrder(0,0,1);
    GXSetTevIndWarp(0,0,1,0,1);
    GXSetIndTexCoordScale(0,0,0);
    if ((*(short *)(pfVar2 + 1) == 0) || (*(short *)(pfVar2 + 1) == 0x168)) {
      *(undefined2 *)(pfVar2 + 1) = 1;
    }
    local_58 = 0x43300000;
    uStack_54 = (int)*(short *)(pfVar2 + 1) ^ 0x80000000;
    PSMTXRotRad(FLOAT_80330684 * (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80330698),
                &local_138,0x7a);
    local_160 = pfVar2[2];
    local_170 = local_138 * local_160;
    local_16c = local_134 * local_160;
    local_164 = local_128 * local_160;
    local_160 = local_124 * local_160;
    local_168 = FLOAT_80330670;
    local_15c = FLOAT_80330670;
    GXSetIndTexMtx(1,&local_170,1);
    uStack_4c = 0x280 / *(uint *)(iVar1 + 100);
    uStack_44 = 0x1c0 / *(uint *)(iVar1 + 0x68);
    local_50 = 0x43300000;
    dVar4 = (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_803306a0);
    local_48 = 0x43300000;
    dVar3 = (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_803306a0);
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,DAT_80238030,auStack_158,0,0,0x280,0xe0,0,1,6,0);
    GXLoadTexObj(auStack_158,0);
    GXLoadTexObj(iVar1 + 0x28,1);
    GXBegin(0x80,7,4);
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_178.m_rgba;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330688;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_178.m_rgba;
    DAT_cc008000 = FLOAT_8033067c;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = (float)dVar4;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330688;
    DAT_cc008000 = FLOAT_8033068c;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_178.m_rgba;
    DAT_cc008000 = FLOAT_8033067c;
    DAT_cc008000 = FLOAT_8033067c;
    DAT_cc008000 = (float)dVar4;
    DAT_cc008000 = (float)dVar3;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_8033068c;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_178.m_rgba;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_8033067c;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = (float)dVar3;
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,DAT_80238030,auStack_158,0,0xe0,0x280,0xe0,0,1,6,0);
    GXLoadTexObj(auStack_158,0);
    dVar5 = (double)*pfVar2;
    GXBegin(0x80,7,4);
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_8033068c;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_178.m_rgba;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330688;
    DAT_cc008000 = FLOAT_8033068c;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_178.m_rgba;
    DAT_cc008000 = FLOAT_8033067c;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = (float)dVar4;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330688;
    DAT_cc008000 = FLOAT_80330690;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_178.m_rgba;
    DAT_cc008000 = FLOAT_8033067c;
    DAT_cc008000 = FLOAT_8033067c;
    DAT_cc008000 = (float)dVar4;
    DAT_cc008000 = (float)dVar3;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_80330690;
    DAT_cc008000 = (float)dVar5;
    DAT_cc008000 = local_178.m_rgba;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = FLOAT_8033067c;
    DAT_cc008000 = FLOAT_80330670;
    DAT_cc008000 = (float)dVar3;
    EndQuadEnv__5CUtilFv(&DAT_8032ec70);
    DisableIndWarp__F13_GXTevStageID16_GXIndTexStageID(1,0);
    GXSetProjection(auStack_c8,0);
    pppInitBlendMode__Fv();
  }
  return;
}

