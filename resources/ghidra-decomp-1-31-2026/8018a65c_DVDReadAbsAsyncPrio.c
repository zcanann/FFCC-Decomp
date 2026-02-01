// Function: DVDReadAbsAsyncPrio
// Entry: 8018a65c
// Size: 220 bytes

undefined4
DVDReadAbsAsyncPrio(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  *(undefined4 *)(param_1 + 8) = 1;
  *(undefined4 *)(param_1 + 0x18) = param_2;
  *(undefined4 *)(param_1 + 0x14) = param_3;
  *(undefined4 *)(param_1 + 0x10) = param_4;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x28) = param_5;
  if ((DAT_8032eae4 != 0) &&
     (((iVar1 = *(int *)(param_1 + 8), iVar1 == 1 || (iVar1 - 4U < 2)) || (iVar1 == 0xe)))) {
    DCInvalidateRange(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x14));
  }
  uVar2 = OSDisableInterrupts();
  *(undefined4 *)(param_1 + 0xc) = 2;
  uVar3 = __DVDPushWaitingQueue(param_6,param_1);
  if ((DAT_8032f080 == 0) && (DAT_8032f08c == 0)) {
    stateReady();
  }
  OSRestoreInterrupts(uVar2);
  return uVar3;
}

