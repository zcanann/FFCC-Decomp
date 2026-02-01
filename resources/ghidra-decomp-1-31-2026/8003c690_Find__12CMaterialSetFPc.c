// Function: Find__12CMaterialSetFPc
// Entry: 8003c690
// Size: 140 bytes

uint Find__12CMaterialSetFPc(CMaterialSet *materialSet,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  while( true ) {
    uVar2 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials);
    if (uVar2 <= uVar3) {
      return 0xffffffff;
    }
    iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,uVar3);
    if ((iVar1 != 0) && (iVar1 = strcmp(iVar1 + 8,param_2), iVar1 == 0)) break;
    uVar3 = uVar3 + 1;
  }
  return uVar3;
}

