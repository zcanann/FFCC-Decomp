// Function: __MidiCtrl_TremoloDepthChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c9528
// Size: 120 bytes

void __MidiCtrl_TremoloDepthChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  int local_18 [5];
  
  local_18[0] = DeltaTimeSumup__FPPUc(param_3);
  if (local_18[0] == 0) {
    local_18[0] = 1;
  }
  iVar1 = DataAddCompute__FPiiPi(param_3 + 0x28,*(undefined *)*param_3,local_18);
  param_3[0x29] = iVar1;
  *(short *)((int)param_3 + 0xae) = (short)local_18[0];
  *param_3 = *param_3 + 1;
  return;
}

