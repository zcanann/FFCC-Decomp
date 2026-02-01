// Function: Rand__5CMathFUl
// Entry: 8001bf9c
// Size: 68 bytes

int Rand__5CMathFUl(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    uVar2 = rand();
    iVar1 = uVar2 - (uVar2 / param_2) * param_2;
  }
  return iVar1;
}

