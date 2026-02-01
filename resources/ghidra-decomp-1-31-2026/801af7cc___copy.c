// Function: __copy
// Entry: 801af7cc
// Size: 48 bytes

void __copy(undefined *param_1,undefined *param_2,int param_3)

{
  undefined uVar1;
  
  if (param_1 == (undefined *)0x0) {
    return;
  }
  if (param_3 != 0) {
    do {
      uVar1 = *param_2;
      param_3 = param_3 + -1;
      param_2 = param_2 + 1;
      *param_1 = uVar1;
      param_1 = param_1 + 1;
    } while (param_3 != 0);
    return;
  }
  return;
}

