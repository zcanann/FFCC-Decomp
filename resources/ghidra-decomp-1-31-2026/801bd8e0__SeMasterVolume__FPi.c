// Function: _SeMasterVolume__FPi
// Entry: 801bd8e0
// Size: 116 bytes

void _SeMasterVolume__FPi(uint *param_1)

{
  uint uVar1;
  
  DAT_8032f434 = *param_1 & 0x7f;
  uVar1 = DAT_8032f444;
  if (DAT_8032f434 != 0) {
    DAT_8032f434 = (DAT_8032f434 + 1) * 4 - 1;
  }
  do {
    *(uint *)(uVar1 + 0xb8) = *(uint *)(uVar1 + 0xb8) | 2;
    uVar1 = uVar1 + 0xc0;
  } while (uVar1 < DAT_8032f444 + 0x3000);
  return;
}

