// Function: BackupTutorialItem__12CCaravanWorkFi
// Entry: 8009ec2c
// Size: 332 bytes

void BackupTutorialItem__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2)

{
  if (param_2 == 0) {
    memcpy(caravanWork->m_inventoryItems,caravanWork->m_backupInventoryBlock,0x148);
    caravanWork->m_inventoryItemCount = caravanWork->m_backupInventoryItemCount;
    memcpy(caravanWork->m_commandListInventorySlotRef,
           caravanWork->m_backupCommandListInventorySlotRef,0x10);
    memcpy(caravanWork->m_commandListExtra,caravanWork->m_backupCmdlistExtra,0x10);
    memcpy(caravanWork->m_equipment,caravanWork->m_backupEquipment,8);
    caravanWork->m_gil = caravanWork->m_backupGil;
    caravanWork->m_currentCmdListIndex = caravanWork->m_backupCurrentCmdListIndex;
    caravanWork->m_weaponIdx = caravanWork->m_backupWeaponIdx;
  }
  else {
    memcpy(caravanWork->m_backupInventoryBlock,caravanWork->m_inventoryItems,0x148);
    memset(caravanWork->m_inventoryItems,0xff,0x148);
    caravanWork->m_backupInventoryItemCount = caravanWork->m_inventoryItemCount;
    caravanWork->m_inventoryItemCount = 0;
    memcpy(caravanWork->m_backupCommandListInventorySlotRef,
           caravanWork->m_commandListInventorySlotRef,0x10);
    memset(caravanWork->m_commandListInventorySlotRef,0xff,0x10);
    memcpy(caravanWork->m_backupCmdlistExtra,caravanWork->m_commandListExtra,0x10);
    memset(caravanWork->m_commandListExtra,0,0x10);
    memcpy(caravanWork->m_backupEquipment,caravanWork->m_equipment,8);
    memset(caravanWork->m_equipment,0xff,8);
    caravanWork->m_backupGil = caravanWork->m_gil;
    caravanWork->m_gil = 0;
    caravanWork->m_backupCurrentCmdListIndex = caravanWork->m_currentCmdListIndex;
    caravanWork->m_currentCmdListIndex = 0;
    caravanWork->m_backupWeaponIdx = caravanWork->m_weaponIdx;
    caravanWork->m_weaponIdx = 0;
  }
  return;
}

