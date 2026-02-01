// Function: allocate_from_fixed_pools
// Entry: 801b20dc
// Size: 720 bytes

int allocate_from_fixed_pools(int *param_1,uint param_2)

{
  int *piVar1;
  int *piVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  uint uVar10;
  int *piVar11;
  uint uVar12;
  uint local_28 [4];
  
  iVar6 = 0;
  for (puVar3 = &DAT_801e6fc0; *puVar3 < param_2; puVar3 = puVar3 + 1) {
    iVar6 = iVar6 + 1;
  }
  piVar11 = param_1 + iVar6 * 2 + 1;
  if ((piVar11[1] == 0) || (*(int *)(piVar11[1] + 0xc) == 0)) {
    uVar10 = 0xfec / ((&DAT_801e6fc0)[iVar6] + 4);
    piVar2 = param_1;
    uVar5 = uVar10;
    if (0x100 < uVar10) {
      uVar10 = 0x100;
      uVar5 = uVar10;
    }
    while ((9 < uVar10 &&
           (piVar2 = (int *)soft_allocate_from_var_pools
                                      (param_1,uVar10 * ((&DAT_801e6fc0)[iVar6] + 4) + 0x14,local_28
                                      ), piVar2 == (int *)0x0))) {
      if (local_28[0] < 0x15) {
        uVar10 = 0;
      }
      else {
        uVar10 = (local_28[0] - 0x14) / ((&DAT_801e6fc0)[iVar6] + 4);
      }
    }
    if (((piVar2 == (int *)0x0) && (uVar10 < uVar5)) &&
       (piVar2 = (int *)allocate_from_var_pools(param_1,uVar5 * ((&DAT_801e6fc0)[iVar6] + 4) + 0x14)
       , piVar2 == (int *)0x0)) {
      return 0;
    }
    if ((piVar2[-1] & 1U) == 0) {
      iVar4 = *(int *)(piVar2[-1] + 8);
    }
    else {
      iVar4 = (piVar2[-2] & 0xfffffff8U) - 8;
    }
    if (piVar11[1] == 0) {
      piVar11[1] = (int)piVar2;
      *piVar11 = (int)piVar2;
    }
    iVar6 = (&DAT_801e6fc0)[iVar6];
    piVar9 = (int *)piVar11[1];
    piVar1 = piVar2 + 5;
    uVar7 = iVar6 + 4;
    iVar8 = *piVar11;
    uVar10 = (iVar4 - 0x14U) / uVar7;
    uVar5 = 0;
    *piVar2 = iVar8;
    piVar2[1] = (int)piVar9;
    *(int **)(iVar8 + 4) = piVar2;
    *piVar9 = (int)piVar2;
    piVar2[2] = iVar6;
    if (uVar10 != 1) {
      if ((8 < uVar10 - 1) && (uVar12 = uVar10 - 2 >> 3, uVar10 != 9)) {
        do {
          *piVar1 = (int)piVar2;
          piVar9 = (int *)((int)piVar1 + uVar7);
          uVar5 = uVar5 + 8;
          piVar1[1] = (int)piVar9;
          piVar1 = (int *)((int)piVar9 + uVar7);
          *piVar9 = (int)piVar2;
          piVar9[1] = (int)piVar1;
          piVar9 = (int *)((int)piVar1 + uVar7);
          *piVar1 = (int)piVar2;
          piVar1[1] = (int)piVar9;
          piVar1 = (int *)((int)piVar9 + uVar7);
          *piVar9 = (int)piVar2;
          piVar9[1] = (int)piVar1;
          piVar9 = (int *)((int)piVar1 + uVar7);
          *piVar1 = (int)piVar2;
          piVar1[1] = (int)piVar9;
          piVar1 = (int *)((int)piVar9 + uVar7);
          *piVar9 = (int)piVar2;
          piVar9[1] = (int)piVar1;
          piVar9 = (int *)((int)piVar1 + uVar7);
          *piVar1 = (int)piVar2;
          piVar1[1] = (int)piVar9;
          piVar1 = (int *)((int)piVar9 + uVar7);
          *piVar9 = (int)piVar2;
          piVar9[1] = (int)piVar1;
          uVar12 = uVar12 - 1;
        } while (uVar12 != 0);
      }
      iVar6 = (uVar10 - 1) - uVar5;
      piVar9 = piVar1;
      if (uVar5 < uVar10 - 1) {
        do {
          *piVar9 = (int)piVar2;
          piVar1 = (int *)((int)piVar9 + uVar7);
          piVar9[1] = (int)piVar1;
          iVar6 = iVar6 + -1;
          piVar9 = piVar1;
        } while (iVar6 != 0);
      }
    }
    *piVar1 = (int)piVar2;
    piVar1[1] = 0;
    piVar2[3] = (int)(piVar2 + 5);
    piVar2[4] = 0;
    piVar11[1] = (int)piVar2;
  }
  iVar6 = *(int *)(piVar11[1] + 0xc);
  *(undefined4 *)(piVar11[1] + 0xc) = *(undefined4 *)(iVar6 + 4);
  *(int *)(piVar11[1] + 0x10) = *(int *)(piVar11[1] + 0x10) + 1;
  if (*(int *)(piVar11[1] + 0xc) == 0) {
    piVar11[1] = *(int *)(piVar11[1] + 4);
    *piVar11 = *(int *)(*piVar11 + 4);
  }
  return iVar6 + 4;
}

