// Function: onDraw__9CRingMenuFv
// Entry: 800a39c4
// Size: 3884 bytes

/* WARNING: Removing unreachable block (ram,0x800a48d4) */
/* WARNING: Removing unreachable block (ram,0x800a48cc) */
/* WARNING: Removing unreachable block (ram,0x800a48c4) */
/* WARNING: Removing unreachable block (ram,0x800a48bc) */
/* WARNING: Removing unreachable block (ram,0x800a48b4) */
/* WARNING: Removing unreachable block (ram,0x800a48ac) */
/* WARNING: Removing unreachable block (ram,0x800a48a4) */
/* WARNING: Removing unreachable block (ram,0x800a489c) */
/* WARNING: Removing unreachable block (ram,0x800a4894) */
/* WARNING: Removing unreachable block (ram,0x800a488c) */
/* WARNING: Removing unreachable block (ram,0x800a4884) */
/* WARNING: Removing unreachable block (ram,0x800a487c) */
/* WARNING: Removing unreachable block (ram,0x800a4874) */
/* WARNING: Removing unreachable block (ram,0x800a486c) */
/* WARNING: Removing unreachable block (ram,0x800a4864) */
/* WARNING: Removing unreachable block (ram,0x800a485c) */
/* WARNING: Removing unreachable block (ram,0x800a4854) */
/* WARNING: Removing unreachable block (ram,0x800a484c) */
/* WARNING: Removing unreachable block (ram,0x800a3a5c) */
/* WARNING: Removing unreachable block (ram,0x800a3a54) */
/* WARNING: Removing unreachable block (ram,0x800a3a4c) */
/* WARNING: Removing unreachable block (ram,0x800a3a44) */
/* WARNING: Removing unreachable block (ram,0x800a3a3c) */
/* WARNING: Removing unreachable block (ram,0x800a3a34) */
/* WARNING: Removing unreachable block (ram,0x800a3a2c) */
/* WARNING: Removing unreachable block (ram,0x800a3a24) */
/* WARNING: Removing unreachable block (ram,0x800a3a1c) */
/* WARNING: Removing unreachable block (ram,0x800a3a14) */
/* WARNING: Removing unreachable block (ram,0x800a3a0c) */
/* WARNING: Removing unreachable block (ram,0x800a3a04) */
/* WARNING: Removing unreachable block (ram,0x800a39fc) */
/* WARNING: Removing unreachable block (ram,0x800a39f4) */
/* WARNING: Removing unreachable block (ram,0x800a39ec) */
/* WARNING: Removing unreachable block (ram,0x800a39e4) */
/* WARNING: Removing unreachable block (ram,0x800a39dc) */
/* WARNING: Removing unreachable block (ram,0x800a39d4) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onDraw__9CRingMenuFv(CRingMenu *ringMenu)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  CGPartyObj *pCVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  uint uVar11;
  int32_t iVar12;
  CCaravanWork *pCVar13;
  int iVar14;
  CRingMenu *pCVar15;
  int *piVar16;
  int *piVar17;
  int *piVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double in_f14;
  double in_f15;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  double dVar29;
  double dVar30;
  double dVar31;
  double dVar32;
  double in_f30;
  double in_f31;
  undefined auStack_1f0 [4];
  undefined auStack_1ec [4];
  undefined auStack_1e8 [4];
  undefined auStack_1e4 [4];
  undefined4 local_1e0;
  undefined auStack_1dc [4];
  undefined4 local_1d8;
  undefined auStack_1d4 [4];
  undefined4 local_1d0;
  uint uStack_1cc;
  undefined4 local_1c8;
  uint uStack_1c4;
  undefined4 local_1c0;
  uint uStack_1bc;
  undefined8 local_1b8;
  float local_1b0;
  float local_1ac;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  double local_190;
  double local_188;
  double local_180;
  CChara *local_178;
  
  if (((Game.game.m_gameWork.m_menuStageMode == '\0') || (ringMenu->menuIndex < 1)) &&
     (Game.game.m_scriptFoodBase[ringMenu->menuIndex] != 0)) {
    uStack_1cc = ringMenu->displayCounter ^ 0x80000000;
    dVar22 = (double)((float)((double)CONCAT44(0x43300000,uStack_1cc) - DOUBLE_80330a00) *
                     FLOAT_80330a08);
    if (ringMenu->animDirection != 0) {
      dVar22 = (double)(float)((double)FLOAT_803309cc - dVar22);
    }
    if ((double)FLOAT_803309c0 != dVar22) {
      if (*(int *)&ringMenu->field_0x10 == 0) {
        local_1c8 = 0x43300000;
        uStack_1c4 = ringMenu->transitionTimer ^ 0x80000000;
        dVar31 = (double)((float)((double)CONCAT44(0x43300000,uStack_1c4) - DOUBLE_80330a00) *
                         FLOAT_80330a08);
      }
      else {
        uStack_1cc = ringMenu->transitionTimer ^ 0x80000000;
        dVar31 = -(double)((float)((double)CONCAT44(0x43300000,uStack_1cc) - DOUBLE_80330a00) *
                           FLOAT_80330a08 - FLOAT_803309cc);
      }
      local_1d0 = 0x43300000;
      SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x16);
      local_1c0 = 0x43300000;
      uStack_1bc = ringMenu->gbaAnimCounter ^ 0x80000000;
      sin((double)((FLOAT_80330a0c *
                   (float)((double)CONCAT44(0x43300000,uStack_1bc) - DOUBLE_80330a00)) /
                  FLOAT_80330a10));
      SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs,0);
      local_1b8 = (double)(CONCAT44(0x43300000,ringMenu->commonFrameCounter) ^ 0x80000000);
      dVar19 = (double)fmod((double)(FLOAT_80330a18 * (float)(local_1b8 - DOUBLE_80330a00)),
                            DOUBLE_80330a20);
      fVar1 = (float)dVar19;
      if (FLOAT_803309cc < fVar1) {
        fVar1 = FLOAT_80330a28 - fVar1;
      }
      dVar19 = (double)(FLOAT_80330a2c * fVar1);
      sin(dVar19);
      sin((double)(float)((double)FLOAT_80330a30 + dVar19));
      dVar19 = (double)sin((double)(float)((double)FLOAT_80330a0c * dVar22));
      local_1a4 = (float)((double)(float)((double)FLOAT_80330a34 * dVar22) * dVar31);
      local_1a0 = FLOAT_80330a5c * (FLOAT_803309cc - (float)dVar19);
      local_1a8 = (float)(dVar22 * dVar31);
      local_1ac = FLOAT_80330a60 + local_1a0;
      piVar16 = ringMenu->battleButtons;
      pCVar15 = (CRingMenu *)&ringMenu->field_0x10;
      local_194 = -local_1a0;
      local_178 = &Chara;
      iVar14 = 2;
      local_190 = DOUBLE_80330a00;
      local_198 = FLOAT_80330a64 + local_1a0;
      local_188 = (double)FLOAT_80330a78;
      local_180 = (double)FLOAT_803309c0;
      local_19c = local_1ac - FLOAT_80330a68;
      local_1a0 = FLOAT_80330a6c + local_1a0;
      do {
        if (iVar14 == 2) {
          fVar1 = local_194;
          if ((ringMenu->menuIndex & 1U) != 0) {
            fVar1 = local_1ac;
          }
          fVar1 = FLOAT_80330a70 + fVar1;
          fVar2 = local_194;
          if ((ringMenu->menuIndex & 2U) != 0) {
            fVar2 = local_198;
          }
          fVar2 = FLOAT_80330a44 + fVar2;
        }
        else {
          fVar1 = local_194;
          if ((ringMenu->menuIndex & 1U) != 0) {
            fVar1 = local_19c;
          }
          fVar1 = FLOAT_80330a68 + fVar1;
          fVar2 = local_194;
          if ((ringMenu->menuIndex & 2U) != 0) {
            fVar2 = local_1a0;
          }
          fVar2 = FLOAT_80330a74 + fVar2;
        }
        dVar23 = (double)fVar2;
        dVar19 = (double)fVar1;
        local_1b8 = (double)(CONCAT44(0x43300000,piVar16[0x10]) ^ 0x80000000);
        dVar24 = (double)(float)((double)(float)(local_1b8 - local_190) * local_188);
        if (-1 < *(int *)((int)pCVar15->battleButtons + 8)) {
          dVar24 = (double)(float)((double)FLOAT_803309cc - dVar24);
        }
        if (iVar14 == 2) {
          local_1b8 = (double)(CONCAT44(0x43300000,
                                        -((int)*(short *)&Game.game.m_partyObjArr
                                                          [ringMenu->menuIndex]->field_0x6f4 & 9U)
                                        >> 0x1f) ^ 0x80000000);
          dVar24 = (double)(float)(local_1b8 - DOUBLE_80330a00);
        }
        if (local_180 != dVar24) {
          SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1f);
          local_1b8 = (double)(longlong)(int)(dVar24 * (double)local_1a4);
          uVar6 = __ct__6CColorFUcUcUcUc
                            (auStack_1d4,0xff,0xff,0xff,(int)(dVar24 * (double)local_1a4));
          SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar6);
          if (iVar14 == 1) {
            dVar24 = (double)sin((double)(float)((double)FLOAT_80330a0c * dVar24));
            local_1b0 = (float)((double)FLOAT_80330a80 + dVar23);
            in_f15 = -(double)(float)((double)FLOAT_80330a70 * (double)(float)dVar24 - dVar19);
            DrawRect__8CMenuPcsFUlfffffffff
                      (in_f15,(double)local_1b0,(double)FLOAT_80330a7c,(double)FLOAT_80330a80,
                       (double)FLOAT_803309c0,(double)FLOAT_80330a5c,(double)FLOAT_803309cc,
                       (double)FLOAT_803309cc,&MenuPcs,0);
            DrawRect__8CMenuPcsFUlfffffffff
                      (in_f15,(double)local_1b0,(double)FLOAT_80330a80,(double)FLOAT_80330a80,
                       (double)FLOAT_80330a68,(double)FLOAT_803309f0,(double)FLOAT_803309cc,
                       (double)FLOAT_803309cc,&MenuPcs,0);
          }
          else if (iVar14 < 1) {
            if (-1 < iVar14) {
              dVar24 = (double)sin((double)(float)((double)FLOAT_80330a0c * dVar24));
              local_1b0 = (float)dVar23;
              in_f15 = -(double)(FLOAT_80330a70 * (float)dVar24 -
                                (float)((double)FLOAT_80330a10 + dVar19));
              DrawRect__8CMenuPcsFUlfffffffff
                        (in_f15,dVar23,(double)FLOAT_80330a7c,(double)FLOAT_80330a5c,
                         (double)FLOAT_803309c0,(double)FLOAT_803309c0,(double)FLOAT_803309cc,
                         (double)FLOAT_803309cc,&MenuPcs,0);
              DrawRect__8CMenuPcsFUlfffffffff
                        (in_f15,dVar23,(double)FLOAT_80330a68,(double)FLOAT_80330a5c,
                         (double)FLOAT_803309c0,(double)FLOAT_803309f0,(double)FLOAT_803309cc,
                         (double)FLOAT_803309cc,&MenuPcs,0);
            }
          }
          else if (iVar14 < 3) {
            local_1b0 = (float)dVar23;
            dVar24 = dVar19;
            DrawRect__8CMenuPcsFUlfffffffff
                      (dVar19,dVar23,(double)FLOAT_80330a84,(double)FLOAT_80330a5c,
                       (double)FLOAT_803309c0,(double)FLOAT_80330a88,(double)FLOAT_803309cc,
                       (double)FLOAT_803309cc,&MenuPcs,0);
            in_f15 = dVar19;
            dVar19 = dVar24;
          }
          if ((iVar14 == 2) &&
             (pCVar7 = Game.game.m_partyObjArr[ringMenu->menuIndex], pCVar7 != (CGPartyObj *)0x0)) {
            pCVar13 = (CCaravanWork *)(pCVar7->gCharaObj).gPrgObj.object.m_scriptHandle;
            if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
              iVar8 = *(int *)&local_178->field_0x2004;
            }
            else {
              iVar8 = _GetIdxCmdList__12CCaravanWorkFv(pCVar13);
            }
            uVar6 = MenuPcs._252_4_;
            DrawInit__5CFontFv((CFont *)MenuPcs._252_4_);
            SetMargin__5CFontFf(FLOAT_80330a8c,(CFont *)uVar6);
            SetShadow__5CFontFi((CFont *)uVar6,1);
            SetTlut__5CFontFi((CFont *)uVar6,4);
            dVar24 = (double)ringMenu->commandScrollOffset;
            dVar25 = (double)FLOAT_803309cc;
            while( true ) {
              for (; dVar25 <= dVar24; dVar24 = (double)(float)(dVar24 - (double)FLOAT_803309cc)) {
                if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
                  iVar8 = iVar8 + 1;
                  iVar3 = iVar8 / 5 + (iVar8 >> 0x1f);
                  iVar8 = iVar8 + (iVar3 - (iVar3 >> 0x1f)) * -5;
                }
                else {
                  iVar8 = GetNextCmdListIdx__12CCaravanWorkFii(pCVar13,iVar8,0xffffffff);
                }
              }
              if ((double)FLOAT_803309d0 < dVar24) break;
              if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
                iVar8 = iVar8 + 4;
                iVar3 = iVar8 / 5 + (iVar8 >> 0x1f);
                iVar8 = iVar8 + (iVar3 - (iVar3 >> 0x1f)) * -5;
              }
              else {
                iVar8 = GetNextCmdListIdx__12CCaravanWorkFii(pCVar13,iVar8,1);
              }
              dVar24 = (double)(float)(dVar24 + (double)FLOAT_803309cc);
            }
            dVar25 = DOUBLE_80330a98;
            if (ABS((double)ringMenu->commandScrollOffset) < DOUBLE_80330aa0) {
              dVar25 = DOUBLE_80330a90 * ABS((double)ringMenu->commandScrollOffset);
            }
            dVar25 = (double)(float)dVar25;
            if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
              iVar3 = iVar8 + 4;
              iVar4 = iVar3 / 5 + (iVar3 >> 0x1f);
              iVar3 = iVar3 + (iVar4 - (iVar4 >> 0x1f)) * -5;
            }
            else {
              iVar3 = GetNextCmdListIdx__12CCaravanWorkFii(pCVar13,iVar8,0xffffffff);
            }
            if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
              iVar4 = iVar3 + 4;
              iVar5 = iVar4 / 5 + (iVar4 >> 0x1f);
              iVar4 = iVar4 + (iVar5 - (iVar5 >> 0x1f)) * -5;
            }
            else {
              iVar4 = GetNextCmdListIdx__12CCaravanWorkFii(pCVar13,iVar3,0xffffffff);
            }
            dVar25 = (double)(float)(dVar25 * (double)local_1a8);
            drawCommand__FiP5CFontffP12CCaravanWorkiff
                      (dVar19,dVar23,(double)(float)(dVar24 - (double)FLOAT_80330a28),dVar25,
                       ringMenu->menuIndex,uVar6,pCVar13,iVar4);
            drawCommand__FiP5CFontffP12CCaravanWorkiff
                      (dVar19,dVar23,(double)(float)(dVar24 - (double)FLOAT_803309cc),dVar25,
                       ringMenu->menuIndex,uVar6,pCVar13,iVar3);
            if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
              iVar3 = iVar8 + 1;
              iVar4 = iVar3 / 5 + (iVar3 >> 0x1f);
              iVar3 = iVar3 + (iVar4 - (iVar4 >> 0x1f)) * -5;
            }
            else {
              iVar3 = GetNextCmdListIdx__12CCaravanWorkFii(pCVar13,iVar8,1);
            }
            if (Game.game.m_gameWork.m_bossArtifactStageIndex == 0x19) {
              iVar4 = iVar3 + 1;
              iVar5 = iVar4 / 5 + (iVar4 >> 0x1f);
              iVar4 = iVar4 + (iVar5 - (iVar5 >> 0x1f)) * -5;
            }
            else {
              iVar4 = GetNextCmdListIdx__12CCaravanWorkFii(pCVar13,iVar3,1);
            }
            drawCommand__FiP5CFontffP12CCaravanWorkiff
                      (dVar19,dVar23,(double)(float)((double)FLOAT_80330a28 + dVar24),dVar25,
                       ringMenu->menuIndex,uVar6,pCVar13,iVar4);
            drawCommand__FiP5CFontffP12CCaravanWorkiff
                      (dVar19,dVar23,(double)(float)((double)FLOAT_803309cc + dVar24),dVar25,
                       ringMenu->menuIndex,uVar6,pCVar13,iVar3);
            drawCommand__FiP5CFontffP12CCaravanWorkiff
                      (dVar19,dVar23,dVar24,(double)local_1a8,ringMenu->menuIndex,uVar6,pCVar13,
                       iVar8);
            DrawInit__8CMenuPcsFv(&MenuPcs);
          }
          uVar6 = MenuPcs._252_4_;
          piVar18 = (int *)((int)&pCVar15->menuBase + 4);
          piVar17 = piVar16 + 1;
          dVar19 = (double)(float)((double)FLOAT_80330aa8 + in_f15);
          iVar8 = 1;
          dVar27 = (double)(float)(dVar19 + (double)FLOAT_80330aac);
          dVar24 = (double)((FLOAT_80330ab0 + local_1b0) - FLOAT_803309ec);
          dVar26 = (double)((FLOAT_80330a3c + local_1b0) - FLOAT_803309ec);
          dVar25 = (double)(float)((double)(float)((double)FLOAT_803309f0 + in_f15) +
                                  (double)FLOAT_80330aac);
          dVar23 = (double)(FLOAT_80330ab4 + local_1b0);
          do {
            uVar11 = piVar18[8];
            if (-1 < (int)uVar11) {
              if ((uVar11 & 0x8000) == 0) {
                iVar12 = Game.game.m_cFlatDataArr[1].m_table[4].index[uVar11];
              }
              else {
                iVar12 = Game.game.m_cFlatDataArr[1].m_table[0].index[(uVar11 & 0xffff7fff) * 5 + 4]
                ;
              }
              local_1b8 = (double)CONCAT44(0x43300000,piVar17[0xe] ^ 0x80000000);
              dVar28 = (double)((float)(local_1b8 - DOUBLE_80330a00) * FLOAT_80330a78);
              if (iVar8 == 0) {
                dVar28 = (double)(float)((double)FLOAT_803309cc - dVar28);
              }
              DrawInit__5CFontFv((CFont *)uVar6);
              SetMargin__5CFontFf(FLOAT_80330a8c,(CFont *)uVar6);
              SetShadow__5CFontFi((CFont *)uVar6,1);
              if (iVar14 == 1) {
                SetTlut__5CFontFi((CFont *)uVar6,0xe);
                in_f14 = (double)FLOAT_80330a4c;
              }
              else if (iVar14 < 1) {
                if (-1 < iVar14) {
                  SetTlut__5CFontFi((CFont *)uVar6,0xd);
                  in_f14 = (double)FLOAT_80330ab8;
                }
              }
              else if (iVar14 < 3) {
                uVar10 = 4;
                if (uVar11 == 1) {
                  uVar10 = 7;
                }
                SetTlut__5CFontFi((CFont *)uVar6,uVar10);
                dVar20 = (double)sin((double)(FLOAT_80330a0c *
                                             (float)((double)FLOAT_803309cc - dVar28)));
                in_f14 = (double)(FLOAT_80330a4c * (FLOAT_80330abc * (float)dVar20 + FLOAT_803309cc)
                                 );
              }
              SetScaleX__5CFontFf((float)in_f14,(CFont *)uVar6);
              SetScaleY__5CFontFf((float)in_f14,(CFont *)uVar6);
              dVar20 = (double)GetWidth__5CFontFPc((CFont *)uVar6,iVar12);
              if ((iVar14 == 2) && (-1 < ringMenu->battleButtons[2])) {
                iVar3 = (int)(FLOAT_80330ac0 *
                             (float)(dVar22 * (double)(float)((double)(float)((double)FLOAT_80330a34
                                                                             * dVar28) * dVar31)));
                local_1b8 = (double)(longlong)iVar3;
                puVar9 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_1dc,0xff,0xff,0xff,iVar3);
                local_1d8 = *puVar9;
                SetColor__5CFontF8_GXColor((CFont *)uVar6,&local_1d8);
              }
              else {
                iVar3 = (int)(dVar22 * (double)(float)((double)(float)((double)FLOAT_80330a34 *
                                                                      dVar28) * dVar31));
                local_1b8 = (double)(longlong)iVar3;
                puVar9 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_1e4,0xff,0xff,0xff,iVar3);
                local_1e0 = *puVar9;
                SetColor__5CFontF8_GXColor((CFont *)uVar6,&local_1e0);
              }
              if (iVar14 == 1) {
                in_f31 = -(double)(float)((double)FLOAT_803309c4 * dVar20 - dVar25);
                in_f30 = dVar24;
              }
              else if (iVar14 < 1) {
                if (-1 < iVar14) {
                  in_f31 = -(double)(float)((double)FLOAT_803309c4 * dVar20 - dVar27);
                  in_f30 = dVar26;
                }
              }
              else if (iVar14 < 3) {
                in_f31 = -(double)(float)((double)FLOAT_803309c4 * dVar20 - dVar19);
                in_f30 = dVar23;
              }
              SetPosX__5CFontFf((float)in_f31,(CFont *)uVar6);
              SetPosY__5CFontFf((float)in_f30,(CFont *)uVar6);
              SetPosZ__5CFontFf(FLOAT_803309c0,(CFont *)uVar6);
              if (iVar14 != 2) {
                Draw__5CFontFPc((CFont *)uVar6,iVar12);
              }
              DrawInit__8CMenuPcsFv(&MenuPcs);
              if (iVar14 == 2) {
                SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs,0x1f);
                pCVar7 = Game.game.m_partyObjArr[ringMenu->menuIndex];
                if (((pCVar7 != (CGPartyObj *)0x0) &&
                    (pCVar13 = (CCaravanWork *)(pCVar7->gCharaObj).gPrgObj.object.m_scriptHandle,
                    pCVar13 != (CCaravanWork *)0x0)) &&
                   (-1 < (int)((uint)(byte)CFlat._4836_1_ << 0x1e |
                              (uint)((byte)CFlat._4836_1_ >> 2)))) {
                  dVar20 = (double)(float)((double)FLOAT_80330aac + in_f30);
                  dVar32 = (double)FLOAT_803309ec;
                  uVar11 = 0;
                  dVar30 = (double)(float)(dVar22 * (double)(float)((double)(float)((double)
                                                  FLOAT_80330a34 * dVar28) * dVar31));
                  dVar29 = (double)(float)(dVar22 * (double)(float)((double)(float)((double)
                                                  FLOAT_80330a84 * dVar28) * dVar31));
                  dVar28 = DOUBLE_80330a00;
                  for (iVar3 = 0; iVar3 < (short)pCVar13->m_numCmdListSlots; iVar3 = iVar3 + 1) {
                    iVar4 = _GetMagicCharge__12CCaravanWorkFiRiRi(pCVar13,iVar3);
                    if (iVar4 == 0) {
                      iVar4 = _IsSelectedCmdList__12CCaravanWorkFi(pCVar13,iVar3);
                      if (iVar4 == 0) {
                        local_1b8 = (double)(longlong)(int)dVar29;
                        uVar10 = __ct__6CColorFUcUcUcUc(auStack_1f0,0x80,0x80,0x80,(int)dVar29);
                        SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar10);
                        fVar1 = FLOAT_803309c0;
                      }
                      else {
                        local_1b8 = (double)(longlong)(int)dVar30;
                        uVar10 = __ct__6CColorFUcUcUcUc(auStack_1ec,0x20,0xff,0x20,(int)dVar30);
                        SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar10);
                        fVar1 = FLOAT_803309c0;
                      }
                    }
                    else {
                      local_1b8 = (double)(longlong)(int)dVar30;
                      uVar10 = __ct__6CColorFUcUcUcUc(auStack_1e8,0,0xff,0,(int)dVar30);
                      SetColor__8CMenuPcsFR6CColor(&MenuPcs,uVar10);
                      fVar1 = (float)((double)CONCAT44(0x43300000,
                                                       System.m_frameCounter >> 2 & 1 ^ 0x80000000)
                                     - DOUBLE_80330a00);
                    }
                    uStack_1bc = uVar11 ^ 0x80000000;
                    dVar21 = (double)FLOAT_80330a38;
                    local_1b8 = (double)(CONCAT44(0x43300000,
                                                  (int)(((uint)(int)(short)pCVar13->
                                                  m_numCmdListSlots >> 0x1c & 1) +
                                                  (short)pCVar13->m_numCmdListSlots * 8) >> 1) ^
                                        0x80000000);
                    local_1c0 = 0x43300000;
                    DrawRect__8CMenuPcsFUlfffffffff
                              ((double)(float)(dVar32 + (double)((float)(dVar19 - (double)(float)(
                                                  local_1b8 - dVar28)) +
                                                  (float)((double)CONCAT44(0x43300000,uStack_1bc) -
                                                         dVar28))),dVar20,dVar21,dVar21,
                               (double)(float)(dVar21 * (double)(float)(dVar21 + (double)fVar1)),
                               (double)FLOAT_803309f0,(double)FLOAT_803309cc,(double)FLOAT_803309cc,
                               &MenuPcs,3);
                    uVar11 = uVar11 + 8;
                  }
                }
              }
            }
            iVar8 = iVar8 + -1;
            piVar17 = piVar17 + -1;
            piVar18 = piVar18 + -1;
          } while (-1 < iVar8);
        }
        iVar14 = iVar14 + -1;
        pCVar15 = (CRingMenu *)((int)(pCVar15 + 0xffffffff) + 0x508);
        piVar16 = piVar16 + -3;
      } while (-1 < iVar14);
      DrawInit__8CMenuPcsFv(&MenuPcs);
    }
  }
  return;
}

