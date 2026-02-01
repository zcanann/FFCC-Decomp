// Function: ARRegisterDMACallback
// Entry: 8018f710
// Size: 68 bytes

undefined4 ARRegisterDMACallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8032f1a0;
  OSDisableInterrupts();
  DAT_8032f1a0 = param_1;
  OSRestoreInterrupts();
  return uVar1;
}

