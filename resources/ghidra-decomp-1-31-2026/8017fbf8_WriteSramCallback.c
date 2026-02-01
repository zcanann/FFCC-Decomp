// Function: WriteSramCallback
// Entry: 8017fbf8
// Size: 96 bytes

void WriteSramCallback(void)

{
  FatalContext[0x16] =
       WriteSram(FatalContext[0x13] + -0x7fcf43c0,FatalContext[0x13],0x40 - FatalContext[0x13]);
  if (FatalContext[0x16] != 0) {
    FatalContext[0x13] = 0x40;
  }
  return;
}

