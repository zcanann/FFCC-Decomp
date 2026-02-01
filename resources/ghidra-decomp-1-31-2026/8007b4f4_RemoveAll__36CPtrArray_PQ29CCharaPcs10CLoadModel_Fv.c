// Function: RemoveAll__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fv
// Entry: 8007b4f4
// Size: 76 bytes

void RemoveAll__36CPtrArray<PQ29CCharaPcs10CLoadModel>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

