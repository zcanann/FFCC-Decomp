// Function: AIGetStreamPlayState
// Entry: 8018eff4
// Size: 16 bytes

uint AIGetStreamPlayState(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c00;
  return uVar1 & 1;
}

