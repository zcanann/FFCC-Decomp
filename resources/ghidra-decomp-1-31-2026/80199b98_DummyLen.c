// Function: DummyLen
// Entry: 80199b98
// Size: 196 bytes

uint DummyLen(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 1;
  iVar1 = OSGetTick();
  for (uVar3 = 0;
      (DAT_8032eb78 = iVar1 * 0x41c64e6d + 0x3039, uVar2 = (DAT_8032eb78 >> 0x10 & 0x1f) + 1,
      uVar2 < 4 && (uVar3 < 10)); uVar3 = uVar3 + 1) {
    iVar1 = OSGetTick();
    iVar1 = iVar1 << uVar4;
    uVar4 = uVar4 + 1;
    if (0x10 < uVar4) {
      uVar4 = 1;
    }
  }
  if (uVar2 < 4) {
    uVar2 = 4;
  }
  return uVar2;
}

