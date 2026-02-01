// Function: AISetStreamVolRight
// Entry: 8018f208
// Size: 28 bytes

void AISetStreamVolRight(uint param_1)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c04;
  DAT_cc006c04 = (param_1 & 0xff) << 8 | uVar1 & 0xffff00ff;
  return;
}

