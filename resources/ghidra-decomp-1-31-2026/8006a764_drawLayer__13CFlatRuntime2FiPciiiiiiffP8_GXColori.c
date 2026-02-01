// Function: drawLayer__13CFlatRuntime2FiPciiiiiiffP8_GXColori
// Entry: 8006a764
// Size: 2040 bytes

/* WARNING: Removing unreachable block (ram,0x8006af40) */
/* WARNING: Removing unreachable block (ram,0x8006af38) */
/* WARNING: Removing unreachable block (ram,0x8006af30) */
/* WARNING: Removing unreachable block (ram,0x8006af28) */
/* WARNING: Removing unreachable block (ram,0x8006af20) */
/* WARNING: Removing unreachable block (ram,0x8006af18) */
/* WARNING: Removing unreachable block (ram,0x8006a79c) */
/* WARNING: Removing unreachable block (ram,0x8006a794) */
/* WARNING: Removing unreachable block (ram,0x8006a78c) */
/* WARNING: Removing unreachable block (ram,0x8006a784) */
/* WARNING: Removing unreachable block (ram,0x8006a77c) */
/* WARNING: Removing unreachable block (ram,0x8006a774) */

void drawLayer__13CFlatRuntime2FiPciiiiiiffP8_GXColori
               (double param_1,double param_2,CFlatRuntime2 *flatRuntime2,int param_4,
               undefined4 param_5,uint param_6,uint param_7,uint param_8,uint param_9,
               short param_10_00,short param_11_00,undefined4 *param_12,uint param_13)

