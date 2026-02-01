// Function: AIRegisterDMACallback
// Entry: 8018ee04
// Size: 68 bytes

undefined4 AIRegisterDMACallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8032f164;
  OSDisableInterrupts();
  DAT_8032f164 = param_1;
  OSRestoreInterrupts();
  return uVar1;
}

