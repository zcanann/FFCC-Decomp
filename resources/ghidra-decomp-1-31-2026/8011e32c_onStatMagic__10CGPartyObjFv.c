// Function: onStatMagic__10CGPartyObjFv
// Entry: 8011e32c
// Size: 1348 bytes

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onStatMagic__10CGPartyObjFv(CGame *param_1)

{
  bool bVar1;
  bool bVar2;
  uint8_t (*paauVar3) [8] [8];
  int iVar4;
  uint uVar5;
  uint uVar6;
  ushort uVar7;
  bool bVar8;
  
  iVar4 = *(int *)((param_1->m_gameWork).m_linkTable[2][2][0] + 4);
  if (iVar4 == 1) {
    if ((*(int *)(param_1->m_gameWork).m_linkTable[2][7][0] == 0) &&
       (*(int *)((param_1->m_gameWork).m_linkTable[2][7][4] + 4) <
        *(int *)(param_1->m_gameWork).m_linkTable[2][2][1])) {
      putTargetParticle__10CGPartyObjFii(param_1,0,1);
      paauVar3 = (param_1->m_gameWork).m_linkTable[2];
      *(uint8_t *)((int)(paauVar3[7] + 0) + 0) = '\0';
      *(uint8_t *)((int)(paauVar3[7] + 0) + 1) = '\0';
      *(uint8_t *)((int)(paauVar3[7] + 0) + 2) = '\0';
      *(uint8_t *)((int)(paauVar3[7] + 0) + 3) = '\x01';
    }
    if (*(int *)(param_1->m_gameWork).m_linkTable[2][7][0] != 0) {
      checkTargetParticle__10CGPartyObjFv(param_1);
    }
  }
  else if (iVar4 < 1) {
    if (((-1 < iVar4) && (*(int *)(param_1->m_gameWork).m_linkTable[2][2][1] == 0)) &&
       (iVar4 = *(int *)(param_1->m_gameWork).m_linkTable[2][2][7], iVar4 != 0x103)) {
      putParticleFromItem__10CGCharaObjFiiiP3Vec
                (param_1,iVar4,0,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][3][1],
                 (param_1->m_gameWork).m_linkTable[0][2][6] + 4);
      putParticleFromItem__10CGCharaObjFiiiP3Vec
                (param_1,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][2][7],1,
                 *(undefined4 *)(param_1->m_gameWork).m_linkTable[2][3][1],0);
    }
  }
  else if (iVar4 < 3) {
    if (*(int *)(param_1->m_gameWork).m_linkTable[2][2][1] == 0) {
      (**(code **)((param_1->m_gameWork).m_bossArtifactStageTable[6] + 0x4c))(param_1,0x19,0,0);
      if (*(int *)(param_1->m_gameWork).m_linkTable[2][2][7] == 0x103) {
        *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][7][0] + 4) =
             *(undefined4 *)((param_1->m_gameWork).m_linkTable[0][2][6] + 4);
        *(undefined4 *)(param_1->m_gameWork).m_linkTable[2][7][1] =
             *(undefined4 *)(param_1->m_gameWork).m_linkTable[0][2][7];
        *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][7][1] + 4) =
             *(undefined4 *)((param_1->m_gameWork).m_linkTable[0][2][7] + 4);
        *(undefined4 *)(param_1->m_gameWork).m_linkTable[2][7][2] =
             *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][7][0] + 4);
        *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][7][2] + 4) =
             *(undefined4 *)(param_1->m_gameWork).m_linkTable[2][7][1];
        *(undefined4 *)(param_1->m_gameWork).m_linkTable[2][7][3] =
             *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][7][1] + 4);
        iVar4 = Rand__5CMathFUl(&Math,4);
        if (iVar4 == 2) {
          paauVar3 = (param_1->m_gameWork).m_linkTable[2] + 2;
          ((uint8_t *)((int)paauVar3 + 0x38))[0] = '\0';
          ((uint8_t *)((int)paauVar3 + 0x38))[1] = '\0';
          ((uint8_t *)((int)paauVar3 + 0x38))[2] = '\x02';
          ((uint8_t *)((int)paauVar3 + 0x38))[3] = '2';
        }
        else if (iVar4 < 2) {
          if (iVar4 == 0) {
            paauVar3 = (param_1->m_gameWork).m_linkTable[2] + 2;
            ((uint8_t *)((int)paauVar3 + 0x38))[0] = '\0';
            ((uint8_t *)((int)paauVar3 + 0x38))[1] = '\0';
            ((uint8_t *)((int)paauVar3 + 0x38))[2] = '\x02';
            ((uint8_t *)((int)paauVar3 + 0x38))[3] = '0';
          }
          else if (-1 < iVar4) {
            paauVar3 = (param_1->m_gameWork).m_linkTable[2] + 2;
            ((uint8_t *)((int)paauVar3 + 0x38))[0] = '\0';
            ((uint8_t *)((int)paauVar3 + 0x38))[1] = '\0';
            ((uint8_t *)((int)paauVar3 + 0x38))[2] = '\x02';
            ((uint8_t *)((int)paauVar3 + 0x38))[3] = '1';
          }
        }
        else if (iVar4 < 4) {
          paauVar3 = (param_1->m_gameWork).m_linkTable[2] + 2;
          ((uint8_t *)((int)paauVar3 + 0x38))[0] = '\0';
          ((uint8_t *)((int)paauVar3 + 0x38))[1] = '\0';
          ((uint8_t *)((int)paauVar3 + 0x38))[2] = '\x02';
          ((uint8_t *)((int)paauVar3 + 0x38))[3] = '8';
        }
      }
      endPSlotBit__10CGCharaObjFi(param_1,0x10);
      endPSlotBit__10CGCharaObjFi(param_1,0x100);
      if ((*(uint *)((param_1->m_gameWork).m_linkTable[2][1][7] + 4) & 2) != 0) {
        _GetNumCombi__12CCaravanWorkFi
                  ((CCaravanWork *)(param_1->m_gameWork).m_bossArtifactStageTable[10],
                   *(undefined4 *)((param_1->m_gameWork).m_linkTable[3][0][2] + 4),1);
      }
    }
    if ((*(int *)(param_1->m_gameWork).m_linkTable[2][2][1] == 8) &&
       (*(int *)(param_1->m_gameWork).m_linkTable[3][0][0] != 0)) {
      sendCombiToScript__10CGCharaObjFP10CGCharaObjii
                (param_1,*(undefined4 *)(param_1->m_gameWork).m_linkTable[2][7][6],
                 *(undefined4 *)((param_1->m_gameWork).m_linkTable[2][7][6] + 4));
    }
    moveCenterTargetParticle__10CGPartyObjFv(param_1);
    if (0x11 < *(int *)(param_1->m_gameWork).m_linkTable[2][2][1]) {
      (param_1->m_gameWork).m_linkTable[2][6][2][4] =
           (param_1->m_gameWork).m_linkTable[2][6][2][4] & 0x7f | 0x80;
    }
    iVar4 = isLoopAnim__8CGPrgObjFv((CGPrgObj *)param_1);
    if (iVar4 != 0) {
      changeStat__8CGPrgObjFiii((CGPrgObj *)param_1,0,0,0);
      return;
    }
  }
  if (*(int *)((param_1->m_gameWork).m_linkTable[2][2][0] + 4) < 2) {
    bVar2 = false;
    bVar1 = false;
    bVar8 = false;
    uVar5 = countLeadingZeros(0x103 - *(int *)(param_1->m_gameWork).m_linkTable[2][2][7]);
    if ((Game.game.m_gameWork.m_menuStageMode != '\0') &&
       (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xf)) {
      bVar8 = true;
    }
    if (bVar8) {
      uVar6 = (**(code **)((param_1->m_gameWork).m_bossArtifactStageTable[6] + 0xc))(param_1);
      uVar6 = countLeadingZeros(0x6d - (uVar6 & 0x6d));
      if ((uVar6 >> 5 & 0xff) != 0) {
        bVar1 = true;
      }
    }
    if ((bVar1) && (*(int *)((param_1->m_gameWork).m_bossArtifactStageTable[10] + 0x3b4) != 0)) {
      bVar2 = true;
    }
    if (bVar2) {
      if (((*(int *)((param_1->m_gameWork).m_linkTable[2][2][0] + 4) == 1) &&
          (*(int *)(param_1->m_gameWork).m_linkTable[2][7][0] != 0)) &&
         ((int)((uint)(byte)m_boss__8CGMonObj._108_1_ << 0x19 |
               (uint)((byte)m_boss__8CGMonObj._108_1_ >> 7)) < 0)) {
        if (*(int *)(param_1->m_gameWork).m_linkTable[2][6][7] == 1) {
          putParticleTrace__8CGPrgObjFiiP8CGObjectfi
                    (SUB84((double)FLOAT_80331a54,0),(CGPrgObj *)param_1,
                     *(int *)((param_1->m_gameWork).m_bossArtifactStageTable[10] + 0x3b4) + 0x4fU |
                     0x100,*(int *)((param_1->m_gameWork).m_linkTable[2][3][3] + 4),
                     (CGObject *)param_1,0);
          playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)param_1,0x3e,0x32,0x96,0,0);
        }
        *(int *)(param_1->m_gameWork).m_linkTable[2][6][7] =
             *(int *)(param_1->m_gameWork).m_linkTable[2][6][7] + 1;
      }
    }
    else {
      bVar1 = false;
      uVar6 = (uint)(char)(param_1->m_gameWork).m_linkTable[0][0][7][2];
      if ((Pad._452_4_ != 0) || ((uVar6 == 0 && (Pad._448_4_ != -1)))) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar7 = 0;
      }
      else {
        uVar7 = *(ushort *)
                 (&Pad.field_0x4 +
                 (uVar6 & ~((int)~(Pad._448_4_ - uVar6 | uVar6 - Pad._448_4_) >> 0x1f)) * 0x54);
      }
      if ((uVar7 & 0x100) == 0) {
        iVar4 = *(int *)((param_1->m_gameWork).m_linkTable[2][2][0] + 4);
        if ((iVar4 == 0) ||
           ((iVar4 == 1 && (*(int *)(param_1->m_gameWork).m_linkTable[2][7][0] == 0)))) {
          if (uVar5 >> 5 == 0) {
            changeStat__8CGPrgObjFiii((CGPrgObj *)param_1,0,0,0);
          }
        }
        else {
          if (*(int *)(param_1->m_gameWork).m_linkTable[2][6][7] == 1) {
            putParticleTrace__8CGPrgObjFiiP8CGObjectfi
                      (SUB84((double)FLOAT_80331a54,0),(CGPrgObj *)param_1,
                       *(int *)((param_1->m_gameWork).m_bossArtifactStageTable[10] + 0x3b4) + 0x4fU
                       | 0x100,*(int *)((param_1->m_gameWork).m_linkTable[2][3][3] + 4),
                       (CGObject *)param_1,0);
            playSe3D__8CGPrgObjFiiiiP3Vec((CGPrgObj *)param_1,0x3e,0x32,0x96,0,0);
          }
          *(int *)(param_1->m_gameWork).m_linkTable[2][6][7] =
               *(int *)(param_1->m_gameWork).m_linkTable[2][6][7] + 1;
        }
      }
      else {
        bVar1 = false;
        if ((Pad._452_4_ != 0) || ((uVar6 == 0 && (Pad._448_4_ != -1)))) {
          bVar1 = true;
        }
        if (bVar1) {
          uVar7 = 0;
        }
        else {
          uVar7 = *(ushort *)
                   (&Pad.field_0x4 +
                   (uVar6 & ~((int)~(Pad._448_4_ - uVar6 | uVar6 - Pad._448_4_) >> 0x1f)) * 0x54);
        }
        if (((uVar7 & 0x200) != 0) && (uVar5 >> 5 == 0)) {
          changeStat__8CGPrgObjFiii((CGPrgObj *)param_1,0,0,0);
        }
      }
    }
  }
  return;
}

