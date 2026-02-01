// Function: AIGetDMAStartAddr
// Entry: 8018ef00
// Size: 28 bytes

uint AIGetDMAStartAddr(void)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar1 = DAT_cc005030;
  uVar2 = DAT_cc005032;
  return (uVar1 & 0x3ff) << 0x10 | uVar2 & 0xffe0;
}

