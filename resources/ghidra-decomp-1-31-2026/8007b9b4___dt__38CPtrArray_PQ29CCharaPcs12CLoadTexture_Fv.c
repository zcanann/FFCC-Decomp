// Function: __dt__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv
// Entry: 8007b9b4
// Size: 124 bytes

CPtrArray * __dt__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv(CPtrArray *ptrArray,short param_2)

{
  if (ptrArray != (CPtrArray *)0x0) {
    ptrArray->vtable = &PTR_PTR_s_CPtrArray<CCharaPcs_CLoadTextur_801fd328;
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

