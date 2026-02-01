// Function: Add__21CPtrArray<P8CTexAnim>FP8CTexAnim
// Entry: 80044eb0
// Size: 112 bytes

bool Add__21CPtrArray<P8CTexAnim>FP8CTexAnim(CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__21CPtrArray<P8CTexAnim>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

