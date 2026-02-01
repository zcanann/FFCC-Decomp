// Function: cbForUnrecoveredError
// Entry: 801890b0
// Size: 104 bytes

void cbForUnrecoveredError(uint param_1)

{
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    __DVDStoreErrorCode(0x1234568);
    DVDReset();
    cbForStateError(0);
  }
  else if ((param_1 & 1) == 0) {
    DVDLowRequestError(cbForUnrecoveredErrorRetry);
  }
  else {
    stateGoToRetry();
  }
  return;
}

