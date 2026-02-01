// Function: __ARQInterruptServiceRoutine
// Entry: 801912ec
// Size: 204 bytes

void __ARQInterruptServiceRoutine(void)

{
  if (DAT_8032f1d8 == (code *)0x0) {
    if (DAT_8032f1dc != (code *)0x0) {
      (*DAT_8032f1dc)(DAT_8032f1d4);
      DAT_8032f1d4 = 0;
      DAT_8032f1dc = (code *)0x0;
    }
  }
  else {
    (*DAT_8032f1d8)(DAT_8032f1d0);
    DAT_8032f1d0 = (int *)0x0;
    DAT_8032f1d8 = (code *)0x0;
  }
  if (DAT_8032f1c0 != (int *)0x0) {
    if (DAT_8032f1c0[2] == 0) {
      ARStartDMA(0,DAT_8032f1c0[4],DAT_8032f1c0[5],DAT_8032f1c0[6]);
    }
    else {
      ARStartDMA(DAT_8032f1c0[2],DAT_8032f1c0[5],DAT_8032f1c0[4],DAT_8032f1c0[6]);
    }
    DAT_8032f1d8 = (code *)DAT_8032f1c0[7];
    DAT_8032f1d0 = DAT_8032f1c0;
    DAT_8032f1c0 = (int *)*DAT_8032f1c0;
  }
  if (DAT_8032f1d0 == (int *)0x0) {
    __ARQServiceQueueLo();
  }
  return;
}

