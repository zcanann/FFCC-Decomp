// Function: EXISetExiCallback
// Entry: 80182820
// Size: 124 bytes

undefined4 EXISetExiCallback(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  puVar3 = FatalContext + param_1 * 0x10 + 0x297;
  uVar1 = OSDisableInterrupts();
  uVar2 = *puVar3;
  *puVar3 = param_2;
  if (param_1 == 2) {
    SetExiInterruptMask(0,0x8030c690);
  }
  else {
    SetExiInterruptMask(param_1,puVar3);
  }
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

