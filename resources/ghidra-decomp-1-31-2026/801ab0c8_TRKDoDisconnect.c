// Function: TRKDoDisconnect
// Entry: 801ab0c8
// Size: 120 bytes

undefined4 TRKDoDisconnect(void)

{
  undefined auStack_58 [12];
  undefined4 local_4c;
  undefined local_48;
  undefined local_44;
  
  DAT_8032a118 = 0;
  memset(&local_4c,0,0x40);
  local_48 = 0x80;
  local_4c = 0x40;
  local_44 = 0;
  TRKWriteUARTN(&local_4c,0x40);
  TRKConstructEvent(auStack_58,1);
  TRKPostEvent(auStack_58);
  return 0;
}

