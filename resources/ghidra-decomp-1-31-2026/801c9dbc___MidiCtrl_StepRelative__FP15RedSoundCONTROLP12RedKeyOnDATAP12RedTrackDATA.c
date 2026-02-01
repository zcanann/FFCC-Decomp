// Function: __MidiCtrl_StepRelative__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9dbc
// Size: 128 bytes

void __MidiCtrl_StepRelative__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  char cVar1;
  short sVar2;
  char *pcVar3;
  
  pcVar3 = (char *)*param_3;
  *param_3 = pcVar3 + 1;
  cVar1 = *pcVar3;
  if (cVar1 == '\0') {
    sVar2 = 0;
  }
  else {
    sVar2 = *(short *)(param_3 + 0x4e) + (short)cVar1;
  }
  *(short *)(param_3 + 0x4e) = sVar2;
  *(undefined2 *)((int)param_3 + 0x13a) = 0;
  if (*(short *)(param_3 + 0x4e) < -9999) {
    *(undefined2 *)(param_3 + 0x4e) = 0xd8f1;
  }
  else if (9999 < *(short *)(param_3 + 0x4e)) {
    *(undefined2 *)(param_3 + 0x4e) = 9999;
  }
  return;
}

