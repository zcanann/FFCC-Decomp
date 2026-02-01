// Function: drawScreenFade__11CGraphicPcsFv
// Entry: 80045178
// Size: 4256 bytes

/* WARNING: Removing unreachable block (ram,0x800461fc) */
/* WARNING: Removing unreachable block (ram,0x800461f4) */
/* WARNING: Removing unreachable block (ram,0x800461ec) */
/* WARNING: Removing unreachable block (ram,0x800461e4) */
/* WARNING: Removing unreachable block (ram,0x800451a0) */
/* WARNING: Removing unreachable block (ram,0x80045198) */
/* WARNING: Removing unreachable block (ram,0x80045190) */
/* WARNING: Removing unreachable block (ram,0x80045188) */

void drawScreenFade__11CGraphicPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 uVar10;
  undefined4 *puVar11;
  uint uVar12;
  undefined4 uVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  uint uVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  int local_334;
  undefined4 local_330;
  undefined4 local_32c;
  undefined4 local_328;
  undefined4 local_324;
  undefined4 local_320;
  int local_31c;
  undefined4 local_318;
  undefined4 local_314;
  undefined4 local_310;
  int local_30c;
  undefined4 local_308;
  undefined4 local_304;
  undefined4 local_300;
  undefined auStack_2fc [4];
  undefined4 local_2f8;
  int local_2f4;
  uint3 local_2f0;
  undefined uStack_2ed;
  undefined4 local_2ec;
  undefined4 local_2e8;
  Vec local_2e4;
  undefined auStack_2d8 [32];
  Mtx MStack_2b8;
  Mat4x4 MStack_288;
  Mat4x4 MStack_248;
  Mtx MStack_208;
  Mat4x4 MStack_1d8;
  undefined8 local_198;
  undefined8 local_190;
  undefined8 local_188;
  undefined4 local_180;
  uint uStack_17c;
  undefined8 local_178;
  undefined4 local_170;
  uint uStack_16c;
  undefined4 local_168;
  uint uStack_164;
  undefined4 local_160;
  uint uStack_15c;
  undefined8 local_158;
  undefined8 local_150;
  undefined8 local_148;
  undefined8 local_140;
  undefined8 local_138;
  undefined8 local_130;
  undefined4 local_128;
  uint uStack_124;
  undefined4 local_120;
  uint uStack_11c;
  undefined4 local_118;
  uint uStack_114;
  longlong local_110;
  undefined4 local_108;
  uint uStack_104;
  undefined4 local_100;
  uint uStack_fc;
  undefined4 local_f8;
  uint uStack_f4;
  longlong local_f0;
  undefined4 local_e8;
  uint uStack_e4;
  undefined4 local_e0;
  uint uStack_dc;
  undefined4 local_d8;
  uint uStack_d4;
  longlong local_d0;
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
  
  C_MTXOrtho(FLOAT_8032fb78,FLOAT_8032fb7c,FLOAT_8032fb78,FLOAT_8032fb80,FLOAT_8032fb78,
             FLOAT_8032fb84,(Mtx *)&MStack_1d8);
  GXSetProjection(&MStack_1d8,1);
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_208);
  PSMTXCopy(&MStack_208,(Mtx *)&MStack_248);
  MStack_248.value[3][2] = FLOAT_8032fb78;
  MStack_248.value[3][1] = FLOAT_8032fb78;
  MStack_248.value[3][0] = FLOAT_8032fb78;
  MStack_248.value[3][3] = FLOAT_8032fb88;
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_288);
  PSMTX44Concat(&MStack_288,&MStack_248,&MStack_288);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  GXSetVtxAttrFmt(0,0xb,1,5,0);
  GXSetVtxAttrFmt(0,0xd,1,3,1);
  PSMTXIdentity(&MStack_2b8);
  GXLoadPosMtxImm(&MStack_2b8,0);
  GXLoadTexMtxImm(&MStack_2b8,0x1e,1);
  iVar16 = 0;
  iVar17 = param_1;
  do {
    if ((*(int *)(iVar17 + 0x14) != 0) || (*(int *)(iVar17 + 4) != 0)) {
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
      GXSetZCompLoc(0);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
      GXSetZMode(0,3,0);
      GXSetCullMode(0);
      GXSetNumTevStages(1);
      GXSetNumIndStages(0);
      GXSetTevDirect(0);
      GXSetNumChans(1);
      GXSetChanCtrl(0,0,0,1,0,2,1);
      GXSetChanCtrl(2,0,0,1,0,2,2);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      puVar11 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_2fc,0xff,0xff,0xff,0xff);
      local_2f8 = *puVar11;
      GXSetChanAmbColor(4,&local_2f8);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
      local_198 = (double)CONCAT44(0x43300000,*(uint *)(iVar17 + 4) ^ 0x80000000);
      local_190 = (double)CONCAT44(0x43300000,*(uint *)(iVar17 + 8) ^ 0x80000000);
      dVar21 = (double)((float)(local_198 - DOUBLE_8032fbb0) / (float)(local_190 - DOUBLE_8032fbb0))
      ;
      if (*(int *)(iVar17 + 0x14) != 0) {
        dVar21 = (double)(float)((double)FLOAT_8032fb88 - dVar21);
      }
      dVar20 = (double)sin((double)(float)((double)FLOAT_8032fb8c * dVar21));
      dVar20 = (double)(float)dVar20;
      local_188 = (double)(longlong)(int)((double)FLOAT_8032fb90 * dVar20);
      _local_2f0 = CONCAT31(*(uint3 *)(iVar17 + 0xc),(char)(int)((double)FLOAT_8032fb90 * dVar20));
      local_2f4 = (uint)*(uint3 *)(iVar17 + 0xc) << 8;
      if (iVar16 == 3) {
        uVar15 = (uint)((double)FLOAT_8032fb94 * dVar20);
        local_188 = (double)(longlong)(int)uVar15;
        iVar14 = (int)((double)FLOAT_8032fb98 * dVar20);
        local_190 = (double)(longlong)iVar14;
        local_304 = _local_2f0;
        local_300 = _local_2f0;
        GXBegin(0x80,0,4);
        uStack_17c = uVar15 ^ 0x80000000;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_300;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000 = FLOAT_8032fb80;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_300;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000._0_2_ = 0;
        local_198 = (double)CONCAT44(0x43300000,uStack_17c);
        DAT_cc008000 = FLOAT_8032fb80;
        DAT_cc008000 = (float)(local_198 - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_304;
        local_180 = 0x43300000;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_17c) - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_304;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = 2;
        local_30c = local_2f4;
        local_308 = _local_2f0;
        GXBegin(0x80,0,4);
        uStack_16c = uVar15 ^ 0x80000000;
        uStack_164 = uVar15 + iVar14 ^ 0x80000000;
        local_178 = (double)CONCAT44(0x43300000,uStack_16c);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = (float)(local_178 - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_308;
        local_170 = 0x43300000;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000 = FLOAT_8032fb80;
        DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_16c) - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_308;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000._0_2_ = 0;
        local_168 = 0x43300000;
        DAT_cc008000 = FLOAT_8032fb80;
        DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_164) - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_30c;
        local_160 = 0x43300000;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_164) - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_30c;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = 2;
        local_314 = _local_2f0;
        local_310 = _local_2f0;
        uStack_15c = uStack_164;
        GXBegin(0x80,0,4);
        uVar15 = 0x1c0 - uVar15;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = FLOAT_8032fb7c;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_310;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000 = FLOAT_8032fb80;
        DAT_cc008000 = FLOAT_8032fb7c;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_310;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000._0_2_ = 0;
        local_158 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
        DAT_cc008000 = FLOAT_8032fb80;
        DAT_cc008000 = (float)(local_158 - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_314;
        local_150 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = (float)(local_150 - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_314;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = 2;
        local_31c = local_2f4;
        local_318 = _local_2f0;
        GXBegin(0x80,0,4);
        uVar12 = uVar15 - iVar14 ^ 0x80000000;
        local_148 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = (float)(local_148 - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_318;
        local_140 = (double)CONCAT44(0x43300000,uVar15 ^ 0x80000000);
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000 = FLOAT_8032fb80;
        DAT_cc008000 = (float)(local_140 - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_318;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000._0_2_ = 0;
        local_138 = (double)CONCAT44(0x43300000,uVar12);
        DAT_cc008000 = FLOAT_8032fb80;
        DAT_cc008000 = (float)(local_138 - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_31c;
        local_130 = (double)CONCAT44(0x43300000,uVar12);
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000._0_2_ = 2;
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = (float)(local_130 - DOUBLE_8032fbb0);
        DAT_cc008000 = FLOAT_8032fb78;
        DAT_cc008000 = local_31c;
        DAT_cc008000._0_2_ = 0;
        DAT_cc008000._0_2_ = 2;
      }
      else if (iVar16 == 2) {
        if (*(int *)(iVar17 + 0x18) == 0) {
LAB_80045874:
          local_324 = _local_2f0;
          local_320 = _local_2f0;
          GXBegin(0x80,0,4);
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = local_320;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000 = FLOAT_8032fb80;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = local_320;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000 = FLOAT_8032fb80;
          DAT_cc008000 = FLOAT_8032fb7c;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = local_324;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = FLOAT_8032fb7c;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = local_324;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000._0_2_ = 2;
        }
        else if (*(int *)(iVar17 + 0x18) == 1) {
          iVar14 = *(int *)(iVar17 + 0x1c);
          if (iVar14 == 0) goto LAB_80045874;
          local_2e4.x = *(float *)(iVar14 + 0x15c);
          local_2e4.z = *(float *)(iVar14 + 0x164);
          local_2e4.y = *(float *)(iVar14 + 0x160) + *(float *)(iVar17 + 0x20);
          PSMTX44MultVec(&MStack_288,&local_2e4,&local_2e4);
          fVar1 = FLOAT_8032fb9c * local_2e4.x + FLOAT_8032fb9c;
          fVar2 = -(FLOAT_8032fba0 * local_2e4.y - FLOAT_8032fba0);
          local_2e4.x = FLOAT_8032fb78;
          if ((FLOAT_8032fb78 <= fVar1) && (local_2e4.x = fVar1, FLOAT_8032fb80 < fVar1)) {
            local_2e4.x = FLOAT_8032fb80;
          }
          local_2e4.y = FLOAT_8032fb78;
          if ((FLOAT_8032fb78 <= fVar2) && (local_2e4.y = fVar2, FLOAT_8032fb7c < fVar2)) {
            local_2e4.y = FLOAT_8032fb7c;
          }
          local_140 = (double)(longlong)(int)local_2e4.y;
          local_138 = (double)(longlong)(int)local_2e4.x;
          iVar14 = (int)(FLOAT_8032fba4 * (float)((double)FLOAT_8032fb88 - dVar20));
          local_130 = (double)(longlong)iVar14;
          local_32c = _local_2f0;
          local_328 = _local_2f0;
          drawSFCircle__11CGraphicPcsFiiii8_GXColor8_GXColor
                    (param_1,0x500,iVar14,(int)local_2e4.x,(int)local_2e4.y,&local_328,&local_32c);
          local_148 = (double)(longlong)(int)local_2e4.x;
          local_150 = (double)(longlong)(int)local_2e4.y;
          local_334 = local_2f4;
          local_330 = _local_2f0;
          drawSFCircle__11CGraphicPcsFiiii8_GXColor8_GXColor
                    (param_1,iVar14,iVar14 + -8,(int)local_2e4.x,(int)local_2e4.y,&local_330,
                     &local_334);
        }
      }
      else if (iVar16 == 0) {
        if (*(int *)(iVar17 + 4) < *(int *)(iVar17 + 8) + -1) {
          GXSetNumTexGens(1);
          GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
          _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
          _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,0);
          GXLoadTexObj(0x80238074,0);
          dVar20 = (double)(*(float *)(iVar17 + 0x2c) * (float)((double)FLOAT_8032fb88 - dVar21));
          dVar21 = (double)sin((double)*(float *)(iVar17 + 0x24));
          dVar23 = (double)(*(float *)(iVar17 + 0x28) *
                           (float)((double)FLOAT_8032fb9c * dVar20) * (float)dVar21);
          dVar21 = (double)cos((double)*(float *)(iVar17 + 0x24));
          uVar10 = _local_2f0;
          dVar22 = (double)(float)(dVar20 + (double)FLOAT_8032fb88);
          dVar21 = (double)(*(float *)(iVar17 + 0x28) *
                           (float)((double)FLOAT_8032fba0 * dVar20) * (float)dVar21);
          GXBegin(0x80,0,4);
          fVar1 = (float)((double)FLOAT_8032fb9c + dVar23);
          fVar7 = (float)((double)FLOAT_8032fb9c * dVar22);
          fVar2 = (float)((double)FLOAT_8032fba0 + dVar21);
          fVar8 = (float)((double)FLOAT_8032fba0 * dVar22);
          fVar9 = fVar1 - fVar7;
          fVar1 = fVar1 + fVar7;
          fVar7 = fVar2 - fVar8;
          DAT_cc008000 = fVar9;
          fVar2 = fVar2 + fVar8;
          DAT_cc008000 = fVar7;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = uVar10;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000 = fVar1;
          DAT_cc008000 = fVar7;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = uVar10;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000 = fVar1;
          DAT_cc008000 = fVar2;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = uVar10;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000 = fVar9;
          DAT_cc008000 = fVar2;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = uVar10;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000._0_2_ = 2;
        }
      }
      else if ((iVar16 == 1) && (iVar14 = *(int *)(iVar17 + 0x18), iVar14 != 0)) {
        if (iVar14 == 4) {
          GXSetNumTexGens(1);
          GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
          _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0,0,4);
          _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
                    (0,0xf,8,10,0xf);
          _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (0,0,0,2,1,0);
          _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg
                    (0,7,4,5,7);
          _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
                    (0,0,0,0,1,0);
          dVar23 = (double)FLOAT_8032fba8;
          uVar15 = 0;
          dVar22 = (double)FLOAT_8032fb78;
          dVar21 = DOUBLE_8032fbb0;
          dVar20 = DOUBLE_8032fbb8;
          do {
            __ct__6CColorFv(&local_2ec);
            __ct__6CColorFv(&local_2e8);
            uVar19 = -(uVar15 & 1) & 0x140;
            uVar18 = -(uVar15 >> 1 & 1) & 0xe0;
            uVar12 = -((int)-(uVar15 & 2) >> 0x1f);
            GetBackBufferRect2__8CGraphicFPvP9_GXTexObjiiiii12_GXTexFilter9_GXTexFmti
                      (&Graphic,DAT_80238030,auStack_2d8,uVar19,uVar18,0x140,0xe0,0,0,6,0);
            GXLoadTexObj(auStack_2d8,0);
            uStack_11c = (uint)*(byte *)(iVar17 + 0xc);
            uStack_124 = (uint)*(byte *)(iVar17 + 0x10);
            uStack_16c = (uint)*(byte *)(iVar17 + 0xd);
            uStack_15c = (uint)*(byte *)(iVar17 + 0x11);
            uStack_dc = (uint)*(byte *)(iVar17 + 0xe);
            uStack_17c = (uint)*(byte *)(iVar17 + 0x12);
            _local_2f0 = *(undefined4 *)(iVar17 + 0xc);
            local_130 = (double)CONCAT44(0x43300000,uVar12 ^ 0x80000000);
            local_2f4 = *(int *)(iVar17 + 0x10);
            local_140 = (double)CONCAT44(0x43300000,uStack_124);
            fVar1 = (float)((double)(float)(local_130 - dVar21) * dVar23);
            local_148 = (double)CONCAT44(0x43300000,uStack_11c);
            local_160 = 0x43300000;
            local_168 = 0x43300000;
            local_180 = 0x43300000;
            local_188 = (double)CONCAT44(0x43300000,uStack_dc);
            local_150 = (double)CONCAT44(0x43300000,uStack_11c);
            local_170 = 0x43300000;
            local_190 = (double)CONCAT44(0x43300000,uStack_dc);
            iVar14 = (int)(fVar1 * ((float)(local_140 - dVar20) - (float)(local_148 - dVar20)) +
                          (float)(local_150 - dVar20));
            local_158 = (double)(longlong)iVar14;
            iVar3 = (int)(fVar1 * ((float)((double)CONCAT44(0x43300000,uStack_15c) - dVar20) -
                                  (float)((double)CONCAT44(0x43300000,uStack_16c) - dVar20)) +
                         (float)((double)CONCAT44(0x43300000,uStack_16c) - dVar20));
            local_178 = (double)(longlong)iVar3;
            local_138 = (double)CONCAT44(0x43300000,uVar12 + 1 ^ 0x80000000);
            iVar4 = (int)(fVar1 * ((float)((double)CONCAT44(0x43300000,uStack_17c) - dVar20) -
                                  (float)(local_188 - dVar20)) + (float)(local_190 - dVar20));
            local_198 = (double)(longlong)iVar4;
            fVar1 = (float)((double)(float)(local_138 - dVar21) * dVar23);
            local_128 = 0x43300000;
            local_120 = 0x43300000;
            local_108 = 0x43300000;
            local_100 = 0x43300000;
            local_e8 = 0x43300000;
            local_e0 = 0x43300000;
            local_118 = 0x43300000;
            local_f8 = 0x43300000;
            local_d8 = 0x43300000;
            iVar5 = (int)(fVar1 * ((float)((double)CONCAT44(0x43300000,uStack_124) - dVar20) -
                                  (float)((double)CONCAT44(0x43300000,uStack_11c) - dVar20)) +
                         (float)((double)CONCAT44(0x43300000,uStack_11c) - dVar20));
            local_110 = (longlong)iVar5;
            iVar6 = (int)(fVar1 * ((float)((double)CONCAT44(0x43300000,uStack_15c) - dVar20) -
                                  (float)((double)CONCAT44(0x43300000,uStack_16c) - dVar20)) +
                         (float)((double)CONCAT44(0x43300000,uStack_16c) - dVar20));
            local_f0 = (longlong)iVar6;
            local_2ec = CONCAT31(CONCAT21(CONCAT11((char)iVar14,(char)iVar3),(char)iVar4),0xff);
            iVar14 = (int)(fVar1 * ((float)((double)CONCAT44(0x43300000,uStack_17c) - dVar20) -
                                   (float)((double)CONCAT44(0x43300000,uStack_dc) - dVar20)) +
                          (float)((double)CONCAT44(0x43300000,uStack_dc) - dVar20));
            local_d0 = (longlong)iVar14;
            local_2e8 = CONCAT31(CONCAT21(CONCAT11((char)iVar5,(char)iVar6),(char)iVar14),0xff);
            uStack_164 = uStack_16c;
            uStack_114 = uStack_11c;
            uStack_104 = uStack_15c;
            uStack_fc = uStack_16c;
            uStack_f4 = uStack_16c;
            uStack_e4 = uStack_17c;
            uStack_d4 = uStack_dc;
            GXBegin(0x80,0,4);
            uStack_c4 = uVar19 ^ 0x80000000;
            uStack_bc = uVar18 ^ 0x80000000;
            uStack_b4 = uVar19 + 0x140 ^ 0x80000000;
            uVar15 = uVar15 + 1;
            local_c8 = 0x43300000;
            uStack_9c = uVar18 + 0xe0 ^ 0x80000000;
            local_c0 = 0x43300000;
            DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_c4) - dVar21);
            DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_bc) - dVar21);
            DAT_cc008000 = (float)dVar22;
            local_b8 = 0x43300000;
            DAT_cc008000 = local_2ec;
            DAT_cc008000._0_2_ = 0;
            DAT_cc008000._0_2_ = 0;
            local_b0 = 0x43300000;
            DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_b4) - dVar21);
            DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_bc) - dVar21);
            DAT_cc008000 = (float)dVar22;
            local_a8 = 0x43300000;
            DAT_cc008000 = local_2ec;
            DAT_cc008000._0_2_ = 2;
            DAT_cc008000._0_2_ = 0;
            local_a0 = 0x43300000;
            DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_b4) - dVar21);
            DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_9c) - dVar21);
            DAT_cc008000 = (float)dVar22;
            local_98 = 0x43300000;
            DAT_cc008000 = local_2e8;
            DAT_cc008000._0_2_ = 2;
            DAT_cc008000._0_2_ = 2;
            local_90 = 0x43300000;
            DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_c4) - dVar21);
            DAT_cc008000 = (float)((double)CONCAT44(0x43300000,uStack_9c) - dVar21);
            DAT_cc008000 = (float)dVar22;
            DAT_cc008000 = local_2e8;
            DAT_cc008000._0_2_ = 0;
            DAT_cc008000._0_2_ = 2;
            uStack_ac = uStack_bc;
            uStack_a4 = uStack_b4;
            uStack_94 = uStack_c4;
            uStack_8c = uStack_9c;
          } while ((int)uVar15 < 4);
        }
        else {
          if (iVar14 == 2) {
            _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,1,5);
          }
          else if (iVar14 == 3) {
            _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(3,4,1,5);
          }
          uVar13 = *(undefined4 *)(iVar17 + 0x10);
          uVar10 = *(undefined4 *)(iVar17 + 0xc);
          GXBegin(0x80,0,4);
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = uVar10;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000 = FLOAT_8032fb80;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = uVar10;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000 = FLOAT_8032fb80;
          DAT_cc008000 = FLOAT_8032fb7c;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = uVar13;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000._0_2_ = 2;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = FLOAT_8032fb7c;
          DAT_cc008000 = FLOAT_8032fb78;
          DAT_cc008000 = uVar13;
          DAT_cc008000._0_2_ = 0;
          DAT_cc008000._0_2_ = 2;
        }
      }
    }
    iVar16 = iVar16 + 1;
    iVar17 = iVar17 + 0x2c;
    if (3 < iVar16) {
      PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_1d8);
      GXSetProjection(&MStack_1d8,0);
      return;
    }
  } while( true );
}

