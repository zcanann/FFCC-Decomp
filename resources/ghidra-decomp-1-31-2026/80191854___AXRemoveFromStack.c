// Function: __AXRemoveFromStack
// Entry: 80191854
// Size: 148 bytes

void __AXRemoveFromStack(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = &DAT_8030cce0 + param_1[3];
  piVar2 = &DAT_8030cd60 + param_1[3];
  if ((int *)*piVar3 == (int *)*piVar2) {
    *piVar2 = 0;
    *piVar3 = 0;
    return;
  }
  if (param_1 == (int *)*piVar3) {
    *piVar3 = *param_1;
    *(undefined4 *)(*piVar3 + 4) = 0;
    return;
  }
  if (param_1 == (int *)*piVar2) {
    *piVar2 = param_1[1];
    *(undefined4 *)*piVar2 = 0;
    return;
  }
  piVar2 = (int *)param_1[1];
  iVar1 = *param_1;
  *piVar2 = iVar1;
  *(int **)(iVar1 + 4) = piVar2;
  return;
}

