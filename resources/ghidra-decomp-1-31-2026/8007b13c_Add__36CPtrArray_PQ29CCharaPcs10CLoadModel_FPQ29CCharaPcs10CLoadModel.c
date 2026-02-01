// Function: Add__36CPtrArray<PQ29CCharaPcs10CLoadModel>FPQ29CCharaPcs10CLoadModel
// Entry: 8007b13c
// Size: 112 bytes

bool Add__36CPtrArray<PQ29CCharaPcs10CLoadModel>FPQ29CCharaPcs10CLoadModel
               (CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__36CPtrArray<PQ29CCharaPcs10CLoadModel>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

