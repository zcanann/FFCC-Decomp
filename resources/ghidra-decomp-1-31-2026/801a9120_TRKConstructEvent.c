// Function: TRKConstructEvent
// Entry: 801a9120
// Size: 24 bytes

void TRKConstructEvent(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0xffffffff;
  return;
}

