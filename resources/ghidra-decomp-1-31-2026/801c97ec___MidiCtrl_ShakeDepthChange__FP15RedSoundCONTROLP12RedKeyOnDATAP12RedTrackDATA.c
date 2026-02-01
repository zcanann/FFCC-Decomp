// Function: __MidiCtrl_ShakeDepthChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c97ec
// Size: 120 bytes

void __MidiCtrl_ShakeDepthChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int local_18 [5];
  
  local_18[0] = DeltaTimeSumup__FPPUc(param_3);
  if (local_18[0] == 0) {
    local_18[0] = 1;
  }
  iVar1 = DataAddCompute__FPiiPi(param_3 + 0x30,*(undefined *)*param_3,local_18);
  param_3[0x31] = iVar1;
  *(short *)((int)param_3 + 0xd2) = (short)local_18[0];
  *param_3 = *param_3 + 1;
  return;
}

