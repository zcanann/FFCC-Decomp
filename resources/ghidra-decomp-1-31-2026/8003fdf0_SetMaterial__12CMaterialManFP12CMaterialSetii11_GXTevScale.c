// Function: SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
// Entry: 8003fdf0
// Size: 8504 bytes

void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale
               (CMaterialMan *materialMan,CMaterialSet *materialSet,undefined4 param_3,
               undefined4 param_4,undefined4 param_5)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint local_c8;
  undefined4 local_c4;
  uint local_c0;
  uint local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  uint local_94;
  uint local_90;
  undefined4 local_8c;
  undefined4 local_88;
  Mtx MStack_84;
  Mtx MStack_54;
  
  bVar1 = false;
  SetStdEnv__12CMaterialManFv();
  iVar2 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,param_3);
  DAT_8032ece8 = iVar2;
  if (*(int *)(iVar2 + 0x28) != 0) {
    if (*(char *)(iVar2 + 0xa2) == '\x03') {
      GXSetArray(10,*(undefined4 *)&materialMan->field_0x4,6);
      Set__9CMaterialF11_GXTexMapID(iVar2,*(undefined4 *)&materialMan->field_0x11c);
      uVar5 = *(uint *)&materialMan->field_0x48 & *(uint *)(iVar2 + 0x24);
      if (*(uint *)&materialMan->field_0x44 != uVar5) {
        *(uint *)&materialMan->field_0x44 = uVar5;
        if ((uVar5 & 2) != 0) {
          IncTexMapIdCur__12CMaterialManFv(materialMan);
        }
        IncTexMapIdCur__12CMaterialManFv(materialMan);
        *(uint *)&materialMan->field_0x44 = uVar5;
        uVar3 = IncTexMapIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1c4 = uVar3;
        uVar3 = IncTexMapIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1c8 = uVar3;
        uVar3 = IncTexMtxCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1d4 = uVar3;
        uVar3 = IncTexMtxCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1e0 = uVar3;
        IncTexCoordIdCur__12CMaterialManFv(materialMan);
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1e8 = uVar3;
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1f8 = uVar3;
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1f4 = uVar3;
        SetTexture__Q29CLightPcs10CBumpLightF11_GXTexMapIDi
                  (*(undefined4 *)(iVar2 + 0x28),*(undefined4 *)&materialMan->field_0x1c8,0);
        PSMTXScale(*(float *)(iVar2 + 0x2c),*(float *)(iVar2 + 0x30),FLOAT_8032faf0,&MStack_54);
        MStack_54.value[0][3] = *(float *)(iVar2 + 100);
        MStack_54.value[1][3] = *(float *)(iVar2 + 0x68);
        GXLoadTexMtxImm(&MStack_54,*(undefined4 *)&materialMan->field_0x1d4,1);
        GXLoadTexMtxImm(0x80268fec,*(undefined4 *)&materialMan->field_0x1e0,1);
        if ((uVar5 & 0x20) == 0) {
          GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
        }
        else {
          GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,
                            *(undefined4 *)&materialMan->field_0x144,0,0x7d);
        }
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1e8,1,4,
                          *(undefined4 *)&materialMan->field_0x1d4,0,0x7d);
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1f8,1,0,
                          *(undefined4 *)&materialMan->field_0x1e0,0,0x7d);
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1f4,1,1,0x3c,0,0x7d);
        *(undefined4 *)&materialMan->field_0x60 = 0;
        if (*(char *)(iVar2 + 0xa5) == '\0') {
          local_a0 = *(undefined4 *)(iVar2 + 0x38);
          GXSetTevColor(2,&local_a0);
        }
        else {
          local_9c = *(undefined4 *)(*(int *)(iVar2 + 0x28) + 0x54);
          GXSetTevColor(2,&local_9c);
        }
        if ((uVar5 & 0x20000) == 0) {
          GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
          _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                    (*(undefined4 *)&materialMan->field_0x60,
                     *(undefined4 *)&materialMan->field_0x13c,
                     *(undefined4 *)&materialMan->field_0x134,4);
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,0xf,8,10,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,param_5,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,4,5,7);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                    (*(undefined4 *)&materialMan->field_0x60,0,0);
          IncNumTevStage__12CMaterialManFv(materialMan);
          addtev_bump_jimen__12CMaterialManF11_GXTevScale(materialMan,param_5);
          if ((uVar5 & 2) == 0) {
            if (materialMan->field_0x4c != '\0') {
              GXClearVtxDesc();
              GXSetVtxDesc(9,3);
              GXSetVtxDesc(10,3);
              GXSetVtxDesc(0xb,3);
              GXSetVtxDesc(0xd,3);
              materialMan->field_0x4c = 0;
            }
          }
          else {
            if (materialMan->field_0x4c != '\x02') {
              GXClearVtxDesc();
              GXSetVtxDesc(9,3);
              GXSetVtxDesc(10,3);
              GXSetVtxDesc(0xb,3);
              GXSetVtxDesc(0xd,3);
              GXSetVtxDesc(0xe,3);
              materialMan->field_0x4c = 2;
            }
            if ((uVar5 & 0x40) == 0) {
              uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
              GXSetTexCoordGen2(uVar3,1,5,0x3c,0,0x7d);
            }
            else {
              uVar3 = *(undefined4 *)&materialMan->field_0x154;
            }
            GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (*(undefined4 *)&materialMan->field_0x60,uVar3,
                       (*(uint *)&materialMan->field_0x134 & 0xff) + 1,4);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                      (*(undefined4 *)&materialMan->field_0x60,0xf,8,10,0xf);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (*(undefined4 *)&materialMan->field_0x60,0,0,param_5,1,3);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                      (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                      (*(undefined4 *)&materialMan->field_0x60,0,0);
            IncNumTevStage__12CMaterialManFv(materialMan);
            GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (*(undefined4 *)&materialMan->field_0x60,uVar3,
                       (*(uint *)&materialMan->field_0x134 & 0xff) + 1,0xff);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                      (*(undefined4 *)&materialMan->field_0x60,0,6,9,0xf);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                      (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                      (*(undefined4 *)&materialMan->field_0x60,0,0);
            IncNumTevStage__12CMaterialManFv(materialMan);
          }
        }
        else {
          if (materialMan->field_0x4c != '\x02') {
            GXClearVtxDesc();
            GXSetVtxDesc(9,3);
            GXSetVtxDesc(10,3);
            GXSetVtxDesc(0xb,3);
            GXSetVtxDesc(0xd,3);
            GXSetVtxDesc(0xe,3);
            materialMan->field_0x4c = 2;
          }
          if ((uVar5 & 0x40) == 0) {
            uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
            GXSetTexCoordGen2(uVar3,1,5,0x3c,0,0x7d);
          }
          else {
            uVar3 = *(undefined4 *)&materialMan->field_0x154;
          }
          GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
          _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                    (*(undefined4 *)&materialMan->field_0x60,
                     *(undefined4 *)&materialMan->field_0x13c,
                     *(undefined4 *)&materialMan->field_0x134,4);
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,0xf,8,10,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,param_5,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,4,5,7);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                    (*(undefined4 *)&materialMan->field_0x60,0,0);
          IncNumTevStage__12CMaterialManFv(materialMan);
          GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
          _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                    (*(undefined4 *)&materialMan->field_0x60,uVar3,
                     (*(uint *)&materialMan->field_0x134 & 0xff) + 1,4);
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,0xf,8,10,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,param_5,1,3);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                    (*(undefined4 *)&materialMan->field_0x60,0,0);
          IncNumTevStage__12CMaterialManFv(materialMan);
          GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
          _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                    (*(undefined4 *)&materialMan->field_0x60,uVar3,
                     (*(uint *)&materialMan->field_0x134 & 0xff) + 1,0xff);
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,0,6,9,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                    (*(undefined4 *)&materialMan->field_0x60,0,0);
          IncNumTevStage__12CMaterialManFv(materialMan);
          addtev_bump_jimen__12CMaterialManF11_GXTevScale(materialMan,param_5);
        }
        addtev_stdShadow__12CMaterialManFUl(materialMan,uVar5);
        if ((uVar5 & 0x80) != 0) {
          uVar3 = IncTexMapIdCur__12CMaterialManFv(materialMan);
          *(undefined4 *)&materialMan->field_0x194 = uVar3;
          uVar3 = IncTexMtxCur__12CMaterialManFv(materialMan);
          *(undefined4 *)&materialMan->field_0x19c = uVar3;
          uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
          *(undefined4 *)&materialMan->field_0x1a4 = uVar3;
          uVar3 = IncTexMapIdCur__12CMaterialManFv(materialMan);
          *(undefined4 *)&materialMan->field_0x1ac = uVar3;
          uVar3 = IncTexMtxCur__12CMaterialManFv(materialMan);
          *(undefined4 *)&materialMan->field_0x1b4 = uVar3;
          uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
          *(undefined4 *)&materialMan->field_0x1bc = uVar3;
          addtev_full_shadow__12CMaterialManFl(materialMan,0);
        }
        GXSetNumTexGens(*(uint *)&materialMan->field_0x124 & 0xff);
        GXSetNumTevStages(*(uint *)&materialMan->field_0x60 & 0xff);
        return;
      }
      SetTexture__Q29CLightPcs10CBumpLightF11_GXTexMapIDi
                (*(undefined4 *)(iVar2 + 0x28),*(undefined4 *)&materialMan->field_0x1c8,0);
      return;
    }
    if (*(char *)(iVar2 + 0xa2) == '\x02') {
      if (materialMan->field_0x4c != '\0') {
        GXClearVtxDesc();
        GXSetVtxDesc(9,3);
        GXSetVtxDesc(10,3);
        GXSetVtxDesc(0xb,3);
        GXSetVtxDesc(0xd,3);
        materialMan->field_0x4c = 0;
      }
      GXSetArray(10,*(undefined4 *)&materialMan->field_0x4,6);
      Set__9CMaterialF11_GXTexMapID(iVar2,*(undefined4 *)&materialMan->field_0x11c);
      uVar5 = *(uint *)&materialMan->field_0x48 & *(uint *)(iVar2 + 0x24);
      if (*(uint *)&materialMan->field_0x44 != uVar5) {
        *(uint *)&materialMan->field_0x44 = uVar5;
        *(int *)&materialMan->field_0x1c4 = *(int *)&materialMan->field_0x11c + 1;
        *(int *)&materialMan->field_0x1c8 = *(int *)&materialMan->field_0x11c + 2;
        *(int *)&materialMan->field_0x1cc = *(int *)&materialMan->field_0x11c + 3;
        uVar3 = IncTexMtxCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1d4 = uVar3;
        uVar3 = IncTexMtxCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1e0 = uVar3;
        uVar3 = IncTexMtxCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1e4 = uVar3;
        IncTexCoordIdCur__12CMaterialManFv(materialMan);
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1e8 = uVar3;
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1f8 = uVar3;
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1f4 = uVar3;
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1fc = uVar3;
        SetTexture__Q29CLightPcs10CBumpLightF11_GXTexMapIDi
                  (*(undefined4 *)(iVar2 + 0x28),*(undefined4 *)&materialMan->field_0x1c8,0);
        GXLoadTexObj(*(undefined4 *)&materialMan->field_0xc,*(undefined4 *)&materialMan->field_0x1cc
                    );
        PSMTXScale(*(float *)(iVar2 + 0x2c),*(float *)(iVar2 + 0x30),FLOAT_8032faf0,&MStack_84);
        MStack_84.value[0][3] = *(float *)(iVar2 + 100);
        MStack_84.value[1][3] = *(float *)(iVar2 + 0x68);
        GXLoadTexMtxImm(&MStack_84,*(undefined4 *)&materialMan->field_0x1d4,1);
        GXLoadTexMtxImm(0x80268fec,*(undefined4 *)&materialMan->field_0x1e0,1);
        GXLoadTexMtxImm(&materialMan->field_0x10,*(undefined4 *)&materialMan->field_0x1e4,0);
        if ((uVar5 & 0x20) == 0) {
          GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
        }
        else {
          GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,
                            *(undefined4 *)&materialMan->field_0x144,0,0x7d);
        }
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1e8,1,4,
                          *(undefined4 *)&materialMan->field_0x1d4,0,0x7d);
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1f8,1,0,
                          *(undefined4 *)&materialMan->field_0x1e0,0,0x7d);
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1f4,1,1,0x3c,0,0x7d);
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1fc,0,0,
                          *(undefined4 *)&materialMan->field_0x1e4,0,0x7d);
        *(undefined4 *)&materialMan->field_0x60 = 0;
        if ((uVar5 & 0x80000) == 0) {
          addtev_bump_water__12CMaterialManF11_GXTevScale(materialMan,param_5);
        }
        else {
          if (*(char *)(iVar2 + 0xa5) == '\0') {
            local_a8 = *(undefined4 *)(iVar2 + 0x38);
            GXSetTevColor(2,&local_a8);
          }
          else {
            local_a4 = *(undefined4 *)(*(int *)(iVar2 + 0x28) + 0x54);
            GXSetTevColor(2,&local_a4);
          }
          addtev_bump_spec_col_water__12CMaterialManF11_GXTevScale(materialMan,param_5);
        }
        addtev_stdShadow__12CMaterialManFUl(materialMan,uVar5);
        GXSetNumTexGens(*(uint *)&materialMan->field_0x124 & 0xff);
        GXSetNumTevStages(*(uint *)&materialMan->field_0x60 & 0xff);
        return;
      }
      SetTexture__Q29CLightPcs10CBumpLightF11_GXTexMapIDi
                (*(undefined4 *)(iVar2 + 0x28),*(undefined4 *)&materialMan->field_0x1c8,0);
      GXLoadTexObj(*(undefined4 *)&materialMan->field_0xc,*(undefined4 *)&materialMan->field_0x1cc);
      return;
    }
    if ((*(uint *)&materialMan->field_0x48 & *(uint *)(iVar2 + 0x24) & 0x1000) == 0) {
      if (materialMan->field_0x4c != '\x01') {
        GXClearVtxDesc();
        GXSetVtxDesc(9,3);
        GXSetVtxDesc(0x19,3);
        GXSetVtxDesc(0xb,3);
        GXSetVtxDesc(0xd,3);
        materialMan->field_0x4c = 1;
      }
      GXSetArray(10,*(undefined4 *)&materialMan->field_0x4,0x12);
      Set__9CMaterialF11_GXTexMapID(iVar2,*(undefined4 *)&materialMan->field_0x11c);
      uVar5 = *(uint *)&materialMan->field_0x48 & *(uint *)(iVar2 + 0x24);
      if (*(uint *)&materialMan->field_0x44 != uVar5) {
        uVar4 = uVar5 & 0x60;
        *(uint *)&materialMan->field_0x44 = uVar5;
        if (uVar4 == 0x40) {
          *(undefined4 *)&materialMan->field_0x1e8 = *(undefined4 *)&materialMan->field_0x154;
          GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1e8,1,4,MaterialMan._336_4_,0,0x7d)
          ;
          uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
          *(undefined4 *)&materialMan->field_0x13c = uVar3;
          GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
        }
        else if (uVar4 < 0x40) {
          if (uVar4 == 0x20) {
            *(undefined4 *)&materialMan->field_0x13c = *(undefined4 *)&materialMan->field_0x148;
            uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
            *(undefined4 *)&materialMan->field_0x1e8 = uVar3;
            GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1e8,1,4,0x3c,0,0x7d);
          }
          else if ((uVar4 < 0x20) && (uVar4 == 0)) {
            IncTexCoordIdCur__12CMaterialManFv(materialMan);
            GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
            *(undefined4 *)&materialMan->field_0x1e8 = *(undefined4 *)&materialMan->field_0x13c;
          }
        }
        else if (uVar4 == 0x60) {
          *(undefined4 *)&materialMan->field_0x13c = *(undefined4 *)&materialMan->field_0x148;
          *(undefined4 *)&materialMan->field_0x1e8 = *(undefined4 *)&materialMan->field_0x154;
        }
        *(int *)&materialMan->field_0x1c4 = *(int *)&materialMan->field_0x11c + 1;
        *(int *)&materialMan->field_0x1c8 = *(int *)&materialMan->field_0x11c + 2;
        uVar3 = IncTexMtxCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1dc = uVar3;
        uVar3 = IncTexMtxCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1d8 = uVar3;
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1ec = uVar3;
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1f0 = uVar3;
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1f4 = uVar3;
        if (-1 < *(short *)(DAT_8032ece8 + 0x20)) {
          *(int *)&materialMan->field_0x1d0 = *(int *)&materialMan->field_0x11c + 3;
          uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
          *(undefined4 *)&materialMan->field_0x200 = uVar3;
        }
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1ec,1,2,
                          *(undefined4 *)&materialMan->field_0x1d8,0,0x7d);
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1f0,1,3,
                          *(undefined4 *)&materialMan->field_0x1d8,0,0x7d);
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1f4,1,1,
                          *(undefined4 *)&materialMan->field_0x1dc,0,0x7d);
        GXLoadTexMtxImm(0x80268f8c,*(undefined4 *)&materialMan->field_0x1dc,1);
        GXLoadTexMtxImm(0x80268fbc,*(undefined4 *)&materialMan->field_0x1d8,1);
        GXSetCurrentMtx(0);
        *(undefined4 *)&materialMan->field_0x60 = 0;
        addtev_bump_st__12CMaterialManFi11_GXTevScale(materialMan,param_4,param_5);
        addtev_stdShadow__12CMaterialManFUl(materialMan,uVar5);
        GXSetNumTexGens(*(uint *)&materialMan->field_0x124 & 0xff);
        GXSetNumTevStages(*(uint *)&materialMan->field_0x60 & 0xff);
      }
      uVar5 = uVar5 & 0x60;
      if (uVar5 == 0x40) {
        *(undefined4 *)&materialMan->field_0x1e8 = *(undefined4 *)&materialMan->field_0x154;
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1e8,1,4,MaterialMan._336_4_,0,0x7d);
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x13c = uVar3;
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
      }
      else if ((uVar5 < 0x40) && (uVar5 == 0x20)) {
        *(undefined4 *)&materialMan->field_0x13c = *(undefined4 *)&materialMan->field_0x148;
        uVar3 = IncTexCoordIdCur__12CMaterialManFv(materialMan);
        *(undefined4 *)&materialMan->field_0x1e8 = uVar3;
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x1e8,1,4,0x3c,0,0x7d);
      }
      SetTexture__Q29CLightPcs10CBumpLightF11_GXTexMapIDi
                (*(undefined4 *)(iVar2 + 0x28),*(undefined4 *)&materialMan->field_0x1c8,
                 *(undefined *)(iVar2 + 0x36));
      if (*(char *)(DAT_8032ece8 + 0xa3) != '\x01') {
        return;
      }
      if (*(char *)(iVar2 + 0xa5) == '\0') {
        local_b0 = *(undefined4 *)(iVar2 + 0x38);
        GXSetTevColor(2,&local_b0);
      }
      else {
        local_ac = *(undefined4 *)(*(int *)(iVar2 + 0x28) + 0x54);
        GXSetTevColor(2,&local_ac);
      }
      if (*(short *)(iVar2 + 0x20) < 0) {
        return;
      }
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture
                (&TextureMan,*(undefined4 *)&materialMan->field_0x1d0,
                 *(CTexture **)(DAT_8032ece8 + 0x48));
      return;
    }
    bVar1 = true;
  }
  if (bVar1) {
    GXSetArray(10,*(undefined4 *)&materialMan->field_0x4,0x12);
  }
  else {
    GXSetArray(10,*(undefined4 *)&materialMan->field_0x4,6);
  }
  Set__9CMaterialF11_GXTexMapID(iVar2,*(undefined4 *)&materialMan->field_0x11c);
  uVar5 = *(uint *)&materialMan->field_0x48 & *(uint *)(iVar2 + 0x24);
  if (*(uint *)&materialMan->field_0x44 == uVar5) {
    return;
  }
  *(uint *)&materialMan->field_0x44 = uVar5;
  GXSetNumIndStages(0);
  if ((uVar5 & 1) == 0) {
    if ((uVar5 & 0x200) == 0) {
      GXSetTevDirect(0);
      if ((uVar5 & 0x20) == 0) {
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                  (0,*(undefined4 *)&materialMan->field_0x13c,
                   *(undefined4 *)&materialMan->field_0x134,4);
      }
      else {
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                  (0,*(undefined4 *)&materialMan->field_0x148,
                   *(undefined4 *)&materialMan->field_0x134,4);
      }
      GXSetTevDirect(0);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (0,0xf,8,10,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,param_5,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (0,7,4,5,7);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      *(undefined4 *)&materialMan->field_0x60 = 1;
    }
    else {
      IncTexMapIdCur__12CMaterialManFv(materialMan);
      local_8c = 0xffff0000;
      local_88 = 0xffff;
      local_b4 = 0xffff0000;
      GXSetTevColor(2,&local_b4);
      local_b8 = local_88;
      GXSetTevColor(3,&local_b8);
      GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (1,0,3,3,3);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (2,2,2,2,3);
      GXSetTevDirect(0);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (0,0xf,8,4,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,0,0,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,1);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (0,*(undefined4 *)&materialMan->field_0x13c,*(undefined4 *)&materialMan->field_0x134
                 ,0xff);
      GXSetTevDirect(1);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (1,0xf,8,6,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (1,7,6,4,7);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (1,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,2);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (1,*(undefined4 *)&materialMan->field_0x13c,*(int *)&materialMan->field_0x134 + 1,
                 0xff);
      GXSetTevDirect(2);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (2,0xf,0,10,0xf);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (2,7,0,5,7);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,0,0,param_5,1,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (2,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0xff,0xff,4);
      *(undefined4 *)&materialMan->field_0x60 = 3;
    }
  }
  else {
    GXSetTevDirect(0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
    *(undefined4 *)&materialMan->field_0x60 = 1;
  }
  if (uVar5 == 0) {
    if (materialMan->field_0x4c != '\0') {
      GXClearVtxDesc();
      GXSetVtxDesc(9,3);
      GXSetVtxDesc(10,3);
      GXSetVtxDesc(0xb,3);
      GXSetVtxDesc(0xd,3);
      materialMan->field_0x4c = 0;
    }
  }
  else {
    if ((uVar5 & 2) == 0) {
      if (materialMan->field_0x4c != '\0') {
        GXClearVtxDesc();
        GXSetVtxDesc(9,3);
        GXSetVtxDesc(10,3);
        GXSetVtxDesc(0xb,3);
        GXSetVtxDesc(0xd,3);
        materialMan->field_0x4c = 0;
      }
    }
    else {
      if (materialMan->field_0x4c != '\x02') {
        GXClearVtxDesc();
        GXSetVtxDesc(9,3);
        GXSetVtxDesc(10,3);
        GXSetVtxDesc(0xb,3);
        GXSetVtxDesc(0xd,3);
        GXSetVtxDesc(0xe,3);
        materialMan->field_0x4c = 2;
      }
      if ((uVar5 & 0x40) == 0) {
        IncTexCoordIdCur__12CMaterialManFv(materialMan);
        uVar3 = *(undefined4 *)&materialMan->field_0x124;
        GXSetTexCoordGen2(uVar3,1,5,0x3c,0,0x7d);
      }
      else {
        uVar3 = *(undefined4 *)&materialMan->field_0x154;
      }
      *(undefined4 *)&materialMan->field_0x60 = 1;
      IncTexMtxCur__12CMaterialManFv(materialMan);
      IncTexMapIdCur__12CMaterialManFv(materialMan);
      GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (*(undefined4 *)&materialMan->field_0x60,uVar3,
                 (*(uint *)&materialMan->field_0x134 & 0xff) + 1,4);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (*(undefined4 *)&materialMan->field_0x60,0xf,8,10,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,param_5,1,2);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                (*(undefined4 *)&materialMan->field_0x60,0,0);
      IncNumTevStage__12CMaterialManFv(materialMan);
      GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (*(undefined4 *)&materialMan->field_0x60,uVar3,
                 (*(uint *)&materialMan->field_0x134 & 0xff) + 1,0xff);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (*(undefined4 *)&materialMan->field_0x60,0,4,9,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                (*(undefined4 *)&materialMan->field_0x60,0,0);
      IncNumTevStage__12CMaterialManFv(materialMan);
    }
    if ((uVar5 & 0x8000) != 0) {
      *(undefined4 *)&materialMan->field_0x44 = 0xffffffff;
      local_90 = (uint)*(byte *)(iVar2 + 0xa4);
      local_bc = local_90;
      GXSetTevColor(3,&local_bc);
      GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
      if ((uVar5 & 0x20) == 0) {
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                  (*(undefined4 *)&materialMan->field_0x60,*(undefined4 *)&materialMan->field_0x13c,
                   (*(uint *)&materialMan->field_0x134 & 0xff) + 1,4);
      }
      else {
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                  (*(undefined4 *)&materialMan->field_0x60,*(undefined4 *)&materialMan->field_0x148,
                   (*(uint *)&materialMan->field_0x134 & 0xff) + 1,4);
      }
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (*(undefined4 *)&materialMan->field_0x60,0xf,8,10,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,param_5,1,2);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                (*(undefined4 *)&materialMan->field_0x60,0,0);
      IncNumTevStage__12CMaterialManFv(materialMan);
      GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (*(undefined4 *)&materialMan->field_0x60,0xff,0xff,0xff);
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (*(undefined4 *)&materialMan->field_0x60,0,4,7,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                (*(undefined4 *)&materialMan->field_0x60,0,0);
      IncNumTevStage__12CMaterialManFv(materialMan);
    }
    if ((uVar5 & 0x10000) != 0) {
      GXSetNumTevStages(1);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
      return;
    }
    if ((uVar5 & 0x40000) != 0) {
      *(undefined4 *)&materialMan->field_0x60 = 0;
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      GXLoadTexMtxImm(&materialMan->field_0xe8,0x1e,0);
      GXSetTexCoordGen2(0,0,0,0x1e,0,0x7d);
      GXLoadTexObj(*(undefined4 *)&materialMan->field_0xd0,0);
      GXSetChanCtrl(4,0,0,1,0,0,2);
      GXSetTevDirect(0);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
      GXSetNumTexGens(1);
      GXSetNumTevStages(1);
      return;
    }
    if ((uVar5 & 0x1000) != 0) {
      if (bVar1) {
        GXClearVtxDesc();
        GXSetVtxDesc(9,3);
        GXSetVtxDesc(0x19,3);
        GXSetVtxDesc(0xb,3);
        GXSetVtxDesc(0xd,3);
        materialMan->field_0x4c = 0xff;
      }
      IncTexMapIdCur__12CMaterialManFv(materialMan);
      *(undefined4 *)&materialMan->field_0xcc = *(undefined4 *)&materialMan->field_0x11c;
      IncTexCoordIdCur__12CMaterialManFv(materialMan);
      *(undefined4 *)&materialMan->field_0xd4 = *(undefined4 *)&materialMan->field_0x124;
      GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0xd4,1,4,0x3c,0,0x7d);
      if (*(int *)&materialMan->field_0xd0 != 0) {
        GXLoadTexObj(*(int *)&materialMan->field_0xd0,*(undefined4 *)&materialMan->field_0xcc);
      }
      GXSetChanCtrl(4,0,0,1,0,0,2);
      GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (*(undefined4 *)&materialMan->field_0x60,*(undefined4 *)&materialMan->field_0xd4,
                 *(undefined4 *)&materialMan->field_0xcc,4);
      if (*(int *)&materialMan->field_0xd0 == 0) {
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (*(undefined4 *)&materialMan->field_0x60,0xf,0xf,0xf,0);
      }
      else {
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (*(undefined4 *)&materialMan->field_0x60,8,8,0,0xf);
      }
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (*(undefined4 *)&materialMan->field_0x60,7,5,0,7);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                (*(undefined4 *)&materialMan->field_0x60,0,0);
      IncNumTevStage__12CMaterialManFv(materialMan);
    }
    if ((((uVar5 & 0x2000) != 0) && (*(int *)&materialMan->field_0xd0 != 0)) &&
       (*(int *)&materialMan->field_0xdc != 0)) {
      if (DAT_8032ecf0 == '\0') {
        DAT_8032ecec = 0;
        DAT_8032ecf0 = '\x01';
      }
      if (DAT_8032ecf8 == '\0') {
        DAT_8032ecf4 = 0;
        DAT_8032ecf8 = '\x01';
      }
      uVar4 = GetButtonDown__4CPadFl(&Pad,0);
      if ((uVar4 & 0x100) != 0) {
        DAT_8032ecec = 0;
      }
      if ((uVar4 & 0x200) != 0) {
        DAT_8032ecf4 = 0;
      }
      GXSetNumChans(1);
      GXSetChanCtrl(4,0,0,1,0,0,2);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,0xf);
      *(undefined4 *)&materialMan->field_0x60 = 0;
      local_94 = (uint)(byte)materialMan->field_0xe4;
      local_98 = CONCAT31(0xffffff,materialMan->field_0xe4);
      GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (1,0,1,2,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                (*(undefined4 *)&materialMan->field_0x60,0,1);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (*(undefined4 *)&materialMan->field_0x60,*(undefined4 *)&materialMan->field_0x124,
                 *(undefined4 *)&materialMan->field_0x11c,4);
      GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x124,1,4,0x3c,0,0x7d);
      GXLoadTexObj(*(undefined4 *)&materialMan->field_0xdc,*(undefined4 *)&materialMan->field_0x11c)
      ;
      IncTexCoordIdCur__12CMaterialManFv(materialMan);
      IncTexMapIdCur__12CMaterialManFv(materialMan);
      local_c0 = local_94;
      GXSetTevKColor(0,&local_c0);
      GXSetTevKColorSel(*(undefined4 *)&materialMan->field_0x60,0xc);
      GXSetTevKAlphaSel(*(undefined4 *)&materialMan->field_0x60,0x1c);
      if (DAT_8032ecec == 0) {
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (*(undefined4 *)&materialMan->field_0x60,10,0xe,8,0xf);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (*(undefined4 *)&materialMan->field_0x60,8,0,0,1,1);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (*(undefined4 *)&materialMan->field_0x60,7,7,7,6);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,1);
        IncNumTevStage__12CMaterialManFv(materialMan);
        GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                  (*(undefined4 *)&materialMan->field_0x60,0,1);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                  (*(undefined4 *)&materialMan->field_0x60,*(undefined4 *)&materialMan->field_0x124,
                   *(undefined4 *)&materialMan->field_0x11c,4);
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x124,1,5,0x3c,0,0x7d);
        GXLoadTexObj(*(undefined4 *)&materialMan->field_0xd0,
                     *(undefined4 *)&materialMan->field_0x11c);
        IncTexCoordIdCur__12CMaterialManFv(materialMan);
        IncTexMapIdCur__12CMaterialManFv(materialMan);
        local_c4 = local_98;
        GXSetTevKColor(1,&local_c4);
        GXSetTevKColorSel(*(undefined4 *)&materialMan->field_0x60,0xd);
        GXSetTevKAlphaSel(*(undefined4 *)&materialMan->field_0x60,0x1d);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (*(undefined4 *)&materialMan->field_0x60,0xe,0xb,8,0xf);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (*(undefined4 *)&materialMan->field_0x60,0xc,0,0,1,2);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (*(undefined4 *)&materialMan->field_0x60,7,7,7,6);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,2);
        IncNumTevStage__12CMaterialManFv(materialMan);
        GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                  (*(undefined4 *)&materialMan->field_0x60,0,1);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                  (*(undefined4 *)&materialMan->field_0x60,0,0,4);
        if (DAT_8032ecf4 == 0) {
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,0xf,2,0xc,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,7,7,6);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,5,6,6);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,1,0,0,1,0);
        }
        else if (DAT_8032ecf4 == 1) {
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,0xf,0xc,2,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,6,6,7);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
        }
        else if (DAT_8032ecf4 == 2) {
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,0xf,0xc,4,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,5,6,6);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,1,0,0,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,6,6,7);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
        }
        else {
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,2,4,0xb,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,2,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,7,7,6);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
        }
        IncNumTevStage__12CMaterialManFv(materialMan);
        if (DAT_8032ecf4 == 0) {
          local_c8 = local_94;
          GXSetTevKColor(3,&local_c8);
          GXSetTevKColorSel(*(undefined4 *)&materialMan->field_0x60,0xf);
          GXSetTevKAlphaSel(*(undefined4 *)&materialMan->field_0x60,0x1f);
          GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
          _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                    (*(undefined4 *)&materialMan->field_0x60,0,0);
          _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,4);
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,0xf,4,0xc,0);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,7,7,6);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
          IncNumTevStage__12CMaterialManFv(materialMan);
        }
      }
      else {
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (*(undefined4 *)&materialMan->field_0x60,0xf,0xf,0xf,0xb);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (*(undefined4 *)&materialMan->field_0x60,7,7,7,5);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
        if (DAT_8032ecf4 == 2) {
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (*(undefined4 *)&materialMan->field_0x60,0xf,0xb,0xc,0xc);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,1,0,0,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (*(undefined4 *)&materialMan->field_0x60,7,5,6,6);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (*(undefined4 *)&materialMan->field_0x60,1,0,0,1,0);
        }
        IncNumTevStage__12CMaterialManFv(materialMan);
      }
    }
    addtev_stdShadow__12CMaterialManFUl(materialMan,uVar5);
    if ((uVar5 & 0x80) != 0) {
      IncTexMapIdCur__12CMaterialManFv(materialMan);
      *(undefined4 *)&materialMan->field_0x194 = *(undefined4 *)&materialMan->field_0x11c;
      IncTexMtxCur__12CMaterialManFv(materialMan);
      *(undefined4 *)&materialMan->field_0x19c = *(undefined4 *)&materialMan->field_0x120;
      IncTexCoordIdCur__12CMaterialManFv(materialMan);
      *(undefined4 *)&materialMan->field_0x1a4 = *(undefined4 *)&materialMan->field_0x124;
      IncTexMapIdCur__12CMaterialManFv(materialMan);
      *(undefined4 *)&materialMan->field_0x1ac = *(undefined4 *)&materialMan->field_0x11c;
      IncTexMtxCur__12CMaterialManFv(materialMan);
      *(undefined4 *)&materialMan->field_0x1b4 = *(undefined4 *)&materialMan->field_0x120;
      IncTexCoordIdCur__12CMaterialManFv(materialMan);
      *(undefined4 *)&materialMan->field_0x1bc = *(undefined4 *)&materialMan->field_0x124;
      addtev_full_shadow__12CMaterialManFl(materialMan,0);
    }
  }
  GXSetNumTexGens((*(uint *)&materialMan->field_0x124 & 0xff) + 1 & 0xff);
  GXSetNumTevStages(*(uint *)&materialMan->field_0x60 & 0xff);
  return;
}

