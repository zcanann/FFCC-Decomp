// Function: clearCaravanWork__12CCaravanWorkFv
// Entry: 800a2a64
// Size: 312 bytes

void clearCaravanWork__12CCaravanWorkFv(CCaravanWork *caravanWork)

{
  caravanWork->m_letterCount = 0;
  caravanWork->m_gil = 0;
  caravanWork->unk_0x3c8 = '\0';
  caravanWork->unk_0x3c9 = '\0';
  caravanWork->m_equipment[0] = -1;
  caravanWork->m_equipment[1] = -1;
  caravanWork->m_equipment[2] = -1;
  caravanWork->m_equipment[3] = -1;
  caravanWork->m_inventoryItemCount = 0;
  memset(caravanWork->m_inventoryItems,0xff,0x148);
  memset(caravanWork->m_evtWorkArr,0,0x100);
  memset(caravanWork->m_evtWordArr,0,0x200);
  caravanWork->m_tempStatBuffTimer = 0;
  caravanWork->m_tempStatBuffId = 0;
  caravanWork->unk_0x3e6 = 0;
  caravanWork->m_evtState0 = 0;
  caravanWork->m_evtState1 = 0;
  memset(caravanWork->m_commandListInventorySlotRef,0xff,0x10);
  memset(caravanWork->m_commandListExtra,0,0x10);
  memset(&caravanWork->m_bonusCondition,0,1);
  memset(caravanWork->m_equipEffectParams,0,7);
  memset(&caravanWork->m_shopBusyFlag,0,1);
  memset(&caravanWork->m_caravanLocalFlags,0,1);
  caravanWork->m_inventoryItemCount = 0;
  memset(caravanWork->m_inventoryItems,0xff,0x148);
  caravanWork->m_progressValue = 0;
  caravanWork->m_numCmdListSlots = 4;
  caravanWork->m_baseCmdListSlots = 4;
  caravanWork->m_currentCmdListIndex = 0;
  caravanWork->m_weaponIdx = 0;
  caravanWork->m_equipEffectFlags = 0;
  caravanWork->unk_0xc1e = '\0';
  caravanWork->m_shopRandSeed = 0;
  return;
}

