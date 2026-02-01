// Function: _VoiceDropedCallback__FPv
// Entry: 801c4fd4
// Size: 92 bytes

void _VoiceDropedCallback__FPv(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_8032f444;
  do {
    if ((puVar1[5] != 0) && (puVar1[5] == param_1)) {
      puVar1[0x23] = 0;
      *puVar1 = 0;
      puVar1[5] = 0;
    }
    puVar1 = puVar1 + 0x30;
  } while (puVar1 < DAT_8032f444 + 0xc00);
  return;
}

