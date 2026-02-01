// Function: setbit32__FPUlUl
// Entry: 8002d9fc
// Size: 32 bytes

void setbit32__FPUlUl(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = param_2 >> 3 & 0x1ffffffc;
  *(uint *)(param_1 + uVar1) = *(uint *)(param_1 + uVar1) | 1 << (param_2 & 0x1f);
  return;
}

