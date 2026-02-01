// Function: __dt__21CPtrArray<P8CTexAnim>Fv
// Entry: 80044e54
// Size: 92 bytes

CPtrArray * __dt__21CPtrArray<P8CTexAnim>Fv(CPtrArray *ptrArray,short param_2)

{
  if (ptrArray != (CPtrArray *)0x0) {
    ptrArray->vtable = &PTR_PTR_s_CPtrArray<CTexAnim_*>_801e9c78;
    RemoveAll__21CPtrArray<P8CTexAnim>Fv(ptrArray);
    if (0 < param_2) {
      __dl__FPv(ptrArray);
    }
  }
  return ptrArray;
}

