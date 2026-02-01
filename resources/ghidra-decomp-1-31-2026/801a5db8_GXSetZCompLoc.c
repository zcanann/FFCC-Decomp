// Function: GXSetZCompLoc
// Entry: 801a5db8
// Size: 56 bytes

void GXSetZCompLoc(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x1dc) =
       *(uint *)(DAT_80333828 + 0x1dc) & 0xffffffbf | (param_1 & 0xff) << 6;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x1dc);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

