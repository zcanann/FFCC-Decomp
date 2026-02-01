// Function: __GBASyncCallback
// Entry: 801a8b40
// Size: 52 bytes

void __GBASyncCallback(int param_1)

{
  OSWakeupThread(&DAT_80328344 + param_1 * 0x100);
  return;
}

