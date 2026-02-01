// Function: SetTexGen__11CTexAnimSetFv
// Entry: 80043f48
// Size: 212 bytes

void SetTexGen__11CTexAnimSetFv(CTexAnimSet *texAnimSet)

{
  undefined4 uVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  
  for (uVar6 = 0;
      uVar4 = GetSize__21CPtrArray<P8CTexAnim>Fv((CPtrArray *)&(texAnimSet->texAnims).size),
      uVar6 < uVar4; uVar6 = uVar6 + 1) {
    iVar3 = __vc__21CPtrArray<P8CTexAnim>FUl(&(texAnimSet->texAnims).size,uVar6);
    fVar2 = FLOAT_8032fb38;
    iVar5 = *(int *)(*(int *)(iVar3 + 8) + 0x108);
    if (iVar5 != 0) {
      uVar1 = *(undefined4 *)(iVar3 + 0x1c);
      iVar5 = iVar5 + *(int *)(*(int *)(iVar3 + 8) + 0x10c) * 0x14;
      *(undefined4 *)(iVar5 + 0x50) = *(undefined4 *)(iVar3 + 0x18);
      *(undefined4 *)(iVar5 + 0x54) = uVar1;
      *(float *)(iVar5 + 0x58) = fVar2;
      *(float *)(iVar5 + 0x5c) = fVar2;
      if (fVar2 == *(float *)(iVar5 + 0x58)) {
        *(undefined *)(iVar5 + 0x4c) = 0;
      }
      else {
        *(undefined *)(iVar5 + 0x4c) = 1;
      }
      if (FLOAT_8032fb38 == *(float *)(iVar5 + 0x5c)) {
        *(undefined *)(iVar5 + 0x4d) = 0;
      }
      else {
        *(undefined *)(iVar5 + 0x4d) = 1;
      }
    }
  }
  return;
}

