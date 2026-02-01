// Function: __dt__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv
// Entry: 8007ba64
// Size: 124 bytes

CPtrArray * __dt__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv(CPtrArray *ptrArray,short param_2)

{
  if (ptrArray != (CPtrArray *)0x0) {
    ptrArray->vtable = &PTR_PTR_s_CPtrArray<CCharaPcs_CLoadAnim_*_801fd31c;
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

