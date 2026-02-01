// Function: AXFXReverbHiInit
// Entry: 80194d00
// Size: 112 bytes

undefined4 AXFXReverbHiInit(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = OSDisableInterrupts();
  *(undefined *)(param_1 + 0x1c4) = 0;
  uVar2 = ReverbHICreate((double)*(float *)(param_1 + 0x1c8),(double)*(float *)(param_1 + 0x1d0),
                         (double)*(float *)(param_1 + 0x1cc),(double)*(float *)(param_1 + 0x1d4),
                         (double)*(float *)(param_1 + 0x1d8),(double)*(float *)(param_1 + 0x1dc),
                         param_1);
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

