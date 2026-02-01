// Function: DVDCancelStreamAsync
// Entry: 8018a8dc
// Size: 188 bytes

undefined4 DVDCancelStreamAsync(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  *(undefined4 *)(param_1 + 8) = 7;
  *(undefined4 *)(param_1 + 0x28) = param_2;
  if ((DAT_8032eae4 != 0) &&
     (((iVar1 = *(int *)(param_1 + 8), iVar1 == 1 || (iVar1 - 4U < 2)) || (iVar1 == 0xe)))) {
    DCInvalidateRange(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x14));
  }
  uVar2 = OSDisableInterrupts();
  *(undefined4 *)(param_1 + 0xc) = 2;
  uVar3 = __DVDPushWaitingQueue(1,param_1);
  if ((DAT_8032f080 == 0) && (DAT_8032f08c == 0)) {
    stateReady();
  }
  OSRestoreInterrupts(uVar2);
  return uVar3;
}

