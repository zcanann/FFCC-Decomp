// Function: onCalc__9CRingMenuFv
// Entry: 800a4c3c
// Size: 1392 bytes

/* WARNING: Removing unreachable block (ram,0x800a5190) */
/* WARNING: Removing unreachable block (ram,0x800a4c4c) */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onCalc__9CRingMenuFv(CRingMenu *ringMenu)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char cVar12;
  CGPartyObj *pCVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  CRingMenu *pCVar13;
  int iVar14;
  int iVar15;
  ushort uVar16;
  int iVar17;
  uint32_t uVar18;
  CCaravanWork *caravanWork;
  int *piVar19;
  int iVar20;
  double dVar21;
  
  if ((Game.game.m_gameWork.m_menuStageMode == '\0') || (ringMenu->menuIndex < 1)) {
    if (ringMenu->animDirection != ((uint)(CFlat._4768_4_ & CFlat._4772_4_) >> 2 & 1)) {
      Printf__7CSystemFPce(&System,&DAT_801da01c,ringMenu->menuIndex);
      uVar4 = countLeadingZeros(ringMenu->animDirection);
      ringMenu->animDirection = uVar4 >> 5 & 0xff;
      ringMenu->displayCounter = 0x10 - ringMenu->displayCounter;
    }
    uVar4 = ringMenu->displayCounter - 1;
    ringMenu->displayCounter = uVar4 & ~((int)uVar4 >> 0x1f);
    uVar4 = ringMenu->transitionTimer - 1;
    ringMenu->transitionTimer = uVar4 & ~((int)uVar4 >> 0x1f);
    ringMenu->commonFrameCounter = ringMenu->commonFrameCounter + 1;
    uVar4 = ringMenu->timerB - 1;
    ringMenu->timerB = uVar4 & ~((int)uVar4 >> 0x1f);
    uVar4 = ringMenu->buttonTimers[0] - 1;
    ringMenu->buttonTimers[0] = uVar4 & ~((int)uVar4 >> 0x1f);
    uVar4 = ringMenu->buttonTimers[1] - 1;
    ringMenu->buttonTimers[1] = uVar4 & ~((int)uVar4 >> 0x1f);
    uVar4 = ringMenu->buttonTimers[2] - 1;
    ringMenu->buttonTimers[2] = uVar4 & ~((int)uVar4 >> 0x1f);
    uVar4 = ringMenu->buttonTimers[3] - 1;
    ringMenu->buttonTimers[3] = uVar4 & ~((int)uVar4 >> 0x1f);
    uVar4 = ringMenu->buttonTimers[4] - 1;
    ringMenu->buttonTimers[4] = uVar4 & ~((int)uVar4 >> 0x1f);
    uVar4 = ringMenu->buttonTimers[5] - 1;
    ringMenu->buttonTimers[5] = uVar4 & ~((int)uVar4 >> 0x1f);
    fVar3 = FLOAT_80330a54;
    fVar2 = FLOAT_803309c0;
    uVar4 = ringMenu->buttonTimers[6] - 1;
    ringMenu->buttonTimers[6] = uVar4 & ~((int)uVar4 >> 0x1f);
    uVar4 = ringMenu->buttonTimers[7] - 1;
    ringMenu->buttonTimers[7] = uVar4 & ~((int)uVar4 >> 0x1f);
    uVar4 = ringMenu->_timerRelated - 1;
    ringMenu->_timerRelated = uVar4 & ~((int)uVar4 >> 0x1f);
    iVar20 = 9;
    pCVar13 = ringMenu;
    do {
      pCVar13->animFloat[0] = pCVar13->animFloat[0] - fVar3;
      if (pCVar13->animFloat[0] < fVar2) {
        pCVar13->animFloat[0] = fVar2;
      }
      pCVar13->animFloat[1] = pCVar13->animFloat[1] - fVar3;
      if (pCVar13->animFloat[1] < fVar2) {
        pCVar13->animFloat[1] = fVar2;
      }
      pCVar13->animFloat[2] = pCVar13->animFloat[2] - fVar3;
      if (pCVar13->animFloat[2] < fVar2) {
        pCVar13->animFloat[2] = fVar2;
      }
      pCVar13 = (CRingMenu *)&pCVar13->stateFlag;
      iVar20 = iVar20 + -1;
    } while (iVar20 != 0);
    fmod((double)(float)ringMenu->spinAccumulator,DOUBLE_80330a98);
    iVar20 = 0x1b;
    do {
      iVar20 = iVar20 + -1;
    } while (iVar20 != 0);
    iVar20 = GetCtrlMode__6JoyBusFi(&Joybus,ringMenu->menuIndex);
    uVar4 = countLeadingZeros(1 - iVar20);
    uVar18 = uVar4 >> 5 & 0xff;
    cVar12 = GetGBAStart__6JoyBusFi(&Joybus,ringMenu->menuIndex);
    if (cVar12 == '\0') {
      uVar18 = 1;
    }
    iVar20 = GetPadType__6JoyBusFi(&Joybus,ringMenu->menuIndex);
    if ((iVar20 == 0x9000000) ||
       (iVar20 = GetPadType__6JoyBusFi(&Joybus,ringMenu->menuIndex), iVar20 == -0x74f00000)) {
      uVar18 = 0;
    }
    if (ringMenu->gbaConnectedFlag != uVar18) {
      ringMenu->gbaConnectedFlag = uVar18;
      ringMenu->gbaAnimCounter = 0xc - ringMenu->gbaAnimCounter;
    }
    dVar21 = (double)FLOAT_803309c0;
    uVar4 = ringMenu->gbaAnimCounter - 1;
    ringMenu->gbaAnimCounter = uVar4 & ~((int)uVar4 >> 0x1f);
    pCVar7 = Game.game.m_partyObjArr[ringMenu->menuIndex];
    if (pCVar7 != (CGPartyObj *)0x0) {
      caravanWork = (CCaravanWork *)(pCVar7->gCharaObj).gPrgObj.object.m_scriptHandle;
      iVar20 = Chara._8196_4_;
      if (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x19) {
        iVar20 = _GetIdxCmdList__12CCaravanWorkFv(caravanWork);
      }
      uVar4 = countLeadingZeros(0x19 - Game.game.m_gameWork.m_bossArtifactStageIndex);
      if ((uVar4 >> 5 & 0xff) == 0) {
        piVar19 = &ringMenu->currentCommandIndex;
      }
      else {
        piVar19 = (int *)&Chara.field_0x2008;
      }
      if (*piVar19 != iVar20) {
        iVar17 = iVar20 + 1;
        iVar14 = iVar20 + 4;
        uVar4 = 1;
        iVar8 = iVar17 / 5 + (iVar17 >> 0x1f);
        iVar5 = iVar14 / 5 + (iVar14 >> 0x1f);
        iVar15 = iVar20;
        iVar10 = iVar20;
        do {
          iVar9 = iVar17 + (iVar8 - (iVar8 >> 0x1f)) * -5;
          if (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x19) {
            iVar9 = GetNextCmdListIdx__12CCaravanWorkFii(caravanWork,iVar10,1);
          }
          iVar10 = iVar14 + (iVar5 - (iVar5 >> 0x1f)) * -5;
          if (Game.game.m_gameWork.m_bossArtifactStageIndex != 0x19) {
            iVar10 = GetNextCmdListIdx__12CCaravanWorkFii(caravanWork,iVar15,0xffffffff);
          }
          iVar15 = *piVar19;
          if (iVar15 != iVar20) {
            uVar11 = 0;
            uVar6 = 0;
            if (iVar15 == iVar10) {
              uVar6 = uVar4;
            }
            if (iVar15 == iVar9) {
              uVar11 = -uVar4;
            }
            if ((uVar6 != 0) || (uVar11 != 0)) {
              if ((uVar6 == 0) || (uVar11 == 0)) {
                if (uVar6 == 0) {
                  if (uVar11 != 0) {
                    dVar21 = (double)(float)((double)CONCAT44(0x43300000,uVar11 ^ 0x80000000) -
                                            DOUBLE_80330a00);
                  }
                }
                else {
                  dVar21 = (double)(float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) -
                                          DOUBLE_80330a00);
                }
              }
              else {
                uVar4 = ringMenu->menuIndex;
                bVar1 = false;
                if ((Pad._452_4_ != 0) || ((uVar4 == 0 && (Pad._448_4_ != -1)))) {
                  bVar1 = true;
                }
                if (bVar1) {
                  uVar16 = 0;
                }
                else {
                  uVar16 = *(ushort *)
                            (&Pad.field_0x4 +
                            (uVar4 & ~((int)~(Pad._448_4_ - uVar4 | uVar4 - Pad._448_4_) >> 0x1f)) *
                            0x54);
                }
                if ((uVar16 & 0x40) != 0) {
                  uVar11 = uVar6;
                }
                dVar21 = (double)(float)((double)CONCAT44(0x43300000,uVar11 ^ 0x80000000) -
                                        DOUBLE_80330a00);
              }
              break;
            }
            dVar21 = (double)FLOAT_803309c0;
          }
          uVar4 = uVar4 + 1;
          iVar15 = iVar10;
          iVar10 = iVar9;
        } while ((int)uVar4 < 4);
      }
      *piVar19 = iVar20;
      fVar2 = FLOAT_80330ae8;
      ringMenu->commandScrollOffset = (float)((double)ringMenu->commandScrollOffset + dVar21);
      ringMenu->commandScrollOffset = ringMenu->commandScrollOffset * fVar2;
    }
  }
  return;
}

