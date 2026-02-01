// Function: __ARHandler
// Entry: 8018f94c
// Size: 120 bytes

void __ARHandler(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  undefined auStack_2d0 [716];
  
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xff77 | 0x20;
  OSClearContext(auStack_2d0);
  OSSetCurrentContext(auStack_2d0);
  if (DAT_8032f1a0 != (code *)0x0) {
    (*DAT_8032f1a0)();
  }
  OSClearContext(auStack_2d0);
  OSSetCurrentContext(param_2);
  return;
}

