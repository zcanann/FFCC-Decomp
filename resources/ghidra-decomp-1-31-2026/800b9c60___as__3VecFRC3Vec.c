// Function: __as__3VecFRC3Vec
// Entry: 800b9c60
// Size: 28 bytes

void __as__3VecFRC3Vec(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = param_2[1];
  *param_1 = *param_2;
  uVar2 = param_2[2];
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return;
}

