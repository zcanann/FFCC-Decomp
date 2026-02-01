// Function: pppRenderMiasma
// Entry: 80109b6c
// Size: 5604 bytes

/* WARNING: Removing unreachable block (ram,0x8010b134) */
/* WARNING: Removing unreachable block (ram,0x8010b12c) */
/* WARNING: Removing unreachable block (ram,0x8010b124) */
/* WARNING: Removing unreachable block (ram,0x80109b8c) */
/* WARNING: Removing unreachable block (ram,0x80109b84) */
/* WARNING: Removing unreachable block (ram,0x80109b7c) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderMiasma(pppMiasma *pppMiasma,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  int iVar2;
  double dVar3;
  uint8_t uVar4;
  float fVar5;
  float fVar6;
  int32_t *piVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int iVar12;
  ushort uVar13;
  short *psVar14;
  uint uVar15;
  pppModelSt *pppModelSt;
  bool bVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  undefined4 local_2b8;
  undefined4 local_2b4;
  undefined4 local_2b0;
  undefined4 local_2ac;
  undefined4 local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  undefined4 local_29c;
  uint8_t local_298 [4];
  undefined4 local_294;
  undefined4 local_290;
  uint8_t local_28c [4];
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_27c;
  pppCVector local_278;
  float local_274;
  float local_270;
  float local_26c;
  float local_268;
  float local_264;
  float local_260;
  float local_25c;
  float local_258;
  float local_254;
  float local_250;
  float local_24c;
  float local_248;
  Vec local_244;
  Vec local_238;
  float local_22c;
  float local_228;
  float local_224;
  float local_220;
  float local_21c;
  float local_218;
  undefined auStack_214 [32];
  undefined auStack_1f4 [32];
  undefined auStack_1d4 [32];
  Mtx MStack_1b4;
  Mtx MStack_184;
  Mtx MStack_154;
  Mtx MStack_124;
  Mat4x4 MStack_f4;
  longlong local_b0;
  longlong local_a8;
  longlong local_a0;
  undefined8 local_98;
  undefined4 local_90;
  CGraphic *local_8c;
  CGraphic *local_88;
  CGraphic *local_84;
  
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x31);
  piVar7 = param_3->m_serializedDataOffsets;
  iVar12 = piVar7[1];
  iVar8 = piVar7[3];
  local_280 = 0;
  psVar14 = (short *)((int)(&pppMiasma->field0_0x0 + 2) + piVar7[2]);
  pppModelSt = (pppModelSt *)pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
  GetTexture__8CMapMeshFP12CMaterialSetRi
            ((CMapMesh *)pppModelSt,pppEnvStPtr->m_materialSetPtr,&local_280);
  if (param_2->m_payload[0x1e] == 0xff) {
    param_2->m_payload[0x1e] = 0xfe;
  }
  local_b0 = (longlong)(int)FLOAT_80331928;
  local_a8 = (longlong)(int)FLOAT_8033192c;
  local_284 = *(undefined4 *)(&pppMiasma->field_0x88 + iVar12);
  local_27c = CONCAT31(CONCAT21(CONCAT11((char)(*psVar14 >> 7),(char)(psVar14[1] >> 7)),
                                (char)(psVar14[2] >> 7)),(char)(psVar14[3] >> 7));
  iVar12 = GXGetTexBufferSize((int)FLOAT_80331928,(int)FLOAT_8033192c,6,0,0);
  local_a0 = (longlong)(int)FLOAT_80331928;
  local_98 = (double)(longlong)(int)FLOAT_8033192c;
  iVar9 = GXGetTexBufferSize((int)FLOAT_80331928,(int)FLOAT_8033192c,0x28,0,0);
  local_244.x = (pppMngStPtr->m_matrix).value[0][3];
  local_244.y = (pppMngStPtr->m_matrix).value[1][3];
  local_244.z = (pppMngStPtr->m_matrix).value[2][3];
  if (Game.game.m_currentSceneId == 7) {
    local_238.x = ppvCameraMatrix0.value[0][3];
    local_238.y = ppvCameraMatrix0.value[1][3];
    local_238.z = ppvCameraMatrix0.value[2][3];
    fVar6 = FLOAT_80331930;
    for (uVar13 = 0; uVar13 < (ushort)(pppModelSt->m_mapMesh).field0_0x0; uVar13 = uVar13 + 1) {
      fVar5 = *(float *)((pppModelSt->m_mapMesh).field14_0x2c + (uint)uVar13 * 0xc);
      if (fVar6 < fVar5) {
        fVar6 = fVar5;
      }
    }
  }
  else {
    local_238.x = (float)CameraPcs._224_4_;
    local_238.y = (float)CameraPcs._228_4_;
    local_238.z = (float)CameraPcs._232_4_;
    fVar6 = FLOAT_80331934;
  }
  fVar6 = fVar6 * *(float *)((int)(&pppMiasma->field0_0x0 + 2) + iVar8);
  dVar18 = (double)fVar6;
  if (Game.game.m_currentSceneId != 7) {
    Game.game.unkFloat_0xca10 = fVar6;
  }
  dVar17 = (double)PSVECDistance(&local_238,&local_244);
  bVar16 = (double)(float)((double)FLOAT_80331938 + dVar18) <= dVar17;
  iVar8 = (int)FLOAT_8033192c;
  local_98 = (double)(longlong)iVar8;
  uVar15 = 0;
  iVar1 = (int)FLOAT_80331928;
  local_a0 = (longlong)iVar1;
  local_90 = __cvt_fp2unsigned();
  uVar10 = __cvt_fp2unsigned((double)FLOAT_80331928);
  dVar17 = (double)FLOAT_8033192c;
  local_8c = &Graphic;
  local_88 = &Graphic;
  local_84 = &Graphic;
  dVar18 = DOUBLE_80331948;
  do {
    local_98 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
    dVar3 = (double)(float)(local_98 - dVar18) * dVar17;
    dVar19 = (double)(float)dVar3;
    iVar2 = (int)dVar3;
    local_a0 = (longlong)iVar2;
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,DAT_80238030,auStack_1d4,0,iVar2,iVar1,iVar8,0,1,6,0);
    uVar11 = __cvt_fp2unsigned(dVar19);
    GXSetScissor(0,uVar11,uVar10,local_90);
    if (bVar16) {
      local_278.m_rgba[0] = '\0';
      local_278.m_rgba[1] = '\0';
      local_278.m_rgba[2] = '\0';
    }
    else {
      local_278.m_rgba[0] = 0xff;
      local_278.m_rgba[1] = 0xff;
      local_278.m_rgba[2] = 0xff;
    }
    local_278.m_rgba[0] = SUB31(local_278.m_rgba._0_3_,2);
    local_278.m_rgba[1] = SUB31(local_278.m_rgba._0_3_,1);
    local_278.m_rgba[2] = (uint8_t)local_278.m_rgba._0_3_;
    local_278.m_rgba[3] = 0xff;
    local_28c[0] = local_278.m_rgba[0];
    local_28c[1] = local_278.m_rgba[1];
    local_28c[2] = local_278.m_rgba[2];
    local_28c[3] = local_278.m_rgba[3];
    RenderColorQuad__5CUtilFffff8_GXColor
              ((double)FLOAT_8033193c,dVar19,(double)FLOAT_80331928,(double)FLOAT_8033192c,
               &DAT_8032ec70,local_28c);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              (FLOAT_8033193c,&local_278,(pppFMATRIX *)&pppMiasma->field_0x40,0,0,1,0,1,1,1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    GXSetChanCtrl(4,1,0,1,0,0,2);
    GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
    GXSetTexCoordGen2(1,1,5,0x3c,0,0x7d);
    GXSetTexCoordGen2(2,1,6,0x3c,0,0x7d);
    GXClearVtxDesc();
    GXSetVtxDesc(9,3);
    GXSetVtxDesc(10,3);
    GXSetVtxDesc(0xb,3);
    GXSetVtxDesc(0xd,3);
    *(undefined *)(pppModelSt->m_mapMesh).field18_0x3c = 0xff;
    *(undefined *)((pppModelSt->m_mapMesh).field18_0x3c + 1) = 0xff;
    *(undefined *)((pppModelSt->m_mapMesh).field18_0x3c + 2) = 0xff;
    *(undefined *)((pppModelSt->m_mapMesh).field18_0x3c + 3) = 0xff;
    local_290 = *(undefined4 *)(pppModelSt->m_mapMesh).field18_0x3c;
    GXSetChanAmbColor(4,&local_290);
    local_294 = *(undefined4 *)(pppModelSt->m_mapMesh).field18_0x3c;
    GXSetChanMatColor(4,&local_294);
    GXSetChanCtrl(4,1,0,1,0,0,2);
    GXLoadPosMtxImm(&pppMiasma->field_0x40,0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_f4);
    GXSetProjection(&MStack_f4,0);
    PSMTXScale(FLOAT_80331940,FLOAT_80331940,FLOAT_80331940,&MStack_154);
    PSMTXConcat(&MStack_154,&(pppMiasma->field0_0x0).m_localMatrix,&MStack_124);
    PSMTXConcat(&ppvWorldMatrix,&MStack_124,(Mtx *)&pppMiasma->field_0x40);
    GXLoadPosMtxImm(&pppMiasma->field_0x40,0);
    GXSetTevDirect(0);
    pppInitBlendMode__Fv();
    pppSetBlendMode__FUc(1);
    GXSetCullMode(1);
    GXSetZMode(1,3,0);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (0,0xf,0xf,0xf,0xc);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,2,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (0,7,7,7,6);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,2,1,0)
    ;
    if (bVar16) {
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x32);
      pppDrawMesh__FP10pppModelStP3Veci(pppModelSt,*(Vec **)&pppMiasma->field_0x70,0);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x33);
    }
    pppInitBlendMode__Fv();
    pppSetBlendMode__FUc(2);
    GXSetTevDirect(0);
    GXSetCullMode(2);
    GXSetZMode(1,3,0);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (0,0xf,0xf,0xf,0xc);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,2,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (0,7,7,7,6);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,2,1,0)
    ;
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x34);
    pppDrawMesh__FP10pppModelStP3Veci(pppModelSt,*(Vec **)&pppMiasma->field_0x70,0);
    SetDrawDoneDebugData__8CGraphicFSc(local_8c,0x35);
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (local_88,DAT_80238030,auStack_1f4,0,iVar2,iVar1,iVar8,iVar12,1,0x28,0);
    if (param_2->m_payload[0x1d] != '\0') {
      if (bVar16) {
        local_278.m_rgba[0] = '\0';
        local_278.m_rgba[1] = '\0';
        local_278.m_rgba[2] = '\0';
      }
      else {
        local_278.m_rgba[0] = 0xff;
        local_278.m_rgba[1] = 0xff;
        local_278.m_rgba[2] = 0xff;
      }
      local_278.m_rgba[0] = SUB31(local_278.m_rgba._0_3_,2);
      local_278.m_rgba[1] = SUB31(local_278.m_rgba._0_3_,1);
      local_278.m_rgba[2] = (uint8_t)local_278.m_rgba._0_3_;
      local_278.m_rgba[3] = 0xff;
      local_298[0] = local_278.m_rgba[0];
      local_298[1] = local_278.m_rgba[1];
      local_298[2] = local_278.m_rgba[2];
      local_298[3] = local_278.m_rgba[3];
      RenderColorQuad__5CUtilFffff8_GXColor
                ((double)FLOAT_8033193c,dVar19,(double)FLOAT_80331928,(double)FLOAT_8033192c,
                 &DAT_8032ec70,local_298);
      GXClearVtxDesc();
      GXSetVtxDesc(9,3);
      GXSetVtxDesc(10,3);
      GXSetVtxDesc(0xb,3);
      GXSetVtxDesc(0xd,3);
      *(undefined *)(pppModelSt->m_mapMesh).field18_0x3c = 0xff;
      *(undefined *)((pppModelSt->m_mapMesh).field18_0x3c + 1) = 0xff;
      *(undefined *)((pppModelSt->m_mapMesh).field18_0x3c + 2) = 0xff;
      *(undefined *)((pppModelSt->m_mapMesh).field18_0x3c + 3) = 0xff;
      local_29c = *(undefined4 *)(pppModelSt->m_mapMesh).field18_0x3c;
      GXSetChanAmbColor(4,&local_29c);
      local_2a0 = *(undefined4 *)(pppModelSt->m_mapMesh).field18_0x3c;
      GXSetChanMatColor(4,&local_2a0);
      GXSetChanCtrl(4,1,0,1,0,0,2);
      GXLoadPosMtxImm(&pppMiasma->field_0x40,0);
      GXSetNumTevStages(1);
      GXSetNumTexGens(0);
      GXSetTevDirect(0);
      pppInitBlendMode__Fv();
      pppSetBlendMode__FUc(1);
      GXSetCullMode(1);
      GXSetZMode(1,3,0);
      fVar6 = FLOAT_80331940 - param_2->m_stepValue;
      PSMTXScale(fVar6,fVar6,fVar6,&MStack_1b4);
      PSMTXConcat(&MStack_1b4,&(pppMiasma->field0_0x0).m_localMatrix,&MStack_184);
      PSMTXConcat(&ppvWorldMatrix,&MStack_184,(Mtx *)&pppMiasma->field_0x40);
      GXLoadPosMtxImm(&pppMiasma->field_0x40,0);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (0,0xf,0xf,0xf,0xc);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (0,7,7,7,6);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,1,0);
      if (bVar16) {
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x36);
        pppDrawMesh__FP10pppModelStP3Veci(pppModelSt,*(Vec **)&pppMiasma->field_0x70,0);
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x37);
      }
      GXSetTevDirect(0);
      pppInitBlendMode__Fv();
      pppSetBlendMode__FUc(2);
      GXSetCullMode(2);
      GXSetZMode(1,3,0);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (0,0xf,0xf,0xf,0xc);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (0,7,7,7,6);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,1,0);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x38);
      pppDrawMesh__FP10pppModelStP3Veci(pppModelSt,*(Vec **)&pppMiasma->field_0x70,0);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x39);
      GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
                (&Graphic,DAT_80238030,auStack_214,0,iVar2,iVar1,iVar8,iVar12 + iVar9,1,0x28,0);
    }
    SetViewport__8CGraphicFv(local_84);
    RenderTextureQuad__5CUtilFffffP9_GXTexObjP5Vec2dP5Vec2dP8_GXColor14_GXBlendFactor14_GXBlendFactor
              ((double)FLOAT_8033193c,dVar19,(double)FLOAT_80331928,(double)FLOAT_8033192c,
               &DAT_8032ec70,auStack_1d4,0,0,0,4,5);
    BeginQuadEnv__5CUtilFv(&DAT_8032ec70);
    SetVtxFmt_POS_CLR_TEX0_TEX1__5CUtilFv(&DAT_8032ec70);
    if (*(char *)&param_2->m_initWOrk == '\0') {
      uVar11 = 0;
    }
    else if (*(char *)&param_2->m_initWOrk == '\x01') {
      uVar11 = 1;
    }
    else {
      uVar11 = 2;
    }
    if (*(char *)&param_2->m_arg3 != '\x02') {
      uVar4 = param_2->m_payload[0x1e];
      local_288 = CONCAT31(CONCAT21(CONCAT11(uVar4,uVar4),uVar4),uVar4);
      local_2a4 = local_288;
      GXSetTevKColor(0,&local_2a4);
      pppSetBlendMode__FUc(0);
      local_2a8 = local_284;
      GXSetChanMatColor(4,&local_2a8);
      GXSetNumTexGens(2);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (1,uVar11,uVar11,uVar11,uVar11);
      GXSetTevDirect(0);
      GXLoadTexObj(auStack_1f4,0);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,1);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (0,0xf,8,0xc,0xc);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,1,0,0,1,1);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (0,7,4,6,6);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,1,0,0,1,1);
      GXSetTevDirect(1);
      GXSetTevKColorSel(1,0xc);
      GXSetTevKAlphaSel(1,0x1c);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,0,0,4);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,1);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (1,2,0xe,0xe,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,8,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (1,1,6,6,7);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,8,0,0,1,0);
      GXSetTevDirect(2);
      GXSetTevKColorSel(2,0xc);
      GXSetTevKAlphaSel(2,0x1c);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0,0,4);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,1);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (2,0xe,2,2,0);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,8,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (2,6,1,1,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,8,0,0,1,0);
      GXSetTevDirect(3);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(3,0,0,4);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(3,0,1);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (3,0xf,0,10,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (3,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (3,7,0,5,7);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (3,0,0,0,1,0);
      GXSetTevDirect(4);
      GXLoadTexObj(auStack_1d4,1);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(4,0,1);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(4,1,1,4);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (4,0xf,0xf,0xf,0);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (4,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (4,7,4,0,7);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (4,0,0,0,1,0);
      GXSetNumTevStages(5);
      local_228 = (float)(dVar19 + (double)FLOAT_8033192c);
      local_220 = FLOAT_8033193c;
      local_21c = (float)dVar19;
      local_218 = FLOAT_8033193c;
      local_22c = FLOAT_80331928;
      local_224 = FLOAT_8033193c;
      pppInitBlendMode__Fv();
      pppSetBlendMode__FUc(0);
      if (*(char *)&param_2->m_arg3 != '\x02') {
        local_2ac = local_284;
        local_25c = local_22c;
        local_258 = local_228;
        local_254 = local_224;
        local_250 = local_220;
        local_24c = local_21c;
        local_248 = local_218;
        RenderQuadTex2__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                  (&DAT_8032ec70,&local_250,&local_25c,&local_2ac,0,0);
      }
    }
    InitConstantRegister__5CUtilFv(&DAT_8032ec70);
    BeginQuadEnv__5CUtilFv(&DAT_8032ec70);
    SetVtxFmt_POS_CLR_TEX__5CUtilFv(&DAT_8032ec70);
    if (*(char *)&param_2->m_arg3 != '\x01') {
      GXSetTevDirect(0);
      GXLoadTexObj(auStack_1f4,0);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (2,uVar11,uVar11,uVar11,uVar11);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,2);
      pppInitBlendMode__Fv();
      pppSetBlendMode__FUc(1);
      local_278.m_rgba[0] = 0xff;
      local_278.m_rgba[1] = 0xff;
      local_278.m_rgba[2] = 0xff;
      local_278.m_rgba[3] = 0xff;
      local_2b0 = 0xffffffff;
      GXSetChanAmbColor(4,&local_2b0);
      local_2b4 = local_27c;
      GXSetChanMatColor(4,&local_2b4);
      GXSetChanCtrl(4,1,0,1,0,0,2);
      GXSetNumChans(1);
      if (param_2->m_payload[0x1d] == '\0') {
        GXSetTevDirect(0);
        GXLoadTexObj(auStack_1f4,0);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
        GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (0,0xf,0xf,0xf,10);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,0,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (0,7,6,4,6);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,1,0,0,1,0);
        GXSetTevDirect(1);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,0,0,4);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (1,0xf,0xf,0xf,0);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (1,0,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (1,7,0,4,7);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (1,0,0,0,1,0);
        GXSetTevDirect(2);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
        GXSetTexCoordGen2(1,1,4,0x3c,0,0x7d);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,1,1,4);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (2,0xf,0xb,0,0xf);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (2,0,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (2,7,0,5,7);
        uVar11 = 0;
        if (param_2->m_payload[0x1c] == '\x01') {
          uVar11 = 1;
        }
        else if (param_2->m_payload[0x1c] == '\x02') {
          uVar11 = 2;
        }
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (2,0,0,uVar11,1,0);
      }
      else {
        GXLoadTexObj(auStack_1f4,0);
        GXLoadTexObj(auStack_214,1);
        GXSetTevDirect(0);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
        GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (0,0xf,10,8,0xf);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,0,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (0,7,5,4,7);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,0,0,0,1,0);
        GXSetTevDirect(1);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,0,1,4);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (1,0xf,8,0xc,0);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (1,1,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (1,7,4,6,0);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (1,1,0,2,1,0);
        GXSetTevDirect(2);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0,1,4);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (2,0xf,0xb,0,0xf);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (2,0,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (2,7,0,5,7);
        uVar11 = 0;
        if (param_2->m_payload[0x1c] == '\x01') {
          uVar11 = 1;
        }
        else if (param_2->m_payload[0x1c] == '\x02') {
          uVar11 = 2;
        }
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (2,0,0,uVar11,1,0);
      }
      GXSetNumTevStages(3);
      GXSetNumTexGens(1);
      local_270 = (float)(dVar19 + (double)FLOAT_8033192c);
      local_220 = FLOAT_8033193c;
      local_264 = (float)dVar19;
      local_218 = FLOAT_8033193c;
      local_22c = FLOAT_80331928;
      local_224 = FLOAT_8033193c;
      local_2b8 = local_27c;
      local_274 = FLOAT_80331928;
      local_26c = FLOAT_8033193c;
      local_268 = FLOAT_8033193c;
      local_260 = FLOAT_8033193c;
      local_228 = local_270;
      local_21c = local_264;
      RenderQuad__5CUtilF3Vec3Vec8_GXColorP5Vec2dP5Vec2d
                (&DAT_8032ec70,&local_268,&local_274,&local_2b8,0,0);
    }
    InitConstantRegister__5CUtilFv(&DAT_8032ec70);
    uVar15 = uVar15 + 1;
  } while ((int)uVar15 < 2);
  EndQuadEnv__5CUtilFv(&DAT_8032ec70);
  pppInitBlendMode__Fv();
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  SetViewport__8CGraphicFv(&Graphic);
  InitConstantRegister__5CUtilFv(&DAT_8032ec70);
  return;
}

