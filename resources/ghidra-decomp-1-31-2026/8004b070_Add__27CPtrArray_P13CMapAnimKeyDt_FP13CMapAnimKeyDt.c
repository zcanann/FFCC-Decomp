// Function: Add__27CPtrArray<P13CMapAnimKeyDt>FP13CMapAnimKeyDt
// Entry: 8004b070
// Size: 112 bytes

bool Add__27CPtrArray<P13CMapAnimKeyDt>FP13CMapAnimKeyDt(CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__27CPtrArray<P13CMapAnimKeyDt>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

