// Function: Add__24CPtrArray<P10CMapShadow>FP10CMapShadow
// Entry: 8002c5a4
// Size: 112 bytes

bool Add__24CPtrArray<P10CMapShadow>FP10CMapShadow(CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__24CPtrArray<P10CMapShadow>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

