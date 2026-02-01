// Function: TRKTargetAddExceptionInfo
// Entry: 801ac378
// Size: 132 bytes

void TRKTargetAddExceptionInfo(undefined4 param_1)

{
  undefined4 local_58;
  undefined4 local_54;
  undefined local_50;
  undefined4 local_4c;
  undefined4 local_48;
  uint local_44;
  
  memset(&local_54,0,0x40);
  local_54 = 0x40;
  local_50 = 0x91;
  local_4c = DAT_8021cfd4;
  TRKTargetReadInstruction(&local_58);
  local_44 = (uint)DAT_8021cfdc._0_2_;
  local_48 = local_58;
  TRKAppendBuffer_ui8(param_1,&local_54,0x40);
  return;
}

