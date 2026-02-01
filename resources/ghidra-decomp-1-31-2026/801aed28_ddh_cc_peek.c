// Function: ddh_cc_peek
// Entry: 801aed28
// Size: 112 bytes

int ddh_cc_peek(void)

{
  int iVar1;
  int iVar2;
  undefined auStack_808 [2052];
  
  iVar1 = EXI2_Poll();
  if (iVar1 < 1) {
    iVar1 = 0;
  }
  else {
    iVar2 = EXI2_ReadN(auStack_808,iVar1);
    if (iVar2 == 0) {
      CircleBufferWriteBytes(&DAT_8032aec0,auStack_808,iVar1);
    }
    else {
      iVar1 = -0x2719;
    }
  }
  return iVar1;
}

