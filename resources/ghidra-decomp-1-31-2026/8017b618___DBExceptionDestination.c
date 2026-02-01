// Function: __DBExceptionDestination
// Entry: 8017b618
// Size: 16 bytes

void __DBExceptionDestination(void)

{
  uint in_MSR;
  
  __DBExceptionDestinationAux(in_MSR | 0x30);
  return;
}

