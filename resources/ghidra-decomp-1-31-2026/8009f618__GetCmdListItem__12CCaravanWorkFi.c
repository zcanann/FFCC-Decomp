// Function: ?GetCmdListItem__12CCaravanWorkFi
// Entry: 8009f618
// Size: 148 bytes

undefined4 _GetCmdListItem__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined auStack_18 [4];
  int local_14 [3];
  
  uVar3 = 0xffffffff;
  iVar2 = _GetCmdListItemName__12CCaravanWorkFi(caravanWork,param_2,local_14,auStack_18);
  if (iVar2 != 0) {
    sVar1 = *(short *)(caravanWork->m_commandListExtra + local_14[0] * 2);
    if (sVar1 == 0x20b) {
      uVar3 = 1;
    }
    else if (sVar1 < 0x20b) {
      if (sVar1 == 0x207) {
        uVar3 = 0;
      }
    }
    else if (sVar1 == 0x20f) {
      uVar3 = 2;
    }
  }
  return uVar3;
}

