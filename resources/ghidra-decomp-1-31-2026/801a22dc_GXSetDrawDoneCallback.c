// Function: GXSetDrawDoneCallback
// Entry: 801a22dc
// Size: 68 bytes

undefined4 GXSetDrawDoneCallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8032f334;
  OSDisableInterrupts();
  DAT_8032f334 = param_1;
  OSRestoreInterrupts();
  return uVar1;
}

