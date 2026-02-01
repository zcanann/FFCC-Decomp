// Function: Add__29CPtrArray<P15CMapLightHolder>FP15CMapLightHolder
// Entry: 80033d24
// Size: 112 bytes

bool Add__29CPtrArray<P15CMapLightHolder>FP15CMapLightHolder(CPtrArray *ptrArray,void *item)

{
  int iVar1;
  
  iVar1 = setSize__29CPtrArray<P15CMapLightHolder>FUl(ptrArray,ptrArray->numItems + 1);
  if (iVar1 != 0) {
    ptrArray->items[ptrArray->numItems] = item;
    ptrArray->numItems = ptrArray->numItems + 1;
  }
  return iVar1 != 0;
}

