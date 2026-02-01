// Function: DVDLowReset
// Entry: 801881a4
// Size: 188 bytes

void DVDLowReset(void)

{
  uint uVar1;
  uint uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  
  DAT_cc006004 = 2;
  uVar2 = DAT_cc003024;
  DAT_cc003024 = uVar2 & 0xfffffffb | 1;
  uVar3 = __OSGetSystemTime();
  uVar1 = DAT_800000f8 / 500000;
  do {
    uVar4 = __OSGetSystemTime();
  } while (((int)((ulonglong)uVar4 >> 0x20) -
            ((uint)((uint)uVar4 < (uint)uVar3) + (int)((ulonglong)uVar3 >> 0x20)) ^ 0x80000000) <
           ((uint)uVar4 - (uint)uVar3 < uVar1 * 0xc >> 3) + 0x80000000);
  DAT_cc003024 = uVar2 | 5;
  DAT_8032f030 = 1;
  uVar3 = __OSGetSystemTime();
  DAT_8032f02c = (int)uVar3;
  DAT_8032f028 = (int)((ulonglong)uVar3 >> 0x20);
  return;
}

