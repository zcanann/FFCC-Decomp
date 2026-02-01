// Function: GXSetClipMode
// Entry: 801a6908
// Size: 40 bytes

void GXSetClipMode(undefined4 param_1)

{
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x1005;
  DAT_cc008000 = param_1;
  *(undefined2 *)(DAT_80333828 + 2) = 1;
  return;
}

