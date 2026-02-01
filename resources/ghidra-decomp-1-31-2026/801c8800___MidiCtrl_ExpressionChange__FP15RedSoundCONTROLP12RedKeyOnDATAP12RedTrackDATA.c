// Function: __MidiCtrl_ExpressionChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8800
// Size: 132 bytes

void __MidiCtrl_ExpressionChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  char *pcVar2;
  int local_18 [4];
  
  local_18[0] = DeltaTimeSumup__FPPUc(param_3);
  if (local_18[0] == 0) {
    local_18[0] = 1;
  }
  pcVar2 = (char *)*param_3;
  *param_3 = pcVar2 + 1;
  uVar1 = DataAddCompute__FPiiPi(param_3 + 0xd,(int)*pcVar2,local_18);
  param_3[0xe] = uVar1;
  param_3[0xf] = local_18[0];
  return;
}

