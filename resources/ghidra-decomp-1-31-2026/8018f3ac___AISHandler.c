// Function: __AISHandler
// Entry: 8018f3ac
// Size: 124 bytes

void __AISHandler(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined auStack_2d0 [712];
  
  uVar1 = DAT_cc006c00;
  DAT_cc006c00 = uVar1 | 8;
  OSClearContext(auStack_2d0);
  OSSetCurrentContext(auStack_2d0);
  if (DAT_8032f160 != (code *)0x0) {
    uVar2 = DAT_cc006c08;
    (*DAT_8032f160)(uVar2);
  }
  OSClearContext(auStack_2d0);
  OSSetCurrentContext(param_2);
  return;
}

