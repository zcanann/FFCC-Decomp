// Function: __dt__29CPtrArray<P15OSFS_TEXTURE_ST>Fv
// Entry: 8004ead0
// Size: 124 bytes

CPtrArray * __dt__29CPtrArray<P15OSFS_TEXTURE_ST>Fv(CPtrArray *ptrArray,short param_2)

{
  if (ptrArray != (CPtrArray *)0x0) {
    ptrArray->vtable = &PTR_PTR_s_CPtrArray<OSFS_TEXTURE_ST_*>_801ea948;
    if (ptrArray->items != (void **)0x0) {
      __dla__FPv(ptrArray->items);
      ptrArray->items = (void **)0x0;
    }
    ptrArray->size = 0;
    ptrArray->numItems = 0;
    if (0 < param_2) {
      __dl__FPv(ptrArray);
    }
  }
  return ptrArray;
}

