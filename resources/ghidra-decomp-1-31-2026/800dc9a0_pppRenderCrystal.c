// Function: pppRenderCrystal
// Entry: 800dc9a0
// Size: 1444 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppRenderCrystal(pppCrystal *pppCrystal,UnkB *param_2,UnkC *param_3)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  pppModelSt *pppModelSt;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  float local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  float local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  Mtx MStack_74;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  
  iVar6 = param_3->m_serializedDataOffsets[2];
  iVar3 = param_3->m_serializedDataOffsets[1];
  if (param_2->m_dataValIndex != 0xffff) {
    iVar7 = 0;
    pppModelSt = (pppModelSt *)pppEnvStPtr->m_mapMeshPtr[param_2->m_dataValIndex];
    local_c0 = 0;
    iVar4 = GetTexture__8CMapMeshFP12CMaterialSetRi
                      ((CMapMesh *)pppModelSt,pppEnvStPtr->m_materialSetPtr,&local_c0);
    if (param_2->m_payload[0] == '\0') {
      if (param_2->m_initWOrk == 0xffff) {
        return;
      }
      iVar7 = GetTexture__8CMapMeshFP12CMaterialSetRi
                        (pppEnvStPtr->m_mapMeshPtr[param_2->m_initWOrk],
                         pppEnvStPtr->m_materialSetPtr,&local_c0);
    }
    local_cc = 0x280;
    local_c4 = 0;
    local_c8 = 0;
    local_d0 = 0x1c0;
    iVar5 = GetBackBufferRect__8CGraphicFRiRiRiRii
                      (&Graphic,&local_c4,&local_c8,&local_cc,&local_d0,0);
    if (iVar5 != 0) {
      pppSetBlendMode__FUc(param_2->m_payload[1]);
      pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc
                ((float)param_2->m_arg3,(pppCVector *)(&pppCrystal->field_0x88 + iVar3),
                 (pppFMATRIX *)&pppCrystal->field_0x40,param_2->m_payload[5],param_2->m_payload[4],
                 param_2->m_payload[1],param_2->m_payload[2],1,1,param_2->m_payload[3]);
      local_a4 = DAT_801db5b8;
      local_a0 = DAT_801db5bc;
      local_9c = DAT_801db5c0;
      local_98 = DAT_801db5c4;
      local_94 = DAT_801db5c8;
      local_90 = DAT_801db5cc;
      local_8c = DAT_801db5d0;
      local_88 = DAT_801db5d4;
      local_84 = DAT_801db5d8;
      local_80 = DAT_801db5dc;
      local_7c = DAT_801db5e0;
      local_78 = DAT_801db5e4;
      fVar1 = FLOAT_80330fa8;
      fVar2 = FLOAT_80330fa8;
      if (param_2->m_payload[0] != '\x01') {
        uStack_3c = *(undefined4 *)(iVar7 + 100);
        uStack_34 = *(undefined4 *)(iVar7 + 0x68);
        local_40 = 0x43300000;
        local_38 = 0x43300000;
        fVar1 = (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80330fc8);
        fVar2 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80330fc8);
      }
      local_b8 = DAT_801db5ec;
      local_b4 = DAT_801db5f0;
      local_b0 = DAT_801db5f4;
      local_a8 = DAT_801db5fc;
      local_bc = ((FLOAT_80330fac * fVar1) / FLOAT_80330fb0) * param_2->m_stepValue;
      local_ac = ((FLOAT_80330fac * fVar2) / FLOAT_80330fb4) * param_2->m_stepValue;
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      GXSetNumTexGens(3);
      GXSetNumTevStages(3);
      if (Game.game.m_currentSceneId == 7) {
        C_MTXLightPerspective
                  (FLOAT_80330fb8,FLOAT_80330fbc,FLOAT_80330fc0,FLOAT_80330fac,FLOAT_80330fc0,
                   FLOAT_80330fc0,&MStack_74);
      }
      else {
        C_MTXLightPerspective
                  ((float)CameraPcs._252_4_,FLOAT_80330fbc,FLOAT_80330fc0,FLOAT_80330fac,
                   FLOAT_80330fc0,FLOAT_80330fc0,&MStack_74);
      }
      GXLoadTexMtxImm(&local_a4,0x40,0);
      GXLoadTexMtxImm(&MStack_74,0x43,0);
      GXSetTexCoordGen2(0,0,1,0x3c,1,0x40);
      GXSetTexCoordGen2(1,0,0,0,0,0x43);
      GXLoadTexObj(iVar5,0);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,1,0,0xff);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,3);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
      GXLoadTexObj(iVar4 + 0x28,2);
      GXSetTexCoordGen2(2,1,4,0x3c,0,0x7d);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1,2,2,4);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (1,0,8,0xb,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (1,7,7,7,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0xff,0xff,4);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (2,0,10,0xb,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (2,7,7,7,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,0,0,0,1,0);
      if (param_2->m_payload[0] == '\x01') {
        GXLoadTexObj(*(undefined4 *)(&pppCrystal->field_0x84 + iVar6),1);
      }
      else {
        GXLoadTexObj(iVar7 + 0x28,1);
      }
      GXSetNumIndStages(1);
      GXSetIndTexOrder(0,0,1);
      GXSetIndTexCoordScale(0,0,0);
      GXSetIndTexMtx(1,&local_bc,1);
      GXSetTevIndirect(0,0,0,3,1,0,0,0,0,0);
      GXClearVtxDesc();
      GXSetVtxDesc(9,3);
      GXSetVtxDesc(10,3);
      GXSetVtxDesc(0xb,3);
      GXSetVtxDesc(0xd,3);
      pppDrawMesh__FP10pppModelStP3Veci(pppModelSt,*(Vec **)&pppCrystal->field_0x70,0);
      GXSetNumIndStages(0);
      GXSetTevDirect(0);
      memset(&local_bc,0,0x18);
      GXSetIndTexMtx(1,&local_bc,1);
    }
  }
  return;
}

