// Function: __cvt_fp2unsigned
// Entry: 801aff44
// Size: 92 bytes

int __cvt_fp2unsigned(double param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = 0;
  if ((DAT_801e6e98 <= param_1) && (iVar1 = -1, param_1 < DAT_801e6ea0)) {
    bVar2 = DAT_801e6ea8 <= param_1;
    if (bVar2) {
      param_1 = param_1 - DAT_801e6ea8;
    }
    iVar1 = (int)param_1;
    if (bVar2) {
      iVar1 = iVar1 + -0x80000000;
    }
  }
  return iVar1;
}

