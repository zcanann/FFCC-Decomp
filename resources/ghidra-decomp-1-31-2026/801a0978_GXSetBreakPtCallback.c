// Function: GXSetBreakPtCallback
// Entry: 801a0978
// Size: 68 bytes

undefined4 GXSetBreakPtCallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8032f324;
  OSDisableInterrupts();
  DAT_8032f324 = param_1;
  OSRestoreInterrupts();
  return uVar1;
}

