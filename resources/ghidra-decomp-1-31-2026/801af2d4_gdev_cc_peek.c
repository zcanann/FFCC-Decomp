// Function: gdev_cc_peek
// Entry: 801af2d4
// Size: 112 bytes

int gdev_cc_peek(void)

{
  int iVar1;
  int iVar2;
  undefined auStack_508 [1284];
  
  iVar1 = DBQueryData();
  if (iVar1 < 1) {
    iVar1 = 0;
  }
  else {
    iVar2 = DBRead(auStack_508,iVar1);
    if (iVar2 == 0) {
      CircleBufferWriteBytes(&DAT_8032b3e0,auStack_508,iVar1);
    }
    else {
      iVar1 = -0x2719;
    }
  }
  return iVar1;
}

