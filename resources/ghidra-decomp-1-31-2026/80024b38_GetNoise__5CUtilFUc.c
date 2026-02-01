// Function: GetNoise__5CUtilFUc
// Entry: 80024b38
// Size: 124 bytes

int GetNoise__5CUtilFUc(CUtil *util,uint param_2)

{
  double dVar1;
  
  dVar1 = (double)RandF__5CMathFv(&Math);
  return (int)((double)(float)((double)CONCAT44(0x43300000,(param_2 & 0xff) << 1 ^ 0x80000000) -
                              DOUBLE_8032f890) * dVar1 -
              (double)(float)((double)CONCAT44(0x43300000,(int)(param_2 & 0xff) >> 1 ^ 0x80000000) -
                             DOUBLE_8032f890));
}

