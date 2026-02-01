// Function: __CARDVerify
// Entry: 8019bd28
// Size: 140 bytes

int __CARDVerify(CARDControl *cardControl)

{
  int iVar1;
  int iVar2;
  
  iVar1 = VerifyID();
  if (-1 < iVar1) {
    iVar1 = VerifyDir(cardControl,0);
    iVar2 = VerifyFAT(cardControl,0);
    iVar1 = iVar1 + iVar2;
    if (iVar1 == 1) {
      iVar1 = -6;
    }
    else if ((iVar1 < 1) && (-1 < iVar1)) {
      iVar1 = 0;
    }
    else {
      iVar1 = -6;
    }
  }
  return iVar1;
}

