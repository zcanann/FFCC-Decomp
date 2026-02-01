// Function: SetMapAnimID__7CMapMngFiiii
// Entry: 8002f710
// Size: 148 bytes

void SetMapAnimID__7CMapMngFiiii
               (CMapMng *mapMng,char param_2,undefined4 param_3,undefined4 param_4,
               undefined1 param_5)

{
  int iVar1;
  CMapAnimRun *mapAnimRun;
  uint32_t index;
  
  iVar1 = GetSize__25CPtrArray<P11CMapAnimRun>Fv(&mapMng->g_CMapAnimRunArray);
  for (index = 0; (int)index < iVar1; index = index + 1) {
    mapAnimRun = (CMapAnimRun *)
                 __vc__25CPtrArray<P11CMapAnimRun>FUl(&mapMng->g_CMapAnimRunArray,index);
    if (*(char *)((int)&(mapAnimRun->mapAnims).items + 1) == param_2) goto LAB_8002f780;
  }
  mapAnimRun = (CMapAnimRun *)0x0;
LAB_8002f780:
  Start__11CMapAnimRunFiii(mapAnimRun,param_3,param_4,param_5);
  return;
}

