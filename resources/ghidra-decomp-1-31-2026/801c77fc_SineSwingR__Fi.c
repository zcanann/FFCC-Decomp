// Function: SineSwingR__Fi
// Entry: 801c77fc
// Size: 64 bytes

int SineSwingR__Fi(uint param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(&DAT_8021e1d0 + ((param_1 ^ 0x200) & 0x1ff) * 4);
  if (((param_1 ^ 0x200) & 0x200) != 0) {
    iVar1 = -iVar1;
  }
  return iVar1;
}

