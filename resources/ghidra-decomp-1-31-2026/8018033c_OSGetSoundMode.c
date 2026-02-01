// Function: OSGetSoundMode
// Entry: 8018033c
// Size: 164 bytes

void OSGetSoundMode(uint param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = -0x7fcf43c0;
  uVar2 = (param_1 & 1) << 2;
  uVar1 = OSDisableInterrupts();
  if (FatalContext[0x15] == 0) {
    FatalContext[0x15] = 1;
    FatalContext[0x14] = uVar1;
  }
  else {
    OSRestoreInterrupts();
    iVar3 = 0;
  }
  if (uVar2 == (*(byte *)(iVar3 + 0x13) & 4)) {
    UnlockSram(0,0);
  }
  else {
    *(byte *)(iVar3 + 0x13) = *(byte *)(iVar3 + 0x13) & 0xfb;
    *(byte *)(iVar3 + 0x13) = *(byte *)(iVar3 + 0x13) | (byte)uVar2;
    UnlockSram(1,0);
  }
  return;
}

