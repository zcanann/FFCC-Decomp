// Function: AXFXChorusShutdown
// Entry: 801960b4
// Size: 80 bytes

undefined4 AXFXChorusShutdown(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  (*(code *)PTR___AXFXFreeFunction_8032eb64)(*param_1);
  OSRestoreInterrupts(uVar1);
  return 1;
}

