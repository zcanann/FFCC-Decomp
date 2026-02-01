// Function: TRKDoStep
// Entry: 801aa348
// Size: 544 bytes

/* WARNING: Removing unreachable block (ram,0x801aa514) */
/* WARNING: Removing unreachable block (ram,0x801aa390) */

undefined4 TRKDoStep(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint unaff_r30;
  uint uVar6;
  undefined4 local_158;
  undefined local_154;
  undefined local_150;
  undefined4 local_118;
  undefined local_114;
  undefined local_110;
  undefined4 local_d8;
  undefined local_d4;
  undefined local_d0;
  undefined4 local_98;
  undefined local_94;
  undefined local_90;
  undefined4 local_58;
  undefined local_54;
  undefined local_50;
  
  TRKSetBufferPosition(param_1,0);
  uVar6 = (uint)*(byte *)(param_1 + 0x18);
  uVar5 = *(uint *)(param_1 + 0x20);
  uVar4 = *(uint *)(param_1 + 0x24);
  if (uVar6 == 0x10) {
LAB_801aa3a0:
    unaff_r30 = (uint)*(byte *)(param_1 + 0x1c);
    if (unaff_r30 == 0) {
      memset(&local_58,0,0x40);
      local_54 = 0x80;
      local_58 = 0x40;
      local_50 = 0x11;
      TRKWriteUARTN(&local_58,0x40);
      return 0;
    }
  }
  else {
    if (uVar6 < 0x10) {
      if (uVar6 != 1) {
        if (uVar6 != 0) goto LAB_801aa438;
        goto LAB_801aa3a0;
      }
    }
    else if (0x11 < uVar6) {
LAB_801aa438:
      memset(&local_d8,0,0x40);
      local_d4 = 0x80;
      local_d8 = 0x40;
      local_d0 = 0x12;
      TRKWriteUARTN(&local_d8,0x40);
      return 0;
    }
    uVar1 = TRKTargetGetPC();
    if ((uVar1 < uVar5) || (uVar4 < uVar1)) {
      memset(&local_98,0,0x40);
      local_94 = 0x80;
      local_98 = 0x40;
      local_90 = 0x11;
      TRKWriteUARTN(&local_98,0x40);
      return 0;
    }
  }
  iVar2 = TRKTargetStopped();
  if (iVar2 == 0) {
    memset(&local_118,0,0x40);
    local_114 = 0x80;
    local_118 = 0x40;
    local_110 = 0x16;
    TRKWriteUARTN(&local_118,0x40);
    return 0;
  }
  memset(&local_158,0,0x40);
  local_154 = 0x80;
  local_158 = 0x40;
  local_150 = 0;
  TRKWriteUARTN(&local_158,0x40);
  if (uVar6 == 0x10) {
LAB_801aa524:
    uVar4 = countLeadingZeros(0x10 - uVar6);
    uVar3 = TRKTargetSingleStep(unaff_r30,uVar4 >> 5);
  }
  else {
    if (uVar6 < 0x10) {
      if (uVar6 != 1) {
        if (uVar6 != 0) {
          return 0;
        }
        goto LAB_801aa524;
      }
    }
    else if (0x11 < uVar6) {
      return 0;
    }
    uVar6 = countLeadingZeros(0x11 - uVar6);
    uVar3 = TRKTargetStepOutOfRange(uVar5,uVar4,uVar6 >> 5);
  }
  return uVar3;
}

