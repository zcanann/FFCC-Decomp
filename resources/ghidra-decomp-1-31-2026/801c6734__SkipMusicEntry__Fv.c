// Function: _SkipMusicEntry__Fv
// Entry: 801c6734
// Size: 588 bytes

void _SkipMusicEntry__Fv(void)

{
  void *dstBuffer;
  int *piVar1;
  int *piVar2;
  undefined auStack_28 [24];
  
  piVar1 = DAT_8032f4b8;
  piVar2 = DAT_8032f3fc;
  if (-1 < *(int *)((int)DAT_8032f3f0 + 0xd98)) {
    do {
      if ((*piVar1 != 0) && (*piVar2 == 0)) {
        *piVar2 = *piVar1;
        piVar2[1] = piVar1[1];
        DAT_8032f3f8 = DAT_8032f3f8 + 1;
      }
      piVar1 = piVar1 + 2;
      piVar2 = piVar2 + 2;
    } while (piVar1 < DAT_8032f4b8 + 0x80);
    piVar1 = DAT_8032f4b8 + 0x80;
    for (piVar2 = DAT_8032f3fc + 0x80; (piVar2 < DAT_8032f3fc + 0x100 && (*piVar2 != 0));
        piVar2 = piVar2 + 2) {
    }
    for (; (piVar2 < DAT_8032f3fc + 0x100 && (piVar1 < DAT_8032f4b8 + 0x100)); piVar1 = piVar1 + 2)
    {
      if (*piVar1 != 0) {
        *piVar2 = *piVar1;
        piVar2[1] = piVar1[1];
        piVar2 = piVar2 + 2;
        DAT_8032f3f8 = DAT_8032f3f8 + 1;
      }
    }
    piVar1 = DAT_8032f4b8 + 0x100;
    for (piVar2 = DAT_8032f3fc + 0x100; (piVar2 < DAT_8032f3fc + 0x180 && (*piVar2 != 0));
        piVar2 = piVar2 + 2) {
    }
    for (; (dstBuffer = DAT_8032f3f0, piVar2 < DAT_8032f3fc + 0x180 &&
           (piVar1 < DAT_8032f4b8 + 0x180)); piVar1 = piVar1 + 2) {
      if (*piVar1 != 0) {
        *piVar2 = *piVar1;
        piVar2[1] = piVar1[1];
        piVar2 = piVar2 + 2;
        DAT_8032f3f8 = DAT_8032f3f8 + 1;
      }
    }
    if (*(int *)((int)DAT_8032f3f0 + 0x470) != -1) {
      if (*(int *)((int)DAT_8032f3f0 + 0x904) != -1) {
        MusicStop__Fi(*(undefined4 *)((int)DAT_8032f3f0 + 0x904));
      }
      memcpy((void *)((int)dstBuffer + 0x494),dstBuffer,0x494);
    }
    memcpy(dstBuffer,(int)dstBuffer + 0x928,0x494);
    memcpy(auStack_28,(int)dstBuffer + 0x944,0xc);
    memset((int)dstBuffer + 0x928,0,0x494);
    memcpy((void *)((int)dstBuffer + 0x944),auStack_28,0xc);
    *(undefined4 *)((int)dstBuffer + 0xd98) = 0xffffffff;
  }
  RedDelete__FPv(DAT_8032f4b8);
  DAT_8032f470 = 0;
  return;
}

