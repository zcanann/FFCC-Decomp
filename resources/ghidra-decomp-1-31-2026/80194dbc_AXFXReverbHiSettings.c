// Function: AXFXReverbHiSettings
// Entry: 80194dbc
// Size: 116 bytes

undefined4 AXFXReverbHiSettings(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  *(undefined *)(param_1 + 0x1c4) = 1;
  ReverbHIModify((double)*(float *)(param_1 + 0x1c8),(double)*(float *)(param_1 + 0x1d0),
                 (double)*(float *)(param_1 + 0x1cc),(double)*(float *)(param_1 + 0x1d4),
                 (double)*(float *)(param_1 + 0x1d8),(double)*(float *)(param_1 + 0x1dc),param_1);
  *(undefined *)(param_1 + 0x1c4) = 0;
  OSRestoreInterrupts(uVar1);
  return 1;
}

