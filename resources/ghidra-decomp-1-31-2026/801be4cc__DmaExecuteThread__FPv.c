// Function: _DmaExecuteThread__FPv
// Entry: 801be4cc
// Size: 132 bytes

undefined4 _DmaExecuteThread__FPv(void)

{
  DAT_8032f3c4 = DAT_8032f3c4 | 2;
  DAT_8032f488 = 0;
  while (DAT_8032f484 = 0, DAT_8032f3c0 != 0) {
    OSWaitSemaphore((OSSemaphore *)&DAT_8032ddd8);
    DAT_8032f484 = 1;
    if (DAT_8032f3c0 != 0) {
      _DmaExecute__Fv();
    }
  }
  DAT_8032f3c4 = DAT_8032f3c4 & 0xfffffffd;
  return 0;
}

