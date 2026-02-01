// Function: GXSetFieldMode
// Entry: 801a5f78
// Size: 124 bytes

void GXSetFieldMode(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x7c) =
       *(uint *)(DAT_80333828 + 0x7c) & 0xffbfffff | (param_2 & 0xff) << 0x16;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x7c);
  __GXFlushTextureState();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1 & 0xff | 0x68000000;
  __GXFlushTextureState();
  return;
}

