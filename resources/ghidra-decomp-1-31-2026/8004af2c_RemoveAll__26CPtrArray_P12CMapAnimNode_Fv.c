// Function: RemoveAll__26CPtrArray<P12CMapAnimNode>Fv
// Entry: 8004af2c
// Size: 76 bytes

void RemoveAll__26CPtrArray<P12CMapAnimNode>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

