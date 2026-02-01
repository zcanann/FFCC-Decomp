// Function: RemoveAll__25CPtrArray<P11CTexAnimSeq>Fv
// Entry: 80044bf0
// Size: 76 bytes

void RemoveAll__25CPtrArray<P11CTexAnimSeq>Fv(CPtrArray *ptrArray)

{
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

