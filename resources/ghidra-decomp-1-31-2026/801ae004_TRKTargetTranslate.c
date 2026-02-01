// Function: TRKTargetTranslate
// Entry: 801ae004
// Size: 88 bytes

uint TRKTargetTranslate(uint param_1)

{
  if (DAT_8032a6a0 <= param_1) {
    if ((param_1 < DAT_8032a6a0 + 0x4000) && ((DAT_8032a400 & 3) != 0)) {
      return param_1;
    }
  }
  if ((0x7dffffff < param_1) && (param_1 < 0x80000001)) {
    return param_1;
  }
  return param_1 & 0x3fffffff | 0x80000000;
}

