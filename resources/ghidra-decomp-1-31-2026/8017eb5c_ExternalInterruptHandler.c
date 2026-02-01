// Function: ExternalInterruptHandler
// Entry: 8017eb5c
// Size: 916 bytes

void ExternalInterruptHandler
               (undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 in_r0;
  undefined4 in_r11;
  undefined4 in_r12;
  undefined4 unaff_r14;
  undefined4 unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined4 unaff_r19;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 unaff_r22;
  undefined4 unaff_r23;
  undefined4 unaff_r24;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  int iVar7;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  code *pcVar8;
  undefined4 unaff_r31;
  undefined8 uVar9;
  
  *param_2 = in_r0;
  param_2[1] = register0x00000004;
  param_2[2] = &DAT_80337600;
  param_2[6] = param_4;
  param_2[7] = param_5;
  param_2[8] = param_6;
  param_2[9] = param_7;
  param_2[10] = param_8;
  param_2[0xb] = in_r11;
  param_2[0xc] = in_r12;
  param_2[0xd] = 0x803363c0;
  param_2[0xe] = unaff_r14;
  param_2[0xf] = unaff_r15;
  param_2[0x10] = unaff_r16;
  param_2[0x11] = unaff_r17;
  param_2[0x12] = unaff_r18;
  param_2[0x13] = unaff_r19;
  param_2[0x14] = unaff_r20;
  param_2[0x15] = unaff_r21;
  param_2[0x16] = unaff_r22;
  param_2[0x17] = unaff_r23;
  param_2[0x18] = unaff_r24;
  param_2[0x19] = unaff_r25;
  param_2[0x1a] = unaff_r26;
  param_2[0x1b] = unaff_r27;
  param_2[0x1c] = unaff_r28;
  param_2[0x1d] = unaff_r29;
  param_2[0x1e] = unaff_r30;
  param_2[0x1f] = unaff_r31;
  param_2[0x6a] = 0;
  param_2[0x6b] = 0;
  param_2[0x6c] = 0;
  param_2[0x6d] = 0;
  param_2[0x6e] = 0;
  param_2[0x6f] = 0;
  param_2[0x70] = 0;
  uVar5 = DAT_cc003000;
  if (((uVar5 & 0xfffeffff) == 0) || (uVar3 = DAT_cc003004, (uVar5 & 0xfffeffff & uVar3) == 0)) {
    OSLoadContext(param_2);
  }
  uVar9 = CONCAT44(DAT_8032ef90,DAT_8032ef94);
  uVar3 = 0;
  if ((uVar5 & 0x80) != 0) {
    uVar1 = DAT_cc00401e;
    if ((uVar1 & 1) != 0) {
      uVar3 = 0x80000000;
    }
    if ((uVar1 & 2) != 0) {
      uVar3 = uVar3 | 0x40000000;
    }
    if ((uVar1 & 4) != 0) {
      uVar3 = uVar3 | 0x20000000;
    }
    if ((uVar1 & 8) != 0) {
      uVar3 = uVar3 | 0x10000000;
    }
    if ((uVar1 & 0x10) != 0) {
      uVar3 = uVar3 | 0x8000000;
    }
  }
  if ((uVar5 & 0x40) != 0) {
    uVar1 = DAT_cc00500a;
    if ((uVar1 & 8) != 0) {
      uVar3 = uVar3 | 0x4000000;
    }
    if ((uVar1 & 0x20) != 0) {
      uVar3 = uVar3 | 0x2000000;
    }
    if ((uVar1 & 0x80) != 0) {
      uVar3 = uVar3 | 0x1000000;
    }
  }
  if (((uVar5 & 0x20) != 0) && (uVar2 = DAT_cc006c00, (uVar2 & 8) != 0)) {
    uVar3 = uVar3 | 0x800000;
  }
  if ((uVar5 & 0x10) != 0) {
    uVar2 = DAT_cc006800;
    if ((uVar2 & 2) != 0) {
      uVar3 = uVar3 | 0x400000;
    }
    if ((uVar2 & 8) != 0) {
      uVar3 = uVar3 | 0x200000;
    }
    if ((uVar2 & 0x800) != 0) {
      uVar3 = uVar3 | 0x100000;
    }
    uVar2 = DAT_cc006814;
    if ((uVar2 & 2) != 0) {
      uVar3 = uVar3 | 0x80000;
    }
    if ((uVar2 & 8) != 0) {
      uVar3 = uVar3 | 0x40000;
    }
    if ((uVar2 & 0x800) != 0) {
      uVar3 = uVar3 | 0x20000;
    }
    uVar2 = DAT_cc006828;
    if ((uVar2 & 2) != 0) {
      uVar3 = uVar3 | 0x10000;
    }
    if ((uVar2 & 8) != 0) {
      uVar3 = uVar3 | 0x8000;
    }
  }
  if ((uVar5 & 0x2000) != 0) {
    uVar3 = uVar3 | 0x20;
  }
  if ((uVar5 & 0x1000) != 0) {
    uVar3 = uVar3 | 0x40;
  }
  if ((uVar5 & 0x400) != 0) {
    uVar3 = uVar3 | 0x1000;
  }
  if ((uVar5 & 0x200) != 0) {
    uVar3 = uVar3 | 0x2000;
  }
  if ((uVar5 & 0x100) != 0) {
    uVar3 = uVar3 | 0x80;
  }
  if ((uVar5 & 8) != 0) {
    uVar3 = uVar3 | 0x800;
  }
  if ((uVar5 & 4) != 0) {
    uVar3 = uVar3 | 0x400;
  }
  if ((uVar5 & 2) != 0) {
    uVar3 = uVar3 | 0x200;
  }
  if ((uVar5 & 0x800) != 0) {
    uVar3 = uVar3 | 0x4000;
  }
  if ((uVar5 & 1) != 0) {
    uVar3 = uVar3 | 0x100;
  }
  uVar3 = uVar3 & ~(DAT_800000c4 | DAT_800000c8);
  if (uVar3 != 0) {
    for (puVar4 = &DAT_80217110; uVar5 = uVar3 & *puVar4, uVar5 == 0; puVar4 = puVar4 + 1) {
    }
    uVar6 = countLeadingZeros(uVar5);
    iVar7 = (int)(short)uVar6;
    pcVar8 = *(code **)(OSAlarm_8032ef60.start._0_4_ + iVar7 * 4);
    if (pcVar8 != (code *)0x0) {
      if (4 < iVar7) {
        DAT_8032ef88 = (short)uVar6;
        uVar9 = OSGetTime();
        OSAlarm_8032ef60.start._4_4_ = param_2[0x66];
      }
      DAT_8032ef90 = (undefined4)((ulonglong)uVar9 >> 0x20);
      DAT_8032ef94 = (undefined4)uVar9;
      OSDisableScheduler();
      (*pcVar8)(iVar7,param_2);
      OSEnableScheduler();
      __OSReschedule();
      OSLoadContext(param_2);
    }
  }
  OSLoadContext(param_2);
  return;
}

