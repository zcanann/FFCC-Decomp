// Function: AIGetDSPSampleRate
// Entry: 8018f0e4
// Size: 20 bytes

uint AIGetDSPSampleRate(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c00;
  return uVar1 >> 6 & 1 ^ 1;
}

