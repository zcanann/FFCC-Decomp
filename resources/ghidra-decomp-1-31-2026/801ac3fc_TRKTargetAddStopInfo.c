// Function: TRKTargetAddStopInfo
// Entry: 801ac3fc
// Size: 140 bytes

void TRKTargetAddStopInfo(undefined4 param_1)

{
  undefined4 local_58;
  undefined4 local_54;
  undefined local_50;
  undefined4 local_4c;
  undefined4 local_48;
  uint local_44;
  
  memset(&local_54,0,0x40);
  local_54 = 0x40;
  local_50 = 0x90;
  local_4c = DAT_8032a248;
  TRKTargetReadInstruction(&local_58);
  local_48 = local_58;
  local_44 = DAT_8032a4c0 & 0xffff;
  TRKAppendBuffer_ui8(param_1,&local_54,0x40);
  return;
}

