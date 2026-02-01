// Function: MusicHistoryManager__9CRedEntryFii
// Entry: 801c2874
// Size: 324 bytes

void MusicHistoryManager__9CRedEntryFii(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  
  if (param_2 == 0) {
    bVar1 = false;
    if ((*(short *)(DAT_8032f3f0 + 0x48e) != 0) && (*(int *)(DAT_8032f3f0 + 0x470) == param_3)) {
      bVar1 = true;
    }
    if ((*(short *)(DAT_8032f3f0 + 0x922) != 0) && (*(int *)(DAT_8032f3f0 + 0x904) == param_3)) {
      bVar1 = true;
    }
    if (((!bVar1) && (iVar2 = SearchMusicSequence__9CRedEntryFi(param_1,param_3), -1 < iVar2)) &&
       (*(int *)(*(int *)(param_1 + 8) + iVar2 * 0x10 + 4) == 0)) {
      MusicHistoryAdd__9CRedEntryFv(param_1);
      *(undefined4 *)(*(int *)(param_1 + 8) + iVar2 * 0x10 + 4) = 1;
    }
  }
  else {
    iVar2 = SearchMusicSequence__9CRedEntryFi(param_1,param_3);
    if ((-1 < iVar2) && (*(int *)(*(int *)(param_1 + 8) + iVar2 * 0x10 + 4) != 0)) {
      MusicHistoryDelete__9CRedEntryFi
                (param_1,*(undefined4 *)(*(int *)(param_1 + 8) + iVar2 * 0x10 + 4));
      *(undefined4 *)(*(int *)(param_1 + 8) + iVar2 * 0x10 + 4) = 0;
    }
  }
  return;
}

