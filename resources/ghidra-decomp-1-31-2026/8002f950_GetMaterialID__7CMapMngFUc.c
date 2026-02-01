// Function: GetMaterialID__7CMapMngFUc
// Entry: 8002f950
// Size: 156 bytes

undefined4 GetMaterialID__7CMapMngFUc(CMapMng *mapMng,char param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = 0;
  iVar5 = *(int *)&mapMng->field_0x213d4;
  while( true ) {
    uVar3 = _UnkMaterialSetGetter((CMaterial *)(iVar5 + 8));
    if (uVar3 <= uVar4) {
      return 0;
    }
    iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(iVar5 + 8,uVar4);
    if ((iVar1 != 0) &&
       (iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(iVar5 + 8,uVar4),
       param_2 == *(char *)(iVar1 + 0xa6))) break;
    uVar4 = uVar4 + 1;
  }
  uVar2 = __vc__22CPtrArray<P9CMaterial>FUl(iVar5 + 8,uVar4);
  return uVar2;
}

