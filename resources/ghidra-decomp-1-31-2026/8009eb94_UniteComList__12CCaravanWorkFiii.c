// Function: UniteComList__12CCaravanWorkFiii
// Entry: 8009eb94
// Size: 152 bytes

void UniteComList__12CCaravanWorkFiii
               (CCaravanWork *caravanWork,int param_2,int param_3,undefined2 param_4)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  undefined local_18 [2];
  int16_t iStack_16;
  undefined auStack_14 [16];
  
  iVar3 = 0;
  iVar4 = param_3;
  if (0 < param_3) {
    do {
      uVar2 = 0xffff;
      if (iVar3 == 0) {
        uVar2 = param_4;
      }
      iVar1 = param_2 + iVar3;
      iVar3 = iVar3 + 1;
      *(undefined2 *)(caravanWork->m_commandListExtra + iVar1 * 2) = uVar2;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (((param_2 <= caravanWork->m_weaponIdx) && ((int)caravanWork->m_weaponIdx < param_2 + param_3))
     && (iVar4 = _GetCmdListItemName__12CCaravanWorkFi(caravanWork,param_2,auStack_14,local_18),
        iVar4 != 0)) {
    caravanWork->m_weaponIdx = iStack_16;
  }
  return;
}

