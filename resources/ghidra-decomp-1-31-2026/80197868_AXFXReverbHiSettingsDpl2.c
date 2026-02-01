// Function: AXFXReverbHiSettingsDpl2
// Entry: 80197868
// Size: 112 bytes

undefined4 AXFXReverbHiSettingsDpl2(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  *(undefined *)(param_1 + 0x254) = 1;
  ReverbHIModifyDpl2((double)*(float *)(param_1 + 600),(double)*(float *)(param_1 + 0x260),
                     (double)*(float *)(param_1 + 0x25c),(double)*(float *)(param_1 + 0x264),
                     (double)*(float *)(param_1 + 0x268),param_1);
  *(undefined *)(param_1 + 0x254) = 0;
  OSRestoreInterrupts(uVar1);
  return 1;
}

