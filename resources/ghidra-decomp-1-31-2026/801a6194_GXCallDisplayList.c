// Function: GXCallDisplayList
// Entry: 801a6194
// Size: 112 bytes

void GXCallDisplayList(undefined4 param_1,undefined4 param_2)

{
  if (DAT_80333828[0x13d] != 0) {
    __GXSetDirtyState();
  }
  if (*DAT_80333828 == 0) {
    __GXSendFlushPrim();
  }
  DAT_cc008000._0_1_ = 0x40;
  DAT_cc008000 = param_1;
  DAT_cc008000 = param_2;
  return;
}

