// Function: OnReset
// Entry: 8017edd4
// Size: 60 bytes

undefined4 OnReset(int param_1)

{
  if (param_1 != 0) {
    DAT_cc004010 = 0xff;
    __OSMaskInterrupts(0xf0000000);
  }
  return 1;
}

