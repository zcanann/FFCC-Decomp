// Function: __DVDPrepareResetAsync
// Entry: 8018b050
// Size: 284 bytes

void __DVDPrepareResetAsync(code *param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar2 = OSDisableInterrupts();
  __DVDClearWaitingQueue();
  pcVar1 = param_1;
  if (DAT_8032f0a0 == 0) {
    if (DAT_8032f080 != 0) {
      *(undefined4 *)(DAT_8032f080 + 0x28) = 0;
    }
    uVar3 = OSDisableInterrupts();
    OSDisableInterrupts();
    DAT_8032f08c = 1;
    if (DAT_8032f080 == 0) {
      DAT_8032f090 = 1;
    }
    OSRestoreInterrupts();
    while (iVar4 = __DVDPopWaitingQueue(), iVar4 != 0) {
      DVDCancelAsync(iVar4,0);
    }
    if (DAT_8032f080 == 0) {
      if (param_1 != (code *)0x0) {
        (*param_1)(0,0);
      }
    }
    else {
      DVDCancelAsync(DAT_8032f080,param_1);
    }
    uVar5 = OSDisableInterrupts();
    DAT_8032f08c = 0;
    if (DAT_8032f090 != 0) {
      DAT_8032f090 = 0;
      stateReady();
    }
    OSRestoreInterrupts(uVar5);
    OSRestoreInterrupts(uVar3);
    pcVar1 = DAT_8032f0a4;
  }
  DAT_8032f0a4 = pcVar1;
  OSRestoreInterrupts(uVar2);
  return;
}

