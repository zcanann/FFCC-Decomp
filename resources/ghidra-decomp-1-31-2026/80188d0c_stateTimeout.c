// Function: stateTimeout
// Entry: 80188d0c
// Size: 52 bytes

void stateTimeout(void)

{
  __DVDStoreErrorCode(0x1234568);
  DVDReset();
  cbForStateError(0);
  return;
}

