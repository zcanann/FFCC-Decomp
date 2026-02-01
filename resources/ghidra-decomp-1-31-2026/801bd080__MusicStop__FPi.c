// Function: _MusicStop__FPi
// Entry: 801bd080
// Size: 116 bytes

void _MusicStop__FPi(int *param_1)

{
  MusicStop__Fi(*param_1);
  if ((*param_1 == -1) || (*DAT_8032f428 == *param_1)) {
    *DAT_8032f428 = -1;
  }
  if (*DAT_8032f428 < 0) {
    DAT_8032f424 = 0;
  }
  return;
}

