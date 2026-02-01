// Function: AXARTQuit
// Entry: 801979ac
// Size: 96 bytes

void AXARTQuit(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  uVar1 = OSDisableInterrupts();
  for (puVar2 = DAT_8032f2b0; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2) {
    MIXReleaseChannel(puVar2[2]);
  }
  DAT_8032f2b0 = (undefined4 *)0x0;
  OSRestoreInterrupts(uVar1);
  return;
}

