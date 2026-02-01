// Function: PADTypeAndStatusCallback
// Entry: 8018d8dc
// Size: 812 bytes

void PADTypeAndStatusCallback(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined auStack_24 [20];
  
  iVar1 = DAT_8032eb1c;
  uVar5 = 0x80000000 >> DAT_8032eb1c;
  uVar2 = DAT_8032f144 & ~uVar5;
  uVar4 = DAT_8032f144 & uVar5;
  iVar3 = 1;
  DAT_8032f144 = uVar2;
  if ((param_2 & 0xf) != 0) {
    DAT_8032eb1c = countLeadingZeros(DAT_8032f140);
    if (DAT_8032eb1c == 0x20) {
      return;
    }
    DAT_8032f140 = DAT_8032f140 & ~(0x80000000U >> DAT_8032eb1c);
    memset(&DAT_8030cca0 + DAT_8032eb1c * 0xc,0,0xc);
    SIGetTypeAsync(DAT_8032eb1c,PADTypeAndStatusCallback);
    return;
  }
  *(uint *)(&DAT_8030cc90 + DAT_8032eb1c * 4) = param_2 & 0xffffff00;
  if (((param_2 & 0x18000000) != 0x8000000) || ((param_2 & 0x1000000) == 0)) {
    DAT_8032eb1c = countLeadingZeros(DAT_8032f140);
    if (DAT_8032eb1c == 0x20) {
      return;
    }
    DAT_8032f140 = DAT_8032f140 & ~(0x80000000U >> DAT_8032eb1c);
    memset(&DAT_8030cca0 + DAT_8032eb1c * 0xc,0,0xc);
    SIGetTypeAsync(DAT_8032eb1c,PADTypeAndStatusCallback);
    return;
  }
  if (1 < DAT_8032eb28) {
    if (((param_2 & 0x80000000) == 0) || ((param_2 & 0x4000000) != 0)) {
      if (uVar4 == 0) {
        iVar3 = SITransfer(iVar1,&DAT_8032eb30,1,&DAT_8030cca0 + iVar1 * 0xc,10,PADOriginCallback,0,
                           0);
      }
      else {
        iVar3 = SITransfer(iVar1,&DAT_8032eb34,3,&DAT_8030cca0 + iVar1 * 0xc,10,PADOriginCallback,0,
                           0);
      }
    }
    else if ((((param_2 & 0x100000) != 0) && ((param_2 & 0x80000) == 0)) &&
            ((param_2 & 0x40000) == 0)) {
      if ((param_2 & 0x40000000) == 0) {
        iVar3 = SITransfer(iVar1,&DAT_8030ccd0 + iVar1,3,&DAT_8030cca0 + iVar1 * 0xc,8,
                           PADProbeCallback,0,0);
      }
      else {
        iVar3 = SITransfer(iVar1,&DAT_8032eb30,1,&DAT_8030cca0 + iVar1 * 0xc,10,PADOriginCallback,0,
                           0);
      }
    }
    if (iVar3 == 0) {
      DAT_8032eb1c = countLeadingZeros(DAT_8032f140);
      DAT_8032f150 = DAT_8032f150 | uVar5;
      if (DAT_8032eb1c != 0x20) {
        DAT_8032f140 = DAT_8032f140 & ~(0x80000000U >> DAT_8032eb1c);
        memset(&DAT_8030cca0 + DAT_8032eb1c * 0xc,0,0xc);
        SIGetTypeAsync(DAT_8032eb1c,PADTypeAndStatusCallback);
      }
    }
    return;
  }
  DAT_8032f13c = DAT_8032f13c | uVar5;
  SIGetResponse(iVar1,auStack_24);
  SISetCommand(iVar1,DAT_8032eb24 | 0x400000);
  SIEnablePolling(DAT_8032f13c);
  DAT_8032eb1c = countLeadingZeros(DAT_8032f140);
  if (DAT_8032eb1c == 0x20) {
    return;
  }
  DAT_8032f140 = DAT_8032f140 & ~(0x80000000U >> DAT_8032eb1c);
  memset(&DAT_8030cca0 + DAT_8032eb1c * 0xc,0,0xc);
  SIGetTypeAsync(DAT_8032eb1c,PADTypeAndStatusCallback);
  return;
}

