// Function: deallocate_from_fixed_pools
// Entry: 801b1f84
// Size: 344 bytes

void deallocate_from_fixed_pools(int param_1,int *param_2,uint param_3)

{
  int *piVar1;
  int *piVar2;
  uint *puVar3;
  int iVar4;
  
  iVar4 = 0;
  for (puVar3 = &DAT_801e6fc0; *puVar3 < param_3; puVar3 = puVar3 + 1) {
    iVar4 = iVar4 + 1;
  }
  piVar1 = (int *)param_2[-1];
  piVar2 = (int *)(param_1 + iVar4 * 8 + 4);
  if (piVar1[3] == 0) {
    if ((int *)piVar2[1] != piVar1) {
      if ((int *)*piVar2 == piVar1) {
        piVar2[1] = *(int *)piVar2[1];
        *piVar2 = *(int *)*piVar2;
      }
      else {
        *(int *)(*piVar1 + 4) = piVar1[1];
        *(int *)piVar1[1] = *piVar1;
        piVar1[1] = piVar2[1];
        *piVar1 = *(int *)piVar1[1];
        *(int **)(*piVar1 + 4) = piVar1;
        *(int **)piVar1[1] = piVar1;
        piVar2[1] = (int)piVar1;
      }
    }
  }
  *param_2 = piVar1[3];
  piVar1[3] = (int)(param_2 + -1);
  iVar4 = piVar1[4];
  piVar1[4] = iVar4 + -1;
  if (iVar4 + -1 == 0) {
    if ((int *)piVar2[1] == piVar1) {
      piVar2[1] = piVar1[1];
    }
    if ((int *)*piVar2 == piVar1) {
      *piVar2 = *piVar1;
    }
    *(int *)(*piVar1 + 4) = piVar1[1];
    *(int *)piVar1[1] = *piVar1;
    if ((int *)piVar2[1] == piVar1) {
      piVar2[1] = 0;
    }
    if ((int *)*piVar2 == piVar1) {
      *piVar2 = 0;
    }
    deallocate_from_var_pools();
  }
  return;
}

