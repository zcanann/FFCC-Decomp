// Function: __dt__26CPtrArray<P12CMapAnimNode>Fv
// Entry: 8004ae60
// Size: 92 bytes

CPtrArray * __dt__26CPtrArray<P12CMapAnimNode>Fv(CPtrArray *ptrArray,short param_2)

{
  if (ptrArray != (CPtrArray *)0x0) {
    ptrArray->vtable = &PTR_PTR_s_CPtrArray<CMapAnimNode_*>_801ea488;
    RemoveAll__26CPtrArray<P12CMapAnimNode>Fv(ptrArray);
    if (0 < param_2) {
      __dl__FPv(ptrArray);
    }
  }
  return ptrArray;
}

