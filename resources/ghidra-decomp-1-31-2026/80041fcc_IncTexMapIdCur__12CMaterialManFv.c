// Function: IncTexMapIdCur__12CMaterialManFv
// Entry: 80041fcc
// Size: 20 bytes

int IncTexMapIdCur__12CMaterialManFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x11c);
  *(int *)(param_1 + 0x11c) = iVar1 + 1;
  return iVar1;
}

