// Function: SetMusicData__9CRedEntryFP12RedMusicHEAD
// Entry: 801c2a60
// Size: 272 bytes

int SetMusicData__9CRedEntryFP12RedMusicHEAD(int param_1,char *param_2)

{
  int iVar1;
  
  if (((*param_2 == 'B') && (param_2[1] == 'G')) && (param_2[2] == 'M')) {
    iVar1 = SearchMusicSequence__9CRedEntryFi(param_1,(int)*(short *)(param_2 + 4));
    if (iVar1 < 0) {
      iVar1 = MusicHeadAdd__9CRedEntryFP12RedMusicHEAD(param_1,param_2);
      if (iVar1 == 0) {
        RedDelete__FPv(param_2);
      }
    }
    else {
      RedDelete__FPv(param_2);
      MusicHistoryChoice__9CRedEntryFP14RedHistoryBANK(param_1,*(int *)(param_1 + 8) + iVar1 * 0x10)
      ;
      iVar1 = *(int *)(*(int *)(param_1 + 8) + iVar1 * 0x10 + 8);
    }
  }
  else {
    RedDelete__FPv(param_2);
    if (DAT_8032f408 != 0) {
      OSReport(s__s_sMusic_Header_was_broken__s_801e7c1d,&DAT_801e7905,&DAT_80333d3d,&DAT_80333d38);
      fflush(&DAT_8021d1a8);
    }
    iVar1 = 0;
  }
  return iVar1;
}

