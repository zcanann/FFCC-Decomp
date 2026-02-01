// Function: TRKDoReset
// Entry: 801ab070
// Size: 88 bytes

undefined4 TRKDoReset(void)

{
  undefined4 local_48;
  undefined local_44;
  undefined local_40;
  
  memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = 0;
  TRKWriteUARTN(&local_48,0x40);
  __TRK_reset();
  return 0;
}

