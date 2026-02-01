// Function: SetMapObjAnim__7CMapMngFiiii
// Entry: 8002f7a4
// Size: 220 bytes

void SetMapObjAnim__7CMapMngFiiii
               (CMapMng *mapMng,int mapObjIndex,undefined4 param_3,undefined4 param_4,
               undefined1 param_5)

{
  int iVar1;
  CPtrArray *ptrArray;
  int iVar2;
  int *piVar3;
  uint32_t index;
  CMapAnimRun *mapAnimRun;
  int iVar4;
  
  iVar1 = GetSize__25CPtrArray<P11CMapAnimRun>Fv(&mapMng->g_CMapAnimRunArray);
  for (index = 0; (int)index < iVar1; index = index + 1) {
    mapAnimRun = (CMapAnimRun *)
                 __vc__25CPtrArray<P11CMapAnimRun>FUl(&mapMng->g_CMapAnimRunArray,index);
    ptrArray = (CPtrArray *)
               __vc__21CPtrArray<P8CMapAnim>FUl
                         (&mapMng->g_CMapAnimArray,
                          *(undefined2 *)((int)&(mapAnimRun->mapAnims).items + 2));
    iVar2 = GetSize__26CPtrArray<P12CMapAnimNode>Fv(ptrArray);
    for (iVar4 = 0; iVar4 < iVar2; iVar4 = iVar4 + 1) {
      piVar3 = (int *)__vc__26CPtrArray<P12CMapAnimNode>FUl(ptrArray,iVar4);
      if ((CMapObj *)*piVar3 == mapMng->mapObjArr + mapObjIndex) goto LAB_8002f858;
    }
  }
  mapAnimRun = (CMapAnimRun *)0x0;
LAB_8002f858:
  Start__11CMapAnimRunFiii(mapAnimRun,param_3,param_4,param_5);
  return;
}

