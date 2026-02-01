// Function: CalcCrc__14CMemoryCardManFPQ22Mc7SaveDat
// Entry: 800c2d28
// Size: 148 bytes

uint CalcCrc__14CMemoryCardManFPQ22Mc7SaveDat(CMemoryCardMan *memoryCardMan,byte *param_2)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  if (param_2 == (byte *)0x0) {
    param_2 = memoryCardMan->m_saveBuffer;
  }
  uVar4 = 0xffffffff;
  iVar2 = 0x1c;
  pbVar3 = param_2;
  while( true ) {
    iVar2 = iVar2 + -1;
    if (iVar2 < 0) break;
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
    uVar4 = uVar4 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar4 >> 0x18 ^ (uint)bVar1) * 4);
  }
  pbVar3 = param_2 + 0x20;
  iVar2 = 0x8bb0;
  while( true ) {
    iVar2 = iVar2 + -1;
    if (iVar2 < 0) break;
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
    uVar4 = uVar4 << 8 ^ *(uint *)(&DAT_801daa0c + (uVar4 >> 0x18 ^ (uint)bVar1) * 4);
  }
  return ~uVar4;
}

