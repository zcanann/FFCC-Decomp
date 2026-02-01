// Function: raise
// Entry: 801b8b30
// Size: 192 bytes

undefined4 raise(int param_1)

{
  undefined4 uVar1;
  code *pcVar2;
  
  if ((param_1 < 1) || (6 < param_1)) {
    uVar1 = 0xffffffff;
  }
  else {
    __begin_critical_region(4);
    pcVar2 = *(code **)(&DAT_8032b844 + param_1 * 4);
    if (pcVar2 != (code *)0x1) {
      *(undefined4 *)(&DAT_8032b844 + param_1 * 4) = 0;
    }
    __end_critical_region(4);
    if ((pcVar2 == (code *)0x1) || ((pcVar2 == (code *)0x0 && (param_1 == 1)))) {
      uVar1 = 0;
    }
    else {
      if (pcVar2 == (code *)0x0) {
        exit(0);
      }
      (*pcVar2)(param_1);
      uVar1 = 0;
    }
  }
  return uVar1;
}

