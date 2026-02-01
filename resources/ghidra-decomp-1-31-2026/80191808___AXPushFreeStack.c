// Function: __AXPushFreeStack
// Entry: 80191808
// Size: 32 bytes

void __AXPushFreeStack(undefined4 *param_1)

{
  *param_1 = DAT_8030cce0;
  DAT_8030cce0 = param_1;
  param_1[3] = 0;
  return;
}

