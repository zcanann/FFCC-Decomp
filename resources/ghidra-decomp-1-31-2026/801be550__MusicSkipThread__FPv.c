// Function: _MusicSkipThread__FPv
// Entry: 801be550
// Size: 128 bytes

undefined4 _MusicSkipThread__FPv(void)

{
  int iVar1;
  
  DAT_8032f3c4 = DAT_8032f3c4 | 8;
  DAT_8032f470 = 0;
  while (DAT_8032f3c0 != 0) {
    OSWaitSemaphore((OSSemaphore *)&DAT_8032e120);
    if (DAT_8032f3c0 != 0) {
      MusicSkipFunction__Fv();
    }
    do {
      iVar1 = OSTryWaitSemaphore((OSSemaphore *)&DAT_8032e120);
    } while (0 < iVar1);
  }
  DAT_8032f3c4 = DAT_8032f3c4 & 0xfffffff7;
  return 0;
}

