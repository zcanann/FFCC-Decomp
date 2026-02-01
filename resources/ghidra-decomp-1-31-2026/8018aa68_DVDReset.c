// Function: DVDReset
// Entry: 8018aa68
// Size: 68 bytes

void DVDReset(void)

{
  undefined4 uVar1;
  
  DVDLowReset();
  DAT_cc006000 = 0x2a;
  uVar1 = DAT_cc006004;
  DAT_cc006004 = uVar1;
  DAT_8032f0b8 = 0;
  DAT_8032f0a8 = 0;
  return;
}

