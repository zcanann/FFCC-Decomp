// Function: __DBExceptionDestinationAux
// Entry: 8017b5d0
// Size: 72 bytes

void __DBExceptionDestinationAux(void)

{
  int iVar1;
  
  iVar1 = iRam000000c0 + -0x80000000;
  OSReport(s_DBExceptionDestination_80216758);
  OSDumpContext(iVar1);
  PPCHalt();
  return;
}

