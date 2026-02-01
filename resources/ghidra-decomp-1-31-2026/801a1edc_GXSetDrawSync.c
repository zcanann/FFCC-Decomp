// Function: GXSetDrawSync
// Entry: 801a1edc
// Size: 184 bytes

void GXSetDrawSync(uint param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1 & 0xffff | 0x48000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1 & 0xffff | 0x47000000;
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
  OSRestoreInterrupts(uVar1);
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

