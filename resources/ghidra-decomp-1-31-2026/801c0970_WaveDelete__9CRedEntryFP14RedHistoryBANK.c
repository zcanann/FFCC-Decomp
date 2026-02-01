// Function: WaveDelete__9CRedEntryFP14RedHistoryBANK
// Entry: 801c0970
// Size: 356 bytes

int WaveDelete__9CRedEntryFP14RedHistoryBANK(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  if (-1 < *param_2) {
    WaveHistoryDelete__9CRedEntryFi(param_1,param_2[1]);
    iVar2 = *param_2;
    *param_2 = -1;
    param_2[3] = 0;
    iVar3 = SearchWaveSequence__9CRedEntryFi(param_1,iVar2);
    if (iVar3 < 0) {
      iVar1 = SearchUseWave__9CRedEntryFi(param_1,iVar2);
      if ((iVar1 != 0) && (DAT_8032f408 != 0)) {
        OSReport(s__s_s__s_801e78d8,&DAT_801e7905,&DAT_80333d30,&DAT_80333d38);
        fflush(&DAT_8021d1a8);
        OSReport(s__s_s__________ERROR___________s_801e7917,&DAT_801e7905,&DAT_80333d30,
                 &DAT_80333d38);
        fflush(&DAT_8021d1a8);
        OSReport(s__s_s_Erase_Using_Wave_Data_____W_801e7944,&DAT_801e7905,&DAT_80333d30,iVar2,
                 &DAT_80333d38);
        fflush(&DAT_8021d1a8);
        OSReport(s__s_s__s_801e78d8,&DAT_801e7905,&DAT_80333d30,&DAT_80333d38);
        fflush(&DAT_8021d1a8);
      }
      RedDeleteA__Fi(*(undefined4 *)(param_2[2] + 0x10));
      RedDelete__Fi(param_2[2]);
    }
    param_2[2] = 0;
    param_2[1] = 0;
  }
  return iVar3;
}

