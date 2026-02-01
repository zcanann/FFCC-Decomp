// Function: __MidiCtrl_PanChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c88e0
// Size: 164 bytes

void __MidiCtrl_PanChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined *puVar2;
  int local_18 [4];
  
  local_18[0] = DeltaTimeSumup__FPPUc(param_3);
  if (local_18[0] == 0) {
    local_18[0] = 1;
  }
  if (param_3[0x2d] == 0) {
    param_3[0x10] = param_3[0x10] + param_3[0x33] * 0x1000;
    param_3[0x33] = 0;
  }
  puVar2 = (undefined *)*param_3;
  *param_3 = puVar2 + 1;
  uVar1 = DataAddCompute__FPiiPi(param_3 + 0x10,*puVar2,local_18);
  param_3[0x11] = uVar1;
  param_3[0x12] = local_18[0];
  return;
}

