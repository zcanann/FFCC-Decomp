// Function: IncTexCoordIdCur__12CMaterialManFv
// Entry: 80041fa4
// Size: 20 bytes

int IncTexCoordIdCur__12CMaterialManFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x124);
  *(int *)(param_1 + 0x124) = iVar1 + 1;
  return iVar1;
}

