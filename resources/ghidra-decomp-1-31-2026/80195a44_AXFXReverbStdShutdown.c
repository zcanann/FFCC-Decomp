// Function: AXFXReverbStdShutdown
// Entry: 80195a44
// Size: 76 bytes

undefined4 AXFXReverbStdShutdown(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  ReverbSTDFree(param_1);
  OSRestoreInterrupts(uVar1);
  return 1;
}

