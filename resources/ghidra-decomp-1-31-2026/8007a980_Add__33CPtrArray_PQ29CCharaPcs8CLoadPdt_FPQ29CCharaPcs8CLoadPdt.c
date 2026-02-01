// Function: Add__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FPQ29CCharaPcs8CLoadPdt
// Entry: 8007a980
// Size: 112 bytes

bool Add__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FPQ29CCharaPcs8CLoadPdt(CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__33CPtrArray<PQ29CCharaPcs8CLoadPdt>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

