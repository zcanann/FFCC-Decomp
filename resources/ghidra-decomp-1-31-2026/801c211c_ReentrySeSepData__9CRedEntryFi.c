// Function: ReentrySeSepData__9CRedEntryFi
// Entry: 801c211c
// Size: 88 bytes

int ReentrySeSepData__9CRedEntryFi(int param_1)

{
  int iVar1;
  
  iVar1 = SearchSeSepSequence__9CRedEntryFi();
  if (-1 < iVar1) {
    SeSepHistoryChoice__9CRedEntryFP14RedHistoryBANK(param_1,*(int *)(param_1 + 4) + iVar1 * 0x10);
  }
  return iVar1;
}

