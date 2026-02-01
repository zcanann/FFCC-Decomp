// Function: Add__25CPtrArray<P11CTexAnimSeq>FP11CTexAnimSeq
// Entry: 80044b78
// Size: 112 bytes

bool Add__25CPtrArray<P11CTexAnimSeq>FP11CTexAnimSeq(CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__25CPtrArray<P11CTexAnimSeq>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

