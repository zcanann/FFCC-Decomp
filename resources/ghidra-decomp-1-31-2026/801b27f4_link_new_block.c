// Function: link_new_block
// Entry: 801b27f4
// Size: 180 bytes

int * link_new_block(int *param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = param_2 + 0x1fU & 0xfffffff8;
  if (uVar2 < 0x10000) {
    uVar2 = 0x10000;
  }
  piVar1 = (int *)__sys_alloc(uVar2);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    Block_construct(piVar1,uVar2);
    if ((int *)*param_1 == (int *)0x0) {
      *param_1 = (int)piVar1;
      *piVar1 = (int)piVar1;
      piVar1[1] = (int)piVar1;
    }
    else {
      *piVar1 = *(int *)*param_1;
      *(int **)(*piVar1 + 4) = piVar1;
      piVar1[1] = *param_1;
      *(int **)*param_1 = piVar1;
      *param_1 = (int)piVar1;
    }
  }
  return piVar1;
}

