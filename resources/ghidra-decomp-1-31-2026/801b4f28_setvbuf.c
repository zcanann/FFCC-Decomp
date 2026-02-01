// Function: setvbuf
// Entry: 801b4f28
// Size: 356 bytes

undefined4 setvbuf(int param_1,int param_2,int param_3,int param_4)

{
  ushort uVar1;
  undefined4 uVar2;
  
  uVar1 = *(ushort *)(param_1 + 4);
  if (param_3 == 0) {
    fflush();
  }
  if ((*(byte *)(param_1 + 8) >> 5 == 0) && ((uVar1 >> 6 & 7) != 0)) {
    if (((param_3 == 0) || (param_3 == 1)) || (param_3 == 2)) {
      if ((*(int *)(param_1 + 0x1c) != 0) && ((*(byte *)(param_1 + 8) >> 4 & 1) != 0)) {
        free();
      }
      __begin_critical_region(2);
      *(byte *)(param_1 + 4) = (byte)(param_3 << 1) & 6 | *(byte *)(param_1 + 4) & 0xf9;
      *(byte *)(param_1 + 8) = *(byte *)(param_1 + 8) & 0xef;
      *(int *)(param_1 + 0x1c) = param_1 + 0xd;
      *(int *)(param_1 + 0x24) = param_1 + 0xd;
      *(undefined4 *)(param_1 + 0x20) = 1;
      *(undefined4 *)(param_1 + 0x28) = 0;
      *(undefined4 *)(param_1 + 0x2c) = 0;
      if ((param_3 == 0) || (param_4 == 0)) {
        **(undefined **)(param_1 + 0x24) = 0;
        __end_critical_region(2);
        uVar2 = 0;
      }
      else {
        if (param_2 == 0) {
          param_2 = malloc(param_4);
          if (param_2 == 0) {
            __end_critical_region(2);
            return 0xffffffff;
          }
          *(byte *)(param_1 + 8) = *(byte *)(param_1 + 8) & 0xef | 0x10;
        }
        *(int *)(param_1 + 0x1c) = param_2;
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x1c);
        *(int *)(param_1 + 0x20) = param_4;
        *(undefined4 *)(param_1 + 0x2c) = 0;
        __end_critical_region(2);
        uVar2 = 0;
      }
    }
    else {
      uVar2 = 0xffffffff;
    }
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

