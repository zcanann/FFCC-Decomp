// Function: __CARDExiHandler
// Entry: 80198690
// Size: 280 bytes

void __CARDExiHandler(int chan)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte local_18 [12];
  
  iVar4 = chan * 0x110;
  OSCancelAlarm(&DAT_80327620 + iVar4);
  if ((&DAT_80327540)[chan * 0x44] == 0) {
    return;
  }
  iVar2 = EXILock(chan,0,0);
  if (iVar2 == 0) {
    iVar2 = -0x80;
  }
  else {
    iVar2 = __CARDReadStatus(chan,(char *)local_18);
    if ((-1 < iVar2) && (iVar2 = __CARDClearStatus(chan), -1 < iVar2)) {
      if ((local_18[0] & 0x18) == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = -5;
      }
      if ((iVar2 == -5) &&
         (iVar3 = *(int *)(&DAT_803275e8 + iVar4), *(int *)(&DAT_803275e8 + iVar4) = iVar3 + -1,
         0 < iVar3 + -1)) {
        iVar2 = Retry(chan);
        if (-1 < iVar2) {
          return;
        }
        goto LAB_80198764;
      }
    }
    EXIUnlock(chan);
  }
LAB_80198764:
  pcVar1 = *(code **)(&DAT_8032760c + iVar4);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_8032760c + iVar4) = 0;
    (*pcVar1)(chan,iVar2);
  }
  return;
}

