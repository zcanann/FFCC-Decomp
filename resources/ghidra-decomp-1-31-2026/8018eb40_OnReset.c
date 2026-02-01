// Function: OnReset
// Entry: 8018eb40
// Size: 404 bytes

int OnReset(int param_1)

{
  bool bVar4;
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar5;
  uint uVar6;
  
  if (DAT_8032f154 != 0) {
    PADSetSamplingCallback(0);
  }
  if (param_1 == 0) {
    iVar5 = 0;
    bVar4 = false;
    if ((DAT_8032f140 == 0) && (DAT_8032eb1c == 0x20)) {
      bVar4 = true;
    }
    if ((bVar4) && (iVar1 = SIBusy(), iVar1 == 0)) {
      iVar5 = 1;
    }
    if ((DAT_8032f158 == 0) && (iVar5 != 0)) {
      uVar2 = OSDisableInterrupts();
      uVar6 = (DAT_8032f150 | 0xf0000000) & ~(DAT_8032f148 | DAT_8032f14c);
      DAT_8032f140 = DAT_8032f140 | uVar6;
      DAT_8032f150 = 0;
      uVar3 = DAT_8032f140 & DAT_8032f13c;
      if ((DAT_800030e3 & 0x40) == 0) {
        DAT_8032f144 = DAT_8032f144 | uVar6;
      }
      DAT_8032f13c = DAT_8032f13c & ~uVar6;
      SIDisablePolling(uVar3);
      if ((DAT_8032eb1c == 0x20) &&
         (DAT_8032eb1c = countLeadingZeros(DAT_8032f140), DAT_8032eb1c != 0x20)) {
        DAT_8032f140 = DAT_8032f140 & ~(0x80000000U >> DAT_8032eb1c);
        memset(&DAT_8030cca0 + DAT_8032eb1c * 0xc,0,0xc);
        SIGetTypeAsync(DAT_8032eb1c,PADTypeAndStatusCallback);
      }
      OSRestoreInterrupts(uVar2);
      DAT_8032f158 = 1;
      iVar5 = 0;
    }
  }
  else {
    DAT_8032f158 = 0;
    iVar5 = 1;
  }
  return iVar5;
}

