// Function: GXSetScissor
// Entry: 801a6838
// Size: 144 bytes

void GXSetScissor(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0xf8) = *(uint *)(DAT_80333828 + 0xf8) & 0xfffff800 | param_2 + 0x156U;
  *(uint *)(iVar1 + 0xf8) = *(uint *)(iVar1 + 0xf8) & 0xff800fff | (param_1 + 0x156) * 0x1000;
  *(uint *)(iVar1 + 0xfc) = *(uint *)(iVar1 + 0xfc) & 0xfffff800 | param_2 + 0x156U + param_4 + -1;
  *(uint *)(iVar1 + 0xfc) =
       *(uint *)(iVar1 + 0xfc) & 0xff800fff | (param_1 + 0x156 + param_3 + -1) * 0x1000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0xf8);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0xfc);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

