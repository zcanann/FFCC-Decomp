// Function: __CARDStart
// Entry: 80198f10
// Size: 436 bytes

undefined4 __CARDStart(int chan,int _callback,int param_3)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  
  uVar2 = OSDisableInterrupts();
  iVar5 = chan * 0x110;
  if ((&DAT_80327540)[chan * 0x44] == 0) {
    uVar7 = 0xfffffffd;
    goto LAB_801990a4;
  }
  if (_callback != 0) {
    *(int *)(&DAT_80327608 + iVar5) = _callback;
  }
  if (param_3 != 0) {
    *(int *)(&DAT_8032760c + iVar5) = param_3;
  }
  *(code **)(&DAT_8032761c + iVar5) = UnlockedCallback;
  iVar3 = EXILock(chan,0,__CARDUnlockedHandler);
  if (iVar3 == 0) {
    uVar7 = 0xffffffff;
    goto LAB_801990a4;
  }
  *(undefined4 *)(&DAT_8032761c + iVar5) = 0;
  iVar3 = EXISelect(chan,0,4);
  if (iVar3 == 0) {
    EXIUnlock(chan);
    uVar7 = 0xfffffffd;
    goto LAB_801990a4;
  }
  OSCancelAlarm(&DAT_80327620 + iVar5);
  bVar1 = (&DAT_803275d4)[iVar5];
  if (bVar1 != 0xf3) {
    if (bVar1 < 0xf3) {
      if (bVar1 == 0xf1) {
LAB_8019903c:
        uVar4 = *(uint *)(&DAT_8032754c + iVar5);
        uVar6 = (DAT_800000f8 >> 2) * 2;
        uVar4 = ((int)uVar4 >> 0xd) + (uint)((int)uVar4 < 0 && (uVar4 & 0x1fff) != 0);
        iVar3 = ((int)uVar4 >> 0x1f) * uVar6 + (int)((ulonglong)uVar4 * (ulonglong)uVar6 >> 0x20);
        OSSetAlarm((OSAlarm *)(&DAT_80327620 + iVar5),iVar3,iVar3,uVar4 * uVar6,TimeoutHandler);
      }
      else if (0xf0 < bVar1) {
        OSSetAlarm((OSAlarm *)(&DAT_80327620 + iVar5),0x10624dd3,0,(DAT_800000f8 / 4000) * 100,
                   TimeoutHandler);
      }
    }
    else if (bVar1 < 0xf5) goto LAB_8019903c;
  }
  uVar7 = 0;
LAB_801990a4:
  OSRestoreInterrupts(uVar2);
  return uVar7;
}

