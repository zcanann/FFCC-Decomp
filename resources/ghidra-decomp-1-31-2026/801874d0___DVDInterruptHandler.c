// Function: __DVDInterruptHandler
// Entry: 801874d0
// Size: 736 bytes

void __DVDInterruptHandler(undefined4 param_1,undefined4 param_2)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  code *pcVar9;
  uint uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  undefined auStack_2e0 [716];
  
  uVar11 = CONCAT44(DAT_8032f048,DAT_8032f04c);
  uVar10 = 0;
  if (DAT_8032f058 != 0) {
    uVar11 = __OSGetSystemTime();
    DAT_8032ead0 = 0;
    DAT_8030ca08 = DAT_8030ca14;
    DAT_8030ca0c = DAT_8030ca18;
    DAT_8030ca10 = DAT_8030ca1c;
    if (DAT_8032f018 == 1) {
      uVar10 = 8;
    }
  }
  DAT_8032f048 = (undefined4)((ulonglong)uVar11 >> 0x20);
  DAT_8032f04c = (undefined4)uVar11;
  DAT_8032f058 = 0;
  DAT_8032f018 = 0;
  uVar3 = DAT_cc006000;
  uVar2 = (uVar3 & 0x2a) << 1 & uVar3 & 0x54;
  if ((uVar2 & 0x40) != 0) {
    uVar10 = 8;
  }
  if ((uVar2 & 0x10) != 0) {
    uVar10 = uVar10 | 1;
  }
  if ((uVar2 & 4) != 0) {
    uVar10 = uVar10 | 2;
  }
  if (uVar10 != 0) {
    DAT_8032f030 = 0;
    OSCancelAlarm(&DAT_8030c9b8);
    uVar11 = CONCAT44(DAT_8032f048,DAT_8032f04c);
  }
  DAT_8032f048 = (undefined4)((ulonglong)uVar11 >> 0x20);
  DAT_8032f04c = (undefined4)uVar11;
  DAT_cc006000 = uVar2 | uVar3 & 0x2a;
  if (DAT_8032f030 == 0) {
LAB_8018764c:
    if (DAT_8032f034 == 0) {
      DAT_cc006004 = 0;
    }
    else {
      uVar3 = DAT_cc006004;
      uVar2 = uVar3 & 4 & (uVar3 & 2) << 1;
      if (uVar2 != 0) {
        uVar10 = uVar10 | 4;
      }
      DAT_cc006004 = uVar2 | uVar3 & 2;
      DAT_8032f034 = 0;
    }
  }
  else {
    uVar12 = __OSGetSystemTime();
    uVar11 = CONCAT44(DAT_8032f048,DAT_8032f04c);
    if (((uint)uVar12 - DAT_8032f02c < (DAT_800000f8 / 4000) * 200) + 0x80000000 <=
        ((int)((ulonglong)uVar12 >> 0x20) - ((uint)((uint)uVar12 < DAT_8032f02c) + DAT_8032f028) ^
        0x80000000)) goto LAB_8018764c;
    uVar2 = DAT_cc006004;
    if ((uVar2 & 4 & (uVar2 & 2) << 1) != 0) {
      if (DAT_8032f024 != (code *)0x0) {
        (*DAT_8032f024)(4);
      }
      DAT_8032f024 = (code *)0x0;
    }
    uVar11 = CONCAT44(DAT_8032f048,DAT_8032f04c);
    uVar4 = DAT_cc006004;
    DAT_cc006004 = uVar4;
  }
  DAT_8032f048 = (undefined4)((ulonglong)uVar11 >> 0x20);
  DAT_8032f04c = (undefined4)uVar11;
  if (((uVar10 & 8) != 0) && (DAT_8032f038 == 0)) {
    uVar10 = uVar10 & 0xfffffff7;
  }
  if ((uVar10 & 1) == 0) {
    DAT_8030c950 = 0xffffffff;
    DAT_8032f05c = 0;
  }
  else {
    if ((&DAT_8030c950)[DAT_8032f05c * 5] == 1) {
      iVar5 = DAT_8032f05c * 5;
      iVar6 = DAT_8032f05c * 5;
      iVar7 = DAT_8032f05c * 5;
      iVar8 = DAT_8032f05c * 5;
      DAT_8032f05c = DAT_8032f05c + 1;
      Read((&DAT_8030c954)[iVar5],(&DAT_8030c958)[iVar6],(&DAT_8030c95c)[iVar7],
           (&DAT_8030c960)[iVar8]);
      uVar11 = CONCAT44(DAT_8032f048,DAT_8032f04c);
      bVar1 = true;
    }
    else if ((&DAT_8030c950)[DAT_8032f05c * 5] == 2) {
      iVar5 = DAT_8032f05c * 5;
      iVar6 = DAT_8032f05c * 5;
      DAT_8032f05c = DAT_8032f05c + 1;
      DVDLowSeek((&DAT_8030c95c)[iVar5],(&DAT_8030c960)[iVar6]);
      uVar11 = CONCAT44(DAT_8032f048,DAT_8032f04c);
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) goto LAB_8018779c;
  }
  DAT_8032f048 = (undefined4)((ulonglong)uVar11 >> 0x20);
  DAT_8032f04c = (undefined4)uVar11;
  OSClearContext(auStack_2e0);
  OSSetCurrentContext(auStack_2e0);
  pcVar9 = DAT_8032f020;
  if (uVar10 != 0) {
    bVar1 = DAT_8032f020 != (code *)0x0;
    DAT_8032f020 = (code *)0x0;
    if (bVar1) {
      (*pcVar9)(uVar10);
    }
    DAT_8032f038 = 0;
  }
  OSClearContext(auStack_2e0);
  OSSetCurrentContext(param_2);
  uVar11 = CONCAT44(DAT_8032f048,DAT_8032f04c);
LAB_8018779c:
  DAT_8032f048 = (undefined4)((ulonglong)uVar11 >> 0x20);
  DAT_8032f04c = (undefined4)uVar11;
  return;
}

