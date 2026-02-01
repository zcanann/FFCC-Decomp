// Function: IsInner__9CLine<64>FP3Vecf
// Entry: 800b9c84
// Size: 160 bytes

undefined4 IsInner__9CLine<64>FP3Vecf(double param_1,float *param_2,float *param_3)

{
  if (param_2[6] != 0.0) {
    if ((float)((double)*param_2 - param_1) <= *param_3) {
      if ((float)((double)param_2[1] - param_1) <= param_3[1]) {
        if (((((float)((double)param_2[2] - param_1) <= param_3[2]) &&
             (*param_3 <= (float)((double)param_2[3] + param_1))) &&
            (param_3[1] <= (float)((double)param_2[4] + param_1))) &&
           (param_3[2] <= (float)((double)param_2[5] + param_1))) {
          return 1;
        }
      }
    }
  }
  return 0;
}

