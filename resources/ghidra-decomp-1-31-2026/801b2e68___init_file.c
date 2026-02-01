// Function: __init_file
// Entry: 801b2e68
// Size: 220 bytes

void __init_file(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  
  uVar1 = *param_2;
  *param_1 = 0;
  param_1[1] = uVar1;
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f;
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xef;
  *(undefined *)((int)param_1 + 9) = 0;
  *(undefined *)((int)param_1 + 10) = 0;
  param_1[6] = 0;
  if (param_4 == 0) {
    setvbuf(param_1,0,0,0);
  }
  else {
    setvbuf(param_1,param_3,2);
  }
  param_1[9] = param_1[7];
  param_1[10] = 0;
  if ((*(ushort *)(param_1 + 1) >> 6 & 7) == 1) {
    param_1[0xe] = __position_file;
    param_1[0xf] = __read_file;
    param_1[0x10] = __write_file;
    param_1[0x11] = __close_file;
  }
  param_1[0x12] = 0;
  return;
}

