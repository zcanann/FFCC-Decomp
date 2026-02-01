// Function: deallocate_from_var_pools
// Entry: 801b23ac
// Size: 660 bytes

void deallocate_from_var_pools(undefined4 *param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  bool bVar7;
  uint uVar8;
  uint *puVar9;
  
  puVar9 = (uint *)(param_2 + -2);
  uVar8 = param_2[-2] & 0xfffffff8;
  *puVar9 = param_2[-2] & 0xfffffffd;
  puVar5 = (uint *)((int)puVar9 + uVar8);
  piVar1 = (int *)(param_2[-1] & 0xfffffffe);
  *puVar5 = *puVar5 & 0xfffffffb;
  puVar5[-1] = uVar8;
  iVar2 = (piVar1[3] & 0xfffffff8U) - 4;
  if (*(int *)((int)piVar1 + iVar2) == 0) {
    *(uint **)((int)piVar1 + iVar2) = puVar9;
    *param_2 = (int)puVar9;
    param_2[1] = (int)puVar9;
  }
  else {
    *param_2 = *(int *)(*(int *)((int)piVar1 + iVar2) + 8);
    *(uint **)(*param_2 + 0xc) = puVar9;
    param_2[1] = *(int *)((int)piVar1 + iVar2);
    *(uint **)(*(int *)((int)piVar1 + iVar2) + 8) = puVar9;
    *(uint **)((int)piVar1 + iVar2) = puVar9;
    puVar5 = *(uint **)((int)piVar1 + iVar2);
    if (((*puVar5 & 4) == 0) && (uVar8 = puVar5[-1], (uVar8 & 2) == 0)) {
      puVar9 = (uint *)((int)puVar5 - uVar8);
      *puVar9 = *puVar9 & 7;
      *puVar9 = *puVar9 | uVar8 + (*puVar5 & 0xfffffff8) & 0xfffffff8;
      if ((*puVar9 & 2) == 0) {
        iVar4 = uVar8 + (*puVar5 & 0xfffffff8);
        *(int *)((int)puVar9 + iVar4 + -4) = iVar4;
      }
      if (*(uint **)((int)piVar1 + iVar2) == puVar5) {
        *(uint *)((int)piVar1 + iVar2) = (*(uint **)((int)piVar1 + iVar2))[3];
      }
      *(uint *)(puVar5[3] + 8) = puVar5[2];
      *(uint *)(*(int *)(puVar5[3] + 8) + 0xc) = puVar5[3];
      puVar5 = puVar9;
    }
    *(uint **)((int)piVar1 + iVar2) = puVar5;
    puVar9 = *(uint **)((int)piVar1 + iVar2);
    uVar8 = *puVar9 & 0xfffffff8;
    puVar5 = (uint *)((int)puVar9 + uVar8);
    uVar6 = *puVar5;
    if ((uVar6 & 2) == 0) {
      *puVar9 = *puVar9 & 7;
      uVar8 = uVar8 + (uVar6 & 0xfffffff8);
      *puVar9 = *puVar9 | uVar8;
      if ((*puVar9 & 2) == 0) {
        *(uint *)((int)puVar9 + (uVar8 - 4)) = uVar8;
      }
      if ((*puVar9 & 2) == 0) {
        *(uint *)((int)puVar9 + uVar8) = *(uint *)((int)puVar9 + uVar8) & 0xfffffffb;
      }
      else {
        *(uint *)((int)puVar9 + uVar8) = *(uint *)((int)puVar9 + uVar8) | 4;
      }
      if (*(uint **)((int)piVar1 + iVar2) == puVar5) {
        *(uint *)((int)piVar1 + iVar2) = (*(uint **)((int)piVar1 + iVar2))[3];
      }
      if (*(uint **)((int)piVar1 + iVar2) == puVar5) {
        *(undefined4 *)((int)piVar1 + iVar2) = 0;
      }
      *(uint *)(puVar5[3] + 8) = puVar5[2];
      *(uint *)(puVar5[2] + 0xc) = puVar5[3];
    }
  }
  uVar8 = **(uint **)((int)piVar1 + iVar2) & 0xfffffff8;
  if ((uint)piVar1[2] < uVar8) {
    piVar1[2] = uVar8;
  }
  bVar7 = false;
  if (((piVar1[4] & 2U) == 0) && ((piVar1[4] & 0xfffffff8U) == (piVar1[3] & 0xfffffff8U) - 0x18)) {
    bVar7 = true;
  }
  if (bVar7) {
    piVar3 = (int *)piVar1[1];
    if (piVar3 == piVar1) {
      piVar3 = (int *)0x0;
    }
    if ((int *)*param_1 == piVar1) {
      *param_1 = piVar3;
    }
    if (piVar3 != (int *)0x0) {
      *piVar3 = *piVar1;
      *(int **)(*piVar3 + 4) = piVar3;
    }
    piVar1[1] = 0;
    *piVar1 = 0;
    __sys_free(piVar1);
  }
  return;
}

