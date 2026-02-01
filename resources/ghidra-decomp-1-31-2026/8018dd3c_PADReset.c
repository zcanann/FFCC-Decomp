// Function: PADReset
// Entry: 8018dd3c
// Size: 256 bytes

undefined4 PADReset(uint param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = OSDisableInterrupts();
  uVar3 = (param_1 | DAT_8032f150) & ~(DAT_8032f148 | DAT_8032f14c);
  DAT_8032f140 = DAT_8032f140 | uVar3;
  DAT_8032f150 = 0;
  uVar2 = DAT_8032f140 & DAT_8032f13c;
  if (DAT_8032eb28 == 4) {
    DAT_8032f144 = DAT_8032f144 | uVar3;
  }
  DAT_8032f13c = DAT_8032f13c & ~uVar3;
  SIDisablePolling(uVar2);
  if (DAT_8032eb1c == 0x20) {
    DAT_8032eb1c = countLeadingZeros(DAT_8032f140);
    if (DAT_8032eb1c != 0x20) {
      DAT_8032f140 = DAT_8032f140 & ~(0x80000000U >> DAT_8032eb1c);
      memset(&DAT_8030cca0 + DAT_8032eb1c * 0xc,0,0xc);
      SIGetTypeAsync(DAT_8032eb1c,PADTypeAndStatusCallback);
    }
  }
  OSRestoreInterrupts(uVar1);
  return 1;
}

