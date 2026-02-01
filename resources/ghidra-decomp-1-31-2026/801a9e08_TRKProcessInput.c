// Function: TRKProcessInput
// Entry: 801a9e08
// Size: 80 bytes

void TRKProcessInput(undefined4 param_1)

{
  undefined auStack_18 [8];
  undefined4 local_10;
  
  TRKConstructEvent(auStack_18,2);
  DAT_8032a100 = 0xffffffff;
  local_10 = param_1;
  TRKPostEvent(auStack_18);
  return;
}

