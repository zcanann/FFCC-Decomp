// Function: __DVDInitWA
// Entry: 80187490
// Size: 64 bytes

void __DVDInitWA(void)

{
  DAT_8032f05c = 0;
  DAT_8030c950 = 0xffffffff;
  __DVDLowSetWAType(0,0);
  OSInitAlarm();
  return;
}

