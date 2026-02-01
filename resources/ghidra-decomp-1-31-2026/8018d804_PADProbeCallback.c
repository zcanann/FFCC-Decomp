// Function: PADProbeCallback
// Entry: 8018d804
// Size: 216 bytes

void PADProbeCallback(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined auStack_14 [12];
  
  iVar1 = DAT_8032eb1c;
  if ((param_2 & 0xf) == 0) {
    DAT_8032f13c = DAT_8032f13c | 0x80000000U >> DAT_8032eb1c;
    SIGetResponse(DAT_8032eb1c,auStack_14);
    SISetCommand(iVar1,DAT_8032eb24 | 0x400000);
    SIEnablePolling(DAT_8032f13c);
    DAT_8032f148 = DAT_8032f148 | 0x80000000U >> DAT_8032eb1c;
  }
  DAT_8032eb1c = countLeadingZeros(DAT_8032f140);
  if (DAT_8032eb1c != 0x20) {
    DAT_8032f140 = DAT_8032f140 & ~(0x80000000U >> DAT_8032eb1c);
    memset(&DAT_8030cca0 + DAT_8032eb1c * 0xc,0,0xc);
    SIGetTypeAsync(DAT_8032eb1c,PADTypeAndStatusCallback);
  }
  return;
}

