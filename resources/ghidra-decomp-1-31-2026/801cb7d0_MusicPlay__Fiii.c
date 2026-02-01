// Function: MusicPlay__Fiii
// Entry: 801cb7d0
// Size: 160 bytes

undefined4 MusicPlay__Fiii(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = SearchMusicBank__9CRedEntryFi(&DAT_8032e154,param_1);
  if (iVar1 != 0) {
    iVar2 = *(int *)(iVar1 + 8);
    iVar1 = SearchWaveBase__9CRedEntryFi(&DAT_8032e154,(int)*(short *)(iVar2 + 6));
    if (iVar1 == 0) {
      return 0xffffffff;
    }
    _MusicPlayStart__FP12RedMusicHEADP13RedWaveHeadWDiii(iVar2,iVar1,param_1,param_2,param_3);
  }
  return 0;
}

