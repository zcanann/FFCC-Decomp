// Function: GetTexture__10pppShapeStFPlP12CMaterialSetRi
// Entry: 80065c6c
// Size: 64 bytes

undefined4
GetTexture__10pppShapeStFPlP12CMaterialSetRi
          (pppShapeSt *pppShapeSt,int param_2,CMaterialSet *materialSet,uint *param_4)

{
  int iVar1;
  
  iVar1 = param_2 + *(short *)(param_2 + 0x10) + 8;
  *param_4 = (uint)*(byte *)(iVar1 + 2);
  iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,*(undefined *)(iVar1 + 2));
  return *(undefined4 *)(iVar1 + 0x3c);
}

