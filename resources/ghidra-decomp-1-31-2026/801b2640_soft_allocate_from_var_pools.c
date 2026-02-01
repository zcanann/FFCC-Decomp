// Function: soft_allocate_from_var_pools
// Entry: 801b2640
// Size: 216 bytes

int soft_allocate_from_var_pools(int *param_1,int param_2,uint *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = param_2 + 0xfU & 0xfffffff8;
  if (uVar3 < 0x50) {
    uVar3 = 0x50;
  }
  *param_3 = 0;
  iVar4 = *param_1;
  if (iVar4 != 0) {
    do {
      if ((uVar3 <= *(uint *)(iVar4 + 8)) && (iVar1 = Block_subBlock(iVar4,uVar3), iVar1 != 0)) {
        *param_1 = iVar4;
        return iVar1 + 8;
      }
      if ((8 < *(uint *)(iVar4 + 8)) && (uVar2 = *(uint *)(iVar4 + 8) - 8, *param_3 < uVar2)) {
        *param_3 = uVar2;
      }
      iVar4 = *(int *)(iVar4 + 4);
    } while (iVar4 != *param_1);
  }
  return 0;
}

