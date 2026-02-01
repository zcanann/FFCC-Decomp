// Function: __AICallbackStackSwitch
// Entry: 8018f4d4
// Size: 88 bytes

void __AICallbackStackSwitch(code *param_1)

{
  DAT_8032f16c = &stack0xffffffe8;
  (*param_1)();
  return;
}

