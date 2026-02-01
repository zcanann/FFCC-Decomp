// Function: AIStopDMA
// Entry: 8018eee8
// Size: 24 bytes

void AIStopDMA(void)

{
  ushort uVar1;
  
  uVar1 = DAT_cc005036;
  DAT_cc005036 = uVar1 & 0x7fff;
  return;
}

