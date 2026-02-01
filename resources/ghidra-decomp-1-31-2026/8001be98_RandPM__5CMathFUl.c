// Function: RandPM__5CMathFUl
// Entry: 8001be98
// Size: 84 bytes

int RandPM__5CMathFUl(undefined4 param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = rand();
    uVar2 = iVar1 * 0xfffe - 0x7fff;
    iVar1 = uVar2 - (uVar2 / param_2) * param_2;
  }
  return iVar1;
}

