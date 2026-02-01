// Function: OutputData
// Entry: 801ab1c0
// Size: 168 bytes

void OutputData(undefined *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < param_2; iVar2 = iVar2 + 1) {
    MWTRACE(8,s__02x_801e6a44,*param_1);
    iVar1 = iVar2 >> 0x1f;
    if ((iVar1 * 0x10 | (uint)(iVar2 * 0x10000000 + iVar1) >> 0x1c) - iVar1 == 0xf) {
      MWTRACE(8,&DAT_801e6a4c);
    }
    param_1 = param_1 + 1;
  }
  MWTRACE(8,&DAT_801e6a4c);
  return;
}

