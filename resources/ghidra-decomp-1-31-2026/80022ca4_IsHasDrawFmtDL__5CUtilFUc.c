// Function: IsHasDrawFmtDL__5CUtilFUc
// Entry: 80022ca4
// Size: 104 bytes

undefined4 IsHasDrawFmtDL__5CUtilFUc(CUtil *util,uint param_2)

{
  uint uVar1;
  
  uVar1 = param_2 & 0xf8;
  if (uVar1 != 0xa0) {
    if (uVar1 < 0xa0) {
      if (uVar1 != 0x90) {
        if (uVar1 < 0x90) {
          if (uVar1 != 0x80) {
            return 0;
          }
        }
        else if (uVar1 != 0x98) {
          return 0;
        }
      }
    }
    else if (uVar1 != 0xb0) {
      if (uVar1 < 0xb0) {
        if (uVar1 != 0xa8) {
          return 0;
        }
      }
      else if (uVar1 != 0xb8) {
        return 0;
      }
    }
  }
  return 1;
}

