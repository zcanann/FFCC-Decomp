// Function: ?GetCurrentWeaponItem__12CCaravanWorkFRiRi
// Entry: 8009f1fc
// Size: 132 bytes

void _GetCurrentWeaponItem__12CCaravanWorkFRiRi(CCaravanWork *caravanWork,int *param_2,int *param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  sVar1 = caravanWork->m_weaponIdx;
  if (sVar1 == 0) {
    iVar4 = 0;
    *param_2 = 0;
    iVar3 = *(int *)((int)(caravanWork->gObjWork).m_ownerObj + 0x58);
    iVar2 = (int)*(short *)(iVar3 + 0xac);
    if (-1 < iVar2) {
      iVar4 = (int)*(short *)(iVar3 + iVar2 * 2 + 0xb6);
    }
    *param_3 = iVar4;
  }
  else if (sVar1 != 1) {
    *param_2 = (int)sVar1;
    iVar2 = _DelCmdListAndItem__12CCaravanWorkFii
                      (*(undefined4 *)((int)(caravanWork->gObjWork).m_ownerObj + 0x58),
                       (int)caravanWork->m_weaponIdx);
    *param_3 = iVar2;
  }
  return;
}

