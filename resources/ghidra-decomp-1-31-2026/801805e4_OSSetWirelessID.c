// Function: OSSetWirelessID
// Entry: 801805e4
// Size: 172 bytes

void OSSetWirelessID(int param_1,short param_2)

{
  short *psVar1;
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
  psVar1 = (short *)(iVar3 + param_1 * 2 + 0x1c);
  if (*psVar1 == param_2) {
    UnlockSram(0,0x14);
  }
  else {
    *psVar1 = param_2;
    UnlockSram(1,0x14);
  }
  return;
}

