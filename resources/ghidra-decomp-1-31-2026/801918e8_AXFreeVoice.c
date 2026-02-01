// Function: AXFreeVoice
// Entry: 801918e8
// Size: 128 bytes

void AXFreeVoice(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  __AXRemoveFromStack(param_1);
  if (*(short *)((int)param_1 + 0x146) == 1) {
    param_1[8] = 1;
  }
  __AXSetPBDefault(param_1);
  *param_1 = DAT_8030cce0;
  DAT_8030cce0 = param_1;
  param_1[3] = 0;
  OSRestoreInterrupts(uVar1);
  return;
}

