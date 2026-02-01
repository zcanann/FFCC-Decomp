// Function: F23
// Entry: 801a8d9c
// Size: 220 bytes

void F23(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == -0x7fcd7c38) {
    iVar1 = 0;
  }
  else if (param_1 == -0x7fcd7b38) {
    iVar1 = 1;
  }
  else if (param_1 == -0x7fcd7a38) {
    iVar1 = 2;
  }
  else if (param_1 == -0x7fcd7938) {
    iVar1 = 3;
  }
  else {
    OSPanic(s_GBAKey_c_8021cef8,0xa9,s_GBA___unexpected_dsp_call_8021cf04);
    iVar1 = -1;
  }
  DSPSendMailToDSP(0xabba0000);
  do {
    iVar2 = DSPCheckMailToDSP();
  } while (iVar2 != 0);
  DSPSendMailToDSP((&DAT_80328418)[iVar1 * 0x40]);
  do {
    iVar1 = DSPCheckMailToDSP();
  } while (iVar1 != 0);
  return;
}

