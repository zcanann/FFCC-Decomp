// Function: RemoveAll__27CPtrArray<P13CMapAnimKeyDt>Fv
// Entry: 80034160
// Size: 76 bytes

void RemoveAll__27CPtrArray<P13CMapAnimKeyDt>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

