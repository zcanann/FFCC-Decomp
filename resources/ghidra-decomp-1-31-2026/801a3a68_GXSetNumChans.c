// Function: GXSetNumChans
// Entry: 801a3a68
// Size: 68 bytes

void GXSetNumChans(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x204) =
       *(uint *)(DAT_80333828 + 0x204) & 0xffffff8f | (param_1 & 0xff) << 4;
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x1009;
  DAT_cc008000 = param_1 & 0xff;
  *(uint *)(iVar1 + 0x4f4) = *(uint *)(iVar1 + 0x4f4) | 4;
  return;
}

