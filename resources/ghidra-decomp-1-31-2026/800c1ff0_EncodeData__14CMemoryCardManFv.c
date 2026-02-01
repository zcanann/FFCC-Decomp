// Function: EncodeData__14CMemoryCardManFv
// Entry: 800c1ff0
// Size: 204 bytes

void EncodeData__14CMemoryCardManFv(CMemoryCardMan *memoryCardMan)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  puVar3 = (uint *)(memoryCardMan->m_saveBuffer + 0x18);
  uVar1 = memoryCardMan->m_saveBuffer[0x11] & 0x1f;
  iVar4 = 0x5b6;
  do {
    uVar2 = *puVar3 << uVar1 | *puVar3 >> 0x20 - uVar1;
    *puVar3 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
              uVar2 >> 0x18;
    uVar2 = puVar3[1] << uVar1 | puVar3[1] >> 0x20 - uVar1;
    puVar3[1] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18;
    uVar2 = puVar3[2] << uVar1 | puVar3[2] >> 0x20 - uVar1;
    puVar3[2] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18;
    uVar2 = puVar3[3] << uVar1 | puVar3[3] >> 0x20 - uVar1;
    puVar3[3] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18;
    uVar2 = puVar3[4] << uVar1 | puVar3[4] >> 0x20 - uVar1;
    puVar3[4] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18;
    uVar2 = puVar3[5] << uVar1 | puVar3[5] >> 0x20 - uVar1;
    puVar3[5] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18;
    uVar2 = puVar3[6] << uVar1 | puVar3[6] >> 0x20 - uVar1;
    puVar3[6] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18;
    puVar3 = puVar3 + 7;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}

