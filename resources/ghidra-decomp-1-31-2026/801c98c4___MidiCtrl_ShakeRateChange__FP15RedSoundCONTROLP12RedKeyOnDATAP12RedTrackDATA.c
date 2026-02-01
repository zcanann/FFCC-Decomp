// Function: __MidiCtrl_ShakeRateChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c98c4
// Size: 176 bytes

void __MidiCtrl_ShakeRateChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  int local_18 [3];
  
  local_18[0] = DeltaTimeSumup__FPPUc(param_3);
  if (local_18[0] == 0) {
    local_18[0] = 1;
  }
  if (*(char *)*param_3 == '\0') {
    uVar2 = 0x100;
  }
  else {
    uVar2 = (uint)*(byte *)*param_3;
  }
  iVar1 = DataAddCompute__FPiiPi(param_3 + 0x2e,0x100 / uVar2,local_18);
  param_3[0x2f] = iVar1;
  *(short *)(param_3 + 0x34) = (short)local_18[0];
  *param_3 = *param_3 + 1;
  return;
}

