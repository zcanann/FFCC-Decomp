// Function: MusicOldClear__9CRedEntryFv
// Entry: 801c26dc
// Size: 140 bytes

int MusicOldClear__9CRedEntryFv(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = 0;
  uVar1 = 0;
  uVar3 = *(uint *)(param_1 + 8);
  do {
    if (iVar2 < *(int *)(uVar3 + 4)) {
      iVar2 = *(int *)(uVar3 + 4);
      uVar1 = uVar3;
    }
    uVar3 = uVar3 + 0x10;
  } while (uVar3 < *(int *)(param_1 + 8) + 0x40U);
  if (iVar2 != 0) {
    MusicMemoryFree__9CRedEntryFP14RedHistoryBANK(param_1,uVar1);
  }
  return iVar2;
}

