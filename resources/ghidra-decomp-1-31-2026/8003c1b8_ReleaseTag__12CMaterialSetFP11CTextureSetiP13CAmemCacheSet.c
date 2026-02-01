// Function: ReleaseTag__12CMaterialSetFP11CTextureSetiP13CAmemCacheSet
// Entry: 8003c1b8
// Size: 312 bytes

void ReleaseTag__12CMaterialSetFP11CTextureSetiP13CAmemCacheSet
               (CMaterialSet *materialSet,CTextureSet *textureSet,int pdtSlotIndex,
               CAmemCacheSet *amemCacheSet)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint index;
  int *piVar6;
  int *piVar7;
  
  index = 0;
  while( true ) {
    uVar3 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials);
    if (uVar3 <= index) break;
    piVar1 = (int *)__vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,index);
    if ((piVar1 != (int *)0x0) && (piVar1[0x27] == pdtSlotIndex)) {
      piVar6 = piVar1;
      piVar7 = piVar1;
      for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)(piVar1 + 6); iVar5 = iVar5 + 1) {
        piVar2 = (int *)piVar7[0xf];
        if (piVar2 != (int *)0x0) {
          iVar4 = piVar2[1];
          piVar2[1] = iVar4 + -1;
          if ((iVar4 + -1 == 0) && (piVar2 != (int *)0x0)) {
            (**(code **)(*piVar2 + 8))(piVar2,1);
          }
          piVar7[0xf] = 0;
        }
        ReleaseTextureIdx__11CTextureSetFiP13CAmemCacheSet
                  (textureSet,(int)*(short *)((int)piVar6 + 0x1a),amemCacheSet);
        piVar7[0xf] = 0;
        piVar7 = piVar7 + 1;
        piVar6 = (int *)((int)piVar6 + 2);
      }
      if (piVar1 != (int *)0x0) {
        iVar5 = piVar1[1];
        piVar1[1] = iVar5 + -1;
        if ((iVar5 + -1 == 0) && (piVar1 != (int *)0x0)) {
          (**(code **)(*piVar1 + 8))(piVar1,1);
        }
      }
      SetAt__22CPtrArray<P9CMaterial>FUlP9CMaterial(&materialSet->materials,index,0);
    }
    index = index + 1;
  }
  return;
}

