// Function: AttachMaterialSet__11CTexAnimSetFP12CMaterialSet
// Entry: 80044440
// Size: 256 bytes

void AttachMaterialSet__11CTexAnimSetFP12CMaterialSet(CTexAnimSet *texAnimSet,CMaterialSet *param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  for (uVar6 = 0;
      uVar4 = GetSize__21CPtrArray<P8CTexAnim>Fv((CPtrArray *)&(texAnimSet->texAnims).size),
      uVar6 < uVar4; uVar6 = uVar6 + 1) {
    iVar1 = __vc__21CPtrArray<P8CTexAnim>FUl(&(texAnimSet->texAnims).size,uVar6);
    piVar2 = *(int **)(*(int *)(iVar1 + 8) + 0x108);
    if (piVar2 != (int *)0x0) {
      iVar5 = piVar2[1];
      piVar2[1] = iVar5 + -1;
      if ((iVar5 + -1 == 0) && (piVar2 != (int *)0x0)) {
        (**(code **)(*piVar2 + 8))(piVar2,1);
      }
      *(undefined4 *)(*(int *)(iVar1 + 8) + 0x108) = 0;
    }
    if ((param_2 != (CMaterialSet *)0x0) &&
       (iVar5 = Find__12CMaterialSetFPc(param_2,*(int *)(iVar1 + 8) + 8), -1 < iVar5)) {
      uVar3 = __vc__22CPtrArray<P9CMaterial>FUl(&param_2->materials,iVar5);
      *(undefined4 *)(*(int *)(iVar1 + 8) + 0x108) = uVar3;
      iVar1 = *(int *)(*(int *)(iVar1 + 8) + 0x108);
      *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + 1;
    }
  }
  return;
}

