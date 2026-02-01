// Function: _VoiceEnvelopeCheck__Fv
// Entry: 801c3db4
// Size: 68 bytes

void _VoiceEnvelopeCheck__Fv(void)

{
  uint uVar1;
  
  uVar1 = DAT_8032f444;
  do {
    if ((*(byte *)(uVar1 + 0x1a) & 7) != 0) {
      *(undefined4 *)(uVar1 + 0xb0) = 0x8000;
    }
    uVar1 = uVar1 + 0xc0;
  } while (uVar1 < DAT_8032f444 + 0x3000);
  return;
}

