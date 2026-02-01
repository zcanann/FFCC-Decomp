// Function: TRKGetInput
// Entry: 801a9e58
// Size: 96 bytes

void TRKGetInput(void)

{
  undefined auStack_18 [8];
  int local_10;
  
  local_10 = TRKTestForPacket();
  if (local_10 != -1) {
    TRKGetBuffer();
    TRKConstructEvent(auStack_18,2);
    DAT_8032a100 = 0xffffffff;
    TRKPostEvent(auStack_18);
  }
  return;
}

