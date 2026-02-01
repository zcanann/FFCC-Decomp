// Function: EntryVoiceSearch__FP12RedTrackDATA
// Entry: 801c3c44
// Size: 368 bytes

int * EntryVoiceSearch__FP12RedTrackDATA(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  piVar1 = (int *)0x0;
  if ((*(byte *)(param_1 + 0x26) & 5) == 0) {
    piVar4 = DAT_8032f444;
    if ((*(byte *)(param_1 + 0x26) & 8) == 0) {
      piVar4 = DAT_8032f444 + *(char *)(DAT_8032f3f4 + 0x490) * 0x30;
    }
    iVar3 = 0x8000;
    piVar2 = DAT_8032f444 + 0xc00;
    do {
      if ((*(byte *)((int)piVar4 + 0x1a) & 3) == 0) {
        if (piVar4[0x2c] < 1) {
          if (*piVar4 != 0) {
            *piVar4 = 0;
          }
          break;
        }
        if (piVar4[0x2c] < iVar3) {
          iVar3 = piVar4[0x2c];
          piVar1 = piVar4;
        }
      }
      piVar4 = piVar4 + 0x30;
    } while (piVar4 < piVar2);
    if ((piVar4 == piVar2) &&
       (*(uint *)(DAT_8032f3f4 + 0x488) = *(uint *)(DAT_8032f3f4 + 0x488) | 2, piVar4 = piVar1,
       iVar3 == 0x8000)) {
      piVar4 = (int *)0x0;
    }
  }
  else if ((((*(byte *)(param_1 + 0x26) & 1) == 0) &&
           (DAT_8032f444[*(char *)(param_1 + 0x14e) * 0x30] != 0)) &&
          (DAT_8032f444[*(char *)(param_1 + 0x14e) * 0x30] != param_1)) {
    piVar4 = (int *)0x0;
  }
  else {
    piVar4 = DAT_8032f444 + *(char *)(param_1 + 0x14e) * 0x30;
  }
  if (piVar4 != (int *)0x0) {
    piVar4[0x24] = piVar4[0x24] & 0xfffffffd;
    piVar4[0x2c] = 0x8000;
  }
  return piVar4;
}

