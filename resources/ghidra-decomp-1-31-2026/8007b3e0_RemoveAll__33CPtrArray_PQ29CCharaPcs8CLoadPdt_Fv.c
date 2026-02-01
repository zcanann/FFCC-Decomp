// Function: RemoveAll__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv
// Entry: 8007b3e0
// Size: 76 bytes

void RemoveAll__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

