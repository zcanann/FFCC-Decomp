// Function: UnuniteComList__12CCaravanWorkFii
// Entry: 8009ea48
// Size: 332 bytes

void UnuniteComList__12CCaravanWorkFii(CCaravanWork *caravanWork,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined local_18 [2];
  int16_t iStack_16;
  undefined auStack_14 [8];
  
  if ((caravanWork->m_weaponIdx == param_2) &&
     (iVar2 = _GetCmdListItemName__12CCaravanWorkFi(caravanWork,param_2,auStack_14,local_18),
     iVar2 != 0)) {
    caravanWork->m_weaponIdx = iStack_16;
  }
  iVar2 = 0;
  if (0 < param_3) {
    if ((8 < param_3) && (uVar4 = param_3 - 1U >> 3, 0 < param_3 + -8)) {
      do {
        iVar3 = param_2 + iVar2;
        iVar2 = iVar2 + 8;
        (caravanWork->m_commandListExtra + iVar3 * 2)[0] = '\0';
        (caravanWork->m_commandListExtra + iVar3 * 2)[1] = '\0';
        caravanWork->m_backupEquipment[iVar3 + -9] = 0;
        caravanWork->m_backupEquipment[iVar3 + -8] = 0;
        caravanWork->m_backupEquipment[iVar3 + -7] = 0;
        caravanWork->m_backupEquipment[iVar3 + -6] = 0;
        caravanWork->m_backupEquipment[iVar3 + -5] = 0;
        caravanWork->m_backupEquipment[iVar3 + -4] = 0;
        caravanWork->m_backupEquipment[iVar3 + -3] = 0;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
    iVar3 = param_3 - iVar2;
    if (iVar2 < param_3) {
      do {
        iVar1 = param_2 + iVar2;
        iVar2 = iVar2 + 1;
        (caravanWork->m_commandListExtra + iVar1 * 2)[0] = '\0';
        (caravanWork->m_commandListExtra + iVar1 * 2)[1] = '\0';
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
  }
  return;
}

