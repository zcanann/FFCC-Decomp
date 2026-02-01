// Function: _MusicNextPlaySequence__FPi
// Entry: 801bd404
// Size: 164 bytes

void _MusicNextPlaySequence__FPi(int *param_1)

{
  int iVar1;
  
  if ((((*param_1 != *(int *)(DAT_8032f3f0 + 0x470)) && (*param_1 != *(int *)(DAT_8032f3f0 + 0x904))
       ) && (*param_1 != *(int *)(DAT_8032f3f0 + 0xd98))) &&
     (iVar1 = SearchMusicSequence__9CRedEntryFi(&DAT_8032e154,*param_1), -1 < iVar1)) {
    *DAT_8032f428 = *param_1;
    DAT_8032f428[1] = param_1[1];
    DAT_8032f428[2] = param_1[2];
  }
  return;
}

