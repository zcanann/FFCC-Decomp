// Function: DeleteAndRemoveAll__22CPtrArray<P9_GXTexObj>Fv
// Entry: 8004e69c
// Size: 136 bytes

void DeleteAndRemoveAll__22CPtrArray<P9_GXTexObj>Fv(CPtrArray *ptrArray)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  for (uVar1 = 0; uVar1 < (uint)ptrArray->numItems; uVar1 = uVar1 + 1) {
    if (*(int *)((int)ptrArray->items + iVar2) != 0) {
      __dl__FPv();
      *(undefined4 *)((int)ptrArray->items + iVar2) = 0;
    }
    iVar2 = iVar2 + 4;
  }
  RemoveAll__22CPtrArray<P9_GXTexObj>Fv(ptrArray);
  return;
}

