// Function: PADSetSpec
// Entry: 8018e400
// Size: 96 bytes

void PADSetSpec(int param_1)

{
  DAT_8032f15c = 0;
  if (param_1 == 1) {
    DAT_8032eb2c = SPEC1_MakeStatus;
  }
  else if (param_1 < 1) {
    if (-1 < param_1) {
      DAT_8032eb2c = SPEC0_MakeStatus;
    }
  }
  else if (param_1 < 6) {
    DAT_8032eb2c = SPEC2_MakeStatus;
  }
  DAT_8032eb28 = param_1;
  return;
}

