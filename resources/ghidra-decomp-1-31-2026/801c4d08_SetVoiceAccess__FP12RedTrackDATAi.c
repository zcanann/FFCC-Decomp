// Function: SetVoiceAccess__FP12RedTrackDATAi
// Entry: 801c4d08
// Size: 80 bytes

void SetVoiceAccess__FP12RedTrackDATAi(int param_1,uint param_2)

{
  int *piVar1;
  
  piVar1 = DAT_8032f444;
  do {
    if ((*piVar1 != 0) && (*piVar1 == param_1)) {
      piVar1[0x24] = piVar1[0x24] | param_2;
    }
    piVar1 = piVar1 + 0x30;
  } while (piVar1 < DAT_8032f444 + 0xc00);
  return;
}

