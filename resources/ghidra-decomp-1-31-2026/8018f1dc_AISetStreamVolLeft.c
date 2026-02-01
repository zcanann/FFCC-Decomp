// Function: AISetStreamVolLeft
// Entry: 8018f1dc
// Size: 28 bytes

void AISetStreamVolLeft(uint param_1)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c04;
  DAT_cc006c04 = param_1 & 0xff | uVar1 & 0xffffff00;
  return;
}

