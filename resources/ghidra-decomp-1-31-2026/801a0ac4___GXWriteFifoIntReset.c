// Function: __GXWriteFifoIntReset
// Entry: 801a0ac4
// Size: 60 bytes

void __GXWriteFifoIntReset(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x10) = *(uint *)(DAT_80333828 + 0x10) & 0xfffffffe | param_1 & 0xff;
  *(uint *)(iVar1 + 0x10) = *(uint *)(iVar1 + 0x10) & 0xfffffffd | (param_2 & 0xff) << 1;
  *(short *)(DAT_8032f2ec + 4) = (short)*(undefined4 *)(iVar1 + 0x10);
  return;
}

