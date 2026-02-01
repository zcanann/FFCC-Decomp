// Function: DecodeData__14CMemoryCardManFv
// Entry: 800c1f20
// Size: 208 bytes

void DecodeData__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  puVar3 = (uint *)(memoryCardMan->m_saveBuffer + 0x18);
  uVar2 = 0x20 - (memoryCardMan->m_saveBuffer[0x11] & 0x1f);
  iVar4 = 0x5b6;
  do {
    uVar1 = *puVar3;
    uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    *puVar3 = uVar1 << (uVar2 & 0x1f) | uVar1 >> 0x20 - (uVar2 & 0x1f);
    uVar1 = puVar3[1];
    uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    puVar3[1] = uVar1 << (uVar2 & 0x1f) | uVar1 >> 0x20 - (uVar2 & 0x1f);
    uVar1 = puVar3[2];
    uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    puVar3[2] = uVar1 << (uVar2 & 0x1f) | uVar1 >> 0x20 - (uVar2 & 0x1f);
    uVar1 = puVar3[3];
    uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    puVar3[3] = uVar1 << (uVar2 & 0x1f) | uVar1 >> 0x20 - (uVar2 & 0x1f);
    uVar1 = puVar3[4];
    uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    puVar3[4] = uVar1 << (uVar2 & 0x1f) | uVar1 >> 0x20 - (uVar2 & 0x1f);
    uVar1 = puVar3[5];
    uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    puVar3[5] = uVar1 << (uVar2 & 0x1f) | uVar1 >> 0x20 - (uVar2 & 0x1f);
    uVar1 = puVar3[6];
    uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    puVar3[6] = uVar1 << (uVar2 & 0x1f) | uVar1 >> 0x20 - (uVar2 & 0x1f);
    puVar3 = puVar3 + 7;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}

