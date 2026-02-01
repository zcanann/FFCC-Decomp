// Function: __dt__21CPtrArray<P8CTexture>Fv
// Entry: 8003be70
// Size: 92 bytes

CPtrArray * __dt__21CPtrArray<P8CTexture>Fv(CPtrArray *ptrArray,short param_2)

{
  if (ptrArray != (CPtrArray *)0x0) {
    ptrArray->vtable = &PTR_PTR_s_CPtrArray<CTexture_*>_801e9ba0;
    RemoveAll__21CPtrArray<P8CTexture>Fv(ptrArray);
    if (0 < param_2) {
      __dl__FPv(ptrArray);
    }
  }
  return ptrArray;
}

