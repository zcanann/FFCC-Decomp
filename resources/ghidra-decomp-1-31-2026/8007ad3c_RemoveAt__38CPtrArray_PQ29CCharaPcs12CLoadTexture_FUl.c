// Function: RemoveAt__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl
// Entry: 8007ad3c
// Size: 68 bytes

void RemoveAt__38CPtrArray<PQ29CCharaPcs12CLoadTexture>FUl(CPtrArray *ptrArray,uint index)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = index * 4;
  ptrArray->items[index] = (void *)0x0;
  for (; index < (uint)ptrArray->numItems; index = index + 1) {
    puVar1 = (undefined4 *)((int)ptrArray->items + iVar2);
    iVar2 = iVar2 + 4;
    *puVar1 = puVar1[1];
  }
  ptrArray->numItems = ptrArray->numItems - 1;
  return;
}

