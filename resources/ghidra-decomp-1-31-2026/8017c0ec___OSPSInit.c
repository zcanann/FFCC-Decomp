// Function: __OSPSInit
// Entry: 8017c0ec
// Size: 84 bytes

undefined4 __OSPSInit(void)

{
  uint uVar1;
  
  uVar1 = PPCMfhid2();
  PPCMthid2(uVar1 | 0xa0000000);
  ICFlashInvalidate();
  sync(0);
  return 0;
}

