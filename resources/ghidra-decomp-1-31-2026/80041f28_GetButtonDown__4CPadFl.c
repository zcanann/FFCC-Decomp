// Function: GetButtonDown__4CPadFl
// Entry: 80041f28
// Size: 100 bytes

undefined2 GetButtonDown__4CPadFl(int param_1,uint param_2)

{
  bool bVar1;
  undefined2 uVar2;
  
  bVar1 = false;
  if (*(int *)(param_1 + 0x1c4) == 0) {
    if (param_2 != 0) goto LAB_80041f50;
    if (*(int *)(param_1 + 0x1c0) == -1) goto LAB_80041f50;
  }
  bVar1 = true;
LAB_80041f50:
  if (bVar1) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined2 *)
             (param_1 + (param_2 &
                        ~((int)~(*(int *)(param_1 + 0x1c0) - param_2 |
                                param_2 - *(int *)(param_1 + 0x1c0)) >> 0x1f)) * 0x54 + 8);
  }
  return uVar2;
}

