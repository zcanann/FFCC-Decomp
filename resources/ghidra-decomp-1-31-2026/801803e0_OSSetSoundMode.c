// Function: OSSetSoundMode
// Entry: 801803e0
// Size: 112 bytes

byte OSSetSoundMode(void)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = -0x7fcf43c0;
  uVar2 = OSDisableInterrupts();
  if (FatalContext[0x15] == 0) {
    FatalContext[0x15] = 1;
    FatalContext[0x14] = uVar2;
  }
  else {
    OSRestoreInterrupts();
    iVar3 = 0;
  }
  bVar1 = *(byte *)(iVar3 + 0x13);
  UnlockSram(0,0);
  return bVar1 >> 7;
}

