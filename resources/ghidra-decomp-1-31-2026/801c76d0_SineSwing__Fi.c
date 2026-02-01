// Function: SineSwing__Fi
// Entry: 801c76d0
// Size: 60 bytes

int SineSwing__Fi(uint param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(&DAT_8021e1d0 + (param_1 & 0x1ff) * 4);
  if ((param_1 & 0x200) != 0) {
    iVar1 = -iVar1;
  }
  return iVar1;
}

