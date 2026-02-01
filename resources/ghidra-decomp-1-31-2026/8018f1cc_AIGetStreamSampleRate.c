// Function: AIGetStreamSampleRate
// Entry: 8018f1cc
// Size: 16 bytes

uint AIGetStreamSampleRate(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c00;
  return uVar1 >> 1 & 1;
}

