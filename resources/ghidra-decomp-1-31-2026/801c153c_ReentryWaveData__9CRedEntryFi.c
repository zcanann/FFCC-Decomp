// Function: ReentryWaveData__9CRedEntryFi
// Entry: 801c153c
// Size: 88 bytes

int ReentryWaveData__9CRedEntryFi(int *param_1)

{
  int iVar1;
  
  iVar1 = SearchWaveSequence__9CRedEntryFi();
  if (-1 < iVar1) {
    WaveHistoryChoice__9CRedEntryFP14RedHistoryBANK(param_1,*param_1 + iVar1 * 0x10);
  }
  return iVar1;
}

