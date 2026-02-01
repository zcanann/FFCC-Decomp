// Function: Add__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FPQ29CCharaPcs12CLoadTexture
// Entry: 8007ac14
// Size: 112 bytes

bool Add__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FPQ29CCharaPcs12CLoadTexture
               (CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

