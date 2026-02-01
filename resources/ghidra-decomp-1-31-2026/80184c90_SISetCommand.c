// Function: SISetCommand
// Entry: 80184c90
// Size: 20 bytes

void SISetCommand(int param_1,undefined4 param_2)

{
  *(undefined4 *)(&DAT_cc006400 + param_1 * 0xc) = param_2;
  return;
}

