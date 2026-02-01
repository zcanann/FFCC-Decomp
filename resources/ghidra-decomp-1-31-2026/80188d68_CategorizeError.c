// Function: CategorizeError
// Entry: 80188d68
// Size: 180 bytes

undefined4 CategorizeError(uint param_1)

{
  if (param_1 == 0x20400) {
    DAT_8032f0b0 = param_1;
    return 1;
  }
  param_1 = param_1 & 0xffffff;
  if (((param_1 == 0x62800) || (param_1 == 0x23a00)) || (param_1 == 0xb5a01)) {
    return 0;
  }
  DAT_8032f0b4 = DAT_8032f0b4 + 1;
  if (DAT_8032f0b4 == 2) {
    if (param_1 == DAT_8032f0b0) {
      DAT_8032f0b0 = param_1;
      return 1;
    }
    DAT_8032f0b0 = param_1;
    return 2;
  }
  DAT_8032f0b0 = param_1;
  if ((param_1 != 0x31100) && (*(int *)(DAT_8032f080 + 8) != 5)) {
    return 3;
  }
  return 2;
}

