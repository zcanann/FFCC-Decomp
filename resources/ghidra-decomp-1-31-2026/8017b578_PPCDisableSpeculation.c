// Function: PPCDisableSpeculation
// Entry: 8017b578
// Size: 40 bytes

void PPCDisableSpeculation(void)

{
  uint uVar1;
  
  uVar1 = PPCMfhid0();
  PPCMthid0(uVar1 | 0x200);
  return;
}

