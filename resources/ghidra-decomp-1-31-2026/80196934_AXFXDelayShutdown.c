// Function: AXFXDelayShutdown
// Entry: 80196934
// Size: 144 bytes

undefined4 AXFXDelayShutdown(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  if (*(int *)(param_1 + 0x30) != 0) {
    (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(int *)(param_1 + 0x30));
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    (*(code *)PTR___AXFXFreeFunction_8032eb64)();
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    (*(code *)PTR___AXFXFreeFunction_8032eb64)();
  }
  OSRestoreInterrupts(uVar1);
  return 1;
}

