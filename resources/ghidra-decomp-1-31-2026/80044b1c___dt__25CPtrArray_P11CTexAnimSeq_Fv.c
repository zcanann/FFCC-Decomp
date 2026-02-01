// Function: __dt__25CPtrArray<P11CTexAnimSeq>Fv
// Entry: 80044b1c
// Size: 92 bytes

CPtrArray * __dt__25CPtrArray<P11CTexAnimSeq>Fv(CPtrArray *ptrArray,short param_2)

{
  if (ptrArray != (CPtrArray *)0x0) {
    ptrArray->vtable = &PTR_PTR_s_CPtrArray<CTexAnimSeq_*>_801e9c84;
    RemoveAll__25CPtrArray<P11CTexAnimSeq>Fv(ptrArray);
    if (0 < param_2) {
      __dl__FPv(ptrArray);
    }
  }
  return ptrArray;
}

