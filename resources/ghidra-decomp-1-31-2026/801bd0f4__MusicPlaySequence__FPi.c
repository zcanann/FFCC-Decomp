// Function: _MusicPlaySequence__FPi
// Entry: 801bd0f4
// Size: 264 bytes

void _MusicPlaySequence__FPi(int *param_1)

{
  int srcBuffer;
  int iVar1;
  
  srcBuffer = DAT_8032f3f0;
  if ((((*param_1 != *(int *)(DAT_8032f3f0 + 0x470)) && (*param_1 != *(int *)(DAT_8032f3f0 + 0x904))
       ) && (*param_1 != *(int *)(DAT_8032f3f0 + 0xd98))) &&
     (iVar1 = SearchMusicSequence__9CRedEntryFi(&DAT_8032e154,*param_1), -1 < iVar1)) {
    iVar1 = param_1[2];
    if (*(int *)(srcBuffer + 0x470) != -1) {
      if (*(int *)(srcBuffer + 0x904) != -1) {
        MusicStop__Fi(*(undefined4 *)(srcBuffer + 0x904));
      }
      if (iVar1 == 0) {
        iVar1 = *(int *)(DAT_8032f418 + *param_1 * 4);
        *(undefined4 *)(DAT_8032f418 + *param_1 * 4) = 0;
      }
      if (iVar1 == 0) {
        memcpy((void *)(srcBuffer + 0x494),srcBuffer,0x494);
        *(undefined4 *)(srcBuffer + 0x470) = 0xffffffff;
      }
    }
    MusicPlay__Fiii(*param_1,param_1[1],iVar1);
  }
  return;
}

