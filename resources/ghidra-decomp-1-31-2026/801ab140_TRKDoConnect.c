// Function: TRKDoConnect
// Entry: 801ab140
// Size: 100 bytes

undefined4 TRKDoConnect(void)

{
  undefined4 local_48;
  undefined local_44;
  undefined local_40;
  
  DAT_8032a118 = 1;
  memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = 0;
  TRKWriteUARTN(&local_48,0x40);
  return 0;
}

