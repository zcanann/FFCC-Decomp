// Function: ghostPartyMog__10CGPartyObjFv
// Entry: 8011b268
// Size: 1320 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void ghostPartyMog__10CGPartyObjFv(CGPartyObj *gPartyObj)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  CGPartyObj *pCVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  double local_28;
  
  pCVar4 = Game.game.m_partyObjArr[0];
  gpmCol__10CGPartyObjFv();
  gpmMove__10CGPartyObjFv(gPartyObj);
  switch(Game.game.m_gameWork.m_bossArtifactStageIndex) {
  default:
    uVar7 = 0;
    break;
  case 4:
  case 8:
  case 9:
  case 0xb:
  case 0xc:
  case 0xd:
    uVar7 = 2;
    break;
  case 6:
  case 10:
    uVar7 = 1;
  }
  local_28 = (double)(CONCAT44(0x43300000,Chara._8276_4_) ^ 0x80000000);
  fVar1 = (float)(local_28 - DOUBLE_80331a60) / FLOAT_80331a50;
  if (uVar7 == 2) {
    fVar2 = FLOAT_80331a58 * fVar1 + FLOAT_80331a58;
  }
  else {
    fVar2 = FLOAT_80331a54;
    if ((uVar7 < 2) && (uVar7 != 0)) {
      fVar2 = FLOAT_80331a58 * (FLOAT_80331a54 - fVar1) + FLOAT_80331a58;
    }
  }
  uVar7 = (uint)(FLOAT_80331a5c * fVar2);
  if (DOUBLE_80331a90 < (double)*(float *)&(gPartyObj->gCharaObj).field_0x5d0) {
    m_boss__8CGMonObj._136_4_ = 1;
  }
  else {
    if ((((int)m_ghostWork__10CGPartyObj._4_4_ < (int)Chara._8264_4_) &&
        ((int)m_ghostWork__10CGPartyObj._8_4_ < (int)Chara._8268_4_)) &&
       ((int)m_ghostWork__10CGPartyObj._12_4_ < (int)Chara._8272_4_)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    if ((bVar3) &&
       (-1 < (int)((uint)(byte)m_boss__8CGMonObj._108_1_ << 0x1b |
                  (uint)((byte)m_boss__8CGMonObj._108_1_ >> 5)))) {
      m_boss__8CGMonObj._108_1_ = m_boss__8CGMonObj._108_1_ & 0xef | 0x10;
      m_boss__8CGMonObj._136_4_ = 2;
      putParticle__8CGPrgObjFiiP8CGObjectfi
                ((double)FLOAT_80331a54,(CGPrgObj *)gPartyObj,299,0,(CGObject *)gPartyObj,0);
    }
    else if (((int)((uint)(byte)m_boss__8CGMonObj._108_1_ << 0x1c) < 0) ||
            ((int)m_ghostWork__10CGPartyObj._24_4_ < 10)) {
      uVar8 = (uint)(byte)m_boss__8CGMonObj._108_1_ << 0x1d |
              (uint)((byte)m_boss__8CGMonObj._108_1_ >> 3);
      if (-1 < (int)uVar8) {
        switch(Game.game.m_gameWork.m_bossArtifactStageIndex) {
        default:
          uVar5 = 0;
          break;
        case 4:
        case 8:
        case 9:
        case 0xb:
        case 0xc:
        case 0xd:
          uVar5 = 2;
          break;
        case 6:
        case 10:
          uVar5 = 1;
        }
        if (uVar5 == 2) {
          fVar2 = FLOAT_80331a58 * fVar1 + FLOAT_80331a58;
        }
        else {
          fVar2 = FLOAT_80331a54;
          if ((uVar5 < 2) && (uVar5 != 0)) {
            fVar2 = FLOAT_80331a58 * (FLOAT_80331a54 - fVar1) + FLOAT_80331a58;
          }
        }
        if ((int)(FLOAT_80331a5c * fVar2) <= (int)m_ghostWork__10CGPartyObj._24_4_) {
          m_boss__8CGMonObj._108_1_ = m_boss__8CGMonObj._108_1_ & 0xfb | 4;
          m_boss__8CGMonObj._136_4_ = 3;
          goto LAB_8011b604;
        }
      }
      if (((int)uVar8 < 0) || ((int)m_ghostWork__10CGPartyObj._28_4_ < 0x97)) {
        m_boss__8CGMonObj._136_4_ = 0;
        m_ghostWork__10CGPartyObj._0_4_ = 0;
      }
      else {
        m_boss__8CGMonObj._136_4_ = 8;
      }
    }
    else {
      switch(Game.game.m_gameWork.m_bossArtifactStageIndex) {
      default:
        uVar8 = 0;
        break;
      case 4:
      case 8:
      case 9:
      case 0xb:
      case 0xc:
      case 0xd:
        uVar8 = 2;
        break;
      case 6:
      case 10:
        uVar8 = 1;
      }
      if (uVar8 == 1) {
        if ((int)Chara._8276_4_ < 0x32) {
          m_boss__8CGMonObj._136_4_ = 5;
        }
        else if (0x5e < (int)Chara._8276_4_) {
          m_boss__8CGMonObj._136_4_ = 4;
        }
      }
      else if (((uVar8 != 0) && (uVar8 < 3)) && ((int)Chara._8276_4_ < 0x32)) {
        m_boss__8CGMonObj._136_4_ = 6;
      }
      m_boss__8CGMonObj._108_1_ = m_boss__8CGMonObj._108_1_ & 0xf7 | 8;
    }
  }
LAB_8011b604:
  if ((((int)((uint)*(byte *)((int)&(pCVar4->gCharaObj).gPrgObj.object.m_weaponNodeFlags + 1) <<
             0x18) < 0) && (m_boss__8CGMonObj._136_4_ != 0)) &&
     (m_boss__8CGMonObj._136_4_ != m_ghostWork__10CGPartyObj._0_4_)) {
    bVar3 = false;
    if (((*(int *)(MenuPcs._288_4_ + 8) != 0) && (*(int *)(MenuPcs._288_4_ + 0xc) < 2)) &&
       (iVar6 = GetWait__4CMesFv(MenuPcs._288_4_ + 0x1c), iVar6 != 4)) {
      bVar3 = true;
    }
    if (!bVar3) {
      m_ghostWork__10CGPartyObj._0_4_ = m_boss__8CGMonObj._136_4_;
      Open__8CMesMenuFPciiiiii
                (MenuPcs._288_4_,
                 Game.game.m_cFlatDataArr[1].m_mesPtr[m_boss__8CGMonObj._136_4_ + -1],0x260,0x20,
                 0x8e20,0,0x65,0x8b);
    }
  }
  uVar8 = 0;
  if ((int)(uVar7 * 3) / 3 < (int)m_ghostWork__10CGPartyObj._24_4_) {
    uVar8 = 0xf;
  }
  else {
    uVar5 = uVar7 << 1;
    if (((int)uVar5 / 3 + ((int)(uVar5 | uVar7 >> 0x1f) >> 0x1f)) - ((int)uVar5 >> 0x1f) <
        (int)m_ghostWork__10CGPartyObj._24_4_) {
      uVar8 = 0xe;
    }
    else if ((int)uVar7 / 3 < (int)m_ghostWork__10CGPartyObj._24_4_) {
      uVar8 = 0xd;
    }
  }
  uVar7 = m_ghostWork__10CGPartyObj._108_4_;
  if ((m_ghostWork__10CGPartyObj._108_4_ != uVar8) &&
     (endPSlotBit__10CGCharaObjFi(gPartyObj,0x400), uVar7 = uVar8, uVar8 != 0)) {
    putParticle__8CGPrgObjFiiP8CGObjectfi
              ((double)FLOAT_80331a54,(CGPrgObj *)gPartyObj,uVar8 | 0x200,
               *(int *)&(gPartyObj->gCharaObj).field_0x58c,(CGObject *)gPartyObj,0);
  }
  m_ghostWork__10CGPartyObj._108_4_ = uVar7;
  return;
}

