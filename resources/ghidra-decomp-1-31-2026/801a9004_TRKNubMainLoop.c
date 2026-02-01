// Function: TRKNubMainLoop
// Entry: 801a9004
// Size: 248 bytes

void TRKNubMainLoop(void)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int local_18 [2];
  undefined4 local_10;
  
  bVar2 = false;
  bVar1 = false;
  while (!bVar2) {
    iVar3 = TRKGetNextEvent(local_18);
    if (iVar3 == 0) {
      if ((bVar1) && (*DAT_8032f358 == '\0')) {
        iVar3 = TRKTargetStopped();
        if (iVar3 == 0) {
          TRKTargetContinue();
        }
        bVar1 = false;
      }
      else {
        bVar1 = true;
        TRKGetInput();
      }
    }
    else {
      bVar1 = false;
      if (local_18[0] == 2) {
        TRKGetBuffer(local_10);
        TRKDispatchMessage();
      }
      else if (local_18[0] < 2) {
        if ((local_18[0] != 0) && (-1 < local_18[0])) {
          bVar2 = true;
        }
      }
      else if (local_18[0] == 5) {
        TRKTargetSupportRequest();
      }
      else if (local_18[0] < 5) {
        TRKTargetInterrupt(local_18);
      }
      TRKDestructEvent(local_18);
    }
  }
  return;
}

