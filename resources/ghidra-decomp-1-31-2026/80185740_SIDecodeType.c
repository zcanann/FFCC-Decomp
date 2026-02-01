// Function: SIDecodeType
// Entry: 80185740
// Size: 324 bytes

uint SIDecodeType(uint param_1)

{
  uint uVar1;
  
  if ((param_1 & 8) != 0) {
    return 8;
  }
  if ((param_1 & 0x47) != 0) {
    return 0x40;
  }
  if ((param_1 & 0xff) != 0) {
    return 0x80;
  }
  if ((param_1 & 0x18000000) != 0) {
    if ((param_1 & 0x18000000) != 0x8000000) {
      return 0x40;
    }
    uVar1 = param_1 & 0xffff0000;
    if (uVar1 == 0x9000000) {
      return uVar1;
    }
    if (((int)uVar1 < 0x9000000) && (uVar1 == 0x8000000)) {
      return uVar1;
    }
    if ((param_1 & 0xffe00000) == 0x8200000) {
      return 0x8200000;
    }
    if (((param_1 & 0x80000000) != 0) && ((param_1 & 0x4000000) == 0)) {
      if ((param_1 & 0x8b100000) == 0x8b100000) {
        return 0x8b100000;
      }
      if ((param_1 & 0x2000000) == 0) {
        return 0x88000000;
      }
    }
    if ((param_1 & 0x9000000) != 0x9000000) {
      return 0x40;
    }
    return 0x9000000;
  }
  param_1 = param_1 & 0xffff0000;
  if (param_1 == 0x40000) {
    return param_1;
  }
  if ((int)param_1 < 0x40000) {
    if (param_1 == 0x20000) {
      return param_1;
    }
    if (((int)param_1 < 0x20000) && (param_1 == 0x10000)) {
      return param_1;
    }
  }
  else {
    if (param_1 == 0x5000000) {
      return param_1;
    }
    if (((int)param_1 < 0x5000000) && (param_1 == 0x2000000)) {
      return param_1;
    }
  }
  return 0x40;
}

