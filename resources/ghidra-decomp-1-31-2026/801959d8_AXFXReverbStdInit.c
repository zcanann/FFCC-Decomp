// Function: AXFXReverbStdInit
// Entry: 801959d8
// Size: 108 bytes

undefined4 AXFXReverbStdInit(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = OSDisableInterrupts();
  *(undefined *)(param_1 + 0x13c) = 0;
  uVar2 = ReverbSTDCreate((double)*(float *)(param_1 + 0x140),(double)*(float *)(param_1 + 0x148),
                          (double)*(float *)(param_1 + 0x144),(double)*(float *)(param_1 + 0x14c),
                          (double)*(float *)(param_1 + 0x150),param_1);
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

