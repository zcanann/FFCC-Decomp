// Function: RemoveAll__22CPtrArray<P9CMaterial>Fv
// Entry: 80043b88
// Size: 76 bytes

void RemoveAll__22CPtrArray<P9CMaterial>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

