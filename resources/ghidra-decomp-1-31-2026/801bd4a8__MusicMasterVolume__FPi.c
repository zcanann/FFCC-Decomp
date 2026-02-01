// Function: _MusicMasterVolume__FPi
// Entry: 801bd4a8
// Size: 116 bytes

void _MusicMasterVolume__FPi(uint *param_1)

{
  uint uVar1;
  
  DAT_8032f430 = *param_1 & 0x7f;
  uVar1 = DAT_8032f444;
  if (DAT_8032f430 != 0) {
    DAT_8032f430 = (DAT_8032f430 + 1) * 4 - 1;
  }
  do {
    *(uint *)(uVar1 + 0xb8) = *(uint *)(uVar1 + 0xb8) | 2;
    uVar1 = uVar1 + 0xc0;
  } while (uVar1 < DAT_8032f444 + 0x3000);
  return;
}

