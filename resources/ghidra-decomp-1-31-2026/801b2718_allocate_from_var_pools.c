// Function: allocate_from_var_pools
// Entry: 801b2718
// Size: 220 bytes

int allocate_from_var_pools(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = param_2 + 0xfU & 0xfffffff8;
  if (uVar3 < 0x50) {
    uVar3 = 0x50;
  }
  iVar1 = *param_1;
  if (iVar1 == 0) {
    iVar1 = link_new_block(param_1,uVar3);
  }
  if (iVar1 == 0) {
    iVar2 = 0;
  }
  else {
    do {
      if ((uVar3 <= *(uint *)(iVar1 + 8)) && (iVar2 = Block_subBlock(iVar1,uVar3), iVar2 != 0)) {
        *param_1 = iVar1;
        goto LAB_801b27d4;
      }
      iVar1 = *(int *)(iVar1 + 4);
    } while (iVar1 != *param_1);
    iVar1 = link_new_block(param_1,uVar3);
    if (iVar1 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = Block_subBlock(iVar1,uVar3);
LAB_801b27d4:
      iVar2 = iVar2 + 8;
    }
  }
  return iVar2;
}

