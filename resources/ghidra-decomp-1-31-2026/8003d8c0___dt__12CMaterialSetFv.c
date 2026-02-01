// Function: __dt__12CMaterialSetFv
// Entry: 8003d8c0
// Size: 216 bytes

CMaterialSet * __dt__12CMaterialSetFv(CMaterialSet *materialSet,short param_2)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  
  if (materialSet != (CMaterialSet *)0x0) {
    uVar4 = 0;
    materialSet->vtable = &PTR_PTR_s_CMaterialSet_801e9bbc;
    while( true ) {
      uVar3 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials);
      if (uVar3 <= uVar4) break;
      iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,uVar4);
      if ((iVar1 != 0) &&
         (piVar2 = (int *)__vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,uVar4),
         piVar2 != (int *)0x0)) {
        (**(code **)(*piVar2 + 8))(piVar2,1);
      }
      uVar4 = uVar4 + 1;
    }
    RemoveAll__22CPtrArray<P9CMaterial>Fv(&materialSet->materials);
    __dt__22CPtrArray<P9CMaterial>Fv(&materialSet->materials,0xffff);
    __dt__4CRefFv((CRef *)materialSet,0);
    if (0 < param_2) {
      __dl__FPv(materialSet);
    }
  }
  return materialSet;
}

