// Function: __DVDFSInit
// Entry: 801882d0
// Size: 56 bytes

void __DVDFSInit(void)

{
  DAT_8032f060 = 0x80000000;
  DAT_8032f064 = DAT_80000038;
  if (DAT_80000038 == 0) {
    return;
  }
  DAT_8032f06c = *(int *)(DAT_80000038 + 8);
  DAT_8032f068 = DAT_80000038 + *(int *)(DAT_80000038 + 8) * 0xc;
  return;
}

