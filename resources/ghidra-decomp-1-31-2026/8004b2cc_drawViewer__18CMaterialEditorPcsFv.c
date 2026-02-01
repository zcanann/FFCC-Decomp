// Function: drawViewer__18CMaterialEditorPcsFv
// Entry: 8004b2cc
// Size: 3068 bytes

void drawViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs)

{
  float fVar1;
  float fVar2;
  ushort uVar3;
  short sVar4;
  ushort uVar5;
  double dVar6;
  int *piVar7;
  ushort *puVar8;
  int iVar9;
  int iVar10;
  byte bVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  byte bVar14;
  undefined4 uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  _ZLISTITEM *local_80;
  undefined4 local_7c;
  undefined4 local_78;
  uint local_74 [5];
  uint local_60;
  uint local_5c;
  uint local_58;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  if (DAT_8032ed1c == '\0') {
    DAT_8032ed18 = &DAT_8032fcb4;
    DAT_8032ed1c = '\x01';
  }
  if (DAT_8032ed24 == '\0') {
    DAT_8032ed20 = 0;
    DAT_8032ed24 = '\x01';
  }
  DAT_8032ed20 = DAT_8032ed20 + 1;
  iVar17 = DAT_8032ed20 >> 0x1f;
  Printf__8CGraphicFPce
            (&Graphic,s_MaterialEditor___c__801d7d60,
             (int)(char)DAT_8032ed18
                        [(iVar17 * 4 | (uint)((DAT_8032ed20 >> 4) * 0x40000000 + iVar17) >> 0x1e) -
                         iVar17]);
  if (*(int *)&materialEditorPcs->field_0xe8 == 0) {
    local_80 = (materialEditorPcs->zlistA).m_root.m_previous;
    while (local_80 != (_ZLISTITEM *)0x0) {
      piVar7 = (int *)GetDataNext__5ZLISTFPP10_ZLISTITEM(&materialEditorPcs->zlistA,&local_80);
      iVar18 = *piVar7;
      GXSetArray(9,*(undefined4 *)(iVar18 + 0x10),0xc);
      GXSetArray(10,*(undefined4 *)(iVar18 + 0x14),0xc);
      GXSetNumChans(1);
      GXClearVtxDesc();
      GXSetChanCtrl(0,0,0,1,0,2,1);
      GXSetChanCtrl(2,0,0,1,0,0,2);
      GXSetNumTevStages(1);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0);
      GXSetZMode(1,3,1);
      local_84 = DAT_8032fca8;
      local_88 = DAT_8032fca8;
      GXSetChanAmbColor(0,&local_88);
      local_8c = local_84;
      GXSetChanMatColor(0,&local_8c);
      GXSetVtxDesc(9,3);
      GXSetVtxDesc(10,3);
      GXSetVtxDesc(0xb,2);
      GXSetVtxDesc(0xd,3);
      GXSetVtxAttrFmt(0,9,1,4,0);
      GXSetVtxAttrFmt(0,10,0,4,0);
      GXSetVtxAttrFmt(0,0xb,1,5,0);
      GXSetVtxAttrFmt(0,0xd,1,4,0);
      GXSetNumTexGens(1);
      GXSetNumTevStages(1);
      GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
      iVar17 = 0;
      do {
        iVar19 = 0;
        for (uVar16 = 0; uVar16 < *(uint *)(iVar18 + 8); uVar16 = uVar16 + 1) {
          if ((*(ushort *)(*(int *)(iVar18 + 0x18) + iVar19) & 0x200) == 0) {
            GXSetCullMode(2);
          }
          else {
            GXSetCullMode(0);
          }
          if (iVar17 == 1) {
            puVar8 = (ushort *)(*(int *)(iVar18 + 0x18) + iVar19);
            if ((*puVar8 & 0x400) != 0) {
              uVar5 = puVar8[1];
              uVar12 = 1;
              uVar13 = 1;
              uVar15 = 1;
              uVar3 = uVar5 >> 2 & 3;
              if (((uVar5 & 3) == 0) && (uVar3 == 0)) {
                uVar12 = 4;
                uVar13 = 5;
              }
              else if (((uVar5 & 3) == 0) && (uVar3 == 2)) {
                uVar12 = 4;
                uVar13 = 1;
              }
              else if (((uVar5 & 3) == 2) && (uVar3 == 0)) {
                uVar15 = 3;
                uVar12 = 1;
                uVar13 = 1;
              }
              GXSetZCompLoc(0);
              _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0);
              _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp
                        (uVar15,uVar12,uVar13,3);
              GXSetZMode(1,3,0);
              GXSetCullMode(0);
              goto LAB_8004b680;
            }
          }
          else {
            if (iVar17 == 0) {
              if ((*(ushort *)(*(int *)(iVar18 + 0x18) + iVar19) & 0x400) != 0) goto LAB_8004be88;
              GXSetZMode(1,3,1);
              _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,0,0,7);
            }
LAB_8004b680:
            bVar14 = 3;
            puVar8 = (ushort *)(*(int *)(iVar18 + 0x18) + iVar19);
            uVar5 = *puVar8;
            if ((*(char *)((int)puVar8 + 0x19) == 'H') &&
               ((int)(short)puVar8[0xf] < (int)(char)materialEditorPcs->field_0x3bc)) {
              uVar3 = puVar8[0x10];
              iVar10 = *(int *)((int)(&materialEditorPcs->m_unkMatrix + 2) +
                               (short)puVar8[0xf] * 4 + 0x10);
              fVar1 = (float)(DOUBLE_8032fcc0 /
                             ((double)CONCAT44(0x43300000,(int)*(short *)(iVar10 + 4) ^ 0x80000000)
                             - DOUBLE_8032fcd0));
              fVar2 = (float)(DOUBLE_8032fcc0 /
                             ((double)CONCAT44(0x43300000,(int)*(short *)(iVar10 + 6) ^ 0x80000000)
                             - DOUBLE_8032fcd0));
              if ((short)uVar3 < 0) {
                *(float *)(puVar8 + 0x28) =
                     fVar1 * (float)((double)CONCAT44(0x43300000,(int)(short)uVar3 ^ 0x80000000) -
                                    DOUBLE_8032fcd0) + FLOAT_8032fcc8;
              }
              else {
                *(float *)(puVar8 + 0x28) =
                     fVar1 * (float)((double)CONCAT44(0x43300000,(int)(short)uVar3 ^ 0x80000000) -
                                    DOUBLE_8032fcd0);
              }
              iVar9 = *(int *)(iVar18 + 0x18) + iVar19;
              sVar4 = *(short *)(iVar9 + 0x24);
              if (sVar4 < 0) {
                *(float *)(iVar9 + 0x58) =
                     fVar1 * (float)((double)CONCAT44(0x43300000,(int)sVar4 ^ 0x80000000) -
                                    DOUBLE_8032fcd0) + FLOAT_8032fcc8;
              }
              else {
                *(float *)(iVar9 + 0x58) =
                     fVar1 * (float)((double)CONCAT44(0x43300000,(int)sVar4 ^ 0x80000000) -
                                    DOUBLE_8032fcd0);
              }
              iVar9 = *(int *)(iVar18 + 0x18) + iVar19;
              sVar4 = *(short *)(iVar9 + 0x28);
              if (sVar4 < 0) {
                *(float *)(iVar9 + 0x60) =
                     fVar1 * (float)((double)CONCAT44(0x43300000,(int)sVar4 ^ 0x80000000) -
                                    DOUBLE_8032fcd0) + FLOAT_8032fcc8;
              }
              else {
                *(float *)(iVar9 + 0x60) =
                     fVar1 * (float)((double)CONCAT44(0x43300000,(int)sVar4 ^ 0x80000000) -
                                    DOUBLE_8032fcd0);
              }
              iVar9 = *(int *)(iVar18 + 0x18) + iVar19;
              sVar4 = *(short *)(iVar9 + 0x2c);
              if (sVar4 < 0) {
                *(float *)(iVar9 + 0x68) =
                     fVar1 * (float)((double)CONCAT44(0x43300000,(int)sVar4 ^ 0x80000000) -
                                    DOUBLE_8032fcd0) + FLOAT_8032fcc8;
              }
              else {
                *(float *)(iVar9 + 0x68) =
                     fVar1 * (float)((double)CONCAT44(0x43300000,(int)sVar4 ^ 0x80000000) -
                                    DOUBLE_8032fcd0);
              }
              sVar4 = *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x22);
              if (sVar4 < 0) {
                *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x22) = -sVar4;
              }
              sVar4 = *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x26);
              if (sVar4 < 0) {
                *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x26) = -sVar4;
              }
              sVar4 = *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x2a);
              if (sVar4 < 0) {
                *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x2a) = -sVar4;
              }
              sVar4 = *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x2e);
              if (sVar4 < 0) {
                *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x2e) = -sVar4;
              }
              dVar6 = DOUBLE_8032fcd0;
              fVar1 = FLOAT_8032fcc8;
              local_48 = 0x43300000;
              iVar9 = *(int *)(iVar18 + 0x18) + iVar19;
              uStack_44 = (int)*(short *)(iVar9 + 0x22) ^ 0x80000000;
              local_50 = 0x43300000;
              local_40 = 0x43300000;
              local_38 = 0x43300000;
              *(float *)(iVar9 + 0x54) =
                   -(fVar2 * (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8032fcd0) -
                    FLOAT_8032fcc8);
              iVar9 = *(int *)(iVar18 + 0x18) + iVar19;
              uStack_4c = (int)*(short *)(iVar9 + 0x26) ^ 0x80000000;
              *(float *)(iVar9 + 0x5c) =
                   -(fVar2 * (float)((double)CONCAT44(0x43300000,uStack_4c) - dVar6) - fVar1);
              iVar9 = *(int *)(iVar18 + 0x18) + iVar19;
              uStack_3c = (int)*(short *)(iVar9 + 0x2a) ^ 0x80000000;
              *(float *)(iVar9 + 100) =
                   -(fVar2 * (float)((double)CONCAT44(0x43300000,uStack_3c) - dVar6) - fVar1);
              iVar9 = *(int *)(iVar18 + 0x18) + iVar19;
              uStack_34 = (int)*(short *)(iVar9 + 0x2e) ^ 0x80000000;
              *(float *)(iVar9 + 0x6c) =
                   -(fVar2 * (float)((double)CONCAT44(0x43300000,uStack_34) - dVar6) - fVar1);
              DCStoreRange(*(int *)(iVar18 + 0x18) + iVar19,0x70);
              if (*(short *)(iVar10 + 2) == 0x20) {
                GXSetNumTevStages(1);
                GXSetNumTexGens(1);
                GXLoadTexObj(*(undefined4 *)
                              ((int)(&materialEditorPcs->m_unkMatrix + 1) +
                              *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x1e) * 4));
                _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                          (0,0xf,8,10,0xf);
                _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (0,0,0,0,1,0);
                _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                          (0,7,4,5,7);
                _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                          (0,0,0,1,1,0);
              }
              if ((*(short *)(iVar10 + 2) == 4) || (*(short *)(iVar10 + 2) == 8)) {
                GXSetNumTevStages(3);
                GXSetNumTexGens(1);
                local_7c = 0xffff0000;
                local_78 = 0xffff;
                local_90 = 0xffff0000;
                GXSetTevColor(2,&local_90);
                local_94 = local_78;
                GXSetTevColor(3,&local_94);
                GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
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
                          (0,0,0,0xff);
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
                          (1,0,1,0xff);
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
                _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
                          (2,0xff,0xff,4);
                GXInitTexObjTlut(*(undefined4 *)
                                  ((int)(&materialEditorPcs->m_unkMatrix + 1) +
                                  *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x1e) * 4),0);
                GXLoadTexObj(*(undefined4 *)
                              ((int)(&materialEditorPcs->m_unkMatrix + 1) +
                              *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x1e) * 4),0);
                GXInitTexObjTlut(*(undefined4 *)
                                  ((int)(&materialEditorPcs->m_unkMatrix + 1) +
                                  *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x1e) * 4),1);
                GXLoadTexObj(*(undefined4 *)
                              ((int)(&materialEditorPcs->m_unkMatrix + 1) +
                              *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x1e) * 4),1);
                GXLoadTlut(*(undefined4 *)
                            (&materialEditorPcs->field_0x33c +
                            *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x1e) * 4),0);
                GXLoadTlut(*(undefined4 *)
                            (&materialEditorPcs->field_0x37c +
                            *(short *)(*(int *)(iVar18 + 0x18) + iVar19 + 0x1e) * 4),1);
              }
            }
            GXSetVtxDesc(10,3);
            GXSetVtxDesc(0xd,3);
            GXSetArray(0xb,*(int *)(iVar18 + 0x18) + iVar19 + 0x30,4);
            GXSetArray(0xd,*(int *)(iVar18 + 0x18) + iVar19 + 0x50,8);
            iVar10 = *(int *)(iVar18 + 0x18);
            local_74[4] = (uint)*(ushort *)(iVar10 + iVar19 + 8);
            local_60 = (uint)*(ushort *)(iVar10 + iVar19 + 10);
            local_5c = (uint)*(ushort *)(iVar10 + iVar19 + 0xc);
            local_74[0] = 0;
            local_74[1] = 1;
            local_74[2] = 2;
            if ((uVar5 & 0xf) == 0) {
              GXBegin(0x90,0,3);
            }
            if ((uVar5 & 0xf) == 1) {
              GXBegin(0x80,0,4);
              bVar14 = 4;
              local_5c = (uint)*(ushort *)(*(int *)(iVar18 + 0x18) + iVar19 + 0xe);
              local_58 = (uint)*(ushort *)(*(int *)(iVar18 + 0x18) + iVar19 + 0xc);
              local_74[2] = 3;
              local_74[3] = 2;
            }
            bVar11 = 0;
            while (bVar11 < bVar14) {
              DAT_cc008000._0_2_ = (short)local_74[bVar11 + 4];
              DAT_cc008000._0_2_ = (short)local_74[bVar11 + 4];
              DAT_cc008000._0_1_ = (char)local_74[bVar11];
              DAT_cc008000._0_2_ = (short)local_74[bVar11];
              bVar11 = bVar11 + 1;
            }
          }
LAB_8004be88:
          iVar19 = iVar19 + 0x70;
        }
        iVar17 = iVar17 + 1;
      } while (iVar17 < 2);
    }
  }
  return;
}

