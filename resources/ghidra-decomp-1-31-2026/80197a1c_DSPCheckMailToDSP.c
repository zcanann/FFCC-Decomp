// Function: DSPCheckMailToDSP
// Entry: 80197a1c
// Size: 16 bytes

ushort DSPCheckMailToDSP(void)

{
  ushort uVar1;
  
  uVar1 = DAT_cc005000;
  return uVar1 >> 0xf;
}

