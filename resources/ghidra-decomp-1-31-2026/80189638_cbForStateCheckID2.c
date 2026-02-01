// Function: cbForStateCheckID2
// Entry: 80189638
// Size: 228 bytes

void cbForStateCheckID2(uint param_1)

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
    DAT_8032f0c4 = stateReadingFST;
    DAT_8032f0b4 = 0;
    if (*(uint *)(DAT_8032f088 + 0x3c) < DAT_8030ca28) {
      OSPanic(&DAT_8032eaec,0x287,s_DVDChangeDisk____FST_in_the_new_d_802175fc);
    }
    DVDLowRead(*(undefined4 *)(DAT_8032f088 + 0x38),DAT_8030ca28 + 0x1f & 0xffffffe0,DAT_8030ca24,
               cbForStateReadingFST);
  }
  return;
}

