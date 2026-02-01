// Function: SetPos__8CMesMenuFff
// Entry: 8009b4e4
// Size: 12 bytes

void SetPos__8CMesMenuFff(double param_1,double param_2,int param_3)

{
  *(float *)(param_3 + 0x3d74) = (float)param_1;
  *(float *)(param_3 + 0x3d78) = (float)param_2;
  return;
}

