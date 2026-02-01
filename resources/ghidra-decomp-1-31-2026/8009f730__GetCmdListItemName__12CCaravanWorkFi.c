// Function: ?GetCmdListItemName__12CCaravanWorkFi
// Entry: 8009f730
// Size: 352 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

undefined4
_GetCmdListItemName__12CCaravanWorkFi
          (CCaravanWork *caravanWork,int param_2,int *param_3,int *param_4)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint16_t *puVar4;
  int iVar5;
  
  if (Game.game.m_gameWork.m_menuStageMode == '\0') {
    iVar5 = 1;
  }
  else {
    puVar4 = (caravanWork->gObjWork).m_elementResistances + param_2 + -0x14;
    if (puVar4[0x10a] == 0) {
      iVar5 = 1;
    }
    else {
      iVar2 = param_2 + 1;
      iVar3 = param_2;
      if (-1 < param_2) {
        do {
          if (puVar4[0x10a] != -1) break;
          puVar4 = puVar4 + -1;
          iVar3 = iVar3 + -1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      iVar5 = 1;
      iVar2 = (int)(short)caravanWork->m_numCmdListSlots - (iVar3 + 1);
      puVar4 = (caravanWork->gObjWork).m_elementResistances + iVar3 + -0x13;
      if (iVar3 + 1 < (int)(short)caravanWork->m_numCmdListSlots) {
        do {
          if (puVar4[0x10a] != -1) break;
          iVar5 = iVar5 + 1;
          puVar4 = puVar4 + 1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
    }
  }
  if (1 < iVar5) {
    iVar3 = param_2 + 1;
    puVar4 = (caravanWork->gObjWork).m_elementResistances + param_2 + -0x14;
    if (-1 < param_2) {
      do {
        if (puVar4[0x10a] != -1) break;
        puVar4 = puVar4 + -1;
        param_2 = param_2 + -1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    sVar1 = *(short *)(caravanWork->m_commandListExtra + param_2 * 2);
    if (((sVar1 == 0x207) || (sVar1 == 0x20b)) || (sVar1 == 0x20f)) {
      *param_3 = param_2;
      iVar3 = 0;
      if (0 < iVar5) {
        do {
          if (*(short *)(Game.game.unkCFlatData0[2] +
                        (short)caravanWork->m_inventoryItems
                               [(short)caravanWork->m_commandListInventorySlotRef[param_2 + iVar3]]
                        * 0x48) == 1) {
            *param_4 = param_2 + iVar3;
            return 1;
          }
          iVar3 = iVar3 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
    }
  }
  return 0;
}

