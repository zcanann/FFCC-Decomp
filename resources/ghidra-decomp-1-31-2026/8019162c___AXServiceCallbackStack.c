// Function: __AXServiceCallbackStack
// Entry: 8019162c
// Size: 116 bytes

void __AXServiceCallbackStack(void)

{
  int iVar1;
  
  iVar1 = __AXPopCallbackStack();
  while (iVar1 != 0) {
    if (*(int *)(iVar1 + 0xc) != 0) {
      if (*(code **)(iVar1 + 0x10) != (code *)0x0) {
        (**(code **)(iVar1 + 0x10))(iVar1);
      }
      __AXRemoveFromStack(iVar1);
      __AXPushFreeStack(iVar1);
    }
    iVar1 = __AXPopCallbackStack();
  }
  return;
}

