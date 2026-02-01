// Function: RemoveAll__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv
// Entry: 8007b43c
// Size: 76 bytes

void RemoveAll__38CPtrArray<PQ29CCharaPcs12CLoadTexture>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

