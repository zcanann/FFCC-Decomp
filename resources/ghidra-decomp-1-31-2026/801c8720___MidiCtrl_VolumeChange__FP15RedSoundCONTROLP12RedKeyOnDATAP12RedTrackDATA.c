// Function: __MidiCtrl_VolumeChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
// Entry: 801c8720
// Size: 148 bytes

void __MidiCtrl_VolumeChange__FP15RedSoundCONTROLP12RedKeyOnDATAP12RedTrackDATA
               (undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  byte *pbVar1;
  undefined4 uVar2;
  uint uVar3;
  int local_18 [4];
  
  local_18[0] = DeltaTimeSumup__FPPUc(param_3);
  if (local_18[0] == 0) {
    local_18[0] = 1;
  }
  pbVar1 = (byte *)*param_3;
  *param_3 = pbVar1 + 1;
  uVar3 = (uint)*pbVar1;
  if (uVar3 != 0) {
    uVar3 = (uVar3 + 1) * 0x100 - 1;
  }
  uVar2 = DataAddCompute__FPiiPi(param_3 + 10,uVar3,local_18);
  param_3[0xb] = uVar2;
  param_3[0xc] = local_18[0];
  return;
}

