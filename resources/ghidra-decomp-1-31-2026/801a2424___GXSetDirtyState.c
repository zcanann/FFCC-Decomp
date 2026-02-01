// Function: __GXSetDirtyState
// Entry: 801a2424
// Size: 160 bytes

void __GXSetDirtyState(void)

{
  if ((*(uint *)(DAT_80333828 + 0x4f4) & 1) != 0) {
    __GXSetSUTexRegs();
  }
  if ((*(uint *)(DAT_80333828 + 0x4f4) & 2) != 0) {
    __GXUpdateBPMask();
  }
  if ((*(uint *)(DAT_80333828 + 0x4f4) & 4) != 0) {
    __GXSetGenMode();
  }
  if ((*(uint *)(DAT_80333828 + 0x4f4) & 8) != 0) {
    __GXSetVCD();
  }
  if ((*(uint *)(DAT_80333828 + 0x4f4) & 0x10) != 0) {
    __GXSetVAT();
  }
  if ((*(uint *)(DAT_80333828 + 0x4f4) & 0x18) != 0) {
    __GXCalculateVLim();
  }
  *(undefined4 *)(DAT_80333828 + 0x4f4) = 0;
  return;
}

