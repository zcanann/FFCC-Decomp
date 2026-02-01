// Function: F25
// Entry: 801a8e78
// Size: 168 bytes

void F25(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == -0x7fcd7c38) {
    uVar1 = 0;
  }
  else if (param_1 == -0x7fcd7b38) {
    uVar1 = 1;
  }
  else if (param_1 == -0x7fcd7a38) {
    uVar1 = 2;
  }
  else if (param_1 == -0x7fcd7938) {
    uVar1 = 3;
  }
  else {
    OSPanic(s_GBAKey_c_8021cef8,0xa9,s_GBA___unexpected_dsp_call_8021cf04);
    uVar1 = 0xffffffff;
  }
  __GBAX01(uVar1,0);
  return;
}

