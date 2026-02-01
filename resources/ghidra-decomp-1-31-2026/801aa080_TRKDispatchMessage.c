// Function: TRKDispatchMessage
// Entry: 801aa080
// Size: 368 bytes

undefined4 TRKDispatchMessage(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0x500;
  TRKSetBufferPosition(param_1,0);
  MWTRACE(1,s_Dispatch_command_0x_08x_801e6828,*(undefined *)(param_1 + 0x14));
  switch(*(undefined *)(param_1 + 0x14)) {
  case 1:
    uVar1 = TRKDoConnect(param_1);
    break;
  case 2:
    uVar1 = TRKDoDisconnect(param_1);
    break;
  case 3:
    uVar1 = TRKDoReset(param_1);
    break;
  case 4:
    uVar1 = TRKDoVersions(param_1);
    break;
  case 5:
    uVar1 = TRKDoSupportMask(param_1);
    break;
  case 7:
    uVar1 = TRKDoOverride(param_1);
    break;
  case 0x10:
    uVar1 = TRKDoReadMemory(param_1);
    break;
  case 0x11:
    uVar1 = TRKDoWriteMemory(param_1);
    break;
  case 0x12:
    uVar1 = TRKDoReadRegisters(param_1);
    break;
  case 0x13:
    uVar1 = TRKDoWriteRegisters(param_1);
    break;
  case 0x17:
    uVar1 = TRKDoSetOption(param_1);
    break;
  case 0x18:
    uVar1 = TRKDoContinue(param_1);
    break;
  case 0x19:
    uVar1 = TRKDoStep(param_1);
    break;
  case 0x1a:
    uVar1 = TRKDoStop(param_1);
  }
  MWTRACE(1,s_Dispatch_complete_err____ld_801e6844,uVar1);
  return uVar1;
}

