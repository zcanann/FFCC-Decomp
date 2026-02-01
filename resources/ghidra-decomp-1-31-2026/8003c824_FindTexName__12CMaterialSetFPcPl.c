// Function: FindTexName__12CMaterialSetFPcPl
// Entry: 8003c824
// Size: 172 bytes

uint FindTexName__12CMaterialSetFPcPl(CMaterialSet *materialSet,char *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  uVar5 = 0;
  do {
    uVar3 = _UnkMaterialSetGetter((CMaterial *)&materialSet->materials);
    if (uVar3 <= uVar5) {
      return 0xffffffff;
    }
    iVar1 = __vc__22CPtrArray<P9CMaterial>FUl(&materialSet->materials,uVar5);
    if (iVar1 != 0) {
      iVar6 = iVar1;
      for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)(iVar1 + 0x18); iVar4 = iVar4 + 1) {
        iVar2 = CheckName__8CTextureFPc(*(CTexture **)(iVar6 + 0x3c));
        if (iVar2 != 0) {
          if (param_3 == (int *)0x0) {
            return uVar5;
          }
          *param_3 = iVar4;
          return uVar5;
        }
        iVar6 = iVar6 + 4;
      }
    }
    uVar5 = uVar5 + 1;
  } while( true );
}

