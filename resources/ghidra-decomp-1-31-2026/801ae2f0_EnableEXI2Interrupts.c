// Function: EnableEXI2Interrupts
// Entry: 801ae2f0
// Size: 72 bytes

void EnableEXI2Interrupts(void)

{
  if ((DAT_8032a6b0 == '\0') && (DAT_8021d03c != (code *)0x0)) {
    (*DAT_8021d03c)();
  }
  return;
}

