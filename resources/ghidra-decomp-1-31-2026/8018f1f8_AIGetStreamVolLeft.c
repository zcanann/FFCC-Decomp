// Function: AIGetStreamVolLeft
// Entry: 8018f1f8
// Size: 16 bytes

uint AIGetStreamVolLeft(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c04;
  return uVar1 & 0xff;
}

