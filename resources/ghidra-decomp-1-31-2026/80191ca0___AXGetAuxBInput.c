// Function: __AXGetAuxBInput
// Entry: 80191ca0
// Size: 52 bytes

void __AXGetAuxBInput(undefined4 *param_1)

{
  if (DAT_8032f1f4 != 0) {
    *param_1 = &DAT_8030e460 + DAT_8032f210 * 0x1e0;
    return;
  }
  *param_1 = 0;
  return;
}

