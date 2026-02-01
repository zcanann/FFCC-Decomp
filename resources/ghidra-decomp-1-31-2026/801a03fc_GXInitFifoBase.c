// Function: GXInitFifoBase
// Entry: 801a03fc
// Size: 108 bytes

void GXInitFifoBase(int *param_1,int param_2,uint param_3)

{
  *param_1 = param_2;
  param_1[1] = param_2 + (param_3 - 4);
  param_1[2] = param_3;
  param_1[7] = 0;
  GXInitFifoLimits(param_1,param_3 - 0x4000,param_3 >> 1 & 0x7fffffe0);
  GXInitFifoPtrs(param_1,param_2,param_2);
  return;
}

