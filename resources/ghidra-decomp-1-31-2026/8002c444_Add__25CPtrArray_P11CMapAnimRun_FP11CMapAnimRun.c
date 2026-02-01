// Function: Add__25CPtrArray<P11CMapAnimRun>FP11CMapAnimRun
// Entry: 8002c444
// Size: 112 bytes

bool Add__25CPtrArray<P11CMapAnimRun>FP11CMapAnimRun(CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__25CPtrArray<P11CMapAnimRun>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

