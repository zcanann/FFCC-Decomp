// Function: _MusicVolume__FPi
// Entry: 801bd51c
// Size: 92 bytes

void _MusicVolume__FPi(undefined4 *param_1)

{
  if (param_1[3] == 1) {
    *DAT_8032f428 = 0xffffffff;
    DAT_8032f424 = 0;
  }
  SetMusicVolume__Fiiii(*param_1,param_1[1],param_1[2],param_1[3]);
  return;
}

