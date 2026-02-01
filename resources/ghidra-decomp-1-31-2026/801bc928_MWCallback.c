// Function: MWCallback
// Entry: 801bc928
// Size: 60 bytes

void MWCallback(void)

{
  DAT_8032f3b4 = 1;
  if (DAT_8032f3a0 != (code *)0x0) {
    (*DAT_8032f3a0)(0);
  }
  return;
}

