// Function: Retry
// Entry: 80198bd4
// Size: 556 bytes

undefined4 Retry(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  iVar4 = param_1 * 0x110;
  iVar2 = EXISelect(param_1,0,4);
  if (iVar2 == 0) {
    EXIUnlock(param_1);
    return 0xfffffffd;
  }
  OSCancelAlarm(&DAT_80327620 + iVar4);
  bVar1 = (&DAT_803275d4)[iVar4];
  if (bVar1 != 0xf3) {
    if (bVar1 < 0xf3) {
      if (bVar1 != 0xf1) {
        if (0xf0 < bVar1) {
          OSSetAlarm((OSAlarm *)(&DAT_80327620 + iVar4),0x10624dd3,0,(DAT_800000f8 / 4000) * 100,
                     TimeoutHandler);
        }
        goto LAB_80198cf4;
      }
    }
    else if (0xf4 < bVar1) goto LAB_80198cf4;
    uVar5 = *(uint *)(&DAT_8032754c + iVar4);
    uVar6 = (DAT_800000f8 >> 2) * 2;
    uVar5 = ((int)uVar5 >> 0xd) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1fff) != 0);
    iVar2 = ((int)uVar5 >> 0x1f) * uVar6 + (int)((ulonglong)uVar5 * (ulonglong)uVar6 >> 0x20);
    OSSetAlarm((OSAlarm *)(&DAT_80327620 + iVar4),iVar2,iVar2,uVar5 * uVar6,TimeoutHandler);
  }
LAB_80198cf4:
  iVar2 = EXIImmEx(param_1,&DAT_803275d4 + iVar4,*(undefined4 *)(&DAT_803275e0 + iVar4),1);
  if (iVar2 == 0) {
    EXIDeselect(param_1);
    EXIUnlock(param_1);
    uVar3 = 0xfffffffd;
  }
  else if (((&DAT_803275d4)[iVar4] == 'R') &&
          (iVar2 = EXIImmEx(param_1,(&DAT_803275c0)[param_1 * 0x44] + 0x200,
                            *(undefined4 *)(&DAT_80327554 + iVar4),1), iVar2 == 0)) {
    EXIDeselect(param_1);
    EXIUnlock(param_1);
    uVar3 = 0xfffffffd;
  }
  else if (*(int *)(&DAT_803275e4 + iVar4) == -1) {
    EXIDeselect(param_1);
    EXIUnlock(param_1);
    uVar3 = 0;
  }
  else {
    if ((&DAT_803275d4)[iVar4] == 'R') {
      uVar3 = 0x200;
    }
    else {
      uVar3 = 0x80;
    }
    iVar2 = EXIDma(param_1,*(undefined4 *)(&DAT_803275f4 + iVar4),uVar3,
                   *(undefined4 *)(&DAT_803275e4 + iVar4),__CARDTxHandler);
    if (iVar2 == 0) {
      EXIDeselect(param_1);
      EXIUnlock(param_1);
      uVar3 = 0xfffffffd;
    }
    else {
      uVar3 = 0;
    }
  }
  return uVar3;
}