{
  float fVar1;
  int iVar2;
  CTexture *texture;
  undefined4 uVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  uint uVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  undefined4 local_1b8;
  uint local_1b4;
  uint local_1b0;
  uint local_1ac;
  uint local_1a8;
  undefined auStack_1a4 [4];
  undefined auStack_1a0 [4];
  Mtx MStack_19c;
  Mat4x4 MStack_16c;
  Mtx MStack_12c;
  undefined8 local_f8;
  undefined4 local_f0;
  uint uStack_ec;
  undefined8 local_e8;
  undefined4 local_e0;
  uint uStack_dc;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined4 local_c8;
  uint uStack_c4;
  undefined4 local_c0;
  uint uStack_bc;
  undefined4 local_b8;
  uint uStack_b4;
  undefined4 local_b0;
  uint uStack_ac;
  undefined4 local_a8;
  uint uStack_a4;
  undefined4 local_a0;
  uint uStack_9c;
  undefined4 local_98;
  uint uStack_94;
  undefined4 local_90;
  uint uStack_8c;
  
  if (*(CTextureSet **)(&flatRuntime2->field_0x1774 + param_4 * 0xc) != (CTextureSet *)0x0) {
    iVar2 = Find__11CTextureSetFPc
                      (*(CTextureSet **)(&flatRuntime2->field_0x1774 + param_4 * 0xc),param_5);
    if (iVar2 < 0) {
      if (1 < (uint)System.m_execParam) {
        Printf__7CSystemFPce(&System,&DAT_801d8f88,param_5);
      }
    }
    else {
      texture = (CTexture *)
                __vc__21CPtrArray<P8CTexture>FUl
                          (*(int *)(&flatRuntime2->field_0x1774 + param_4 * 0xc) + 8,iVar2);
      GXSetNumChans(1);
      GXSetChanCtrl(0,0,0,0,0,2,1);
      GXSetChanCtrl(2,0,0,0,0,2,2);
      local_1b8 = *param_12;
      GXSetChanMatColor(4,&local_1b8);
      C_MTXOrtho(FLOAT_80330144,FLOAT_80330148,FLOAT_80330144,FLOAT_8033014c,FLOAT_80330144,
                 FLOAT_80330150,(Mtx *)&MStack_16c);
      GXSetProjection(&MStack_16c,1);
      PSMTXIdentity(&MStack_19c);
      GXLoadPosMtxImm(&MStack_19c,0);
      GXSetCurrentMtx(0);
      uVar7 = param_13 >> 1 & 2;
      if (uVar7 == 1) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,1,5);
      }
      else if (uVar7 == 2) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3,4,1,5);
      }
      else {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
      }
      GXSetZMode(0,7,0);
      PSMTXIdentity(&MStack_19c);
      GXLoadPosMtxImm(&MStack_19c,0);
      GXSetCullMode(0);
      SetTexture__11CTextureManF11_GXTexMapIDP8CTexture(&TextureMan,0,texture);
      uStack_ec = texture->field95_0x68;
      local_f8 = (double)CONCAT44(0x43300000,texture->field94_0x64);
      local_f0 = 0x43300000;
      PSMTXScale(FLOAT_80330140 / (float)(local_f8 - DOUBLE_80330158),
                 FLOAT_80330140 / (float)((double)CONCAT44(0x43300000,uStack_ec) - DOUBLE_80330158),
                 FLOAT_80330140,&MStack_12c);
      GXLoadTexMtxImm(&MStack_12c,0x1e,1);
      GXSetNumTexGens(1);
      GXSetTexCoordGen2(0,1,4,0x1e,0,0x7d);
      GXClearVtxDesc();
      GXSetVtxDesc(9,1);
      GXSetVtxDesc(0xd,1);
      GXSetVtxAttrFmt(0,9,1,4,0);
      GXSetVtxAttrFmt(0,0xd,1,3,0);
      iVar2 = SetTextureTev__11CTextureManFP8CTexture(&TextureMan,texture);
      uStack_dc = param_9 ^ 0x80000000;
      local_e8 = (double)CONCAT44(0x43300000,param_8 ^ 0x80000000);
      sVar5 = param_10_00 + (short)param_8;
      sVar6 = param_11_00 + (short)param_9;
      local_e0 = 0x43300000;
      dVar12 = (double)(float)((double)(float)(local_e8 - DOUBLE_80330160) * param_1);
      local_d8 = (double)CONCAT44(0x43300000,param_6 ^ 0x80000000);
      dVar11 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,uStack_dc) -
                                              DOUBLE_80330160) * param_2);
      fVar1 = FLOAT_80330144;
      if ((param_13 & 1) != 0) {
        fVar1 = (float)((double)FLOAT_80330154 * dVar12);
      }
      dVar10 = (double)((float)(local_d8 - DOUBLE_80330160) - fVar1);
      local_d0 = (double)CONCAT44(0x43300000,param_7 ^ 0x80000000);
      fVar1 = FLOAT_80330144;
      if ((param_13 & 1) != 0) {
        fVar1 = (float)((double)FLOAT_80330154 * dVar11);
      }
      dVar9 = (double)((float)(local_d0 - DOUBLE_80330160) - fVar1);
      dVar13 = (double)(float)(dVar10 + dVar12);
      dVar14 = (double)(float)(dVar9 + dVar11);
      if (uVar7 == 3) {
        GXSetNumTexGens(2);
        GXSetTexCoordGen2(1,1,5,0x3c,0,0x7d);
        GXClearVtxDesc();
        GXSetVtxDesc(9,1);
        GXSetVtxDesc(0xd,1);
        GXSetVtxDesc(0xe,1);
        GXSetVtxAttrFmt(0,9,1,4,0);
        GXSetVtxAttrFmt(0,0xd,1,3,0);
        GXSetVtxAttrFmt(0,0xe,1,3,1);
        GXSetNumTevStages(iVar2 + 1U & 0xff);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(iVar2,1,1,0xff);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                  (iVar2,0xf,8,0,0xf);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (iVar2,0,0,2,1,0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                  (iVar2,7,4,0,7);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                  (iVar2,0,0,0,1,0);
        dVar14 = (double)FLOAT_80330144;
        uVar7 = 0;
        dVar12 = (double)(longlong)(int)(dVar12 * (double)FLOAT_80330154);
        dVar13 = (double)(longlong)(int)(dVar11 * (double)FLOAT_80330154);
        dVar11 = DOUBLE_80330160;
        do {
          __ct__6CColorFv(auStack_1a4);
          __ct__6CColorFv(auStack_1a0);
          local_d0._4_4_ = SUB84(dVar12,0);
          local_d8._4_4_ = SUB84(dVar13,0);
          local_1a8 = local_d0._4_4_;
          local_1ac = local_d8._4_4_;
          dVar8 = dVar10;
          if ((uVar7 & 1) != 0) {
            uStack_dc = local_d0._4_4_ ^ 0x80000000;
            local_e0 = 0x43300000;
            dVar8 = (double)(float)(dVar10 + (double)(float)((double)CONCAT44(0x43300000,uStack_dc)
                                                            - DOUBLE_80330160));
          }
          local_1b0 = (uint)dVar8;
          local_e8 = (double)(longlong)(int)local_1b0;
          dVar8 = dVar9;
          if ((uVar7 & 2) != 0) {
            local_f0 = 0x43300000;
            uStack_ec = local_d8._4_4_ ^ 0x80000000;
            dVar8 = (double)(float)(dVar9 + (double)(float)((double)CONCAT44(0x43300000,uStack_ec) -
                                                           DOUBLE_80330160));
          }
          local_1b4 = (uint)dVar8;
          local_f8 = (double)(longlong)(int)local_1b4;
          sVar5 = param_10_00;
          if ((uVar7 & 1) != 0) {
            sVar5 = param_10_00 + SUB82(dVar12,0);
          }
          sVar6 = param_11_00;
          if ((uVar7 & 2) != 0) {
            sVar6 = param_11_00 + SUB82(dVar13,0);
          }
          local_d8 = dVar13;
          local_d0 = dVar12;
          uVar3 = GetBackBufferRect__8CGraphicFRiRiRiRii
                            (&Graphic,&local_1b0,&local_1b4,&local_1a8,&local_1ac,0);
          GXLoadTexObj(uVar3,1);
          GXBegin(0x80,0,4);
          uVar7 = uVar7 + 1;
          local_c8 = 0x43300000;
          uStack_c4 = local_1b0 ^ 0x80000000;
          local_c0 = 0x43300000;
          local_b0 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_c4) - dVar11);
          local_b8 = 0x43300000;
          uStack_bc = local_1b4 ^ 0x80000000;
          local_a8 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_bc) - dVar11);
          DAT_cc008000 = (float)dVar14;
          DAT_cc008000._0_2_ = sVar5;
          DAT_cc008000._0_2_ = sVar6;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000._0_2_ = 0;
          sVar4 = sVar5 + (short)local_1a8;
          uStack_b4 = local_1b0 + local_1a8 ^ 0x80000000;
          local_98 = 0x43300000;
          local_a0 = 0x43300000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_b4) - dVar11);
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_bc) - dVar11);
          DAT_cc008000 = (float)dVar14;
          DAT_cc008000._0_2_ = sVar4;
          DAT_cc008000._0_2_ = sVar6;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_b4) - dVar11);
          local_90 = 0x43300000;
          sVar6 = sVar6 + (short)local_1ac;
          uStack_9c = local_1b4 + local_1ac ^ 0x80000000;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_9c) - dVar11);
          DAT_cc008000 = (float)dVar14;
          DAT_cc008000._0_2_ = sVar4;
          DAT_cc008000._0_2_ = sVar6;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_c4) - dVar11);
          DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_9c) - dVar11);
          DAT_cc008000 = (float)dVar14;
          DAT_cc008000._0_2_ = sVar5;
          DAT_cc008000._0_2_ = sVar6;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000._0_2_ = 2;
          uStack_ac = uStack_bc;
          uStack_a4 = uStack_b4;
          uStack_94 = uStack_c4;
          uStack_8c = uStack_9c;
        } while ((int)uVar7 < 4);
      }
      else {
        GXBegin(0x80,0,4);
        DAT_cc008000 = (float)dVar10;
        DAT_cc008000 = (float)dVar9;
        DAT_cc008000 = FLOAT_80330144;
        DAT_cc008000._0_2_ = param_10_00;
        DAT_cc008000._0_2_ = param_11_00;
        DAT_cc008000 = (float)dVar13;
        DAT_cc008000 = (float)dVar9;
        DAT_cc008000 = FLOAT_80330144;
        DAT_cc008000._0_2_ = sVar5;
        DAT_cc008000._0_2_ = param_11_00;
        DAT_cc008000 = (float)dVar13;
        DAT_cc008000 = (float)dVar14;
        DAT_cc008000 = FLOAT_80330144;
        DAT_cc008000._0_2_ = sVar5;
        DAT_cc008000._0_2_ = sVar6;
        DAT_cc008000 = (float)dVar10;
        DAT_cc008000 = (float)dVar14;
        DAT_cc008000 = FLOAT_80330144;
        DAT_cc008000._0_2_ = param_10_00;
        DAT_cc008000._0_2_ = sVar6;
      }
      PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_16c);
      GXSetProjection(&MStack_16c,0);
    }
  }
  return;
}

