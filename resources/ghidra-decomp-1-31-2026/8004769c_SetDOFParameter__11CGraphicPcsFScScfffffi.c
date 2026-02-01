// Function: SetDOFParameter__11CGraphicPcsFScScfffffi
// Entry: 8004769c
// Size: 36 bytes

void SetDOFParameter__11CGraphicPcsFScScfffffi
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               int param_6,undefined param_7,undefined param_8,undefined4 param_9)

{
  *(undefined *)(param_6 + 0xc4) = param_8;
  *(float *)(param_6 + 200) = (float)param_1;
  *(float *)(param_6 + 0xcc) = (float)param_2;
  *(undefined *)(param_6 + 0xe0) = param_7;
  *(undefined4 *)(param_6 + 0xd0) = param_9;
  *(float *)(param_6 + 0xd4) = (float)param_3;
  *(float *)(param_6 + 0xd8) = (float)param_4;
  *(float *)(param_6 + 0xdc) = (float)param_5;
  return;
}

