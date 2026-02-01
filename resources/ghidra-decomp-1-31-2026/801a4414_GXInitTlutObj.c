// Function: GXInitTlutObj
// Entry: 801a4414
// Size: 72 bytes

void GXInitTlutObj(uint *param_1,uint param_2,int param_3,undefined2 param_4)

{
  *param_1 = 0;
  *param_1 = *param_1 & 0xfffff3ff | param_3 << 10;
  param_1[1] = param_1[1] & 0xffe00000 | param_2 >> 5 & 0x1ffffff;
  param_1[1] = param_1[1] & 0xffffff | 0x64000000;
  *(undefined2 *)(param_1 + 2) = param_4;
  return;
}

