// Function: ProfEnd__8CProfileFv
// Entry: 800211d4
// Size: 200 bytes

void ProfEnd__8CProfileFv(int param_1)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)__cvt_sll_flt(*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  *(float *)(param_1 + 0x60) =
       FLOAT_8032f850 *
       (float)(dVar2 / (double)(float)((double)CONCAT44(0x43300000,
                                                        (DAT_800000f8 / 500000) * 0x8235 >> 3) -
                                      DOUBLE_8032f858));
  iVar1 = *(int *)(param_1 + 0x68) + 1;
  *(int *)(param_1 + 0x68) = iVar1;
  if (iVar1 == 0x5a) {
    *(float *)(param_1 + 100) = FLOAT_8032f854;
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  if (*(float *)(param_1 + 100) < *(float *)(param_1 + 0x60)) {
    *(float *)(param_1 + 100) = *(float *)(param_1 + 0x60);
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  return;
}

