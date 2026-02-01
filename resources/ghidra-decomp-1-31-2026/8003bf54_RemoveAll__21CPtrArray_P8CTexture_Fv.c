// Function: RemoveAll__21CPtrArray<P8CTexture>Fv
// Entry: 8003bf54
// Size: 76 bytes

void RemoveAll__21CPtrArray<P8CTexture>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

