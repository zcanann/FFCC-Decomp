// Function: OSSetProgressiveMode
// Entry: 801804f4
// Size: 108 bytes

undefined OSSetProgressiveMode(void)

{
  undefined uVar1;
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
  uVar1 = *(undefined *)(iVar3 + 0x12);
  UnlockSram(0,0);
  return uVar1;
}

