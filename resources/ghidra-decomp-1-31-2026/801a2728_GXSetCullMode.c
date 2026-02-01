// Function: GXSetCullMode
// Entry: 801a2728
// Size: 76 bytes

void GXSetCullMode(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  if (param_1 == 2) {
    param_1 = 1;
  }
  else if ((param_1 < 2) && (0 < param_1)) {
    param_1 = 2;
  }
  *(uint *)(DAT_80333828 + 0x204) = *(uint *)(DAT_80333828 + 0x204) & 0xffff3fff | param_1 << 0xe;
  *(uint *)(iVar1 + 0x4f4) = *(uint *)(iVar1 + 0x4f4) | 4;
  return;
}

