// Function: DSPCheckMailFromDSP
// Entry: 80197a2c
// Size: 16 bytes

ushort DSPCheckMailFromDSP(void)

{
  ushort uVar1;
  
  uVar1 = DAT_cc005004;
  return uVar1 >> 0xf;
}

