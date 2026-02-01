// Function: __OSDoHotReset
// Entry: 8017f56c
// Size: 72 bytes

void __OSDoHotReset(int param_1)

{
  OSDisableInterrupts();
  DAT_cc002002 = 0;
  ICFlashInvalidate();
  Reset(param_1 << 3);
  return;
}

