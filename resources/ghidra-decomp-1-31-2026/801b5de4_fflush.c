// Function: fflush
// Entry: 801b5de4
// Size: 312 bytes

undefined4 fflush(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1 == 0) {
    uVar1 = __flush_all();
  }
  else if ((*(char *)(param_1 + 10) == '\0') && ((*(ushort *)(param_1 + 4) >> 6 & 7) != 0)) {
    if ((*(byte *)(param_1 + 4) >> 3 & 7) == 1) {
      uVar1 = 0;
    }
    else {
      if (2 < *(byte *)(param_1 + 8) >> 5) {
        *(byte *)(param_1 + 8) = *(byte *)(param_1 + 8) & 0x1f | 0x40;
      }
      if (*(byte *)(param_1 + 8) >> 5 == 2) {
        *(undefined4 *)(param_1 + 0x28) = 0;
      }
      if (*(byte *)(param_1 + 8) >> 5 == 1) {
        if ((*(ushort *)(param_1 + 4) >> 6 & 7) == 1) {
          uVar3 = ftell(param_1);
        }
        else {
          uVar3 = 0;
        }
        iVar2 = __flush_buffer(param_1,0);
        if (iVar2 == 0) {
          uVar1 = 0;
          *(byte *)(param_1 + 8) = *(byte *)(param_1 + 8) & 0x1f;
          *(undefined4 *)(param_1 + 0x18) = uVar3;
          *(undefined4 *)(param_1 + 0x28) = 0;
        }
        else {
          *(undefined *)(param_1 + 10) = 1;
          uVar1 = 0xffffffff;
          *(undefined4 *)(param_1 + 0x28) = 0;
        }
      }
      else {
        uVar1 = 0;
        *(byte *)(param_1 + 8) = *(byte *)(param_1 + 8) & 0x1f;
      }
    }
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

