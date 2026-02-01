// Function: TRKResetBuffer
// Entry: 801a9b30
// Size: 64 bytes

void TRKResetBuffer(int param_1,int param_2)

{
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  if (param_2 == 0) {
    TRK_memset(param_1 + 0x10,0,0x880);
  }
  return;
}

