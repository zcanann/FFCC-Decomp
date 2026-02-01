// Function: __OSEnableBarnacle
// Entry: 80183c18
// Size: 444 bytes

void __OSEnableBarnacle(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *local_10 [2];
  
  iVar1 = EXIGetID(param_1,param_2,local_10);
  if ((iVar1 != 0) && (local_10[0] != (undefined4 *)0x1020000)) {
    if ((int)local_10[0] < 0x1020000) {
      if (local_10[0] == (undefined4 *)0x4) {
        return;
      }
      if ((int)local_10[0] < 4) {
        if (local_10[0] == (undefined4 *)0x80000010) {
          return;
        }
        if ((int)local_10[0] < -0x7ffffff0) {
          if (local_10[0] == (undefined4 *)0x80000008) {
            return;
          }
          if (((int)local_10[0] < -0x7ffffff8) && (local_10[0] == (undefined4 *)0x80000004)) {
            return;
          }
        }
        else {
          if (local_10[0] == (undefined4 *)0xffffffff) {
            return;
          }
          if (((int)local_10[0] < -1) && (local_10[0] == &DAT_80000020)) {
            return;
          }
        }
      }
      else {
        if (local_10[0] == (undefined4 *)0x20) {
          return;
        }
        if ((int)local_10[0] < 0x20) {
          if (local_10[0] == (undefined4 *)0x10) {
            return;
          }
          if (((int)local_10[0] < 0x10) && (local_10[0] == (undefined4 *)0x8)) {
            return;
          }
        }
        else if (local_10[0] == (undefined4 *)0x1010000) {
          return;
        }
      }
    }
    else {
      if (local_10[0] == (undefined4 *)0x4040404) {
        return;
      }
      if ((int)local_10[0] < 0x4040404) {
        if (local_10[0] == (undefined4 *)0x4020100) {
          return;
        }
        if ((int)local_10[0] < 0x4020100) {
          if (local_10[0] == (undefined4 *)0x3010000) {
            return;
          }
          if (((int)local_10[0] < 0x3010000) && (local_10[0] == (undefined4 *)0x2020000)) {
            return;
          }
        }
        else {
          if (local_10[0] == (undefined4 *)0x4020300) {
            return;
          }
          if (((int)local_10[0] < 0x4020300) && (local_10[0] == (undefined4 *)0x4020200)) {
            return;
          }
        }
      }
      else {
        if (local_10[0] == (undefined4 *)0x4130000) {
          return;
        }
        if ((int)local_10[0] < 0x4130000) {
          if (local_10[0] == (undefined4 *)0x4120000) {
            return;
          }
          if (((int)local_10[0] < 0x4120000) && (local_10[0] == (undefined4 *)0x4060000)) {
            return;
          }
        }
        else if (local_10[0] == (undefined4 *)0x4220000) {
          return;
        }
      }
    }
    iVar1 = ProbeBarnacle(param_1,param_2,local_10);
    if (iVar1 != 0) {
      DAT_8032effc = 0xa5ff005a;
      DAT_8032eff8 = 0xa5ff005a;
      DAT_8032eff0 = param_1;
      DAT_8032eff4 = param_2;
    }
  }
  return;
}

