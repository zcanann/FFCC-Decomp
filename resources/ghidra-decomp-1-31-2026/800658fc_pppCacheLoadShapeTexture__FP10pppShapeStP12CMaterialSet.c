// Function: pppCacheLoadShapeTexture__FP10pppShapeStP12CMaterialSet
// Entry: 800658fc
// Size: 240 bytes

void pppCacheLoadShapeTexture__FP10pppShapeStP12CMaterialSet
               (pppShapeSt *pppShapeSt,CMaterialSet *materialSet)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  int iVar6;
  uint uVar7;
  void *pvVar8;
  char *pcVar9;
  char local_118 [264];
  
  pvVar8 = pppShapeSt->m_animData;
  memset(local_118,0,0x100);
  pvVar5 = pvVar8;
  for (iVar6 = 0; iVar6 < *(short *)((int)pvVar8 + 6); iVar6 = iVar6 + 1) {
    sVar1 = *(short *)((int)pvVar5 + 0x10);
    iVar4 = 0;
    for (iVar3 = 0; iVar3 < *(short *)((int)pvVar8 + sVar1 + 2); iVar3 = iVar3 + 1) {
      iVar2 = iVar4 + sVar1;
      iVar4 = iVar4 + 8;
      local_118[*(byte *)((int)pvVar8 + iVar2 + 10)] = '\x01';
    }
    pvVar5 = (void *)((int)pvVar5 + 8);
  }
  pcVar9 = local_118;
  uVar7 = 0;
  do {
    if (*pcVar9 != '\0') {
      CacheLoadTexture__12CMaterialSetFiP13CAmemCacheSet
                (materialSet,uVar7,(CAmemCacheSet *)CAMemCacheSet);
    }
    uVar7 = uVar7 + 1;
    pcVar9 = pcVar9 + 1;
  } while (uVar7 < 0x100);
  return;
}

