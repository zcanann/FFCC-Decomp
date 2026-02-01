// Function: __ARQServiceQueueLo
// Entry: 801911e8
// Size: 256 bytes

void __ARQServiceQueueLo(void)

{
  if ((DAT_8032f1d4 == (int *)0x0) && (DAT_8032f1c8 != (int *)0x0)) {
    DAT_8032f1d4 = DAT_8032f1c8;
    DAT_8032f1c8 = (int *)*DAT_8032f1c8;
  }
  if (DAT_8032f1d4 != (int *)0x0) {
    if (DAT_8032f1e0 < (uint)DAT_8032f1d4[6]) {
      if (DAT_8032f1d4[2] == 0) {
        ARStartDMA(0,DAT_8032f1d4[4],DAT_8032f1d4[5],DAT_8032f1e0);
      }
      else {
        ARStartDMA(DAT_8032f1d4[2],DAT_8032f1d4[5],DAT_8032f1d4[4],DAT_8032f1e0);
      }
    }
    else {
      if (DAT_8032f1d4[2] == 0) {
        ARStartDMA(0,DAT_8032f1d4[4],DAT_8032f1d4[5]);
      }
      else {
        ARStartDMA(DAT_8032f1d4[2],DAT_8032f1d4[5],DAT_8032f1d4[4]);
      }
      DAT_8032f1dc = DAT_8032f1d4[7];
    }
    DAT_8032f1d4[6] = DAT_8032f1d4[6] - DAT_8032f1e0;
    DAT_8032f1d4[4] = DAT_8032f1d4[4] + DAT_8032f1e0;
    DAT_8032f1d4[5] = DAT_8032f1d4[5] + DAT_8032f1e0;
  }
  return;
}

