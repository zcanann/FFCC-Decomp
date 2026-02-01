// Function: cbForStateBusy
// Entry: 8018a024
// Size: 1592 bytes

void cbForStateBusy(uint param_1)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  bool bVar4;
  
  puVar2 = DAT_8032f080;
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    __DVDStoreErrorCode(0x1234568);
    DVDReset();
    cbForStateError(0);
  }
  else {
    if ((DAT_8032f09c != 3) && (DAT_8032f09c != 0xf)) {
      if ((DAT_8032f09c == 1) || ((DAT_8032f09c - 4U < 2 || (DAT_8032f09c == 0xe)))) {
        bVar4 = true;
      }
      else if (DAT_8032f09c == DAT_8032eaf4) {
        bVar4 = true;
      }
      else {
        bVar4 = false;
      }
      if (bVar4) {
        iVar3 = DAT_cc006018;
        *(int *)(DAT_8032f080 + 0x20) =
             *(int *)(DAT_8032f080 + 0x20) + (*(int *)(DAT_8032f080 + 0x1c) - iVar3);
      }
      puVar2 = DAT_8032f080;
      if ((param_1 & 8) != 0) {
        DAT_8032f0a0 = 0;
        DAT_8032f080 = &DAT_8030ca60;
        *(undefined4 *)(puVar2 + 0xc) = 10;
        if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
          (**(code **)(puVar2 + 0x28))(0xfffffffd,puVar2);
        }
        if (DAT_8032f0a4 != (code *)0x0) {
          (*DAT_8032f0a4)(0,puVar2);
        }
        stateReady();
        return;
      }
      if ((param_1 & 1) == 0) {
        if (DAT_8032f09c == 0xe) {
          *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
          __DVDStoreErrorCode(0x1234567);
          DVDLowStopMotor(cbForStateError);
          return;
        }
        if (((((DAT_8032f09c == 1) || (DAT_8032f09c == 4)) || (DAT_8032f09c == 5)) ||
            (DAT_8032f09c == 0xe)) &&
           (*(int *)(DAT_8032f080 + 0x20) == *(int *)(DAT_8032f080 + 0x14))) {
          if (DAT_8032f0a0 == 0) {
            bVar4 = false;
          }
          else {
            DAT_8032f0a8 = 0;
            DAT_8032f0a0 = 0;
            DAT_8032f080 = &DAT_8030ca60;
            *(undefined4 *)(puVar2 + 0xc) = 10;
            if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
              (**(code **)(puVar2 + 0x28))(0xfffffffd,puVar2);
            }
            if (DAT_8032f0a4 != (code *)0x0) {
              (*DAT_8032f0a4)(0,puVar2);
            }
            stateReady();
            bVar4 = true;
          }
          puVar2 = DAT_8032f080;
          if (bVar4) {
            return;
          }
          DAT_8032f080 = &DAT_8030ca60;
          *(undefined4 *)(puVar2 + 0xc) = 0;
          if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
            (**(code **)(puVar2 + 0x28))(*(undefined4 *)(puVar2 + 0x20));
          }
          stateReady();
          return;
        }
        DVDLowRequestError(cbForStateGettingError);
        return;
      }
      bVar4 = false;
      DAT_8032f0b4 = 0;
      if (DAT_8032f0a0 != 0) {
        DAT_8032f0a8 = 0;
        DAT_8032f0a0 = 0;
        DAT_8032f080 = &DAT_8030ca60;
        *(undefined4 *)(puVar2 + 0xc) = 10;
        if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
          (**(code **)(puVar2 + 0x28))(0xfffffffd,puVar2);
        }
        if (DAT_8032f0a4 != (code *)0x0) {
          (*DAT_8032f0a4)(0,puVar2);
        }
        stateReady();
        bVar4 = true;
      }
      puVar2 = DAT_8032f080;
      if (bVar4) {
        return;
      }
      if (((DAT_8032f09c == 1) || (DAT_8032f09c - 4U < 2)) || (DAT_8032f09c == 0xe)) {
        bVar4 = true;
      }
      else if (DAT_8032f09c == DAT_8032eaf4) {
        bVar4 = true;
      }
      else {
        bVar4 = false;
      }
      if (bVar4) {
        if (*(int *)(DAT_8032f080 + 0x20) != *(int *)(DAT_8032f080 + 0x14)) {
          stateBusy();
          return;
        }
        DAT_8032f080 = &DAT_8030ca60;
        *(undefined4 *)(puVar2 + 0xc) = 0;
        if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
          (**(code **)(puVar2 + 0x28))(*(undefined4 *)(puVar2 + 0x20));
        }
        stateReady();
        return;
      }
      if (DAT_8032f09c - 9U < 4) {
        bVar4 = true;
      }
      else if (DAT_8032f09c == DAT_80217670) {
        bVar4 = true;
      }
      else if (DAT_8032f09c == DAT_80217674) {
        bVar4 = true;
      }
      else if (DAT_8032f09c == DAT_80217678) {
        bVar4 = true;
      }
      else {
        bVar4 = false;
      }
      if (bVar4) {
        if ((DAT_8032f09c == 0xb) || (DAT_8032f09c == 10)) {
          iVar3 = DAT_cc006020;
          iVar3 = iVar3 << 2;
        }
        else {
          iVar3 = DAT_cc006020;
        }
        DAT_8032f080 = &DAT_8030ca60;
        *(undefined4 *)(puVar2 + 0xc) = 0;
        if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
          (**(code **)(puVar2 + 0x28))(iVar3);
        }
        stateReady();
        return;
      }
      if (DAT_8032f09c != 6) {
        DAT_8032f080 = &DAT_8030ca60;
        *(undefined4 *)(puVar2 + 0xc) = 0;
        if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
          (**(code **)(puVar2 + 0x28))(0);
        }
        stateReady();
        return;
      }
      if (*(int *)(DAT_8032f080 + 0x1c) == 0) {
        uVar1 = DAT_cc006020;
        if ((uVar1 & 1) != 0) {
          DAT_8032f080 = &DAT_8030ca60;
          *(undefined4 *)(puVar2 + 0xc) = 9;
          if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
            (**(code **)(puVar2 + 0x28))(0xfffffffe);
          }
          stateReady();
          return;
        }
        DAT_8032f094 = 0;
        *(undefined4 *)(DAT_8032f080 + 0x1c) = 1;
        DVDLowAudioStream(0,*(undefined4 *)(DAT_8032f080 + 0x14),
                          *(undefined4 *)(DAT_8032f080 + 0x10),cbForStateBusy);
        return;
      }
      DAT_8032f080 = &DAT_8030ca60;
      *(undefined4 *)(puVar2 + 0xc) = 0;
      if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
        (**(code **)(puVar2 + 0x28))(0);
      }
      stateReady();
      return;
    }
    if ((param_1 & 2) == 0) {
      DAT_8032f0b4 = 0;
      if (DAT_8032f09c == 0xf) {
        DAT_8032f0b8 = 1;
      }
      if (DAT_8032f0a0 == 0) {
        bVar4 = false;
      }
      else {
        DAT_8032f0a8 = 7;
        DAT_8032f0a0 = 0;
        DAT_8032f080 = &DAT_8030ca60;
        *(undefined4 *)(puVar2 + 0xc) = 10;
        if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
          (**(code **)(puVar2 + 0x28))(0xfffffffd,puVar2);
        }
        if (DAT_8032f0a4 != (code *)0x0) {
          (*DAT_8032f0a4)(0,puVar2);
        }
        stateReady();
        bVar4 = true;
      }
      if (!bVar4) {
        *(undefined4 *)(DAT_8032f080 + 0xc) = 7;
        DVDLowWaitCoverClose(cbForStateMotorStopped);
      }
    }
    else {
      *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
      __DVDStoreErrorCode(0x1234567);
      DVDLowStopMotor(cbForStateError);
    }
  }
  return;
}

