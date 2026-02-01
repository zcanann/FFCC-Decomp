// Function: ?GetMagicCharge__12CCaravanWorkFiRiRi
// Entry: 8009f890
// Size: 332 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

uint _GetMagicCharge__12CCaravanWorkFiRiRi(CCaravanWork *caravanWork,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint16_t *puVar5;
  int iVar6;
  
  uVar1 = 0;
  if ((1 < param_2) && (caravanWork->m_commandListInventorySlotRef[param_2] == 0xffff)) {
    uVar1 = 1;
  }
  uVar2 = countLeadingZeros(uVar1);
  if (uVar2 >> 5 == 0) {
    return 0;
  }
  if (Game.game.m_gameWork.m_menuStageMode == '\0') {
    iVar6 = 1;
  }
  else {
    puVar5 = (caravanWork->gObjWork).m_elementResistances + param_2 + -0x14;
    if (puVar5[0x10a] == 0) {
      iVar6 = 1;
    }
    else {
      iVar3 = param_2 + 1;
      iVar4 = param_2;
      if (-1 < param_2) {
        do {
          if (puVar5[0x10a] != -1) break;
          puVar5 = puVar5 + -1;
          iVar4 = iVar4 + -1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      iVar6 = 1;
      iVar3 = (int)(short)caravanWork->m_numCmdListSlots - (iVar4 + 1);
      puVar5 = (caravanWork->gObjWork).m_elementResistances + iVar4 + -0x13;
      if (iVar4 + 1 < (int)(short)caravanWork->m_numCmdListSlots) {
        do {
          if (puVar5[0x10a] != -1) break;
          iVar6 = iVar6 + 1;
          puVar5 = puVar5 + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
  }
  if (iVar6 == 1) {
    uVar2 = countLeadingZeros(param_2 - (short)caravanWork->m_currentCmdListIndex);
    return uVar2 >> 5 & 0xff;
  }
  iVar4 = param_2 + 1;
  puVar5 = (caravanWork->gObjWork).m_elementResistances + param_2 + -0x14;
  if (-1 < param_2) {
    do {
      if (puVar5[0x10a] != -1) break;
      puVar5 = puVar5 + -1;
      param_2 = param_2 + -1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  uVar2 = 0;
  if ((param_2 <= (short)caravanWork->m_currentCmdListIndex) &&
     ((int)(short)caravanWork->m_currentCmdListIndex <= param_2 + iVar6 + -1)) {
    uVar2 = 1;
  }
  return uVar2;
}

