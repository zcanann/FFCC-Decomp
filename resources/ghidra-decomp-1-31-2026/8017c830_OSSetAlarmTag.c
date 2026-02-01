// Function: OSSetAlarmTag
// Entry: 8017c830
// Size: 8 bytes

void OSSetAlarmTag(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  return;
}

