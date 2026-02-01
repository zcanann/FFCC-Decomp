// Function: AXFXDelayInit
// Entry: 801968ec
// Size: 72 bytes

void AXFXDelayInit(int param_1)

{
  OSDisableInterrupts();
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  OSRestoreInterrupts();
  AXFXDelaySettings(param_1);
  return;
}

