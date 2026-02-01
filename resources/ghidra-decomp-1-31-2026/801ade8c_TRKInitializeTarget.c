// Function: TRKInitializeTarget
// Entry: 801ade8c
// Size: 76 bytes

undefined4 TRKInitializeTarget(void)

{
  DAT_8032a1bc = 1;
  DAT_8032a1b0 = __TRK_get_MSR();
  DAT_8032a6a0 = 0xe0000000;
  return 0;
}

