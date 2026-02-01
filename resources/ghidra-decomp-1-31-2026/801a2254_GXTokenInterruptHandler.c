// Function: GXTokenInterruptHandler
// Entry: 801a2254
// Size: 136 bytes

void GXTokenInterruptHandler(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  undefined auStack_2d0 [712];
  
  uVar1 = *(undefined2 *)(DAT_8032f2f0 + 0xe);
  if (DAT_8032f330 != (code *)0x0) {
    OSClearContext(auStack_2d0);
    OSSetCurrentContext(auStack_2d0);
    (*DAT_8032f330)(uVar1);
    OSClearContext(auStack_2d0);
    OSSetCurrentContext(param_2);
  }
  *(ushort *)(DAT_8032f2f0 + 10) = *(ushort *)(DAT_8032f2f0 + 10) & 0xfffb | 4;
  return;
}

