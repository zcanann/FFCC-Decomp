// Function: __MidiCtrl_StepRelative2__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9e3c
// Size: 128 bytes

void __MidiCtrl_StepRelative2__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte bVar1;
  short sVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)*param_3;
  *param_3 = pbVar3 + 1;
  bVar1 = *pbVar3;
  *(undefined2 *)(param_3 + 0x4e) = 0;
  if (bVar1 == 0) {
    sVar2 = 0;
  }
  else {
    sVar2 = *(short *)((int)param_3 + 0x13a) + (ushort)bVar1;
  }
  *(short *)((int)param_3 + 0x13a) = sVar2;
  if (*(short *)((int)param_3 + 0x13a) < -9999) {
    *(undefined2 *)((int)param_3 + 0x13a) = 0xd8f1;
  }
  else if (9999 < *(short *)((int)param_3 + 0x13a)) {
    *(undefined2 *)((int)param_3 + 0x13a) = 9999;
  }
  return;
}

