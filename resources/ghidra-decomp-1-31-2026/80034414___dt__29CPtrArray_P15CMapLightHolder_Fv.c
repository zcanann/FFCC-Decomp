// Function: __dt__29CPtrArray<P15CMapLightHolder>Fv
// Entry: 80034414
// Size: 124 bytes

CPtrArray * __dt__29CPtrArray<P15CMapLightHolder>Fv(CPtrArray *ptrArray,short param_2)

{
  if (ptrArray != (CPtrArray *)0x0) {
    ptrArray->vtable = &PTR_PTR_s_CPtrArray<CMapLightHolder_*>_801e89a8;
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

