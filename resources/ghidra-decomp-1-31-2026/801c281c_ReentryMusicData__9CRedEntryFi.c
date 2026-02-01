// Function: ReentryMusicData__9CRedEntryFi
// Entry: 801c281c
// Size: 88 bytes

int ReentryMusicData__9CRedEntryFi(int param_1)

{
  int iVar1;
  
  iVar1 = SearchMusicSequence__9CRedEntryFi();
  if (-1 < iVar1) {
    MusicHistoryChoice__9CRedEntryFP14RedHistoryBANK(param_1,*(int *)(param_1 + 8) + iVar1 * 0x10);
  }
  return iVar1;
}

