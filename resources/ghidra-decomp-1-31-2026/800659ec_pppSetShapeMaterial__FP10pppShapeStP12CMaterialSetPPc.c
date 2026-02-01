// Function: pppSetShapeMaterial__FP10pppShapeStP12CMaterialSetPPc
// Entry: 800659ec
// Size: 168 bytes

void pppSetShapeMaterial__FP10pppShapeStP12CMaterialSetPPc
               (pppShapeSt *pppShapeSt,CMaterialSet *materialSet,char **textureName)

{
  undefined uVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  void *pvVar5;
  int iVar6;
  int iVar7;
  
  pvVar4 = pppShapeSt->m_animData;
  pvVar5 = pvVar4;
  for (iVar3 = 0; iVar3 < *(short *)((int)pvVar4 + 6); iVar3 = iVar3 + 1) {
    iVar2 = (int)pvVar4 + (int)*(short *)((int)pvVar5 + 0x10);
    iVar6 = iVar2;
    for (iVar7 = 0; iVar7 < *(short *)(iVar2 + 2); iVar7 = iVar7 + 1) {
      uVar1 = FindTexName__12CMaterialSetFPcPl(materialSet,textureName[*(byte *)(iVar6 + 10)],0);
      *(undefined *)(iVar6 + 10) = uVar1;
      *(int *)(iVar6 + 0xc) = (int)pppShapeSt->m_displayListData + *(int *)(iVar6 + 0xc);
      iVar6 = iVar6 + 8;
    }
    pvVar5 = (void *)((int)pvVar5 + 8);
  }
  return;
}

