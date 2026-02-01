// Function: __AXPushCallbackStack
// Entry: 80191828
// Size: 16 bytes

void __AXPushCallbackStack(int param_1)

{
  *(int *)(param_1 + 8) = DAT_8032f1e8;
  DAT_8032f1e8 = param_1;
  return;
}

