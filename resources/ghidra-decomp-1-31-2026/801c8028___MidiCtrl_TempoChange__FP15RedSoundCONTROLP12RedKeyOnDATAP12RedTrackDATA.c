// Function: __MidiCtrl_TempoChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8028
// Size: 140 bytes

void __MidiCtrl_TempoChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (int param_1,undefined4 param_2,int *param_3)

{
  undefined4 uVar1;
  uint local_18 [3];
  
  if (*(char *)*param_3 == '\0') {
    local_18[0] = 0x100;
  }
  else {
    local_18[0] = (uint)*(byte *)*param_3;
  }
  uVar1 = DataAddCompute__FPiiPi(param_1 + 0x448,*(undefined *)(*param_3 + 1),local_18);
  *(undefined4 *)(param_1 + 0x44c) = uVar1;
  *(uint *)(param_1 + 0x450) = local_18[0];
  *param_3 = *param_3 + 2;
  return;
}

