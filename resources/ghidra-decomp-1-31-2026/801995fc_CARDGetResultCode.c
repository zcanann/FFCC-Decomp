// Function: CARDGetResultCode
// Entry: 801995fc
// Size: 48 bytes

undefined4 CARDGetResultCode(int param_1)

{
  if ((-1 < param_1) && (param_1 < 2)) {
    return (&DAT_80327544)[param_1 * 0x44];
  }
  return 0xffffff80;
}

