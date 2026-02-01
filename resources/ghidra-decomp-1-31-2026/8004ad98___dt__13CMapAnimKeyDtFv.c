// Function: __dt__13CMapAnimKeyDtFv
// Entry: 8004ad98
// Size: 148 bytes

CMapAnim * __dt__13CMapAnimKeyDtFv(CMapAnim *mapAnim,short param_2)

{
  void *pvVar1;
  CStage *ptr;
  
  if (mapAnim != (CMapAnim *)0x0) {
    pvVar1 = (void *)(mapAnim->mapAnimNodes).numItems;
    if (pvVar1 != (void *)0x0) {
      __dla__FPv(pvVar1);
      (mapAnim->mapAnimNodes).numItems = 0;
    }
    pvVar1 = (void *)(mapAnim->mapAnimNodes).defaultSize;
    if (pvVar1 != (void *)0x0) {
      __dla__FPv(pvVar1);
      (mapAnim->mapAnimNodes).defaultSize = 0;
    }
    ptr = (mapAnim->mapAnimNodes).stage;
    if (ptr != (CStage *)0x0) {
      __dla__FPv(ptr);
      (mapAnim->mapAnimNodes).stage = (CStage *)0x0;
    }
    if (0 < param_2) {
      __dl__FPv(mapAnim);
    }
  }
  return mapAnim;
}

