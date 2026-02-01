// Function: MEMIntrruptHandler
// Entry: 8017ee10
// Size: 108 bytes

void MEMIntrruptHandler(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  ushort uVar2;
  ushort uVar3;
  
  uVar3 = DAT_cc004024;
  uVar2 = DAT_cc004022;
  uVar1 = DAT_cc00401e;
  DAT_cc004020 = 0;
  if (__OSErrorTable._60_4_ == 0) {
    __OSUnhandledException(0xf,param_2,uVar1,(uVar3 & 0x3ff) << 0x10 | (uint)uVar2);
  }
  else {
    (*(code *)__OSErrorTable._60_4_)(0xf);
  }
  return;
}

