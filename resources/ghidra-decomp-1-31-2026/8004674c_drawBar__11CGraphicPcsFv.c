// Function: drawBar__11CGraphicPcsFv
// Entry: 8004674c
// Size: 2812 bytes

/* WARNING: Removing unreachable block (ram,0x8004722c) */
/* WARNING: Removing unreachable block (ram,0x80047224) */
/* WARNING: Removing unreachable block (ram,0x8004721c) */
/* WARNING: Removing unreachable block (ram,0x80047214) */
/* WARNING: Removing unreachable block (ram,0x80046774) */
/* WARNING: Removing unreachable block (ram,0x8004676c) */
/* WARNING: Removing unreachable block (ram,0x80046764) */
/* WARNING: Removing unreachable block (ram,0x8004675c) */

void drawBar__11CGraphicPcsFv(void)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  bool bVar4;
  int32_t iVar5;
  undefined4 uVar6;
  int iVar7;
  COrder *pCVar8;
  undefined4 *puVar9;
  undefined2 uVar10;
  uint uVar11;
  short sVar12;
  int iVar13;
  uint32_t uVar14;
  int iVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  undefined auStack_338 [4];
  undefined auStack_334 [4];
  undefined4 local_330;
  undefined4 local_32c;
  undefined4 local_328;
  undefined auStack_324 [4];
  undefined auStack_320 [4];
  undefined4 local_31c;
  undefined4 local_318;
  undefined4 local_314;
  undefined4 local_310;
  undefined4 local_30c;
  undefined4 local_308;
  undefined4 local_304;
  undefined4 local_300;
  undefined4 local_2fc;
  undefined4 local_2f8;
  undefined4 local_2f4;
  undefined4 local_2f0;
  Mtx MStack_2ec;
  Mat4x4 MStack_2bc;
  char acStack_27c [256];
  char acStack_17c [260];
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  
  C_MTXOrtho(FLOAT_8032fb78,FLOAT_8032fb7c,FLOAT_8032fb78,FLOAT_8032fb80,FLOAT_8032fb78,
             FLOAT_8032fb84,(Mtx *)&MStack_2bc);
  GXSetProjection(&MStack_2bc,1);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  GXSetZCompLoc(0);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6,1,0,7,0);
  GXSetZMode(0,3,0);
  GXSetCullMode(0);
  GXSetNumTevStages(1);
  GXSetTevDirect(0);
  GXSetNumChans(1);
  GXSetChanCtrl(0,0,0,1,0,2,1);
  GXSetChanCtrl(2,0,0,1,0,2,2);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(0xb,1);
  GXSetVtxDesc(0xd,1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  GXSetVtxAttrFmt(0,0xb,1,5,0);
  GXSetVtxAttrFmt(0,0xd,1,3,1);
  PSMTXIdentity(&MStack_2ec);
  GXLoadPosMtxImm(&MStack_2ec,0);
  GXLoadTexMtxImm(&MStack_2ec,0x1e,1);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  bVar4 = false;
  bVar3 = false;
  if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
    bVar3 = true;
  }
  if (bVar3) {
    iVar7 = 0;
  }
  else {
    countLeadingZeros(Pad._448_4_);
    iVar7 = Pad._60_4_;
  }
  if ((iVar7 != 0) && (iVar7 = GetPadType__6JoyBusFi(&Joybus,0), iVar7 != 0x40000)) {
    bVar4 = true;
  }
  dVar16 = (double)FLOAT_8032fbc4;
  local_2f0 = DAT_8032fb74;
  local_2f8 = DAT_8032fb74;
  local_2f4 = DAT_8032fb74;
  GXBegin(0x80,0,4);
  DAT_cc008000 = FLOAT_8032fbc4;
  DAT_cc008000 = FLOAT_8032fbc8;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = local_2f4;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = FLOAT_8032fbcc;
  DAT_cc008000 = FLOAT_8032fbc8;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = local_2f4;
  DAT_cc008000._0_2_ = 2;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = FLOAT_8032fbcc;
  DAT_cc008000 = FLOAT_8032fbd0;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = local_2f8;
  DAT_cc008000._0_2_ = 2;
  DAT_cc008000._0_2_ = 2;
  DAT_cc008000 = FLOAT_8032fbc4;
  DAT_cc008000 = FLOAT_8032fbd0;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = local_2f8;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 2;
  pCVar8 = (COrder *)GetFirstOrder__7CSystemFv(&System);
  iVar5 = System.m_orderCount;
  dVar17 = (double)FLOAT_8032fb9c;
  dVar18 = (double)FLOAT_8032fbd4;
  iVar15 = System.m_orderCount + -1;
  iVar13 = 0;
  uVar11 = 0x10;
  for (iVar7 = 0; iVar7 < iVar5; iVar7 = iVar7 + 1) {
    uVar14 = pCVar8->mPriority;
    dVar19 = (double)pCVar8->mLastTime;
    local_2fc = Hsb2Rgb__5CMathFiii(&Math,iVar13 / iVar5,100,100);
    dVar19 = (double)(float)((double)(float)(dVar17 * dVar19) / dVar18);
    local_2f0 = local_2fc;
    if (uVar14 == 0x26) {
      local_304 = local_2fc;
      local_300 = local_2fc;
      GXBegin(0x80,0,4);
      DAT_cc008000 = (float)dVar16;
      fVar1 = FLOAT_8032fbd8;
      if (bVar4) {
        uStack_74 = uVar11 ^ 0x80000000;
        local_78 = 0x43300000;
        fVar1 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8032fbb0);
      }
      DAT_cc008000 = fVar1;
      DAT_cc008000 = FLOAT_8032fb78;
      fVar1 = FLOAT_8032fb88 + (float)(dVar16 + dVar19);
      DAT_cc008000 = local_300;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000 = fVar1;
      fVar2 = FLOAT_8032fbd8;
      if (bVar4) {
        uStack_6c = uVar11 ^ 0x80000000;
        local_70 = 0x43300000;
        fVar2 = (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_8032fbb0);
      }
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8032fb78;
      DAT_cc008000 = local_300;
      DAT_cc008000._0_2_ = 2;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000 = fVar1;
      DAT_cc008000 = FLOAT_8032fbc8;
      DAT_cc008000 = FLOAT_8032fb78;
      DAT_cc008000 = local_304;
      DAT_cc008000._0_2_ = 2;
      DAT_cc008000._0_2_ = 2;
      DAT_cc008000 = (float)dVar16;
      dVar16 = (double)(float)(dVar16 + dVar19);
      DAT_cc008000 = FLOAT_8032fbc8;
      DAT_cc008000 = FLOAT_8032fb78;
      DAT_cc008000 = local_304;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000._0_2_ = 2;
    }
    else if (uVar14 != 0x27) {
      local_30c = local_2fc;
      local_308 = local_2fc;
      GXBegin(0x80,0,4);
      DAT_cc008000 = (float)dVar16;
      fVar1 = FLOAT_8032fbdc;
      if (bVar4) {
        uStack_6c = uVar11 ^ 0x80000000;
        local_70 = 0x43300000;
        fVar1 = (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_8032fbb0);
      }
      DAT_cc008000 = fVar1;
      DAT_cc008000 = FLOAT_8032fb78;
      fVar1 = FLOAT_8032fb88 + (float)(dVar16 + dVar19);
      DAT_cc008000 = local_308;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000 = fVar1;
      fVar2 = FLOAT_8032fbdc;
      if (bVar4) {
        uStack_74 = uVar11 ^ 0x80000000;
        local_78 = 0x43300000;
        fVar2 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8032fbb0);
      }
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8032fb78;
      DAT_cc008000 = local_308;
      DAT_cc008000._0_2_ = 2;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000 = fVar1;
      DAT_cc008000 = FLOAT_8032fbd8;
      DAT_cc008000 = FLOAT_8032fb78;
      DAT_cc008000 = local_30c;
      DAT_cc008000._0_2_ = 2;
      DAT_cc008000._0_2_ = 2;
      DAT_cc008000 = (float)dVar16;
      dVar16 = (double)(float)(dVar16 + dVar19);
      DAT_cc008000 = FLOAT_8032fbd8;
      DAT_cc008000 = FLOAT_8032fb78;
      DAT_cc008000 = local_30c;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000._0_2_ = 2;
    }
    if (iVar7 == iVar15) {
      local_310 = Hsb2Rgb__5CMathFiii(&Math,0,100,100);
      local_2f0 = local_310;
      dVar19 = (double)GetPerformance__6CSoundFv(&Sound);
      dVar19 = (double)((float)((double)FLOAT_8032fb9c * dVar19) / FLOAT_8032fbd4);
      local_318 = local_2f0;
      local_314 = local_2f0;
      GXBegin(0x80,0,4);
      DAT_cc008000 = (float)dVar16;
      fVar1 = FLOAT_8032fbd8;
      if (bVar4) {
        uStack_6c = uVar11 ^ 0x80000000;
        local_70 = 0x43300000;
        fVar1 = (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_8032fbb0);
      }
      DAT_cc008000 = fVar1;
      DAT_cc008000 = FLOAT_8032fb78;
      fVar1 = FLOAT_8032fb88 + (float)(dVar16 + dVar19);
      DAT_cc008000 = local_314;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000 = fVar1;
      fVar2 = FLOAT_8032fbd8;
      if (bVar4) {
        uStack_74 = uVar11 ^ 0x80000000;
        local_78 = 0x43300000;
        fVar2 = (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8032fbb0);
      }
      DAT_cc008000 = fVar2;
      DAT_cc008000 = FLOAT_8032fb78;
      DAT_cc008000 = local_314;
      DAT_cc008000._0_2_ = 2;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000 = fVar1;
      DAT_cc008000 = FLOAT_8032fbc8;
      DAT_cc008000 = FLOAT_8032fb78;
      DAT_cc008000 = local_318;
      DAT_cc008000._0_2_ = 2;
      DAT_cc008000._0_2_ = 2;
      DAT_cc008000 = (float)dVar16;
      DAT_cc008000 = FLOAT_8032fbc8;
      DAT_cc008000 = FLOAT_8032fb78;
      DAT_cc008000 = local_318;
      DAT_cc008000._0_2_ = 0;
      DAT_cc008000._0_2_ = 2;
    }
    pCVar8 = (COrder *)GetNextOrder__7CSystemFPQ27CSystem6COrder(&System,pCVar8);
    uVar11 = uVar11 + 8;
    iVar13 = iVar13 + 0x168;
  }
  iVar7 = IsFrameRateOver__8CGraphicFv(&Graphic);
  if (iVar7 == 0) {
    puVar9 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_324,0,0xff,0,0xff);
  }
  else {
    puVar9 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_320,0xff,0,0,0xff);
  }
  local_32c = *puVar9;
  local_328 = local_32c;
  local_31c = local_32c;
  local_2f0 = local_32c;
  GXBegin(0x80,0,4);
  DAT_cc008000 = FLOAT_8032fbc4;
  DAT_cc008000 = FLOAT_8032fbe0;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = local_328;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = FLOAT_8032fbe4;
  DAT_cc008000 = FLOAT_8032fbe0;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = local_328;
  DAT_cc008000._0_2_ = 2;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = FLOAT_8032fbe4;
  DAT_cc008000 = FLOAT_8032fbe8;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = local_32c;
  DAT_cc008000._0_2_ = 2;
  DAT_cc008000._0_2_ = 2;
  DAT_cc008000 = FLOAT_8032fbc4;
  DAT_cc008000 = FLOAT_8032fbe8;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = local_32c;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 2;
  iVar7 = IsFifoOver__8CGraphicFv(&Graphic);
  if (iVar7 == 0) {
    puVar9 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_338,0,0xff,0,0xff);
  }
  else {
    puVar9 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_334,0xff,0,0,0xff);
  }
  uVar6 = *puVar9;
  local_330 = uVar6;
  local_2f0 = uVar6;
  GXBegin(0x80,0,4);
  DAT_cc008000 = FLOAT_8032fbec;
  DAT_cc008000 = FLOAT_8032fbe0;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = uVar6;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = FLOAT_8032fbf0;
  DAT_cc008000 = FLOAT_8032fbe0;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = uVar6;
  DAT_cc008000._0_2_ = 2;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000 = FLOAT_8032fbf0;
  DAT_cc008000 = FLOAT_8032fbe8;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = uVar6;
  DAT_cc008000._0_2_ = 2;
  DAT_cc008000._0_2_ = 2;
  DAT_cc008000 = FLOAT_8032fbec;
  DAT_cc008000 = FLOAT_8032fbe8;
  DAT_cc008000 = FLOAT_8032fb78;
  DAT_cc008000 = uVar6;
  DAT_cc008000._0_2_ = 0;
  DAT_cc008000._0_2_ = 2;
  if (bVar4) {
    InitDebugString__8CGraphicFv(&Graphic);
    pCVar8 = (COrder *)GetFirstOrder__7CSystemFv(&System);
    dVar18 = (double)FLOAT_8032fbc4;
    dVar17 = (double)FLOAT_8032fb9c;
    dVar16 = (double)FLOAT_8032fbd4;
    sVar12 = 0x10;
    for (iVar7 = 0; iVar7 < iVar5; iVar7 = iVar7 + 1) {
      uVar14 = pCVar8->mPriority;
      dVar19 = (double)(float)((double)(float)(dVar17 * (double)pCVar8->mLastTime) / dVar16);
      if (uVar14 != 0x27) {
        sprintf((double)pCVar8->mLastTime,acStack_17c,s__s__d____3f___801d7ba4,pCVar8->mDebugName,
                pCVar8->mInsertIndex);
        if (uVar14 == 0x17) {
          sprintf((double)(float)CFlat._4920_4_,(double)(float)CFlat._4924_4_,
                  (double)(float)CFlat._4928_4_,(double)(float)CFlat._4932_4_,
                  (double)(float)CFlat._4936_4_,(double)(float)CFlat._72_4_,acStack_27c,
                  s_MOVE___1f___BG___1f___OBJ___1f___801d7bb4);
          strcat(acStack_17c,acStack_27c);
        }
        uVar10 = __cvt_fp2unsigned((double)(float)((double)FLOAT_8032fb88 + dVar18));
        DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,uVar10,sVar12,acStack_17c,8);
        dVar18 = (double)(float)(dVar18 + dVar19);
      }
      pCVar8 = (COrder *)GetNextOrder__7CSystemFPQ27CSystem6COrder(&System,pCVar8);
      sVar12 = sVar12 + 8;
    }
  }
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_2bc);
  GXSetProjection(&MStack_2bc,0);
  return;
}

