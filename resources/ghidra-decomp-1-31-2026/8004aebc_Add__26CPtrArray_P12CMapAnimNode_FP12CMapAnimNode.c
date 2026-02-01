// Function: Add__26CPtrArray<P12CMapAnimNode>FP12CMapAnimNode
// Entry: 8004aebc
// Size: 112 bytes

bool Add__26CPtrArray<P12CMapAnimNode>FP12CMapAnimNode(CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__26CPtrArray<P12CMapAnimNode>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

