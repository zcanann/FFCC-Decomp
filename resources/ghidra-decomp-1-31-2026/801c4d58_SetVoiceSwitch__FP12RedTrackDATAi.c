// Function: SetVoiceSwitch__FP12RedTrackDATAi
// Entry: 801c4d58
// Size: 72 bytes

void SetVoiceSwitch__FP12RedTrackDATAi(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = DAT_8032f444;
  do {
    if ((*piVar1 != 0) && (*piVar1 == param_1)) {
      piVar1[0x25] = param_2;
    }
    piVar1 = piVar1 + 0x30;
  } while (piVar1 < DAT_8032f444 + 0xc00);
  return;
}

