// Function: GetProgressive__8CGraphicFv
// Entry: 80019a50
// Size: 68 bytes

int GetProgressive__8CGraphicFv(void)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = VIGetDTVStatus();
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = OSSetSoundMode();
    uVar1 = countLeadingZeros(1 - iVar2);
    iVar2 = (uVar1 >> 5) + 1;
  }
  return iVar2;
}

