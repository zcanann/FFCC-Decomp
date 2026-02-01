// Function: cbForStateGettingError
// Entry: 80188e1c
// Size: 660 bytes

void cbForStateGettingError(uint param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined *puVar4;
  int iVar5;
  undefined4 uVar6;
  
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    __DVDStoreErrorCode(0x1234568);
    DVDReset();
    cbForStateError(0);
  }
  else if ((param_1 & 2) == 0) {
    uVar3 = DAT_cc006020;
    uVar2 = uVar3 & 0xff000000;
    iVar5 = CategorizeError(uVar3);
    puVar4 = DAT_8032f080;
    if (iVar5 == 1) {
      *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
      __DVDStoreErrorCode(uVar3);
      DVDLowStopMotor(cbForStateError);
    }
    else {
      if (iVar5 - 2U < 2) {
        uVar6 = 0;
      }
      else if (uVar2 == 0x1000000) {
        uVar6 = 4;
      }
      else if (uVar2 == 0x2000000) {
        uVar6 = 6;
      }
      else if (uVar2 == 0x3000000) {
        uVar6 = 3;
      }
      else {
        uVar6 = 5;
      }
      if (DAT_8032f0a0 == 0) {
        bVar1 = false;
      }
      else {
        DAT_8032f0a0 = 0;
        DAT_8032f080 = &DAT_8030ca60;
        DAT_8032f0a8 = uVar6;
        *(undefined4 *)(puVar4 + 0xc) = 10;
        if (*(code **)(puVar4 + 0x28) != (code *)0x0) {
          (**(code **)(puVar4 + 0x28))(0xfffffffd,puVar4);
        }
        if (DAT_8032f0a4 != (code *)0x0) {
          (*DAT_8032f0a4)(0,puVar4);
        }
        stateReady();
        bVar1 = true;
      }
      if (!bVar1) {
        if (iVar5 == 2) {
          __DVDStoreErrorCode(uVar3);
          stateGoToRetry();
        }
        else if (iVar5 == 3) {
          if ((uVar3 & 0xffffff) == 0x31100) {
            DVDLowSeek(*(undefined4 *)(DAT_8032f080 + 0x10),cbForUnrecoveredError);
          }
          else {
            (*DAT_8032f0c4)(DAT_8032f080);
          }
        }
        else if (uVar2 == 0x1000000) {
          *(undefined4 *)(DAT_8032f080 + 0xc) = 5;
          stateMotorStopped();
        }
        else if (uVar2 == 0x2000000) {
          *(undefined4 *)(DAT_8032f080 + 0xc) = 3;
          stateCoverClosed();
        }
        else if (uVar2 == 0x3000000) {
          *(undefined4 *)(DAT_8032f080 + 0xc) = 4;
          stateMotorStopped();
        }
        else {
          *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
          __DVDStoreErrorCode(0x1234567);
          DVDLowStopMotor(cbForStateError);
        }
      }
    }
  }
  else {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    __DVDStoreErrorCode(0x1234567);
    DVDLowStopMotor(cbForStateError);
  }
  return;
}

