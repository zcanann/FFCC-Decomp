// Function: TRKWriteUARTN
// Entry: 801ae248
// Size: 60 bytes

int TRKWriteUARTN(void)

{
  uint uVar1;
  
  uVar1 = (*DAT_8021d04c)();
  return (int)(-uVar1 | uVar1) >> 0x1f;
}

