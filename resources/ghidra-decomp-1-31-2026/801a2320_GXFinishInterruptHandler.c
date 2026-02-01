// Function: GXFinishInterruptHandler
// Entry: 801a2320
// Size: 132 bytes

void GXFinishInterruptHandler(undefined4 param_1,undefined4 param_2)

{
  undefined auStack_2d0 [716];
  
  *(ushort *)(DAT_8032f2f0 + 10) = *(ushort *)(DAT_8032f2f0 + 10) & 0xfff7 | 8;
  DAT_8032f338 = 1;
  if (DAT_8032f334 != (code *)0x0) {
    OSClearContext(auStack_2d0);
    OSSetCurrentContext(auStack_2d0);
    (*DAT_8032f334)();
    OSClearContext(auStack_2d0);
    OSSetCurrentContext(param_2);
  }
  OSWakeupThread(&DAT_8032f33c);
  return;
}

