// Function: stateReady
// Entry: 80189ad4
// Size: 560 bytes

void stateReady(void)

{
  undefined *puVar1;
  int iVar2;
  
  iVar2 = __DVDCheckWaitingQueue();
  if (iVar2 == 0) {
    DAT_8032f080 = (undefined *)0x0;
    return;
  }
  if (DAT_8032f08c != 0) {
    DAT_8032f080 = (undefined *)0x0;
    DAT_8032f090 = 1;
    return;
  }
  DAT_8032f080 = (undefined *)__DVDPopWaitingQueue();
  if (DAT_8032f098 != 0) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    puVar1 = DAT_8032f080;
    DAT_8032f080 = &DAT_8030ca60;
    if (*(code **)(puVar1 + 0x28) != (code *)0x0) {
      (**(code **)(puVar1 + 0x28))(0xffffffff);
    }
    stateReady();
    return;
  }
  DAT_8032f09c = *(int *)(DAT_8032f080 + 8);
  if (DAT_8032f0a8 == 0) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 1;
    stateBusy(DAT_8032f080);
    return;
  }
  if (DAT_8032f0a8 == 4) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 5;
    DVDLowWaitCoverClose(cbForStateMotorStopped);
    DAT_8032f0a8 = 0;
    return;
  }
  if (DAT_8032f0a8 < 4) {
    if (DAT_8032f0a8 == 2) {
      *(undefined4 *)(DAT_8032f080 + 0xc) = 0xb;
      DVDLowWaitCoverClose(cbForStateMotorStopped);
      DAT_8032f0a8 = 0;
      return;
    }
    if (1 < DAT_8032f0a8) {
      *(undefined4 *)(DAT_8032f080 + 0xc) = 4;
      DVDLowWaitCoverClose(cbForStateMotorStopped);
      DAT_8032f0a8 = 0;
      return;
    }
    if (DAT_8032f0a8 < 1) {
      DAT_8032f0a8 = 0;
      return;
    }
  }
  else {
    if (7 < DAT_8032f0a8) {
      DAT_8032f0a8 = 0;
      return;
    }
    if (DAT_8032f0a8 < 6) {
      *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
      __DVDStoreErrorCode(DAT_8032f0ac);
      DVDLowStopMotor(cbForStateError);
      DAT_8032f0a8 = 0;
      return;
    }
  }
  *(undefined4 *)(DAT_8032f080 + 0xc) = 3;
  if (DAT_8032f09c == 0xd) {
LAB_80189c44:
    __DVDClearWaitingQueue();
    puVar1 = DAT_8032f080;
    DAT_8032f080 = &DAT_8030ca60;
    if (*(code **)(puVar1 + 0x28) != (code *)0x0) {
      (**(code **)(puVar1 + 0x28))(0xfffffffc);
    }
    stateReady();
  }
  else {
    if (DAT_8032f09c < 0xd) {
      if ((DAT_8032f09c < 6) && (3 < DAT_8032f09c)) goto LAB_80189c44;
    }
    else if (DAT_8032f09c == 0xf) goto LAB_80189c44;
    DVDReset();
    OSCreateAlarm(&DAT_8030ca90);
    OSSetAlarm((OSAlarm *)&DAT_8030ca90,0x10624dd3,0,(DAT_800000f8 / 4000) * 0x47e,AlarmHandler);
  }
  DAT_8032f0a8 = 0;
  return;
}

