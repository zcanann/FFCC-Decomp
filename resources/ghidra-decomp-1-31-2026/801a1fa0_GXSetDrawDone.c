// Function: GXSetDrawDone
// Entry: 801a1fa0
// Size: 152 bytes

void GXSetDrawDone(void)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x45000002;
  if (*(int *)(DAT_80333828 + 0x4f4) != 0) {
    __GXSetDirtyState();
  }
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  PPCSync();
  DAT_8032f338 = 0;
  OSRestoreInterrupts(uVar1);
  return;
}

