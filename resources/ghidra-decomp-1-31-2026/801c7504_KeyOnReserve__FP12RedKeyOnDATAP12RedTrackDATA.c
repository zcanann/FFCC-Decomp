// Function: KeyOnReserve__FP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c7504
// Size: 240 bytes

void KeyOnReserve__FP12RedKeyOnDATAP12RedTrackDATA(int param_1,int param_2)

{
  int *piVar1;
  
  if ((*(byte *)(param_2 + 0x26) & 5) == 0) {
    if ((*(byte *)(param_2 + 0x26) & 8) == 0) {
      piVar1 = (int *)(param_1 + 0x400);
      do {
        if (*piVar1 == 0) {
          *piVar1 = param_2;
          piVar1[1] = *(int *)(param_2 + 0x24);
          DAT_8032f3f8 = DAT_8032f3f8 + 1;
          return;
        }
        piVar1 = piVar1 + 2;
      } while (piVar1 < (int *)(param_1 + 0x600));
    }
    else {
      piVar1 = (int *)(param_1 + 0x200);
      do {
        if (*piVar1 == 0) {
          *piVar1 = param_2;
          piVar1[1] = *(int *)(param_2 + 0x24);
          DAT_8032f3f8 = DAT_8032f3f8 + 1;
          return;
        }
        piVar1 = piVar1 + 2;
      } while (piVar1 < (int *)(param_1 + 0x400));
    }
  }
  else {
    piVar1 = (int *)(param_1 + *(char *)(param_2 + 0x14e) * 8);
    if ((*piVar1 == 0) || (*piVar1 == param_2)) {
      *piVar1 = param_2;
      piVar1[1] = *(int *)(param_2 + 0x24);
      DAT_8032f3f8 = DAT_8032f3f8 + 1;
    }
  }
  return;
}

