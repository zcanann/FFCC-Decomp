// Function: __ARGetInterruptStatus
// Entry: 8018f9e4
// Size: 16 bytes

ushort __ARGetInterruptStatus(void)

{
  ushort uVar1;
  
  uVar1 = DAT_cc00500a;
  return uVar1 & 0x20;
}

