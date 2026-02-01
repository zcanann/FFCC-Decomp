// Function: SIBusy
// Entry: 80184060
// Size: 32 bytes

undefined4 SIBusy(void)

{
  if (DAT_80217304 != -1) {
    return 1;
  }
  return 0;
}

