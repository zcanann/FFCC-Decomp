// Function: DVDCancelAsync
// Entry: 8018ac04
// Size: 636 bytes

undefined4 DVDCancelAsync(int param_1,code *param_2)

{
  int iVar1;
  undefined4 uVar2;
  code *pcVar3;
  
  uVar2 = OSDisableInterrupts();
  switch(*(undefined4 *)(param_1 + 0xc)) {
  case 1:
    if (DAT_8032f0a0 != 0) {
      OSRestoreInterrupts(uVar2);
      return 0;
    }
    DAT_8032f0a0 = 1;
    if ((*(int *)(param_1 + 8) == 4) || (DAT_8032f0a4 = param_2, *(int *)(param_1 + 8) == 1)) {
      DAT_8032f0a4 = param_2;
      DVDLowBreak();
    }
    break;
  case 2:
    __DVDDequeueWaitingQueue(param_1);
    *(undefined4 *)(param_1 + 0xc) = 10;
    if (*(code **)(param_1 + 0x28) != (code *)0x0) {
      (**(code **)(param_1 + 0x28))(0xfffffffd,param_1);
    }
    if (param_2 != (code *)0x0) {
      (*param_2)(0,param_1);
    }
    break;
  case 3:
    iVar1 = *(int *)(param_1 + 8);
    if (iVar1 == 0xd) {
LAB_8018ad34:
      if (param_2 != (code *)0x0) {
        (*param_2)(0,param_1);
      }
    }
    else {
      if (iVar1 < 0xd) {
        if ((iVar1 < 6) && (3 < iVar1)) goto LAB_8018ad34;
      }
      else if (iVar1 == 0xf) goto LAB_8018ad34;
      if (DAT_8032f0a0 != 0) {
        OSRestoreInterrupts(uVar2);
        return 0;
      }
      DAT_8032f0a0 = 1;
      DAT_8032f0a4 = param_2;
    }
    break;
  case 4:
  case 5:
  case 6:
  case 7:
  case 0xb:
    pcVar3 = (code *)DVDLowClearCallback();
    if (pcVar3 != cbForStateMotorStopped) {
      OSRestoreInterrupts(uVar2);
      return 0;
    }
    if (*(int *)(param_1 + 0xc) == 4) {
      DAT_8032f0a8 = 3;
    }
    if (*(int *)(param_1 + 0xc) == 5) {
      DAT_8032f0a8 = 4;
    }
    if (*(int *)(param_1 + 0xc) == 6) {
      DAT_8032f0a8 = 1;
    }
    if (*(int *)(param_1 + 0xc) == 0xb) {
      DAT_8032f0a8 = 2;
    }
    if (*(int *)(param_1 + 0xc) == 7) {
      DAT_8032f0a8 = 7;
    }
    DAT_8032f080 = &DAT_8030ca60;
    *(undefined4 *)(param_1 + 0xc) = 10;
    if (*(code **)(param_1 + 0x28) != (code *)0x0) {
      (**(code **)(param_1 + 0x28))(0xfffffffd,param_1);
    }
    if (param_2 != (code *)0x0) {
      (*param_2)(0,param_1);
    }
    stateReady();
    break;
  case 0xffffffff:
  case 0:
  case 10:
    if (param_2 != (code *)0x0) {
      (*param_2)(0,param_1);
    }
  }
  OSRestoreInterrupts(uVar2);
  return 1;
}

