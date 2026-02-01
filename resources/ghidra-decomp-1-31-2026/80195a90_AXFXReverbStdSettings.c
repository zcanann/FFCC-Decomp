// Function: AXFXReverbStdSettings
// Entry: 80195a90
// Size: 112 bytes

undefined4 AXFXReverbStdSettings(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  *(undefined *)(param_1 + 0x13c) = 1;
  ReverbSTDModify((double)*(float *)(param_1 + 0x140),(double)*(float *)(param_1 + 0x148),
                  (double)*(float *)(param_1 + 0x144),(double)*(float *)(param_1 + 0x14c),
                  (double)*(float *)(param_1 + 0x150),param_1);
  *(undefined *)(param_1 + 0x13c) = 0;
  OSRestoreInterrupts(uVar1);
  return 1;
}

