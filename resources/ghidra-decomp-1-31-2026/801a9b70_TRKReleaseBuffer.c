// Function: TRKReleaseBuffer
// Entry: 801a9b70
// Size: 100 bytes

void TRKReleaseBuffer(int param_1)

{
  if (((param_1 != -1) && (-1 < param_1)) && (param_1 < 3)) {
    TRKAcquireMutex(&DAT_80328750 + param_1 * 0x890);
    (&DAT_80328754)[param_1 * 0x224] = 0;
    TRKReleaseMutex(&DAT_80328750 + param_1 * 0x890);
  }
  return;
}

