// Function: CMapShadowInsertOctTree__FQ210CMapShadow6TARGETR8COctTree
// Entry: 8004c71c
// Size: 236 bytes

void CMapShadowInsertOctTree__FQ210CMapShadow6TARGETR8COctTree
               (CMapShadow *mapShadow,COctTree *octTree)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  ClearShadow__8COctTreeFv(octTree);
  if (*(int *)((int)octTree->field2_0x8 + 0x3c) != 0) {
    uVar4 = 0;
    while( true ) {
      uVar2 = GetSize__24CPtrArray<P10CMapShadow>Fv(&MapMng.m_mapShadowArray);
      if (uVar2 <= uVar4) break;
      if ((((*(uint *)((int)octTree->field2_0x8 + 0x3c) & 1 << uVar4) != 0) &&
          (iVar1 = __vc__24CPtrArray<P10CMapShadow>FUl(0x80266b98,uVar4),
          (&mapShadow->field_0xf0)[iVar1] != '\0')) && (*(char *)(iVar1 + 7) == '\0')) {
        iVar3 = *(int *)(iVar1 + 0xc);
        local_28 = *(undefined4 *)(iVar3 + 0xc4);
        local_24 = *(undefined4 *)(iVar3 + 0xd4);
        local_20 = *(undefined4 *)(iVar3 + 0xe4);
        InsertShadow__8COctTreeFlR3VecR6CBound
                  (octTree,uVar4,&local_28,iVar1 + (int)mapShadow * 0x18 + 0xc0);
      }
      uVar4 = uVar4 + 1;
    }
  }
  return;
}

