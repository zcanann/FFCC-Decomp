// Function: RandF__5CMathFv
// Entry: 8001beec
// Size: 68 bytes

double RandF__5CMathFv(void)

{
  uint uVar1;
  
  uVar1 = rand();
  return (double)(FLOAT_8032f790 *
                 (float)((double)CONCAT44(0x43300000,uVar1 ^ 0x80000000) - DOUBLE_8032f750));
}

