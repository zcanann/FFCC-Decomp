// Function: __DVDPrintFatalMessage
// Entry: 8018b5f4
// Size: 48 bytes

void __DVDPrintFatalMessage(void)

{
  if (DAT_8032f0c8 != (code *)0x0) {
    (*DAT_8032f0c8)();
  }
  return;
}

