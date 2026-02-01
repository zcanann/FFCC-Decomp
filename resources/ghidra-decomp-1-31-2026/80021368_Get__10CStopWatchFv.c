// Function: Get__10CStopWatchFv
// Entry: 80021368
// Size: 120 bytes

double Get__10CStopWatchFv(int param_1)

{
  double dVar1;
  
  dVar1 = (double)__cvt_sll_flt(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  return (double)(FLOAT_8032f850 *
                 (float)(dVar1 / (double)(float)((double)CONCAT44(0x43300000,
                                                                  (DAT_800000f8 / 500000) * 0x8235
                                                                  >> 3) - DOUBLE_8032f858)));
}

