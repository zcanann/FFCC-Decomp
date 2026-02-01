// Function: Start__11CMapAnimRunFiii
// Entry: 8004a4a0
// Size: 24 bytes

void Start__11CMapAnimRunFiii(CMapAnimRun *mapAnimRun,int numItems,uint32_t size,undefined items)

{
  (mapAnimRun->mapAnims).numItems = numItems;
  (mapAnimRun->mapAnims).size = size;
  *(undefined *)&(mapAnimRun->mapAnims).items = items;
  (mapAnimRun->mapAnims).vtable = (void *)(mapAnimRun->mapAnims).numItems;
  return;
}

