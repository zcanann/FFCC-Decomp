// Function: EXIGetID
// Entry: 801836dc
// Size: 944 bytes

undefined4 EXIGetID(int param_1,int param_2,int *param_3)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  code *pcVar12;
  int unaff_r29;
  undefined4 local_2c [2];
  
  iVar8 = param_1 * 0x40;
  if (((param_1 == 0) && (param_2 == 2)) && (DAT_8032efe8 != 0)) {
    *param_3 = DAT_8032efe8;
    return 1;
  }
  if ((param_1 < 2) && (param_2 == 0)) {
    iVar9 = __EXIProbe(param_1);
    if (iVar9 == 0) {
      return 0;
    }
    if (FatalContext[param_1 * 0x10 + 0x29f] == (&DAT_800030c0)[param_1]) {
      *param_3 = FatalContext[param_1 * 0x10 + 0x29e];
      return FatalContext[param_1 * 0x10 + 0x29f];
    }
    uVar10 = OSDisableInterrupts();
    if (((FatalContext[param_1 * 0x10 + 0x29a] & 8) == 0) &&
       (iVar9 = __EXIProbe(param_1), iVar9 != 0)) {
      EXIClearInterrupts(param_1,1,0,0);
      FatalContext[param_1 * 0x10 + 0x299] = 0;
      __OSUnmaskInterrupts(0x100000 >> param_1 * 3);
      FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] | 8;
      OSRestoreInterrupts(uVar10);
      bVar1 = true;
    }
    else {
      OSRestoreInterrupts(uVar10);
      bVar1 = false;
    }
    if (!bVar1) {
      return 0;
    }
    unaff_r29 = (&DAT_800030c0)[param_1];
  }
  uVar10 = OSDisableInterrupts();
  bVar1 = false;
  if ((param_1 < 2) && (param_2 == 0)) {
    bVar1 = true;
  }
  if (bVar1) {
    pcVar12 = UnlockedHandler;
  }
  else {
    pcVar12 = (code *)0x0;
  }
  uVar11 = EXILock(param_1,param_2,pcVar12);
  uVar2 = countLeadingZeros(uVar11);
  uVar2 = uVar2 >> 5;
  if (uVar2 == 0) {
    uVar11 = EXISelect(param_1,param_2,0);
    uVar3 = countLeadingZeros(uVar11);
    uVar2 = uVar3 >> 5;
    if (uVar2 == 0) {
      local_2c[0] = 0;
      uVar11 = EXIImm(param_1,local_2c,2,1,0);
      uVar2 = countLeadingZeros(uVar11);
      uVar11 = EXISync(param_1);
      uVar4 = countLeadingZeros(uVar11);
      uVar11 = EXIImm(param_1,param_3,4,0,0);
      uVar5 = countLeadingZeros(uVar11);
      uVar11 = EXISync(param_1);
      uVar6 = countLeadingZeros(uVar11);
      uVar11 = EXIDeselect(param_1);
      uVar7 = countLeadingZeros(uVar11);
      uVar2 = (uVar3 | uVar2 | uVar4 | uVar5 | uVar6 | uVar7) >> 5;
    }
    uVar11 = OSDisableInterrupts();
    if ((FatalContext[param_1 * 0x10 + 0x29a] & 0x10) == 0) {
      OSRestoreInterrupts(uVar11);
    }
    else {
      FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] & 0xffffffef;
      SetExiInterruptMask(param_1,iVar8 + -0x7fcf3970);
      if (0 < (int)FatalContext[param_1 * 0x10 + 0x2a0]) {
        pcVar12 = (code *)FatalContext[param_1 * 0x10 + 0x2a2];
        iVar9 = FatalContext[param_1 * 0x10 + 0x2a0] + -1;
        FatalContext[param_1 * 0x10 + 0x2a0] = iVar9;
        if (0 < iVar9) {
          memmove(iVar8 + -0x7fcf3948,iVar8 + -0x7fcf3940,FatalContext[param_1 * 0x10 + 0x2a0] << 3)
          ;
        }
        (*pcVar12)(param_1,0);
      }
      OSRestoreInterrupts(uVar11);
    }
  }
  OSRestoreInterrupts(uVar10);
  if ((param_1 < 2) && (param_2 == 0)) {
    uVar10 = OSDisableInterrupts();
    if ((FatalContext[param_1 * 0x10 + 0x29a] & 8) == 0) {
      OSRestoreInterrupts(uVar10);
    }
    else if (((FatalContext[param_1 * 0x10 + 0x29a] & 0x10) == 0) ||
            (FatalContext[param_1 * 0x10 + 0x29d] != 0)) {
      FatalContext[param_1 * 0x10 + 0x29a] = FatalContext[param_1 * 0x10 + 0x29a] & 0xfffffff7;
      __OSMaskInterrupts(0x500000 >> param_1 * 3);
      OSRestoreInterrupts(uVar10);
    }
    else {
      OSRestoreInterrupts(uVar10);
    }
    OSDisableInterrupts();
    iVar8 = (&DAT_800030c0)[param_1];
    if (uVar2 == 0 && iVar8 == unaff_r29) {
      FatalContext[param_1 * 0x10 + 0x29e] = *param_3;
      FatalContext[param_1 * 0x10 + 0x29f] = unaff_r29;
    }
    OSRestoreInterrupts();
    if (uVar2 == 0 && iVar8 == unaff_r29) {
      uVar10 = FatalContext[param_1 * 0x10 + 0x29f];
    }
    else {
      uVar10 = 0;
    }
  }
  else if (uVar2 == 0) {
    uVar10 = 1;
  }
  else {
    uVar10 = 0;
  }
  return uVar10;
}

