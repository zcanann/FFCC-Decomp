// Function: __dt__22CPtrArray<P9CMaterial>Fv
// Entry: 80043aac
// Size: 92 bytes

CPtrArray * __dt__22CPtrArray<P9CMaterial>Fv(CPtrArray *ptrArray,short param_2)

{
  if (ptrArray != (CPtrArray *)0x0) {
    ptrArray->vtable = &PTR_PTR_s_CPtrArray<CMaterial_*>_801e9bfc;
    RemoveAll__22CPtrArray<P9CMaterial>Fv(ptrArray);
    if (0 < param_2) {
      __dl__FPv(ptrArray);
    }
  }
  return ptrArray;
}

