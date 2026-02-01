// Function: __OSResetSWInterruptHandler
// Entry: 8017f86c
// Size: 244 bytes

void __OSResetSWInterruptHandler(void)

{
  uint uVar1;
  uint uVar2;
  code *pcVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  
  uVar4 = __OSGetSystemTime();
  uVar1 = DAT_800000f8 / 500000;
  do {
    DAT_8032efc8 = (int)((ulonglong)uVar4 >> 0x20);
    DAT_8032efcc = (uint)uVar4;
    uVar5 = __OSGetSystemTime();
    uVar4 = CONCAT44(DAT_8032efc8,DAT_8032efcc);
    if (((uint)uVar5 - DAT_8032efcc < uVar1 * 100 >> 3) + 0x80000000 <=
        ((int)((ulonglong)uVar5 >> 0x20) - ((uint)((uint)uVar5 < DAT_8032efcc) + DAT_8032efc8) ^
        0x80000000)) break;
    uVar2 = DAT_cc003000;
  } while ((uVar2 & 0x10000) == 0);
  uVar1 = DAT_cc003000;
  if ((uVar1 & 0x10000) == 0) {
    DAT_8032efb4 = 1;
    DAT_8032efb8 = 1;
    __OSMaskInterrupts(0x200);
    pcVar3 = DAT_8032efb0;
    if (DAT_8032efb0 != (code *)0x0) {
      DAT_8032efb0 = (code *)0x0;
      (*pcVar3)();
    }
  }
  DAT_cc003000 = 2;
  return;
}

