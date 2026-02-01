// Function: __AXGetAuxAInput
// Entry: 80191bd0
// Size: 52 bytes

void __AXGetAuxAInput(undefined4 *param_1)

{
  if (DAT_8032f1f0 != 0) {
    *param_1 = &DAT_8030cde0 + DAT_8032f210 * 0x1e0;
    return;
  }
  *param_1 = 0;
  return;
}

