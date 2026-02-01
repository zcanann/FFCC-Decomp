// Function: EXIDma
// Entry: 801824a0
// Size: 236 bytes

undefined4 EXIDma(int param_1,uint param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  if (((FatalContext[param_1 * 0x10 + 0x29a] & 3) == 0) &&
     ((FatalContext[param_1 * 0x10 + 0x29a] & 4) != 0)) {
    FatalContext[param_1 * 0x10 + 0x298] = param_5;
    if (FatalContext[param_1 * 0x10 + 0x298] != 0) {
      EXIClearInterrupts(param_1,0,1,0);
      __OSUnmaskInterrupts(0x200000 >> param_1 * 3);
    }
    FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] | 1;
    *(uint *)(&DAT_cc006804 + param_1 * 0x14) = param_2 & 0x3ffffe0;
    *(undefined4 *)(&DAT_cc006808 + param_1 * 0x14) = param_3;
    (&DAT_cc00680c)[param_1 * 5] = param_4 << 2 | 3;
    OSRestoreInterrupts(uVar1);
    uVar1 = 1;
  }
  else {
    OSRestoreInterrupts(uVar1);
    uVar1 = 0;
  }
  return uVar1;
}

