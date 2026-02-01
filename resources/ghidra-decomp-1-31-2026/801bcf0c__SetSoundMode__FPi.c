// Function: _SetSoundMode__FPi
// Entry: 801bcf0c
// Size: 124 bytes

void _SetSoundMode__FPi(int *param_1)

{
  DAT_8032f3c8 = *param_1;
  if (*param_1 == 1) {
    OSGetSoundMode(0);
  }
  else {
    OSGetSoundMode(1);
  }
  DAT_8032f400 = DAT_8032f3c8;
  if (DAT_8032f3c8 == 2) {
    AXSetMode(2);
  }
  else {
    AXSetMode(0);
  }
  return;
}

