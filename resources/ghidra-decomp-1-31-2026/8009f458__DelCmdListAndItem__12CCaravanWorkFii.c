// Function: ?DelCmdListAndItem__12CCaravanWorkFii
// Entry: 8009f458
// Size: 448 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int _DelCmdListAndItem__12CCaravanWorkFii(CCaravanWork *caravanWork,int param_2)

{
  short *psVar1;
  uint16_t uVar2;
  int iVar3;
  int iVar4;
  uint16_t *puVar5;
  int iVar6;
  int local_18;
  undefined auStack_14 [12];
  
  puVar5 = (caravanWork->gObjWork).m_elementResistances + param_2 + -0x14;
  psVar1 = (short *)(puVar5 + 0x102);
  if (param_2 == 0) {
    if (caravanWork->m_equipment[0] < 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = (int)(short)caravanWork->m_inventoryItems[caravanWork->m_equipment[0]];
    }
  }
  else if (param_2 == 1) {
    if (caravanWork->m_equipment[2] < 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = (int)(short)caravanWork->m_inventoryItems[caravanWork->m_equipment[2]];
    }
  }
  else {
    if (Game.game.m_gameWork.m_menuStageMode == '\0') {
      iVar6 = 1;
    }
    else if (puVar5[0x10a] == 0) {
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
    if (iVar6 < 2) {
      if (*psVar1 < 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = (int)(short)caravanWork->m_inventoryItems[*psVar1];
      }
    }
    else {
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
      uVar2 = *(uint16_t *)(caravanWork->m_commandListExtra + param_2 * 2);
      iVar4 = _GetCmdListItemName__12CCaravanWorkFi(caravanWork,param_2,auStack_14,&local_18);
      if (iVar4 != 0) {
        uVar2 = caravanWork->m_inventoryItems
                [(short)caravanWork->m_commandListInventorySlotRef[local_18]];
      }
      iVar4 = (int)(short)uVar2;
    }
  }
  return iVar4;
}

