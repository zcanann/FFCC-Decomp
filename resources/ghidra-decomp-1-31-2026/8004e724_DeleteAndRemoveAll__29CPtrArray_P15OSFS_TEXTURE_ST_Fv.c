// Function: DeleteAndRemoveAll__29CPtrArray<P15OSFS_TEXTURE_ST>Fv
// Entry: 8004e724
// Size: 136 bytes

void DeleteAndRemoveAll__29CPtrArray<P15OSFS_TEXTURE_ST>Fv(CPtrArray *ptrArray)

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
  RemoveAll__29CPtrArray<P15OSFS_TEXTURE_ST>Fv(ptrArray);
  return;
}

