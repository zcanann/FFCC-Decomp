// Function: SeSepOldDelete__9CRedEntryFv
// Entry: 801c1cbc
// Size: 152 bytes

uint SeSepOldDelete__9CRedEntryFv(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = 0;
  iVar1 = 0;
  uVar3 = *(uint *)(param_1 + 4);
  do {
    if ((*(int *)(uVar3 + 0xc) != 0) && (iVar1 < *(int *)(uVar3 + 4))) {
      iVar1 = *(int *)(uVar3 + 4);
      uVar2 = uVar3;
    }
    uVar3 = uVar3 + 0x10;
  } while (uVar3 < *(int *)(param_1 + 4) + 0x1000U);
  if (uVar2 != 0) {
    SeSepMemoryFree__9CRedEntryFP14RedHistoryBANK(param_1,uVar2);
  }
  return uVar2;
}

