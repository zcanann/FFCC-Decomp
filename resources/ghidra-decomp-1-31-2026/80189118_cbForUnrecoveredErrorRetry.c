// Function: cbForUnrecoveredErrorRetry
// Entry: 80189118
// Size: 152 bytes

void cbForUnrecoveredErrorRetry(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    __DVDStoreErrorCode(0x1234568);
    DVDReset();
    cbForStateError(0);
  }
  else {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    if ((param_1 & 2) == 0) {
      uVar1 = DAT_cc006020;
      __DVDStoreErrorCode(uVar1);
      DVDLowStopMotor(cbForStateError);
    }
    else {
      __DVDStoreErrorCode(0x1234567);
      DVDLowStopMotor(cbForStateError);
    }
  }
  return;
}

