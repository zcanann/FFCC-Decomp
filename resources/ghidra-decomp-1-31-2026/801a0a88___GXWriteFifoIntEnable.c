// Function: __GXWriteFifoIntEnable
// Entry: 801a0a88
// Size: 60 bytes

void __GXWriteFifoIntEnable(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 8) = *(uint *)(DAT_80333828 + 8) & 0xfffffffb | (param_1 & 0xff) << 2;
  *(uint *)(iVar1 + 8) = *(uint *)(iVar1 + 8) & 0xfffffff7 | (param_2 & 0xff) << 3;
  *(short *)(DAT_8032f2ec + 2) = (short)*(undefined4 *)(iVar1 + 8);
  return;
}

