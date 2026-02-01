// Function: AIStartDMA
// Entry: 8018eed0
// Size: 24 bytes

void AIStartDMA(void)

{
  ushort uVar1;
  
  uVar1 = DAT_cc005036;
  DAT_cc005036 = uVar1 | 0x8000;
  return;
}

