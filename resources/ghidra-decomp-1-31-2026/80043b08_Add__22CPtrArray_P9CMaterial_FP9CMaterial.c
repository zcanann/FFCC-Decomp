// Function: Add__22CPtrArray<P9CMaterial>FP9CMaterial
// Entry: 80043b08
// Size: 112 bytes

bool Add__22CPtrArray<P9CMaterial>FP9CMaterial(CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__22CPtrArray<P9CMaterial>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

