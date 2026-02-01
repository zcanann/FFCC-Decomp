// Function: GXSetDrawSyncCallback
// Entry: 801a2210
// Size: 68 bytes

undefined4 GXSetDrawSyncCallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8032f330;
  OSDisableInterrupts();
  DAT_8032f330 = param_1;
  OSRestoreInterrupts();
  return uVar1;
}

