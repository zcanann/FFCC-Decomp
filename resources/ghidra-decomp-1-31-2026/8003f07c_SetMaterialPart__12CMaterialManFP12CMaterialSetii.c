// Function: SetMaterialPart__12CMaterialManFP12CMaterialSetii
// Entry: 8003f07c
// Size: 2768 bytes

void SetMaterialPart__12CMaterialManFP12CMaterialSetii
               (CMaterialMan *materialMan,CMaterialSet *materialSet,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  *(undefined4 *)&materialMan->field_0x11c = *(undefined4 *)&materialMan->field_0x128;
  *(undefined4 *)&materialMan->field_0x134 = *(undefined4 *)&materialMan->field_0x128;
  *(undefined4 *)&materialMan->field_0x120 = *(undefined4 *)&materialMan->field_0x12c;
  *(undefined4 *)&materialMan->field_0x138 = *(undefined4 *)&materialMan->field_0x12c;
  *(undefined4 *)&materialMan->field_0x124 = *(undefined4 *)&materialMan->field_0x130;
  *(undefined4 *)&materialMan->field_0x13c = *(undefined4 *)&materialMan->field_0x130;
  *(undefined4 *)&materialMan->field_0x48 = *(undefined4 *)&materialMan->field_0x40;
  iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,param_3);
  Set__9CMaterialF11_GXTexMapID(iVar1,*(undefined4 *)&materialMan->field_0x11c);
  uVar3 = *(uint *)&materialMan->field_0x48 & *(uint *)(iVar1 + 0x24);
  if (*(uint *)&materialMan->field_0x44 == uVar3) {
    if ((uVar3 & 0x200) != 0) {
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                (1,*(undefined4 *)&materialMan->field_0x13c,*(int *)&materialMan->field_0x134 + 1,
                 0xff);
    }
  }
  else {
    *(uint *)&materialMan->field_0x44 = uVar3;
    GXSetArray(10,*(undefined4 *)&materialMan->field_0x4,6);
    GXSetNumIndStages(0);
    GXSetTevDirect(0);
    if ((uVar3 & 0x400) == 0) {
      if ((uVar3 & 1) != 0) {
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (0,0xf,0xc,10,0xf);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,0,0,1,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (0,7,6,5,7);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (0,0,0,2,1,0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
        *(undefined4 *)&materialMan->field_0x60 = 1;
        if ((materialMan->field_0x4c != '\x03') && (param_4 != 0)) {
          GXClearVtxDesc();
          GXSetVtxDesc(9,3);
          GXSetVtxDesc(10,3);
          GXSetVtxDesc(0xb,3);
          materialMan->field_0x4c = 3;
        }
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        return;
      }
      if ((uVar3 & 0x200) == 0) {
        if ((uVar3 & 0x800) == 0) {
          if ((uVar3 & 0x20) == 0) {
            GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (0,*(undefined4 *)&materialMan->field_0x13c,
                       *(undefined4 *)&materialMan->field_0x134,4);
          }
          else {
            *(int *)&materialMan->field_0x124 = *(int *)&materialMan->field_0x124 + -1;
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (0,*(undefined4 *)&materialMan->field_0x148,
                       *(undefined4 *)&materialMan->field_0x134,4);
          }
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (0,0xf,8,10,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (0,0,0,1,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (0,7,4,5,7);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (0,0,0,2,1,0);
          _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
          *(undefined4 *)&materialMan->field_0x60 = 1;
          if (uVar3 == 0) {
            if ((materialMan->field_0x4c != '\0') && (param_4 != 0)) {
              GXClearVtxDesc();
              GXSetVtxDesc(9,3);
              GXSetVtxDesc(10,3);
              GXSetVtxDesc(0xb,3);
              GXSetVtxDesc(0xd,3);
              materialMan->field_0x4c = 0;
            }
          }
          else if ((uVar3 & 2) == 0) {
            if ((materialMan->field_0x4c != '\0') && (param_4 != 0)) {
              GXClearVtxDesc();
              GXSetVtxDesc(9,3);
              GXSetVtxDesc(10,3);
              GXSetVtxDesc(0xb,3);
              GXSetVtxDesc(0xd,3);
              materialMan->field_0x4c = 0;
            }
          }
          else {
            if ((materialMan->field_0x4c != '\x02') && (param_4 != 0)) {
              GXClearVtxDesc();
              GXSetVtxDesc(9,3);
              GXSetVtxDesc(10,3);
              GXSetVtxDesc(0xb,3);
              GXSetVtxDesc(0xd,3);
              GXSetVtxDesc(0xe,3);
              materialMan->field_0x4c = 2;
            }
            if ((uVar3 & 0x40) == 0) {
              *(int *)&materialMan->field_0x124 = *(int *)&materialMan->field_0x124 + 1;
              uVar2 = *(undefined4 *)&materialMan->field_0x124;
              GXSetTexCoordGen2(uVar2,1,5,0x3c,0,0x7d);
            }
            else {
              uVar2 = *(undefined4 *)&materialMan->field_0x154;
            }
            *(undefined4 *)&materialMan->field_0x60 = 1;
            GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (*(undefined4 *)&materialMan->field_0x60,uVar2,
                       (*(uint *)&materialMan->field_0x134 & 0xff) + 1,4);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                      (*(undefined4 *)&materialMan->field_0x60,0xf,8,10,0xf);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (*(undefined4 *)&materialMan->field_0x60,0,0,1,1,1);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                      (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                      (*(undefined4 *)&materialMan->field_0x60,0,0);
            *(uint *)&materialMan->field_0x60 =
                 (*(uint *)&materialMan->field_0x60 & 0xff) + 1 & 0xff;
            GXSetTevDirect(*(undefined4 *)&materialMan->field_0x60);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (*(undefined4 *)&materialMan->field_0x60,uVar2,
                       (*(uint *)&materialMan->field_0x134 & 0xff) + 1,0xff);
            _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                      (*(undefined4 *)&materialMan->field_0x60,0,2,9,0xf);
            _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (*(undefined4 *)&materialMan->field_0x60,0,0,1,1,0);
            _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                      (*(undefined4 *)&materialMan->field_0x60,7,7,7,0);
            _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                      (*(undefined4 *)&materialMan->field_0x60,0,0,0,1,0);
            _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
                      (*(undefined4 *)&materialMan->field_0x60,0,0);
            *(uint *)&materialMan->field_0x60 =
                 (*(uint *)&materialMan->field_0x60 & 0xff) + 1 & 0xff;
          }
        }
        else {
          if ((uVar3 & 0x20) == 0) {
            GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (0,*(undefined4 *)&materialMan->field_0x13c,
                       *(undefined4 *)&materialMan->field_0x134,4);
          }
          else {
            *(int *)&materialMan->field_0x124 = *(int *)&materialMan->field_0x124 + -1;
            _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                      (0,*(undefined4 *)&materialMan->field_0x148,
                       *(undefined4 *)&materialMan->field_0x134,4);
          }
          _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                    (1,3,3,3,0);
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (0,0xf,8,10,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (0,0,0,1,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (0,7,4,5,7);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (0,0,0,2,1,0);
          _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,1);
          *(undefined4 *)&materialMan->field_0x60 = 1;
          if ((materialMan->field_0x4c != '\0') && (param_4 != 0)) {
            GXClearVtxDesc();
            GXSetVtxDesc(9,3);
            GXSetVtxDesc(10,3);
            GXSetVtxDesc(0xb,3);
            GXSetVtxDesc(0xd,3);
            materialMan->field_0x4c = 0;
          }
        }
      }
      else {
        local_20 = 0xffff0000;
        *(int *)&materialMan->field_0x11c = *(int *)&materialMan->field_0x11c + 1;
        local_1c = 0xffff;
        local_24 = 0xffff0000;
        GXSetTevColor(2,&local_24);
        local_28 = local_1c;
        GXSetTevColor(3,&local_28);
        if ((uVar3 & 0x20) == 0) {
          GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
        }
        else {
          *(int *)&materialMan->field_0x124 = *(int *)&materialMan->field_0x124 + -1;
          *(undefined4 *)&materialMan->field_0x13c = *(undefined4 *)&materialMan->field_0x148;
        }
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
                  (0,*(undefined4 *)&materialMan->field_0x13c,
                   *(undefined4 *)&materialMan->field_0x134,0xff);
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
                  (2,0,0,1,1,0);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (2,0,0,2,1,0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2,0xff,0xff,4);
        *(undefined4 *)&materialMan->field_0x60 = 3;
        if ((materialMan->field_0x4c != '\0') && (param_4 != 0)) {
          GXClearVtxDesc();
          GXSetVtxDesc(9,3);
          GXSetVtxDesc(10,3);
          GXSetVtxDesc(0xb,3);
          GXSetVtxDesc(0xd,3);
          materialMan->field_0x4c = 0;
        }
      }
    }
    else {
      if ((uVar3 & 0x20) == 0) {
        GXSetTexCoordGen2(*(undefined4 *)&materialMan->field_0x13c,1,4,0x3c,0,0x7d);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                  (0,*(undefined4 *)&materialMan->field_0x13c,
                   *(undefined4 *)&materialMan->field_0x134,4);
      }
      else {
        *(int *)&materialMan->field_0x124 = *(int *)&materialMan->field_0x124 + -1;
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                  (0,*(undefined4 *)&materialMan->field_0x148,
                   *(undefined4 *)&materialMan->field_0x134,4);
      }
      _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                (0,0xf,0xc,10,0xf);
      _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,1,1,0);
      _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                (0,7,4,5,7);
      _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                (0,0,0,2,1,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      *(undefined4 *)&materialMan->field_0x60 = 1;
      if ((materialMan->field_0x4c != '\0') && (param_4 != 0)) {
        GXClearVtxDesc();
        GXSetVtxDesc(9,3);
        GXSetVtxDesc(10,3);
        GXSetVtxDesc(0xb,3);
        GXSetVtxDesc(0xd,3);
        materialMan->field_0x4c = 0;
      }
    }
    GXSetNumTexGens((*(uint *)&materialMan->field_0x124 & 0xff) + 1 & 0xff);
    GXSetNumTevStages(*(uint *)&materialMan->field_0x60 & 0xff);
  }
  return;
}

