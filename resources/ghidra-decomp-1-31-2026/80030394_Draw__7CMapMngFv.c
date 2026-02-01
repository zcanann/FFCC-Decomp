// Function: Draw__7CMapMngFv
// Entry: 80030394
// Size: 3312 bytes

/* WARNING: Removing unreachable block (ram,0x80031068) */
/* WARNING: Removing unreachable block (ram,0x80031060) */
/* WARNING: Removing unreachable block (ram,0x800303ac) */
/* WARNING: Removing unreachable block (ram,0x800303a4) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Draw__7CMapMngFv(CMapMng *mapMng)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  CMapMng *pCVar6;
  undefined *puVar7;
  CMapMng *pCVar8;
  undefined *puVar9;
  uint uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  undefined4 local_4a8;
  undefined4 local_4a4;
  undefined4 local_4a0;
  undefined4 local_49c;
  undefined4 local_498;
  undefined4 local_494;
  undefined4 local_490;
  undefined4 local_48c;
  undefined4 local_488;
  undefined4 local_484;
  Vec local_480;
  Vec local_474;
  float local_468;
  float local_464;
  float local_460;
  float local_45c;
  float local_458;
  float local_454;
  undefined auStack_450 [64];
  Mtx MStack_410;
  undefined auStack_3e0 [64];
  Mtx MStack_3a0;
  Mat4x4 MStack_370;
  undefined auStack_330 [96];
  undefined auStack_2d0 [256];
  undefined auStack_1d0 [392];
  
  if ((mapMng->field_0x2298b != '\0') && (mapMng->field10_0xc != 0)) {
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetCullMode(1);
    GXSetZMode(1,3,1);
    SetNumDiffuse__9CLightPcsFUl(&LightPcs,0);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_370);
    GXSetProjection(&MStack_370,0);
    mapMng->field_0x2298a = 1;
    if ((DAT_8032ecb8 & 8) == 0) {
      pCVar8 = mapMng;
      for (iVar4 = 0; iVar4 < mapMng->field8_0x8; iVar4 = iVar4 + 1) {
        Draw__8COctTreeFUc(pCVar8->octTreeArr,0);
        pCVar8 = (CMapMng *)&pCVar8->octTreeArr[0].field_0x38;
      }
      pCVar6 = &MapMng;
      pCVar8 = pCVar6;
      for (iVar4 = 0; iVar4 < mapMng->field10_0xc; iVar4 = iVar4 + 1) {
        Draw__7CMapObjFUc(pCVar8->mapObjArr,0x40);
        pCVar8 = (CMapMng *)&pCVar8->octTreeArr[2].field51_0x3c.z;
      }
      DrawShoki__8CPartPcsFv(&PartPcs);
      GXSetColorUpdate(1);
      GXSetAlphaUpdate(0);
      GXSetCullMode(1);
      GXSetZMode(1,3,1);
      SetNumDiffuse__9CLightPcsFUl(&LightPcs,0);
      for (iVar4 = 0; iVar4 < mapMng->field10_0xc; iVar4 = iVar4 + 1) {
        Draw__7CMapObjFUc(pCVar6->mapObjArr,0);
        pCVar6 = (CMapMng *)&pCVar6->octTreeArr[2].field51_0x3c.z;
      }
      pCVar8 = mapMng;
      for (iVar4 = 0; iVar4 < mapMng->field8_0x8; iVar4 = iVar4 + 1) {
        Draw__8COctTreeFUc(pCVar8->octTreeArr,1);
        pCVar8 = (CMapMng *)&pCVar8->octTreeArr[0].field_0x38;
      }
      if (Game.game.m_currentSceneId == 4) {
        drawMakeTexShadow__9CCharaPcsFv(&CharaPcs);
        InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei
                  (&MaterialMan,0xffffffff,4,0,3,0xe,3,10);
        MaterialMan._68_4_ = 0xffffffff;
        MaterialMan._72_4_ = 0xace0f;
        MaterialMan._76_1_ = 0xff;
        MaterialMan._296_4_ = 0;
        MaterialMan._284_4_ = 0;
        MaterialMan._300_4_ = 0x1e;
        MaterialMan._288_4_ = 0x1e;
        MaterialMan._304_4_ = 0;
        MaterialMan._292_4_ = 0;
        MaterialMan._517_1_ = 0xff;
        MaterialMan._518_1_ = 0xff;
        MaterialMan._88_4_ = 0;
        MaterialMan._92_4_ = 0;
        MaterialMan._520_1_ = 0;
        SetFog__8CGraphicFii(&Graphic,(uint)(byte)MapMng._141704_1_,0);
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        GXSetCullMode(1);
        GXSetZMode(1,3,1);
        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                  (0,0,1,2,3);
        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                  (1,0,1,2,3);
        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                  (2,0,1,2,3);
        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                  (3,0,1,2,3);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(3,0,0);
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        GXSetCullMode(1);
        GXSetZMode(1,3,1);
        SetNumDiffuse__9CLightPcsFUl(&LightPcs,0);
        uVar1 = GetNumTexShadow__9CCharaPcsFv(&CharaPcs);
        if (uVar1 != 0) {
          GXSetNumIndStages(0);
          GXSetTevDirect(0);
          GXSetNumChans(1);
          GXSetColorUpdate(1);
          GXSetAlphaUpdate(0);
          GXSetCullMode(0);
          GXSetZMode(1,3,0);
          _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,5);
          GXSetChanCtrl(4,0,0,0,0,2,2);
          local_490 = CharaPcs._396_4_;
          GXSetChanMatColor(4,&local_490);
          _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                    (0,0,1,2,3);
          _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                    (1,0,0,0,0);
          GXSetNumTevStages(1);
          GXSetZCompLoc(0);
          _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
          iVar4 = 0;
          do {
            uVar10 = 8;
            if ((int)uVar1 < 9) {
              uVar10 = uVar1;
            }
            GetTexShadow__9CCharaPcsFiiP9_GXTexObjP3VecPA3_A4_f
                      (&CharaPcs,iVar4,uVar10,auStack_2d0,auStack_330,auStack_1d0);
            puVar9 = auStack_1d0;
            puVar7 = auStack_2d0;
            iVar3 = 0;
            iVar5 = 0x1e;
            for (iVar2 = 0; iVar2 < (int)uVar10; iVar2 = iVar2 + 1) {
              GXLoadTexMtxImm(puVar9,iVar5,0);
              GXLoadTexObj(puVar7,iVar2);
              GXSetTexCoordGen2(iVar2,0,0,iVar5,0,0x7d);
              GXSetTevDirect(iVar3);
              _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                        (iVar3,iVar2,iVar2,4);
              _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(iVar3,0,1);
              if (iVar2 == 0) {
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                          (iVar3,0xf,10,0xc,0xf);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (iVar3,0,0,0,1,0);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                          (iVar3,7,4,5,7);
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (iVar3,0,0,0,1,0);
              }
              else {
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                          (iVar3,0xf,0xf,0xf,0);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (iVar3,0,0,0,1,0);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                          (iVar3,7,4,5,0);
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (iVar3,0,0,0,1,0);
              }
              iVar5 = iVar5 + 3;
              iVar3 = iVar3 + 1;
              puVar9 = puVar9 + 0x30;
              puVar7 = puVar7 + 0x20;
            }
            GXSetTevDirect(iVar3);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (iVar3,0xff,0xff,4);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                      (iVar3,0xf,0xf,0xf,0);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (iVar3,0,0,0,1,0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                      (iVar3,7,6,0,5);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (iVar3,1,0,0,0,2);
            iVar2 = iVar3 + 1;
            GXSetTevDirect(iVar2);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (iVar2,0xff,0xff,4);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                      (iVar2,0xf,0xf,0xf,0);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (iVar2,0,0,0,1,0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                      (iVar2,2,5,2,0);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (iVar2,0xe,0,0,0,0);
            GXSetNumTexGens(uVar10 & 0xff);
            GXSetNumTevStages(iVar3 + 2U & 0xff);
            uVar1 = uVar1 - uVar10;
            iVar4 = iVar4 + uVar10;
            pCVar8 = mapMng;
            for (iVar2 = 0; iVar2 < mapMng->field8_0x8; iVar2 = iVar2 + 1) {
              DrawCharaShadow__8COctTreeFUc(pCVar8->octTreeArr,0);
              pCVar8 = (CMapMng *)&pCVar8->octTreeArr[0].field_0x38;
            }
          } while (uVar1 != 0);
        }
      }
    }
    if ((DAT_8032ecb8 & 8) != 0) {
      local_484 = 0xff;
      local_494 = 0xff;
      GXSetCopyClear(&local_494,0xffffff);
    }
    if ((DAT_8032ecb8 & 1) != 0) {
      local_488 = DAT_8032f978;
      local_45c = DAT_801d7300;
      local_458 = DAT_801d7304;
      local_454 = DAT_801d7308;
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_3a0);
      dVar13 = (double)local_458;
      dVar12 = (double)local_454;
      dVar11 = (double)FLOAT_8032f9b0;
      local_474.x = (float)(dVar11 * -(double)local_45c);
      local_474.y = (float)(dVar11 * -dVar13);
      local_4a4 = local_488;
      local_474.z = (float)(dVar11 * -dVar12);
      GXInitLightColor(auStack_3e0,&local_4a4);
      PSMTXMultVec(&MStack_3a0,&local_474,&local_474);
      GXInitLightPos((double)local_474.x,(double)local_474.y,(double)local_474.z,auStack_3e0);
      local_474.y = (float)dVar13;
      local_474.x = local_45c;
      local_474.z = (float)dVar12;
      PSMTXMultVecSR(&MStack_3a0,&local_474,&local_474);
      GXInitLightDir((double)local_474.x,(double)local_474.y,(double)local_474.z,auStack_3e0);
      GXInitLightSpot((double)FLOAT_8032f9b4,auStack_3e0,4);
      GXInitLightAttnK((double)FLOAT_8032f9a0,(double)FLOAT_8032f9b8,(double)FLOAT_8032f9a0,
                       auStack_3e0);
      GXLoadLightObjImm(auStack_3e0,1);
      local_468 = DAT_801d730c;
      local_464 = DAT_801d7310;
      local_460 = DAT_801d7314;
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_410);
      dVar12 = (double)local_464;
      dVar13 = (double)local_460;
      dVar11 = (double)FLOAT_8032f9b0;
      local_480.x = (float)(dVar11 * -(double)local_468);
      local_480.y = (float)(dVar11 * -dVar12);
      local_4a8 = local_488;
      local_480.z = (float)(dVar11 * -dVar13);
      GXInitLightColor(auStack_450,&local_4a8);
      PSMTXMultVec(&MStack_410,&local_480,&local_480);
      GXInitLightPos((double)local_480.x,(double)local_480.y,(double)local_480.z,auStack_450);
      local_480.y = (float)dVar12;
      local_480.x = local_468;
      local_480.z = (float)dVar13;
      PSMTXMultVecSR(&MStack_410,&local_480,&local_480);
      GXInitLightDir((double)local_480.x,(double)local_480.y,(double)local_480.z,auStack_450);
      GXInitLightSpot((double)FLOAT_8032f9b4,auStack_450,4);
      GXInitLightAttnK((double)FLOAT_8032f9a0,(double)FLOAT_8032f9b8,(double)FLOAT_8032f9a0,
                       auStack_450);
      GXLoadLightObjImm(auStack_450,2);
      GXSetNumChans(1);
      GXSetChanCtrl(0,1,0,1,3,2,1);
      GXSetChanCtrl(2,0,0,1,0,0,2);
      local_498 = DAT_8032f97c;
      GXSetChanMatColor(4,&local_498);
      local_49c = DAT_8032f980;
      GXSetChanAmbColor(4,&local_49c);
      if ((DAT_8032ecb8 & 2) == 0) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,6,5,5);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
        GXSetZCompLoc(1);
        GXSetZMode(1,3,1);
        GXSetCullMode(1);
      }
      else {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,1,5);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
        GXSetZCompLoc(1);
        GXSetZMode(0,7,0);
        GXSetCullMode(1);
      }
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      GXSetNumTevStages(1);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
      pCVar8 = &MapMng;
      for (iVar4 = 0; iVar4 < mapMng->field10_0xc; iVar4 = iVar4 + 1) {
        DrawHit__7CMapObjFv(pCVar8->mapObjArr);
        pCVar8 = (CMapMng *)&pCVar8->octTreeArr[2].field51_0x3c.z;
      }
      SetOffsetZBuff__10CCameraPcsFf((double)FLOAT_8032f9a0,&CameraPcs);
    }
    if ((DAT_8032ecb8 & 4) != 0) {
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
      GXSetZCompLoc(0);
      GXSetZMode(1,3,1);
      GXSetCullMode(1);
      GXSetNumTevStages(1);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
      GXSetNumChans(1);
      GXSetChanCtrl(0,0,0,0,0,2,1);
      GXSetChanCtrl(2,0,0,0,0,2,2);
      local_48c = 0xffffff80;
      local_4a0 = 0xffffff80;
      GXSetChanMatColor(4,&local_4a0);
      SetOffsetZBuff__10CCameraPcsFf((double)FLOAT_8032f9bc,&CameraPcs);
      pCVar6 = &MapMng;
      pCVar8 = pCVar6;
      for (iVar4 = 0; iVar4 < mapMng->field10_0xc; iVar4 = iVar4 + 1) {
        DrawHitWire__7CMapObjFv(pCVar8->mapObjArr);
        pCVar8 = (CMapMng *)&pCVar8->octTreeArr[2].field51_0x3c.z;
      }
      for (iVar4 = 0; iVar4 < mapMng->field10_0xc; iVar4 = iVar4 + 1) {
        DrawHitNormal__7CMapObjFv(pCVar6->mapObjArr);
        pCVar6 = (CMapMng *)&pCVar6->octTreeArr[2].field51_0x3c.z;
      }
      SetOffsetZBuff__10CCameraPcsFf((double)FLOAT_8032f9a0,&CameraPcs);
    }
  }
  return;
}

