// Function: TRKDoOverride
// Entry: 801ab018
// Size: 88 bytes

undefined4 TRKDoOverride(void)

{
  undefined4 local_48;
  undefined local_44;
  undefined local_40;
  
  memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = 0;
  TRKWriteUARTN(&local_48,0x40);
  __TRK_copy_vectors();
  return 0;
}

