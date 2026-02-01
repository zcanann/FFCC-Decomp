// Function: AIGetStreamVolRight
// Entry: 8018f224
// Size: 16 bytes

uint AIGetStreamVolRight(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c04;
  return uVar1 >> 8 & 0xff;
}

