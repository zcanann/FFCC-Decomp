// Function: TRKTargetReadInstruction
// Entry: 801ad26c
// Size: 76 bytes

int TRKTargetReadInstruction(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int local_8 [2];
  
  local_8[0] = 4;
  iVar1 = TRKTargetAccessMemory(param_1,param_2,local_8,0,1);
  if ((iVar1 == 0) && (local_8[0] != 4)) {
    iVar1 = 0x700;
  }
  return iVar1;
}

