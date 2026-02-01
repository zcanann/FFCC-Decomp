// Function: THPSimpleInit
// Entry: 8010585c
// Size: 288 bytes

undefined4 THPSimpleInit(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  CheckQueue__5CFileFv(&File);
  memset(&SimpleControl,0,0x174);
  LCEnable();
  iVar1 = THPInit();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = OSDisableInterrupts();
    DAT_8032ee4c = 0;
    DAT_8032ee54 = 0;
    DAT_8032ee58 = 0;
    DAT_8032ee5c = param_1;
    DAT_8032ee50 = AIRegisterDMACallback(THPAudioMixCallback__Fv);
    if ((DAT_8032ee50 == 0) && (DAT_8032ee5c != 0)) {
      AIRegisterDMACallback(0);
      OSRestoreInterrupts(uVar2);
      uVar2 = 0;
    }
    else {
      OSRestoreInterrupts(uVar2);
      if (DAT_8032ee5c == 0) {
        memset(0x802ffc40,0,0x500);
        DCFlushRange(0x802ffc40,0x500);
        AIInitDMA(DAT_8032ee4c * 0x280 + -0x7fd003c0,0x280);
        AIStartDMA();
      }
      uVar2 = 1;
      DAT_8032ee48 = 1;
    }
  }
  return uVar2;
}

