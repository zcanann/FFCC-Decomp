// Function: AXFXReverbHiShutdown
// Entry: 80194d70
// Size: 76 bytes

undefined4 AXFXReverbHiShutdown(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  ReverbHIFree(param_1);
  OSRestoreInterrupts(uVar1);
  return 1;
}

