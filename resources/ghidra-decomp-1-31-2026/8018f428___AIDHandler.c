// Function: __AIDHandler
// Entry: 8018f428
// Size: 172 bytes

void __AIDHandler(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  undefined auStack_2d0 [716];
  
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xff5f | 8;
  OSClearContext(auStack_2d0);
  OSSetCurrentContext(auStack_2d0);
  if ((DAT_8032f164 != (code *)0x0) && (DAT_8032f174 == 0)) {
    DAT_8032f174 = 1;
    if (DAT_8032f168 == 0) {
      (*DAT_8032f164)();
    }
    else {
      __AICallbackStackSwitch();
    }
    DAT_8032f174 = 0;
  }
  OSClearContext(auStack_2d0);
  OSSetCurrentContext(param_2);
  return;
}

