// Function: ClearSeSepData__9CRedEntryFi
// Entry: 801c1f50
// Size: 180 bytes

int ClearSeSepData__9CRedEntryFi(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = 0;
  if (param_2 == -1) {
    uVar2 = *(uint *)(param_1 + 4);
    do {
      if (*(int *)(uVar2 + 0xc) != 0) {
        SeSepMemoryFree__9CRedEntryFP14RedHistoryBANK(param_1,uVar2);
      }
      uVar2 = uVar2 + 0x10;
    } while (uVar2 < *(int *)(param_1 + 4) + 0x1000U);
  }
  else {
    iVar1 = SearchSeSepSequence__9CRedEntryFi(param_1,param_2);
    if (-1 < iVar1) {
      iVar1 = SeSepMemoryFree__9CRedEntryFP14RedHistoryBANK
                        (param_1,*(int *)(param_1 + 4) + iVar1 * 0x10);
    }
  }
  return iVar1;
}

