// Function: __pool_free
// Entry: 801b1ed8
// Size: 88 bytes

void __pool_free(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 != 0) {
    if ((*(uint *)(param_2 + -4) & 1) == 0) {
      uVar1 = *(uint *)(*(uint *)(param_2 + -4) + 8);
    }
    else {
      uVar1 = (*(uint *)(param_2 + -8) & 0xfffffff8) - 8;
    }
    if (uVar1 < 0x45) {
      deallocate_from_fixed_pools();
    }
    else {
      deallocate_from_var_pools();
    }
  }
  return;
}

