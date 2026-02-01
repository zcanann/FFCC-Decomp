// Function: GXSetDispCopyFrame2Field
// Entry: 801a2ba4
// Size: 40 bytes

void GXSetDispCopyFrame2Field(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(uint *)(DAT_80333828 + 0x1ec) = *(uint *)(DAT_80333828 + 0x1ec) & 0xffffcfff | param_1 << 0xc;
  *(uint *)(iVar1 + 0x1fc) = *(uint *)(iVar1 + 0x1fc) & 0xffffcfff;
  return;
}

