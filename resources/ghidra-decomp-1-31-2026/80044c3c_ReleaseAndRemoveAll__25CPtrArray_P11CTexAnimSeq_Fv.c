// Function: ReleaseAndRemoveAll__25CPtrArray<P11CTexAnimSeq>Fv
// Entry: 80044c3c
// Size: 204 bytes

void ReleaseAndRemoveAll__25CPtrArray<P11CTexAnimSeq>Fv(CPtrArray *ptrArray)

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
  if (ptrArray->items != (void **)0x0) {
    __dla__FPv(ptrArray->items);
    ptrArray->items = (void **)0x0;
  }
  ptrArray->size = 0;
  ptrArray->numItems = 0;
  return;
}

