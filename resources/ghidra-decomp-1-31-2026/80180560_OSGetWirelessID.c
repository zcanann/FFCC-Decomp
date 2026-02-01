// Function: OSGetWirelessID
// Entry: 80180560
// Size: 132 bytes

undefined2 OSGetWirelessID(int param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar2 = OSDisableInterrupts();
  if (FatalContext[0x15] == 0) {
    iVar3 = -0x7fcf43ac;
    FatalContext[0x15] = 1;
    FatalContext[0x14] = uVar2;
  }
  else {
    OSRestoreInterrupts();
    iVar3 = 0;
  }
  uVar1 = *(undefined2 *)(iVar3 + param_1 * 2 + 0x1c);
  UnlockSram(0,0x14);
  return uVar1;
}

