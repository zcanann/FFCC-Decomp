// Function: OSSendMessage
// Entry: 8017ec24
// Size: 200 bytes

undefined4 OSSendMessage(int param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = OSDisableInterrupts();
  while( true ) {
    iVar3 = *(int *)(param_1 + 0x14);
    if (*(int *)(param_1 + 0x1c) < iVar3) {
      iVar2 = *(int *)(param_1 + 0x18) + *(int *)(param_1 + 0x1c);
      *(undefined4 *)(*(int *)(param_1 + 0x10) + (iVar2 - (iVar2 / iVar3) * iVar3) * 4) = param_2;
      *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
      OSWakeupThread(param_1 + 8);
      OSRestoreInterrupts(uVar1);
      return 1;
    }
    if ((param_3 & 1) == 0) break;
    OSSleepThread(param_1);
  }
  OSRestoreInterrupts(uVar1);
  return 0;
}

