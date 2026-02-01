// Function: GXSetPointSize
// Entry: 801a2684
// Size: 72 bytes

void GXSetPointSize(uint param_1,int param_2)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x7c) =
       (param_1 & 0xff) << 8 | *(uint *)(DAT_80333828 + 0x7c) & 0xffff00ff;
  *(uint *)(iVar1 + 0x7c) = *(uint *)(iVar1 + 0x7c) & 0xffc7ffff | param_2 << 0x13;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x7c);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

