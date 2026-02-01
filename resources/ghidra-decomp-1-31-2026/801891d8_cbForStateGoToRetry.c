// Function: cbForStateGoToRetry
// Entry: 801891d8
// Size: 344 bytes

void cbForStateGoToRetry(uint param_1)

{
  bool bVar1;
  undefined *puVar2;
  
  puVar2 = DAT_8032f080;
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    __DVDStoreErrorCode(0x1234568);
    DVDReset();
    cbForStateError(0);
  }
  else if ((param_1 & 2) == 0) {
    DAT_8032f0b4 = 0;
    if ((((DAT_8032f09c == 4) || (DAT_8032f09c == 5)) || (DAT_8032f09c == 0xd)) ||
       (DAT_8032f09c == 0xf)) {
      DAT_8032f0b8 = 1;
    }
    if (DAT_8032f0a0 == 0) {
      bVar1 = false;
    }
    else {
      DAT_8032f0a8 = 2;
      DAT_8032f080 = &DAT_8030ca60;
      DAT_8032f0a0 = 0;
      *(undefined4 *)(puVar2 + 0xc) = 10;
      if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
        (**(code **)(puVar2 + 0x28))(0xfffffffd,puVar2);
      }
      if (DAT_8032f0a4 != (code *)0x0) {
        (*DAT_8032f0a4)(0,puVar2);
      }
      stateReady();
      bVar1 = true;
    }
    if (!bVar1) {
      *(undefined4 *)(DAT_8032f080 + 0xc) = 0xb;
      stateMotorStopped();
    }
  }
  else {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    __DVDStoreErrorCode(0x1234567);
    DVDLowStopMotor(cbForStateError);
  }
  return;
}

