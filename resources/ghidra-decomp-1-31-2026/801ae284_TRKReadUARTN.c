// Function: TRKReadUARTN
// Entry: 801ae284
// Size: 60 bytes

int TRKReadUARTN(void)

{
  uint uVar1;
  
  uVar1 = (*DAT_8021d048)();
  return (int)(-uVar1 | uVar1) >> 0x1f;
}

