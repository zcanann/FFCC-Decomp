// Function: __pool_alloc
// Entry: 801b1f30
// Size: 84 bytes

undefined4 __pool_alloc(undefined4 param_1,uint param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else if (param_2 < 0xffffffd0) {
    if (param_2 < 0x45) {
      uVar1 = allocate_from_fixed_pools();
    }
    else {
      uVar1 = allocate_from_var_pools();
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

