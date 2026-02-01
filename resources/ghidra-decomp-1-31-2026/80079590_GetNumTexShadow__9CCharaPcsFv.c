// Function: GetNumTexShadow__9CCharaPcsFv
// Entry: 80079590
// Size: 60 bytes

int GetNumTexShadow__9CCharaPcsFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = *(int *)(*(int *)(param_1 + 0x4c) + 0x160);
  while( true ) {
    if (*(int *)(param_1 + 0x4c) == iVar2) break;
    if (((*(uint *)(iVar2 + 8) & 0x200) != 0) && (*(int *)(iVar2 + 0x120) != 0)) {
      iVar1 = iVar1 + 1;
    }
    iVar2 = *(int *)(iVar2 + 0x160);
  }
  return iVar1;
}

