// Function: RemoveAll__29CPtrArray<P15CMapLightHolder>Fv
// Entry: 80033d94
// Size: 76 bytes

void RemoveAll__29CPtrArray<P15CMapLightHolder>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

