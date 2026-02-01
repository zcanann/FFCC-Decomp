// Function: SetReverb__10CRedDriverFii
// Entry: 801bfdf8
// Size: 92 bytes

void SetReverb__10CRedDriverFii(undefined4 param_1,undefined4 param_2,int param_3)

{
  SetReverb__FiiPi(param_2,*(undefined4 *)(&DAT_8021ec10 + param_3 * 0x1c),
                   param_3 * 0x1c + -0x7fde13ec);
  return;
}

