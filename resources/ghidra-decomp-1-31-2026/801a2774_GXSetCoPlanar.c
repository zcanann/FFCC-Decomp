// Function: GXSetCoPlanar
// Entry: 801a2774
// Size: 60 bytes

void GXSetCoPlanar(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x204) =
       *(uint *)(DAT_80333828 + 0x204) & 0xfff7ffff | (param_1 & 0xff) << 0x13;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0xfe080000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x204);
  return;
}

