// Function: menu__10CGPartyObjFv
// Entry: 801238c8
// Size: 1160 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void menu__10CGPartyObjFv(CGPartyObj *partyObj)

{
  byte bVar1;
  uint8_t uVar2;
  bool bVar3;
  int iVar4;
  ushort uVar6;
  undefined4 uVar5;
  uint uVar7;
  void *portIndex;
  
  bVar1 = (partyObj->gCharaObj).field_0x6b8;
  portIndex = (partyObj->gCharaObj).gPrgObj.object.m_scriptHandle[0xed];
  if (-1 < (int)((uint)bVar1 << 0x1c | (uint)(bVar1 >> 4))) {
    if (Game.game.m_gameWork.m_menuStageMode != '\0') {
      return;
    }
    uVar2 = (partyObj->gCharaObj).gPrgObj.object.m_animStateMisc;
    bVar3 = false;
    uVar7 = (uint)(char)uVar2;
    if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
      bVar3 = true;
    }
    if (bVar3) {
      iVar4 = 0;
    }
    else {
      iVar4 = *(int *)(&Pad.field_0x54 +
                      (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54)
      ;
    }
    if (iVar4 == 0) {
      return;
    }
    if (2 < (uint)System.m_execParam) {
      uVar5 = GetCtrlMode__6JoyBusFi(&Joybus,(int)(char)uVar2);
      Printf__7CSystemFPce(&System,&DAT_801dcd78,portIndex,uVar5);
    }
    ChgCtrlMode__6JoyBusFi(&Joybus,portIndex);
    if ((CFlat._4768_4_ & 8) == 0) {
      return;
    }
    PlaySe__6CSoundFiiii(&Sound,8,0x40,0x7f,0);
    return;
  }
  if ((Game.game.m_gameWork.m_menuStageMode != '\0') ||
     (iVar4 = GetPadType__6JoyBusFi
                        (&Joybus,(int)(char)(partyObj->gCharaObj).gPrgObj.object.m_animStateMisc),
     iVar4 != 0x40000)) {
    if (Game.game.m_gameWork.m_menuStageMode == '\0') {
      return;
    }
    if (Game.game.m_gameWork.m_gamePaused != '\0') {
      return;
    }
    if ((partyObj->gCharaObj).gPrgObj.object.m_animStateMisc != '\0') {
      return;
    }
  }
  if (Game.game.m_gameWork.m_menuStageMode == '\0') {
    bVar3 = false;
    uVar7 = (uint)(char)(partyObj->gCharaObj).gPrgObj.object.m_animStateMisc;
    if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
      bVar3 = true;
    }
    if (bVar3) {
      uVar6 = 0;
    }
    else {
      uVar6 = *(ushort *)
               (&Pad.field_0xa +
               (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
    }
    if ((uVar6 & 0x10) != 0) goto LAB_80123a6c;
  }
  if (Game.game.m_gameWork.m_menuStageMode == '\0') {
    return;
  }
  bVar3 = false;
  uVar7 = (uint)(char)(partyObj->gCharaObj).gPrgObj.object.m_animStateMisc;
  if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
    bVar3 = true;
  }
  if (bVar3) {
    uVar6 = 0;
  }
  else {
    uVar6 = *(ushort *)
             (&Pad.field_0x8 +
             (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
  }
  if ((uVar6 & 0x800) == 0) {
    return;
  }
LAB_80123a6c:
  if (Game.game.m_gameWork.m_menuStageMode != '\0') {
    if ((((int)((uint)*(byte *)&(partyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags << 0x18) < 0)
        && ((((int)((uint)*(byte *)((int)&(partyObj->gCharaObj).gPrgObj.object.m_weaponNodeFlags + 1
                                   ) << 0x18) < 0 || ((*(ushort *)&partyObj->field_0x6f4 & 2) != 0))
            || ((*(ushort *)&partyObj->field_0x6f4 & 4) != 0)))) &&
       (((int)((uint)(byte)(partyObj->gCharaObj).field_0x63c << 0x18) < 0 &&
        (*(short *)((partyObj->gCharaObj).gPrgObj.object.m_scriptHandle + 7) != 0)))) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      ChgCtrlMode__6JoyBusFi(&Joybus,portIndex);
      Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = '\x01';
    }
    else {
      PlaySe__6CSoundFiiii(&Sound,4,0x40,0x7f,0);
    }
    return;
  }
  bVar3 = false;
  uVar7 = (uint)(char)(partyObj->gCharaObj).gPrgObj.object.m_animStateMisc;
  if ((Pad._452_4_ != 0) || ((uVar7 == 0 && (Pad._448_4_ != -1)))) {
    bVar3 = true;
  }
  if (bVar3) {
    iVar4 = 0;
  }
  else {
    iVar4 = *(int *)(&Pad.field_0x54 +
                    (uVar7 & ~((int)~(Pad._448_4_ - uVar7 | uVar7 - Pad._448_4_) >> 0x1f)) * 0x54);
  }
  if (iVar4 == 0) {
    if ((CFlat._4768_4_ & 8) != 0) {
      PlaySe__6CSoundFiiii(&Sound,7,0x40,0x7f,0);
    }
  }
  else if ((CFlat._4768_4_ & 8) != 0) {
    PlaySe__6CSoundFiiii(&Sound,8,0x40,0x7f,0);
  }
  ChgCtrlMode__6JoyBusFi(&Joybus,portIndex);
  return;
}

