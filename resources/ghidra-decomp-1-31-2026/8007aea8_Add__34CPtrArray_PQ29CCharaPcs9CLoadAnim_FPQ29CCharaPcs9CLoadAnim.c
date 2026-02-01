// Function: Add__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FPQ29CCharaPcs9CLoadAnim
// Entry: 8007aea8
// Size: 112 bytes

bool Add__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FPQ29CCharaPcs9CLoadAnim
               (CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__34CPtrArray<PQ29CCharaPcs9CLoadAnim>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

