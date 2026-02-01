// Function: THPAudioMixCallback__Fv
// Entry: 801040c8
// Size: 376 bytes

void THPAudioMixCallback__Fv(void)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_8032ee5c == 0) {
    DAT_8032ee4c = DAT_8032ee4c ^ 1;
    AIInitDMA(DAT_8032ee4c * 0x280 + -0x7fd003c0,0x280);
    uVar1 = OSEnableInterrupts();
    MixAudio__FPsPsUl(DAT_8032ee4c * 0x280 + -0x7fd003c0,0,0xa0);
    DCFlushRange(DAT_8032ee4c * 0x280 + -0x7fd003c0,0x280);
    OSRestoreInterrupts(uVar1);
  }
  else {
    if (DAT_8032ee5c == 1) {
      if (DAT_8032ee54 != 0) {
        DAT_8032ee58 = DAT_8032ee54;
      }
      (*DAT_8032ee50)();
      iVar2 = AIGetDMAStartAddr();
      DAT_8032ee54 = iVar2 + -0x80000000;
    }
    else {
      (*DAT_8032ee50)();
      iVar2 = AIGetDMAStartAddr();
      DAT_8032ee58 = iVar2 + -0x80000000;
    }
    DAT_8032ee4c = DAT_8032ee4c ^ 1;
    AIInitDMA(DAT_8032ee4c * 0x280 + -0x7fd003c0,0x280);
    uVar1 = OSEnableInterrupts();
    if (DAT_8032ee58 != 0) {
      DCInvalidateRange(DAT_8032ee58,0x280);
    }
    MixAudio__FPsPsUl(DAT_8032ee4c * 0x280 + -0x7fd003c0,DAT_8032ee58,0xa0);
    DCFlushRange(DAT_8032ee4c * 0x280 + -0x7fd003c0,0x280);
    OSRestoreInterrupts(uVar1);
  }
  return;
}

