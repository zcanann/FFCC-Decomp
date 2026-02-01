// Function: __ARClearInterrupt
// Entry: 8018f9c4
// Size: 32 bytes

void __ARClearInterrupt(void)

{
  ushort uVar1;
  
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xff77 | 0x20;
  return;
}

