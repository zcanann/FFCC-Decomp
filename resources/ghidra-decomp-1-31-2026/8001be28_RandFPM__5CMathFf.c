// Function: RandFPM__5CMathFf
// Entry: 8001be28
// Size: 112 bytes

/* WARNING: Removing unreachable block (ram,0x8001be80) */
/* WARNING: Removing unreachable block (ram,0x8001be38) */

double RandFPM__5CMathFf(double param_1)

{
  uint uVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_8032f740;
  if (dVar2 != param_1) {
    uVar1 = rand();
    dVar2 = (double)(float)(param_1 *
                           (double)(FLOAT_8032f78c *
                                    (float)((double)CONCAT44(0x43300000,uVar1 ^ 0x80000000) -
                                           DOUBLE_8032f750) + FLOAT_8032f744));
  }
  return dVar2;
}

