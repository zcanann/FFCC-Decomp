// Function: TRKDoNotifyStopped
// Entry: 801ab994
// Size: 152 bytes

int TRKDoNotifyStopped(int param_1)

{
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10 [2];
  
  iVar1 = TRKGetFreeBuffer(&local_14,&local_18);
  if (iVar1 == 0) {
    if (iVar1 == 0) {
      if (param_1 == 0x90) {
        TRKTargetAddStopInfo(local_18);
      }
      else {
        TRKTargetAddExceptionInfo(local_18);
      }
    }
    iVar1 = TRKRequestSend(local_18,local_10,2,3,1);
    if (iVar1 == 0) {
      TRKReleaseBuffer(local_10[0]);
    }
    TRKReleaseBuffer(local_14);
  }
  return iVar1;
}

