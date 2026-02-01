// Function: ResetRsdList__18CMaterialEditorPcsFP5ZLIST
// Entry: 8004de94
// Size: 316 bytes

void ResetRsdList__18CMaterialEditorPcsFP5ZLIST(CMaterialEditorPcs *materialEditorPcs,ZLIST *zlist)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  _ZLISTITEM *local_28 [4];
  
  local_28[0] = (zlist->m_root).m_previous;
  while (local_28[0] != (_ZLISTITEM *)0x0) {
    piVar1 = (int *)GetDataNext__5ZLISTFPP10_ZLISTITEM(zlist,local_28);
    iVar4 = *piVar1;
    if (iVar4 != 0) {
      if (*(void **)(iVar4 + 0xc) != (void *)0x0) {
        __dla__FPv(*(void **)(iVar4 + 0xc));
        *(undefined4 *)(iVar4 + 0xc) = 0;
      }
      if (*(void **)(iVar4 + 0x10) != (void *)0x0) {
        __dla__FPv(*(void **)(iVar4 + 0x10));
        *(undefined4 *)(iVar4 + 0x10) = 0;
      }
      if (*(void **)(iVar4 + 0x14) != (void *)0x0) {
        __dla__FPv(*(void **)(iVar4 + 0x14));
        *(undefined4 *)(iVar4 + 0x14) = 0;
      }
      if (*(void **)(iVar4 + 0x18) != (void *)0x0) {
        __dla__FPv(*(void **)(iVar4 + 0x18));
        *(undefined4 *)(iVar4 + 0x18) = 0;
      }
      if (iVar4 != 0) {
        __dl__FPv(iVar4);
      }
    }
    puVar2 = (undefined4 *)piVar1[1];
    iVar4 = piVar1[2];
    if (puVar2 != (undefined4 *)0x0) {
      for (iVar3 = 0; iVar3 < iVar4; iVar3 = iVar3 + 1) {
        if ((void *)*puVar2 != (void *)0x0) {
          __dla__FPv((void *)*puVar2);
          *puVar2 = 0;
        }
        puVar2 = puVar2 + 5;
      }
      if ((void *)piVar1[1] != (void *)0x0) {
        __dla__FPv((void *)piVar1[1]);
        piVar1[1] = 0;
      }
      piVar1[1] = 0;
    }
    __dl__FPv(piVar1);
  }
  DeleteList__5ZLISTFv(zlist);
  return;
}

