// Function: ReleaseAndRemoveAll__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv
// Entry: 8007a9f8
// Size: 176 bytes

void ReleaseAndRemoveAll__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv(CPtrArray *ptrArray)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = 0;
  for (uVar3 = 0; uVar3 < (uint)ptrArray->numItems; uVar3 = uVar3 + 1) {
    piVar1 = *(int **)((int)ptrArray->items + iVar4);
    if (piVar1 != (int *)0x0) {
      iVar2 = piVar1[1];
      piVar1[1] = iVar2 + -1;
      if ((iVar2 + -1 == 0) && (piVar1 != (int *)0x0)) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)((int)ptrArray->items + iVar4) = 0;
    }
    iVar4 = iVar4 + 4;
  }
  RemoveAll__33CPtrArray<PQ29CCharaPcs8CLoadPdt>Fv(ptrArray);
  return;
}

