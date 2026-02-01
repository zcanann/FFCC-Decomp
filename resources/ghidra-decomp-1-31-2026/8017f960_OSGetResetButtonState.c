// Function: OSGetResetButtonState
// Entry: 8017f960
// Size: 664 bytes

uint OSGetResetButtonState(void)

{
  byte bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint extraout_r4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  
  uVar2 = OSDisableInterrupts();
  uVar9 = __OSGetSystemTime();
  uVar10 = CONCAT44(DAT_8032efc8,DAT_8032efcc);
  uVar3 = (uint)((ulonglong)uVar9 >> 0x20);
  uVar4 = (uint)uVar9;
  uVar8 = DAT_cc003000;
  if ((uVar8 & 0x10000) == 0) {
    if (DAT_8032efb4 == 0) {
      DAT_8032efb4 = 1;
      uVar8 = (uint)(DAT_8032efc4 != 0 || DAT_8032efc0 != 0);
      uVar10 = uVar9;
      uVar9 = CONCAT44(DAT_8032efc0,DAT_8032efc4);
    }
    else {
      bVar1 = 1;
      if ((DAT_8032efc4 == 0 && DAT_8032efc0 == 0) &&
         ((uint)((DAT_800000f8 / 500000) * 100 >> 3 < uVar4 - DAT_8032efcc) +
          (uVar3 - ((uint)(uVar4 < DAT_8032efcc) + DAT_8032efc8) ^ 0x80000000) < 0x80000001)) {
        bVar1 = 0;
      }
      uVar8 = (uint)bVar1;
      uVar10 = CONCAT44(DAT_8032efc8,DAT_8032efcc);
      uVar9 = CONCAT44(DAT_8032efc0,DAT_8032efc4);
    }
  }
  else if (DAT_8032efb4 == 0) {
    if ((DAT_8032efc4 == 0 && DAT_8032efc0 == 0) ||
       ((uVar4 - DAT_8032efc4 < (DAT_800000f8 / 4000) * 0x28) + 0x80000000 <=
        (uVar3 - ((uint)(uVar4 < DAT_8032efc4) + DAT_8032efc0) ^ 0x80000000))) {
      uVar9 = 0;
      uVar8 = 0;
      uVar10 = CONCAT44(DAT_8032efc8,DAT_8032efcc);
    }
    else {
      uVar8 = 1;
      uVar10 = CONCAT44(DAT_8032efc8,DAT_8032efcc);
      uVar9 = CONCAT44(DAT_8032efc0,DAT_8032efc4);
    }
  }
  else {
    DAT_8032efb4 = 0;
    uVar8 = DAT_8032efb8;
    if (DAT_8032efb8 == 0) {
      uVar10 = CONCAT44(DAT_8032efc8,DAT_8032efcc);
      uVar9 = 0;
    }
  }
  DAT_8032efc0 = (int)((ulonglong)uVar9 >> 0x20);
  DAT_8032efc4 = (uint)uVar9;
  DAT_8032efc8 = (int)((ulonglong)uVar10 >> 0x20);
  DAT_8032efcc = (uint)uVar10;
  DAT_8032efb8 = uVar8;
  if ((DAT_800030e3 & 0x3f) != 0) {
    uVar7 = (DAT_800030e3 & 0x3f) * 0x3c;
    uVar5 = uVar7 * (DAT_800000f8 >> 2);
    uVar6 = DAT_8032ef5c + uVar5;
    uVar5 = DAT_8032ef58 +
            (int)((ulonglong)uVar7 * (ulonglong)(DAT_800000f8 >> 2) >> 0x20) +
            (uint)CARRY4(DAT_8032ef5c,uVar5);
    if ((uVar5 ^ 0x80000000) < (uint)(uVar6 < uVar4) + (uVar3 ^ 0x80000000)) {
      uVar10 = __div2i(uVar3 - ((uVar4 < uVar6) + uVar5),uVar4 - uVar6,0);
      __div2i((int)((ulonglong)uVar10 >> 0x20),(int)uVar10,0,2);
      uVar9 = CONCAT44(DAT_8032efc0,DAT_8032efc4);
      uVar10 = CONCAT44(DAT_8032efc8,DAT_8032efcc);
      if ((extraout_r4 & 1) == 0) {
        uVar8 = 1;
        uVar10 = CONCAT44(DAT_8032efc8,DAT_8032efcc);
        uVar9 = CONCAT44(DAT_8032efc0,DAT_8032efc4);
      }
      else {
        uVar8 = 0;
      }
    }
  }
  DAT_8032efc0 = (int)((ulonglong)uVar9 >> 0x20);
  DAT_8032efc4 = (uint)uVar9;
  DAT_8032efc8 = (int)((ulonglong)uVar10 >> 0x20);
  DAT_8032efcc = (uint)uVar10;
  OSRestoreInterrupts(uVar2);
  return uVar8;
}

