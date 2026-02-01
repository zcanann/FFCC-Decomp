// Function: pppRenderCrystal2
// Entry: 8013e694
// Size: 1212 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderCrystal2(pppCrystal2 *pppCrystal2,UnkB *param_2,UnkC *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  pppModelSt *pppModelSt;
  undefined4 local_188;
  float local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  float local_174;
  undefined4 local_170;
  undefined auStack_16c [32];
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  Mtx MStack_11c;
  Mtx MStack_ec;
  Mtx MStack_bc;
  Mtx MStack_8c;
  Mtx MStack_5c;
  
  iVar2 = param_3->m_serializedDataOffsets[2];
  iVar1 = param_3->m_serializedDataOffsets[1];
  if (param_2->m_dataValIndex != 0xffff) {
    iVar3 = 0;
    pppModelSt = (pppModelSt *)pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
    local_188 = 0;
    GetTexture__8CMapMeshFP12CMaterialSetRi
              ((CMapMesh *)pppModelSt,pppEnvStPtr->m_materialSetPtr,&local_188);
    if (param_2->m_payload[0] == '\0') {
      if (param_2->m_initWOrk == 0xffff) {
        return;
      }
      iVar3 = GetTexture__8CMapMeshFP12CMaterialSetRi
                        (pppEnvStPtr->m_mapMeshPtr[param_2->m_initWOrk],
                         pppEnvStPtr->m_materialSetPtr,&local_188);
    }
    pppSetBlendMode__FUc(0);
    GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
              (&Graphic,DAT_80238030,auStack_16c,0,0,0x280,0x1c0,0,1,4,0);
    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
              ((float)param_2->m_arg3,(pppCVector *)(&pppCrystal2->field_0x88 + iVar1),
               (pppFMATRIX *)&pppCrystal2->field_0x40,param_2->m_payload[5],param_2->m_payload[4],
               param_2->m_payload[1],param_2->m_payload[2],1,1,param_2->m_payload[3]);
    GXSetProjection(&ppvScreenMatrix,0);
    local_180 = DAT_801dd60c;
    local_17c = DAT_801dd610;
    local_178 = DAT_801dd614;
    local_170 = DAT_801dd61c;
    local_184 = FLOAT_80331fd0 * param_2->m_stepValue;
    local_14c = DAT_801dd620;
    local_148 = DAT_801dd624;
    local_144 = DAT_801dd628;
    local_140 = DAT_801dd62c;
    local_13c = DAT_801dd630;
    local_138 = DAT_801dd634;
    local_134 = DAT_801dd638;
    local_130 = DAT_801dd63c;
    local_12c = DAT_801dd640;
    local_128 = DAT_801dd644;
    local_124 = DAT_801dd648;
    local_120 = DAT_801dd64c;
    local_174 = local_184;
    PSMTXIdentity(&MStack_ec);
    PSMTXConcat(&pppMngStPtr->m_matrix,&(pppCrystal2->field0_0x0).m_localMatrix,&MStack_8c);
    if (Game.game.m_currentSceneId == 7) {
      C_MTXLightPerspective
                (FLOAT_80331fd4,FLOAT_80331fd8,*(float *)(param_2->m_payload + 8),
                 -*(float *)(param_2->m_payload + 8),FLOAT_80331fdc,FLOAT_80331fdc,&MStack_11c);
      PSMTXConcat(&ppvCameraMatrix0,&MStack_8c,&MStack_bc);
    }
    else {
      C_MTXLightPerspective
                ((float)CameraPcs._252_4_,FLOAT_80331fd8,*(float *)(param_2->m_payload + 8),
                 -*(float *)(param_2->m_payload + 8),FLOAT_80331fdc,FLOAT_80331fdc,&MStack_11c);
      PSMTXConcat(&CameraPcs.m_cameraMatrix,&MStack_8c,&MStack_bc);
    }
    PSMTXConcat(&MStack_11c,&MStack_bc,&MStack_ec);
    PSMTXInverse(&MStack_bc,&MStack_5c);
    PSMTXTranspose(&MStack_5c,&MStack_5c);
    if (param_2->m_payload[0] == '\0') {
      GXLoadTexObj(iVar3 + 0x28,1);
    }
    else {
      GXLoadTexObj(*(undefined4 *)(&pppCrystal2->field_0x84 + iVar2),1);
    }
    GXSetNumIndStages(1);
    GXSetIndTexOrder(0,0,1);
    GXSetIndTexCoordScale(0,0,0);
    GXSetIndTexMtx(1,&local_184,1);
    GXSetTevIndirect(0,0,0,3,1,0,0,0,0,0);
    GXLoadTexMtxImm(&local_14c,0x40,0);
    GXLoadTexMtxImm(&MStack_5c,0x21,0);
    GXSetTexCoordGen2(0,0,1,0x21,1,0x40);
    GXLoadTexObj(auStack_16c,0);
    GXLoadTexMtxImm(&MStack_ec,0x1e,0);
    GXSetTexCoordGen2(1,0,0,0x1e,0,0x7d);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,1,0,4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
              (0,0xf,8,0xc,10);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
              (0,7,7,7,6);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0,0,0,0,1,0)
    ;
    GXSetNumTevStages(1);
    GXSetNumTexGens(2);
    GXClearVtxDesc();
    GXSetVtxDesc(9,3);
    GXSetVtxDesc(10,3);
    GXSetVtxDesc(0xb,3);
    GXSetVtxDesc(0xd,3);
    pppDrawMesh__FP10pppModelStP3Veci(pppModelSt,(Vec *)0x0,0);
    DisableIndMtx__5CUtilFv(&DAT_8032ec70);
  }
  return;
}

