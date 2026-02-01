// Function: cbForStateCoverClosed
// Entry: 80189958
// Size: 112 bytes

void cbForStateCoverClosed(uint param_1)

{
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
    DAT_8032f0b4 = 0;
    stateCheckID();
  }
  return;
}

