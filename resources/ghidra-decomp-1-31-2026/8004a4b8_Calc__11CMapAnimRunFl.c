// Function: Calc__11CMapAnimRunFl
// Entry: 8004a4b8
// Size: 168 bytes

void Calc__11CMapAnimRunFl(CMapAnimRun *mapAnimRun,uint32_t param_2)

{
  CMapAnim *mapAnim;
  void *pvVar1;
  
  if ((int)(mapAnimRun->mapAnims).vtable < 0) {
    if ((mapAnimRun->mapAnims).defaultSize != param_2) {
      return;
    }
    (mapAnimRun->mapAnims).vtable = (void *)(mapAnimRun->mapAnims).numItems;
  }
  mapAnim = (CMapAnim *)
            __vc__21CPtrArray<P8CMapAnim>FUl
                      (0x80266b60,*(undefined2 *)((int)&(mapAnimRun->mapAnims).items + 2));
  Calc__8CMapAnimFl(mapAnim,(mapAnimRun->mapAnims).vtable);
  pvVar1 = (void *)((int)(mapAnimRun->mapAnims).vtable + 1);
  (mapAnimRun->mapAnims).vtable = pvVar1;
  if ((int)(mapAnimRun->mapAnims).size < (int)pvVar1) {
    if (*(char *)&(mapAnimRun->mapAnims).items == '\0') {
      (mapAnimRun->mapAnims).vtable = (void *)0xffffffff;
    }
    else {
      (mapAnimRun->mapAnims).vtable = (void *)0x0;
    }
  }
  return;
}

