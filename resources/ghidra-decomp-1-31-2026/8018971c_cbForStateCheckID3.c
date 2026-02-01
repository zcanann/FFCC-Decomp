// Function: cbForStateCheckID3
// Entry: 8018971c
// Size: 252 bytes

void cbForStateCheckID3(uint param_1)

{
  undefined *puVar1;
  bool bVar2;
  
  puVar1 = DAT_8032f080;
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    __DVDStoreErrorCode(0x1234568);
    DVDReset();
    cbForStateError(0);
  }
  else if ((param_1 & 1) == 0) {
    DVDLowRequestError(cbForStateGettingError);
  }
  else {
    bVar2 = false;
    DAT_8032f0b4 = 0;
    if (DAT_8032f0a0 != 0) {
      DAT_8032f0a8 = 0;
      DAT_8032f0a0 = 0;
      DAT_8032f080 = &DAT_8030ca60;
      *(undefined4 *)(puVar1 + 0xc) = 10;
      if (*(code **)(puVar1 + 0x28) != (code *)0x0) {
        (**(code **)(puVar1 + 0x28))(0xfffffffd,puVar1);
      }
      if (DAT_8032f0a4 != (code *)0x0) {
        (*DAT_8032f0a4)(0,puVar1);
      }
      stateReady();
      bVar2 = true;
    }
    if (!bVar2) {
      *(undefined4 *)(DAT_8032f080 + 0xc) = 1;
      stateBusy(DAT_8032f080);
    }
  }
  return;
}

