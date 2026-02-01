// Function: __destroy_new_array
// Entry: 801af87c
// Size: 124 bytes

void __destroy_new_array(int param_1,code *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 != 0) {
    if (param_2 != (code *)0x0) {
      iVar2 = *(int *)(param_1 + -0x10);
      uVar3 = *(uint *)(param_1 + -0xc);
      iVar1 = param_1 + iVar2 * uVar3;
      for (uVar4 = 0; uVar4 < uVar3; uVar4 = uVar4 + 1) {
        iVar1 = iVar1 - iVar2;
        (*param_2)(iVar1,0xffffffff);
      }
    }
    __dla__FPv((void *)(param_1 + -0x10));
  }
  return;
}

