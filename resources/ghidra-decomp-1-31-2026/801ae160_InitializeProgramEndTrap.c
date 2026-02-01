// Function: InitializeProgramEndTrap
// Entry: 801ae160
// Size: 88 bytes

void InitializeProgramEndTrap(void)

{
  TRK_memcpy(0x8017b4d8,&DAT_801e6ba0,4);
  ICInvalidateRange(0x8017b4d8,4);
  DCFlushRange(0x8017b4d8,4);
  return;
}

