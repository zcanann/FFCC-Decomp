// Function: pppCalcFrameShape__FPlRsRsRss
// Entry: 80065678
// Size: 100 bytes

void pppCalcFrameShape__FPlRsRsRss
               (int param_1,short *param_2,short *param_3,short *param_4,short param_5)

{
  short sVar1;
  
  sVar1 = *param_2;
  *param_3 = sVar1;
  *param_4 = *param_4 + param_5;
  sVar1 = *(short *)(param_1 + sVar1 * 8 + 0x12);
  if (*param_4 < sVar1) {
    return;
  }
  *param_4 = *param_4 - sVar1;
  *param_2 = *param_2 + 1;
  if (*param_2 < *(short *)(param_1 + 6)) {
    return;
  }
  *param_2 = 0;
  *param_4 = 0;
  return;
}

