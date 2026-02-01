// Function: KeyOnReserveClear__FP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c74c8
// Size: 60 bytes

void KeyOnReserveClear__FP12RedKeyOnDATAP12RedTrackDATA(int *param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = param_1;
  do {
    if (*piVar1 == param_2) {
      *piVar1 = 0;
    }
    piVar1 = piVar1 + 2;
  } while (piVar1 < param_1 + 0x180);
  return;
}

