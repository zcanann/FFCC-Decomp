// Function: MusicOldChoice__9CRedEntryFv
// Entry: 801c2768
// Size: 112 bytes

uint MusicOldChoice__9CRedEntryFv(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 0;
  iVar1 = 0;
  uVar3 = *(uint *)(param_1 + 8);
  do {
    if (*(int *)(uVar3 + 0xc) == 0) {
      return uVar3;
    }
    if (iVar1 < *(int *)(uVar3 + 4)) {
      iVar1 = *(int *)(uVar3 + 4);
      uVar2 = uVar3;
    }
    uVar3 = uVar3 + 0x10;
  } while (uVar3 < *(int *)(param_1 + 8) + 0x40U);
  return uVar2;
}

