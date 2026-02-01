// Function: _MusicCrossPlaySequence__FPi
// Entry: 801bd1fc
// Size: 520 bytes

void _MusicCrossPlaySequence__FPi(int *param_1)

{
  int iVar1;
  void *pvVar2;
  
  param_1[2] = param_1[2] * 200;
  iVar1 = param_1[2] / 0x3c + (param_1[2] >> 0x1f);
  param_1[2] = iVar1 - (iVar1 >> 0x1f);
  if (param_1[2] == 0) {
    param_1[2] = param_1[2] + 1;
  }
  pvVar2 = DAT_8032f3f0;
  if ((*param_1 != *(int *)((int)DAT_8032f3f0 + 0x470)) &&
     (*param_1 != *(int *)((int)DAT_8032f3f0 + 0xd98))) {
    if (*param_1 == *(int *)((int)DAT_8032f3f0 + 0x904)) {
      *(int *)((int)DAT_8032f3f0 + 0x458) = -*(int *)((int)DAT_8032f3f0 + 0x454) / param_1[2];
      *(int *)((int)pvVar2 + 0x45c) = param_1[2];
      pvVar2 = DAT_8032f3f0;
      *(int *)((int)DAT_8032f3f0 + 0x8ec) =
           (0x1ff800 - *(int *)((int)DAT_8032f3f0 + 0x8e8)) / param_1[2];
      *(int *)((int)pvVar2 + 0x8f0) = param_1[2];
      pvVar2 = (void *)RedNew__Fi(0x494);
      memcpy(pvVar2,(int)DAT_8032f3f0 + 0x494,0x494);
      memcpy((void *)((int)DAT_8032f3f0 + 0x494),DAT_8032f3f0,0x494);
      memcpy(DAT_8032f3f0,pvVar2,0x494);
      RedDelete__FPv(pvVar2);
    }
    else {
      iVar1 = SearchMusicSequence__9CRedEntryFi(&DAT_8032e154,*param_1);
      if (-1 < iVar1) {
        DAT_8032f42c = param_1[2];
        iVar1 = 0;
        if (*(int *)((int)pvVar2 + 0x470) != -1) {
          if (*(int *)((int)pvVar2 + 0x904) != -1) {
            MusicStop__Fi(*(undefined4 *)((int)pvVar2 + 0x904));
          }
          *(int *)((int)pvVar2 + 0x458) = -*(int *)((int)pvVar2 + 0x454) / param_1[2];
          *(int *)((int)pvVar2 + 0x45c) = param_1[2];
          iVar1 = *(int *)(DAT_8032f418 + *param_1 * 4);
          *(undefined4 *)(DAT_8032f418 + *param_1 * 4) = 0;
          if (iVar1 == 0) {
            memcpy((void *)((int)pvVar2 + 0x494),pvVar2,0x494);
            *(undefined4 *)((int)pvVar2 + 0x470) = 0xffffffff;
          }
        }
        MusicPlay__Fiii(*param_1,param_1[1],iVar1);
      }
    }
  }
  return;
}

