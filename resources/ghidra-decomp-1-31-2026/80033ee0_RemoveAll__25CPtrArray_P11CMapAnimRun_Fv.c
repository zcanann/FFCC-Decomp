// Function: RemoveAll__25CPtrArray<P11CMapAnimRun>Fv
// Entry: 80033ee0
// Size: 76 bytes

void RemoveAll__25CPtrArray<P11CMapAnimRun>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

