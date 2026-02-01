// Function: GXSetNumTexGens
// Entry: 801a1c40
// Size: 64 bytes

void GXSetNumTexGens(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x204) = *(uint *)(DAT_80333828 + 0x204) & 0xfffffff0 | param_1 & 0xff;
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x103f;
  DAT_cc008000 = param_1 & 0xff;
  *(uint *)(iVar1 + 0x4f4) = *(uint *)(iVar1 + 0x4f4) | 4;
  return;
}

