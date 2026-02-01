// Function: ChkCrc__14CMemoryCardManFPQ22Mc7SaveDat
// Entry: 800c2c70
// Size: 184 bytes

uint ChkCrc__14CMemoryCardManFPQ22Mc7SaveDat(CMemoryCardMan *memoryCardMan,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  if (param_2 == (byte *)0x0) {
    param_2 = memoryCardMan->m_saveBuffer;
  }
  pbVar4 = param_2;
  if (param_2 == (byte *)0x0) {
    pbVar4 = memoryCardMan->m_saveBuffer;
  }
  uVar2 = 0xffffffff;
  iVar3 = 0x1c;
  pbVar5 = pbVar4;
  while (iVar3 = iVar3 + -1, -1 < iVar3) {
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
    uVar2 = uVar2 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar2 >> 0x18 ^ (uint)bVar1) * 4);
  }
  pbVar4 = pbVar4 + 0x20;
  iVar3 = 0x8bb0;
  while (iVar3 = iVar3 + -1, -1 < iVar3) {
    bVar1 = *pbVar4;
    pbVar4 = pbVar4 + 1;
    uVar2 = uVar2 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar2 >> 0x18 ^ (uint)bVar1) * 4);
  }
  uVar2 = countLeadingZeros(~uVar2 - *(int *)(param_2 + 0x1c));
  return uVar2 >> 5;
}

