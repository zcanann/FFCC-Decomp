// Function: RemoveAll__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv
// Entry: 8007b498
// Size: 76 bytes

void RemoveAll__34CPtrArray<PQ29CCharaPcs9CLoadAnim>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

