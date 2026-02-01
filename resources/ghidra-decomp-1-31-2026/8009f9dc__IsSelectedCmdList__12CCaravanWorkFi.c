// Function: ?IsSelectedCmdList__12CCaravanWorkFi
// Entry: 8009f9dc
// Size: 52 bytes

uint _IsSelectedCmdList__12CCaravanWorkFi(CCaravanWork *caravanWork,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar1 = 0;
  if ((1 < param_2) && (caravanWork->m_commandListInventorySlotRef[param_2] == 0xffff)) {
    uVar1 = 1;
  }
  uVar2 = countLeadingZeros(uVar1);
  return uVar2 >> 5;
}

