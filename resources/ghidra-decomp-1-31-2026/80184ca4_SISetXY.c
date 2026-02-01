// Function: SISetXY
// Entry: 80184ca4
// Size: 108 bytes

uint SISetXY(int param_1,int param_2)

{
  uint uVar1;
  
  OSDisableInterrupts();
  uVar1 = DAT_80217308 & 0xfc0000ff | param_1 << 0x10 | param_2 << 8;
  DAT_cc006430 = uVar1;
  DAT_80217308 = uVar1;
  OSRestoreInterrupts();
  return uVar1;
}

