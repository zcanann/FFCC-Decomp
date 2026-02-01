// Function: SIGetTypeAsync
// Entry: 80185604
// Size: 312 bytes

undefined4 SIGetTypeAsync(int param_1,code *param_2)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = OSDisableInterrupts();
  uVar3 = SIGetType(param_1);
  if ((*(uint *)(&DAT_80217318 + param_1 * 4) & 0x80) == 0) {
    (*param_2)(param_1,uVar3);
  }
  else {
    param_1 = param_1 * 0x10;
    pcVar1 = *(code **)(&DAT_8030c8b0 + param_1);
    if (pcVar1 != param_2) {
      if (pcVar1 == (code *)0x0) {
        *(code **)(&DAT_8030c8b0 + param_1) = param_2;
      }
      else if (*(code **)(&DAT_8030c8b4 + param_1) != param_2) {
        if (*(code **)(&DAT_8030c8b4 + param_1) == (code *)0x0) {
          *(code **)(&DAT_8030c8b4 + param_1) = param_2;
        }
        else if (*(code **)(&DAT_8030c8b8 + param_1) != param_2) {
          if (*(code **)(&DAT_8030c8b8 + param_1) == (code *)0x0) {
            *(code **)(&DAT_8030c8b8 + param_1) = param_2;
          }
          else if ((*(code **)(&DAT_8030c8bc + param_1) != param_2) &&
                  (*(code **)(&DAT_8030c8bc + param_1) == (code *)0x0)) {
            *(code **)(&DAT_8030c8bc + param_1) = param_2;
          }
        }
      }
    }
  }
  OSRestoreInterrupts(uVar2);
  return uVar3;
}

