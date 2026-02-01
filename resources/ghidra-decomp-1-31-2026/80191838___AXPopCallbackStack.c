// Function: __AXPopCallbackStack
// Entry: 80191838
// Size: 28 bytes

void __AXPopCallbackStack(void)

{
  if (DAT_8032f1e8 == 0) {
    return;
  }
  DAT_8032f1e8 = *(undefined4 *)(DAT_8032f1e8 + 8);
  return;
}

